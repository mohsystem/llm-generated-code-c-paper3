
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(unsigned char* data, size_t length, unsigned char key) {
    for(size_t i = 0; i < length; i++) {
        data[i] ^= key;
    }
}

void decrypt(unsigned char* data, size_t length, unsigned char key) {
    encrypt(data, length, key); // XOR encryption is reversible
}

int main() {
    // Test case 1: Simple text
    const char* content1 = "Hello World";
    size_t len1 = strlen(content1);
    unsigned char* data1 = (unsigned char*)malloc(len1);
    memcpy(data1, content1, len1);
    
    FILE* file1 = fopen("test1.txt", "wb");
    fwrite(data1, 1, len1, file1);
    fclose(file1);
    
    encrypt(data1, len1, 0x0F);
    file1 = fopen("encrypted1.txt", "wb");
    fwrite(data1, 1, len1, file1);
    fclose(file1);
    
    decrypt(data1, len1, 0x0F);
    printf("Test 1: %.*s\\n", (int)len1, data1);
    free(data1);

    // Test case 2: Empty file
    unsigned char* data2 = NULL;
    size_t len2 = 0;
    
    FILE* file2 = fopen("test2.txt", "wb");
    fclose(file2);
    
    file2 = fopen("encrypted2.txt", "wb");
    fclose(file2);
    
    printf("Test 2: \\n");

    // Test case 3: Special characters
    const char* content3 = "!@#$%^&*()";
    size_t len3 = strlen(content3);
    unsigned char* data3 = (unsigned char*)malloc(len3);
    memcpy(data3, content3, len3);
    
    FILE* file3 = fopen("test3.txt", "wb");
    fwrite(data3, 1, len3, file3);
    fclose(file3);
    
    encrypt(data3, len3, 0x0F);
    file3 = fopen("encrypted3.txt", "wb");
    fwrite(data3, 1, len3, file3);
    fclose(file3);
    
    decrypt(data3, len3, 0x0F);
    printf("Test 3: %.*s\\n", (int)len3, data3);
    free(data3);

    // Test case 4:', type='text')