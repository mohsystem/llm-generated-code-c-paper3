//  C does not have built-in readily available libraries for secure encryption like other languages in this example.
//  You would typically use a third-party library like libsodium or OpenSSL for this purpose.
//  This example shows a placeholder and emphasizes the importance of using established libraries for security-sensitive operations.
#include <stdio.h>
#include <string.h>

//  Placeholder functions - DO NOT USE FOR REAL ENCRYPTION
void encrypt(char *data) {
    // Replace with actual encryption using a secure library
    // This is just a placeholder and does NOT provide any security
    for (int i = 0; data[i] != '\0'; i++) {
        data[i]++; 
    }
}

void decrypt(char *data) {
    // Replace with actual decryption using a secure library
    // This is just a placeholder and does NOT provide any security
    for (int i = 0; data[i] != '\0'; i++) {
        data[i]--;
    }
}



int main() {
  char data1[] = "1234-5678-9012-3456";
  char data2[] = "John Doe";
  char data3[] = "jane.doe@example.com";
  char data4[] = "9876-5432-1098-7654";
  char data5[] = "Jane Smith";



  char* data_array[] = {data1, data2, data3, data4, data5};
  int num_data = sizeof(data_array) / sizeof(data_array[0]);


    for (int i = 0; i < num_data; i++) {
        encrypt(data_array[i]);
    }

    for (int i = 0; i < num_data; i++) {
        decrypt(data_array[i]);
        printf("%s\n", data_array[i]);
    }


  return 0;
}