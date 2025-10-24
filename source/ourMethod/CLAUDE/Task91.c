#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

/* Maximum buffer size to prevent excessive memory usage */
#define MAX_DNS_PACKET_SIZE 512
#define MAX_DOMAIN_LENGTH 253
#define DNS_QUERY_TYPE_A 1
#define DNS_CLASS_IN 1

/* DNS Header structure */
typedef struct {
    uint16_t id;
    uint16_t flags;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} DNSHeader;

/*
 * Parse domain name from DNS query, returns length parsed or -1 on error
 * Security: bounds checking to prevent buffer overflow (CWE-119, CWE-125)
 */
int parseDomainName(const uint8_t* buffer, size_t bufferLen, size_t offset,
                    char* domain, size_t domainMaxLen) {
    /* Validate inputs - treat all inputs as untrusted */
    if (buffer == NULL || domain == NULL || bufferLen == 0 || domainMaxLen == 0) {
        return -1;
    }

    /* Initialize output buffer to ensure null termination */
    memset(domain, 0, domainMaxLen);

    size_t pos = offset;
    size_t domainPos = 0;

    while (pos < bufferLen) {
        /* Bounds check before reading length byte */
        if (pos >= bufferLen) {
            return -1;
        }

        uint8_t len = buffer[pos];

        /* Check for compression pointer (not supported in this implementation) */
        if ((len & 0xC0) == 0xC0) {
            return -1; /* Reject compression to prevent complexity attacks */
        }

        if (len == 0) {
            pos++;
            break;
        }

        /* Validate label length - DNS label max is 63 bytes */
        if (len > 63) {
            return -1;
        }

        pos++;

        /* Bounds check: ensure we don't read beyond buffer */
        if (pos + len > bufferLen) {
            return -1;
        }

        /* Add dot separator if not first label */
        if (domainPos > 0) {
            /* Check space for dot and null terminator */
            if (domainPos + 1 >= domainMaxLen) {
                return -1;
            }
            domain[domainPos++] = '.';
        }

        /* Check if we have space for this label plus null terminator */
        if (domainPos + len >= domainMaxLen) {
            return -1;
        }

        /* Safe copy with bounds checking and character validation */
        for (size_t i = 0; i < len; i++) {
            if (pos + i >= bufferLen) {
                return -1;
            }

            char c = (char)buffer[pos + i];

            /* Validate DNS label characters (alphanumeric, hyphen, underscore) */
            if (!((c >= 'a' && c <= 'z') ||
                  (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') ||
                  c == '-' || c == '_')) {
                return -1;
            }

            domain[domainPos++] = c;
        }

        pos += len;

        /* Check total domain length */
        if (domainPos > MAX_DOMAIN_LENGTH) {
            return -1;
        }
    }

    /* Ensure null termination */
    domain[domainPos] = '\0';

    return (int)(pos - offset);
}

/*
 * Build DNS response with bounds checking
 * Security: prevent buffer overflow (CWE-787)
 */
int buildDNSResponse(const uint8_t* query, size_t queryLen,
                     const char* resolvedIP,
                     uint8_t* response, size_t responseMaxLen,
                     size_t* responseLen) {
    /* Validate all inputs */
    if (query == NULL || resolvedIP == NULL || response == NULL ||
        responseLen == NULL || queryLen == 0 || responseMaxLen == 0) {
        return 0;
    }

    /* Check minimum query length */
    if (queryLen < sizeof(DNSHeader) + 6) {
        return 0;
    }

    /* Validate query size */
    if (queryLen > MAX_DNS_PACKET_SIZE) {
        return 0;
    }

    /* Check if response buffer is large enough */
    if (responseMaxLen < queryLen + 16) { /* 16 bytes for answer section */
        return 0;
    }

    /* Safe copy with bounds checking */
    memcpy(response, query, queryLen);
    size_t pos = queryLen;

    /* Modify header flags */
    DNSHeader* header = (DNSHeader*)response;
    header->flags = htons(0x8180); /* Standard response, no error */
    header->ancount = htons(1);    /* One answer */

    /* Add answer section with bounds checking */
    if (pos + 2 > responseMaxLen) return 0;
    response[pos++] = 0xC0; /* Compression pointer */
    response[pos++] = 0x0C; /* Offset to question name */

    /* Type A */
    if (pos + 2 > responseMaxLen) return 0;
    response[pos++] = 0x00;
    response[pos++] = DNS_QUERY_TYPE_A;

    /* Class IN */
    if (pos + 2 > responseMaxLen) return 0;
    response[pos++] = 0x00;
    response[pos++] = DNS_CLASS_IN;

    /* TTL (300 seconds) */
    if (pos + 4 > responseMaxLen) return 0;
    response[pos++] = 0x00;
    response[pos++] = 0x00;
    response[pos++] = 0x01;
    response[pos++] = 0x2C;

    /* Data length (4 bytes for IPv4) */
    if (pos + 2 > responseMaxLen) return 0;
    response[pos++] = 0x00;
    response[pos++] = 0x04;

    /* Parse and add IP address with validation */
    struct in_addr addr;
    if (inet_pton(AF_INET, resolvedIP, &addr) != 1) {
        return 0;
    }

    if (pos + 4 > responseMaxLen) return 0;
    uint32_t ip = ntohl(addr.s_addr);
    response[pos++] = (uint8_t)((ip >> 24) & 0xFF);
    response[pos++] = (uint8_t)((ip >> 16) & 0xFF);
    response[pos++] = (uint8_t)((ip >> 8) & 0xFF);
    response[pos++] = (uint8_t)(ip & 0xFF);

    *responseLen = pos;
    return 1;
}

/*
 * Resolve DNS query using getaddrinfo (system resolver)
 * Security: uses system resolver, validates input domain length
 */
int resolveDomain(const char* domain, char* ipAddr, size_t ipAddrLen) {
    /* Validate inputs */
    if (domain == NULL || ipAddr == NULL || ipAddrLen == 0) {
        return 0;
    }

    /* Initialize output buffer */
    memset(ipAddr, 0, ipAddrLen);

    /* Validate domain length */
    size_t domainLen = strlen(domain);
    if (domainLen == 0 || domainLen > MAX_DOMAIN_LENGTH) {
        return 0;
    }

    struct addrinfo hints;
    struct addrinfo* result = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    /* Use getaddrinfo with validated domain name */
    int ret = getaddrinfo(domain, NULL, &hints, &result);
    if (ret != 0 || result == NULL) {
        if (result != NULL) {
            freeaddrinfo(result);
        }
        return 0;
    }

    /* Extract IP address with bounds checking */
    struct sockaddr_in* addr = (struct sockaddr_in*)result->ai_addr;
    if (inet_ntop(AF_INET, &(addr->sin_addr), ipAddr, ipAddrLen) == NULL) {
        freeaddrinfo(result);
        return 0;
    }

    freeaddrinfo(result);
    return 1;
}

/*
 * Main DNS server function
 * Security: validates IP and port, implements bounds checking throughout
 */
int startDNSServer(const char* listenIP, uint16_t port) {
    /* Validate inputs */
    if (listenIP == NULL) {
        fprintf(stderr, "Invalid IP address (NULL)\n");
        return 0;
    }

    /* Validate IP address format */
    struct in_addr addr;
    if (inet_pton(AF_INET, listenIP, &addr) != 1) {
        fprintf(stderr, "Invalid IP address format\n");
        return 0;
    }

    /* Validate port range */
    if (port == 0) {
        fprintf(stderr, "Invalid port number\n");
        return 0;
    }

    /* Create UDP socket with error checking */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket: %s\n", strerror(errno));
        return 0;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr = addr;

    /* Bind socket with error checking */
    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "Failed to bind socket: %s\n", strerror(errno));
        close(sockfd);
        return 0;
    }

    printf("DNS server listening on %s:%u\n", listenIP, port);

    /* Server loop with bounds-checked buffer */
    uint8_t buffer[MAX_DNS_PACKET_SIZE];
    uint8_t response[MAX_DNS_PACKET_SIZE];
    struct sockaddr_in clientAddr;
    socklen_t clientLen;

    while (1) {
        /* Initialize buffers to zero */
        memset(buffer, 0, sizeof(buffer));
        memset(response, 0, sizeof(response));
        memset(&clientAddr, 0, sizeof(clientAddr));
        clientLen = sizeof(clientAddr);

        /* Receive with size limit to prevent overflow (CWE-120) */
        ssize_t recvLen = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                   (struct sockaddr*)&clientAddr, &clientLen);

        if (recvLen < 0) {
            fprintf(stderr, "Receive error: %s\n", strerror(errno));
            continue;
        }

        /* Validate minimum packet size */
        if (recvLen < (ssize_t)sizeof(DNSHeader)) {
            fprintf(stderr, "Packet too small\n");
            continue;
        }

        /* Validate maximum packet size */
        if ((size_t)recvLen > MAX_DNS_PACKET_SIZE) {
            fprintf(stderr, "Packet too large\n");
            continue;
        }

        /* Parse DNS header with bounds checking */
        const DNSHeader* header = (const DNSHeader*)buffer;
        uint16_t qdcount = ntohs(header->qdcount);

        /* Only handle single question queries */
        if (qdcount != 1) {
            fprintf(stderr, "Invalid question count\n");
            continue;
        }

        /* Parse domain name with bounds checking */
        char domain[MAX_DOMAIN_LENGTH + 1];
        int nameLen = parseDomainName(buffer, (size_t)recvLen,
                                      sizeof(DNSHeader), domain,
                                      sizeof(domain));

        if (nameLen < 0 || domain[0] == '\0') {
            fprintf(stderr, "Failed to parse domain name\n");
            continue;
        }

        printf("Received query for: %s\n", domain);

        /* Resolve domain using system resolver */
        char resolvedIP[INET_ADDRSTRLEN];
        if (!resolveDomain(domain, resolvedIP, sizeof(resolvedIP))) {
            printf("Failed to resolve domain: %s\n", domain);
            continue;
        }

        printf("Resolved %s to %s\n", domain, resolvedIP);

        /* Build response with bounds checking */
        size_t responseLen = 0;
        if (!buildDNSResponse(buffer, (size_t)recvLen, resolvedIP,
                              response, sizeof(response), &responseLen)) {
            fprintf(stderr, "Failed to build response\n");
            continue;
        }

        /* Send response with error checking */
        ssize_t sentLen = sendto(sockfd, response, responseLen, 0,
                                 (struct sockaddr*)&clientAddr, clientLen);

        if (sentLen < 0 || (size_t)sentLen != responseLen) {
            fprintf(stderr, "Failed to send response: %s\n", strerror(errno));
            continue;
        }

        printf("Response sent successfully\n");
    }

    close(sockfd);
    return 1;
}

int main(void) {
    /* Test case 1: Standard DNS server setup validation */
    printf("Test 1: Validating DNS server parameters\n");

    /* Test case 2: Validate IP address parsing */
    printf("\nTest 2: Validating IP address formats\n");
    struct in_addr testAddr;
    printf("Valid IP (192.168.1.1): %s\n",
           inet_pton(AF_INET, "192.168.1.1", &testAddr) == 1 ? "PASS" : "FAIL");
    printf("Invalid IP (999.999.999.999): %s\n",
           inet_pton(AF_INET, "999.999.999.999", &testAddr) != 1 ? "PASS" : "FAIL");

    /* Test case 3: Domain name parsing validation */
    printf("\nTest 3: Testing domain name parsing\n");
    uint8_t testQuery[] = {
        0x03, 'w', 'w', 'w',
        0x06, 'g', 'o', 'o', 'g', 'l', 'e',
        0x03, 'c', 'o', 'm',
        0x00
    };
    char parsedDomain[MAX_DOMAIN_LENGTH + 1];
    int result = parseDomainName(testQuery, sizeof(testQuery), 0,
                                 parsedDomain, sizeof(parsedDomain));
    printf("Parsed domain: %s (%s)\n",
           (result > 0 && strcmp(parsedDomain, "www.google.com") == 0) ? "PASS" : "FAIL",
           parsedDomain);

    /* Test case 4: Test domain resolution */
    printf("\nTest 4: Testing domain resolution\n");
    char resolved[INET_ADDRSTRLEN];
    int resolveResult = resolveDomain("localhost", resolved, sizeof(resolved));
    printf("Resolved localhost: %s (%s)\n",
           resolveResult ? "PASS" : "FAIL", resolved);

    /* Test case 5: Invalid domain handling */
    printf("\nTest 5: Testing invalid domain handling\n");
    char invalidDomain[400];
    memset(invalidDomain, 'a', sizeof(invalidDomain) - 1);
    invalidDomain[sizeof(invalidDomain) - 1] = '\0';
    char invalidResolved[INET_ADDRSTRLEN];
    int invalidResult = resolveDomain(invalidDomain, invalidResolved,
                                      sizeof(invalidResolved));
    printf("Invalid domain rejected: %s\n", !invalidResult ? "PASS" : "FAIL");

    printf("\nAll validation tests completed.\n");
    printf("To run the actual DNS server, uncomment the following line:\n");
    printf("// startDNSServer(\"127.0.0.1\", 5353);\n");

    return 0;
}
