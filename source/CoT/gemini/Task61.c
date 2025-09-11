#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

char* getRootElement(const char* xmlString) {
    xmlDocPtr doc = xmlReadMemory(xmlString, strlen(xmlString), "input.xml", NULL, 0);
    if (doc == NULL) {
        return NULL;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);

    if (root != NULL) {
        char* rootName = (char*)xmlStrdup(root->name); // Allocate memory for root name
        xmlFreeDoc(doc); // Free the document before returning
        return rootName;
    } else {
      xmlFreeDoc(doc);
      return NULL;
    }

}

int main() {
  char *xmlString1 = "<note><to>Tove</to><from>Jani</from><heading>Reminder</heading><body>Don't forget me this weekend!</body></note>";
  char *xmlString2 = "<bookstore><book><title>The Great Gatsby</title><author>F. Scott Fitzgerald</author></book></bookstore>";
  char *xmlString3 = "<data></data>";
  char *xmlString4 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root><element1>Value1</element1><element2>Value2</element2></root>";
  char *xmlString5 = "<invalid-xml><tag1></tag1><tag2>";


  char *root1 = getRootElement(xmlString1);
  if(root1 != NULL) {
    printf("Root element 1: %s\n", root1);
    xmlFree(root1); // Free allocated memory by xmlStrdup
  } else {
    printf("Root element 1: Invalid format or no root found\n");
  }

  char *root2 = getRootElement(xmlString2);
  if(root2 != NULL) {
    printf("Root element 2: %s\n", root2);
    xmlFree(root2);
  } else {
    printf("Root element 2: Invalid format or no root found\n");
  }

  char *root3 = getRootElement(xmlString3);
  if(root3 != NULL) {
    printf("Root element 3: %s\n", root3);
    xmlFree(root3);
  } else {
    printf("Root element 3: Invalid format or no root found\n");
  }

  char *root4 = getRootElement(xmlString4);
  if(root4 != NULL) {
    printf("Root element 4: %s\n", root4);
    xmlFree(root4);
  } else {
    printf("Root element 4: Invalid format or no root found\n");
  }

  char *root5 = getRootElement(xmlString5);
  if(root5 != NULL) {
    printf("Root element 5: %s\n", root5);
    xmlFree(root5);
  } else {
    printf("Root element 5: Invalid format or no root found\n");
  }

  return 0;
}