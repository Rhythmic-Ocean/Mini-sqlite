#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all_thingies.h"

void exe_writer(char **arguments, FILE *filename) {
    if (strcmp(arguments[0], "CREATE") == 0) {
        char stat;
        printf("Are you sure you want to overwrite any table that may exist here? (y/n)\n");
        scanf(" %c", &stat); 

        if (stat == 'y') {
            
            if (master_memory_headers != NULL) {
                for (int i = 0; i < columns; i++) {
                    free(master_memory_headers[i]);
                }
                free(master_memory_headers);
                master_memory_headers = NULL;
            }

           
            if (rows != 0) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < columns; j++) {
                        free(row[i].column_data[j]);
                    }
                    free(row[i].column_data);
                }
                free(row);
                row = NULL;
            }

            int buffer_read = GOOD_BUFFER;
            master_memory_headers = malloc(sizeof(char*) * buffer_read); 
            if (!master_memory_headers) {
                printf("Memory error!\n");
                exit(1);
            }

            int p = 1;  
            while (arguments[p] != NULL && p < buffer_read) {
                master_memory_headers[p-1] = malloc(MAX_CHAR_LENGTH);
                if (!master_memory_headers[p-1]) {
                    printf("Memory error!\n");
                    exit(1);
                }
                strcpy(master_memory_headers[p-1], arguments[p]);
                p++;
            }
            master_memory_headers[p-1] = NULL;  

            columns = p-1; 
            rows = 0;     
        }
    } 
    else if (strcmp(arguments[0], "INSERT") == 0) {
        if (strcmp(arguments[1], "NEW") == 0) {
            rows++;
            table_row *temp = realloc(row, sizeof(table_row) * rows); // Corrected
            if (!temp) {
                printf("Memory error!\n");
                exit(1);
            }
            row = temp;
            row[rows - 1].column_data = malloc(sizeof(char*) * columns);  
            if (!row[rows - 1].column_data) {
                printf("Memory error!\n");
                exit(1);
            }
            int p = 0;
            while (arguments[p + 2] != NULL && p < columns) {
                row[rows - 1].column_data[p] = malloc(MAX_CHAR_LENGTH);
                if (!row[rows - 1].column_data[p]) {
                    printf("Memory error!\n");
                    exit(1);
                }
                strcpy(row[rows - 1].column_data[p], arguments[p + 2]);  
                p++;
            } 
        } 
        else {
            printf("Wrong argument for INSERT command!\n");
        }  
    } 
    else if (strcmp(arguments[0], "EXIT") == 0) {
        commit(filename);
        exit(0);
    } 
    else {
        printf("Wrong argument!\n");
        exit(1);
    }
}  