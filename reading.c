#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all_thingies.h"

void printer(char **arguments, FILE *filename)
{
    if (strcmp(arguments[0], "READ") == 0) { 
        if (strcmp(arguments[1], "ALL") == 0) { 
            for (int i = 0; i < columns; i++) {
                printf("|%-15s", master_memory_headers[i]);
            }
            printf("|\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    printf("|%-15s", row[i].column_data[j]);
                }
                printf("|\n");
            }
        }
    }
}
