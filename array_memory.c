#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all_thingies.h"

void head_reader(FILE *filename)
{
    int buffer_read = GOOD_BUFFER;
    master_memory_headers = malloc(sizeof(char*) * buffer_read);
    int p = 0;
    char *init_header = malloc(sizeof(char) * GOOD_BUFFER); 
    if (!(master_memory_headers && init_header)) {
        printf("Memory error!\n");
        exit(1);
    }

    if (fgets(init_header, GOOD_BUFFER, filename) != NULL) {
        char *header = strtok(init_header, ",\n");
        while (header != NULL) {
            master_memory_headers[p] = malloc(sizeof(char) * (strlen(header) + 1));
            if (!master_memory_headers[p]) {
                printf("Memory error!\n");
                free(init_header);
                for (int i = 0; i < p; i++) {
                    free(master_memory_headers[i]);
                }
                free(master_memory_headers);
                fclose(filename);
                exit(1);
            }
            strcpy(master_memory_headers[p], header);
            p++;
            header = strtok(NULL, ",\n");
        }
        master_memory_headers[p] = NULL;
        columns = p;
    } 
    else {
        printf("No headers found. Enter headers first.\n");
        free(init_header);
        free(master_memory_headers);
        return;
    }

    free(init_header);
    body_reader(filename, p);
}

void body_reader(FILE *filename, int heads) {
    int buffer_read = GOOD_BUFFER;
    row = malloc(sizeof(table_row) * buffer_read);
    if (!row) {
        printf("Memory error!\n");
        exit(1);
    }

    int p = 0; 
    char *body_reader = malloc(sizeof(char) * GOOD_BUFFER);
    if (!body_reader) {
        printf("Memory error!\n");
        exit(1);
    }

    while (fgets(body_reader, GOOD_BUFFER, filename) != NULL) {
        row[p].column_data = malloc(sizeof(char*) * (heads+1));
        row[p].id = p + 1;

        int p1 = 0;
        char *data = strtok(body_reader, ",\n");
        while (data != NULL) {
            row[p].column_data[p1] = malloc(sizeof(char) * (strlen(data) + 1));
            if (!row[p].column_data[p1]) {
                printf("Memory error!\n");
                exit(1);
            }
            strcpy(row[p].column_data[p1], data);
            p1++;
            data = strtok(NULL, ",\n");
        }
        row[p].column_data[p1] = NULL;  
        p++;

        if (p >= buffer_read) {
            buffer_read += GOOD_BUFFER;
            table_row *temp = realloc(row, sizeof(table_row) * buffer_read);
            if (!temp) {
                printf("Memory error!\n");
                exit(1);
            }
            row = temp;
        }
    }
    printf("Rows: %d\n", p);
    rows = p;
    free(body_reader);
}