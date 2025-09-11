
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void toJadenCase(char* str) {
    if(!str || strlen(str) == 0) return;
    
    int i;
    int capitalize = 1;
    
    for(i = 0; str[i] != '\\0'; i++) {
        if(capitalize && isalpha(str[i])) {
            str[i] = toupper(str[i]);
            capitalize = 0;
        }
        else if(str[i] == ' ') {
            capitalize = 1;
        }
    }
}

int main() {
    char str1[] = "How can mirrors be real if our eyes aren't real";
    char str2[] = "school is the tool to brainwash the youth";
    char str3[] = "if everybody in the world dropped out of school we would have a much more intelligent society";
    char str4[] = "";
    char str5[] = "trees are never sad look at them every once in awhile they're quite beautiful";
    
    toJadenCase(str1);
    toJadenCase(str2);
    toJadenCase(str3);
    toJadenCase(str4);
    toJadenCase(str5);
    
    printf("%s\\n", str1);
    printf("%s\\n", str2);
    printf("%s\\n", str3);
    printf("%s\\n", str4);
    printf("%s\\n", str5);
    
    return 0;
}
