
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHILDREN 100
#define MAX_NAME_LENGTH 256

typedef struct XMLNode {
    char name[MAX_NAME_LENGTH];
    struct XMLNode* children[MAX_CHILDREN];
    int childCount;
} XMLNode;

static int index = 0;

XMLNode* createNode(const char* name) {
    XMLNode* node = (XMLNode*)malloc(sizeof(XMLNode));
    strncpy(node->name, name, MAX_NAME_LENGTH - 1);
    node->name[MAX_NAME_LENGTH - 1] = '\\0';
    node->childCount = 0;
    return node;
}

void freeNode(XMLNode* node) {
    if (node == NULL) return;
    
    for (int i = 0; i < node->childCount; i++) {
        freeNode(node->children[i]);
    }
    free(node);
}

XMLNode* parseElement(const char* xml, int length) {
    // Skip whitespace
    while (index < length && isspace(xml[index])) {
        index++;
    }
    
    if (index >= length || xml[index] != '<') {
        return NULL;
    }
    
    // Skip '<'
    index++;
    
    // Get tag name
    char tagName[MAX_NAME_LENGTH] = {0};
    int nameIndex = 0;
    while (index < length && xml[index] != '>' && nameIndex < MAX_NAME_LENGTH - 1) {
        tagName[nameIndex++] = xml[index++];
    }
    index++; // Skip '>'
    
    XMLNode* node = createNode(tagName);
    
    // Handle self-closing tags
    if (tagName[strlen(tagName) - 1] == '/') {
        tagName[strlen(tagName) - 1] = '\\0';
        strncpy(node->name, tagName, MAX_NAME_LENGTH - 1);
        return node;
    }
    
    // Parse children until closing tag
    while (index < length) {
        if (xml[index] == '<' && xml[index + 1] == '/') {
            // Skip closing tag
            while (index < length && xml[index] != '>') index++;
            index++;
            break;
        }
        
        XMLNode* child = parseElement(xml, length);
        if (child != NULL && node->childCount < MAX_CHILDREN) {
            node->children[node->childCount++] = child;
        } else {
            index++;
        }
    }
    
    return node;
}

XMLNode* parseXML(const char* xml) {
    if (xml == NULL || strlen(xml) == 0) {
        return NULL;
    }
    
    index = 0;
    return parseElement(xml, strlen(xml));
}

int main() {
    const char* testCases[] = {
        "<root><child1/><child2/></root>",
        "<document><header>Title</header><body>Content</body></document>",
        "<single/>",
        "<parent><child><grandchild/></child></parent>",
        "<root></root>"
    };
    
    for (int i = 0; i < 5; i++) {
        XMLNode* root = parseXML(testCases[i]);
        if (root != NULL) {
            printf("Root element: %s\\n", root->name);
            printf("Number of children: %d\\n", root->childCount);
            printf("---\\n");
            freeNode(root);
        }
    }
    
    return 0;
}
