/*
 * This program requires the libxml2 library.
 * To compile on a Debian-based system (like Ubuntu):
 * 1. Install the library: sudo apt-get install libxml2-dev
 * 2. Compile with: gcc your_file_name.c -o your_program_name -lxml2
 */
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/**
 * @brief Parses an XML string and extracts the root element's name.
 * 
 * This function safely parses an XML string using libxml2, with options
 * to disable network access, preventing XXE attacks that rely on external
 * resource fetching.
 * 
 * @param xml_string The input XML string. Must be a null-terminated C string.
 * @param out_buffer A character buffer to store the root element name.
 * @param buffer_size The size of the output buffer.
 * @return 0 on success, -1 on failure (e.g., parsing error, invalid input,
 *         or buffer too small). On failure, out_buffer will be empty.
 */
int getRootElementName(const char* xml_string, char* out_buffer, size_t buffer_size) {
    if (out_buffer == NULL || buffer_size == 0) {
        return -1; // Invalid output buffer
    }
    out_buffer[0] = '\0'; // Ensure buffer is empty on error

    if (xml_string == NULL || *xml_string == '\0') {
        return -1; // Invalid input string
    }

    // XML_PARSE_NONET disables network access, a key defense against XXE.
    // libxml2 >= 2.9.0 disables external entity loading by default, but this adds defense-in-depth.
    xmlDocPtr doc = xmlReadMemory(xml_string, (int)strlen(xml_string), "noname.xml", NULL, XML_PARSE_NONET);
    if (doc == NULL) {
        return -1; // Failed to parse document
    }

    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (root == NULL) {
        xmlFreeDoc(doc);
        return -1; // No root element found
    }

    int result = -1;
    if (root->name != NULL) {
        // Use snprintf for safe, bounded string copy
        int written = snprintf(out_buffer, buffer_size, "%s", (const char*)root->name);
        if (written > 0 && (size_t)written < buffer_size) {
            result = 0; // Success
        }
    }
    
    xmlFreeDoc(doc);
    return result;
}

int main() {
    const char* testCases[] = {
        // 1. Simple valid XML
        "<root><child>data</child></root>",
        // 2. XML with attributes and a different root name
        "<document id='123'><item>value</item></document>",
        // 3. Malformed XML (unclosed tag)
        "<notes><note>text</notes>",
        // 4. Empty string input
        "",
        // 5. XML with a DOCTYPE declaration (should be safely rejected/ignored)
        "<?xml version=\"1.0\"?><!DOCTYPE root [<!ENTITY xxe SYSTEM \"file:///etc/passwd\">]><root>&xxe;</root>"
    };
    int num_test_cases = sizeof(testCases) / sizeof(testCases[0]);

    // Initialize the XML library.
    // Should be called once per application thread.
    xmlInitParser();

    for (int i = 0; i < num_test_cases; i++) {
        char root_element_name[256];
        printf("Test Case %d:\n", i + 1);
        printf("Input XML: \"%s\"\n", testCases[i]);
        
        if (getRootElementName(testCases[i], root_element_name, sizeof(root_element_name)) == 0) {
            printf("Root Element: \"%s\"\n\n", root_element_name);
        } else {
            printf("Root Element: \"\"\n\n");
        }
    }

    // Clean up the XML library.
    xmlCleanupParser();

    return 0;
}