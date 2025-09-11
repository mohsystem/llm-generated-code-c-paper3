#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

void storeData(const char* data) {
    MYSQL* conn = mysql_init(0);
    mysql_real_connect(conn, "localhost", "username", "password", "myDatabase", 0, NULL, 0);
    char query[255];
    sprintf(query, "INSERT INTO myTable (column) VALUES ('%s')", data);
    mysql_query(conn, query);
    mysql_close(conn);
}

int main() {
    const char* url = "http://example.com";
    htmlDocPtr doc = htmlReadFile(url, NULL, 0);
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression("//selector", context);
    xmlNodeSetPtr nodes = result->nodesetval;
    for (int i = 0; i < nodes->nodeNr; i++) {
        xmlChar* data = xmlNodeGetContent(nodes->nodeTab[i]);
        storeData((char*)data);
        xmlFree(data);
    }
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    return 0;
}