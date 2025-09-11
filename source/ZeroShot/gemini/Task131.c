#include <stdio.h>
#include <string.h>

// Note: C doesn't have built-in serialization/deserialization like Java or Python.
// This example shows a simplified version for string data. Real-world scenarios
// require careful handling of data types, memory management, and security considerations
// for proper deserialization.


// This function simply returns the input string. In a real application,
// you would need to replace this with actual base64 decoding
// and deserialization logic.
char* deserialize(const char* base64Encoded) {
    // Basic demonstration - in reality, you would need to allocate
    // memory for the deserialized string and perform the actual decoding
    // and deserialization.  Avoid direct use of untrusted data.
    char* result = strdup(base64Encoded); 
    return result; 
}



int main() {

    char* test1 = "SGVsbG8=";
    printf("%s\n", deserialize(test1));
    free(deserialize(test1));


    char* test2 = "V29ybGQ=";
    printf("%s\n", deserialize(test2));
    free(deserialize(test2));


    char* test3 = "MTIz";
    printf("%s\n", deserialize(test3));
    free(deserialize(test3));



    char* test4 = "VGVzdA==";
    printf("%s\n", deserialize(test4));
    free(deserialize(test4));

    char* test5 = "RGF0YQ==";
    printf("%s\n", deserialize(test5));
    free(deserialize(test5));

    return 0;
}