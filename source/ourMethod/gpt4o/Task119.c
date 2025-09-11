#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*** parseCSV(const char* input, int* numRows, int* numCols) {
    char*** result = NULL;
    char* inputCopy = strdup(input);
    char* line = strtok(inputCopy, "\n");
    int rowCount = 0;

    while (line != NULL) {
        char** row = NULL;
        char* cell = strtok(line, ",");
        int colCount = 0;

        while (cell != NULL) {
            row = realloc(row, sizeof(char*) * (colCount + 1));
            row[colCount] = strdup(cell);
            colCount++;
            cell = strtok(NULL, ",");
        }

        result = realloc(result, sizeof(char**) * (rowCount + 1));
        result[rowCount] = row;
        rowCount++;
        line = strtok(NULL, "\n");
    }

    free(inputCopy);
    *numRows = rowCount;
    *numCols = (rowCount > 0) ? colCount : 0;
    return result;
}

int main() {
    int numRows, numCols;
    char*** data1 = parseCSV("name,age,city\nJohn,25,New York", &numRows, &numCols);
    char*** data2 = parseCSV("fruit,quantity\nApple,10", &numRows, &numCols);
    char*** data3 = parseCSV("product,price\nLaptop,999.99", &numRows, &numCols);
    char*** data4 = parseCSV("car,year\nToyota,2020", &numRows, &numCols);
    char*** data5 = parseCSV("language,level\nJava,Expert", &numRows, &numCols);
    return 0;
}