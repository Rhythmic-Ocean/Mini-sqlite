#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all_thingies.h"

void read(FILE *filename) {
    char *line;
    char **arguments;
    printf("File opened successfully for reading.\n");
    do {
        printf("reading> ");
        line = line_reader();  
        if (line == NULL) {    
            printf("Error reading line.\n");
            continue;
        }
        printf("Read line: %s\n", line);
        if (strcmp(line, "EXIT") == 0) {
            free(line);
            break;
        }
        arguments = arg_reader(line);
        if (arguments == NULL) { 
            printf("Error reading arguments.\n");
            free(line);
            continue;
        }
        printer(arguments, filename);
        free(line);
        free(arguments); 
    } while (1); 

    printf("Exiting read function.\n");
}

void write(FILE *filename) {
    char *line;
    char **arguments;
    printf("File opened successfully for writing.\n");
    do {
        printf("writing> ");
        line = line_reader(); 
        if (line == NULL) {  
            printf("Error reading line.\n");
            continue;
        }
        printf("Read line: %s\n", line);
        arguments = arg_reader(line);
        if (arguments == NULL) { 
            printf("Error reading arguments.\n");
            free(line);
            continue;
        }
        printf("Arguments read successfully.\n");
        
        exe_writer(arguments, filename);
        
 
    } while (line != NULL && strcmp(line, "EXIT") != 0); 
    free(line);
    free(arguments);

    printf("Exiting write function.\n");
    commit(filename);
}

char *line_reader(void) {
    int buffer_read = GOOD_BUFFER;
    int p = 0;
    char *buffer = malloc(sizeof(char) * buffer_read);
    if (!buffer) {
        printf("Memory error!!\n");
        exit(1);
    }
    int c;
    int count = 0;
    while (1) {
        c = getchar();
        count++;
        if(count == 1 && c == '\n')
        {
            continue;
        }
        if (c == EOF) { 
            free(buffer); 
            return NULL;  
        }
        if (c == '\n') {
            buffer[p] = '\0';
            return buffer;
        }
        buffer[p] = c;
        p++;
        if (p >= buffer_read) {
            buffer_read += GOOD_BUFFER;
            buffer = realloc(buffer, buffer_read);
            if (!buffer) {
                printf("Memory error\n");
                exit(1);
            }
        }
    }
}

char **arg_reader(char *line) {
    int buffer_read = GOOD_BUFFER;
    char **tokens = malloc(sizeof(char*) * buffer_read);
    int p = 0;
    char *token;

    if (!tokens) {
        printf("Memory error\n");
        exit(1);
    }

    token = strtok(line, DELIM);
    while (token != NULL) {
        if (p >= buffer_read - 1) {
            buffer_read += GOOD_BUFFER;
            tokens = realloc(tokens, buffer_read);
            if (!tokens) {
                printf("Memory error\n");
                exit(1);
            }
        }

        tokens[p] = malloc(MAX_CHAR_LENGTH);
        if (!tokens[p]) {
            printf("Memory error.\n");
            for (int i = 0; i < p; i++) {
                free(tokens[i]);
            }
            free(tokens);
            exit(1);
        }
        strcpy(tokens[p], token);
        p++;

        token = strtok(NULL, DELIM);
    }
    tokens[p] = NULL; 
    return tokens;
}
void commit(FILE *filename)
{
    printf("Committing changes to file...\n");
    for(int i = 0; i < columns; i++)
    {
        fprintf(filename, "%s", master_memory_headers[i]);
        if(i < columns - 1)
        {
            fprintf(filename, ",");
        }
    }
    for(int i = 0; i < rows; i++)
    {
        fprintf(filename, "\n");
        for(int j = 0; j < columns; j++)
        {
            fprintf(filename, "%s", row[i].column_data[j]);
            if(j < columns - 1)
            {
                fprintf(filename, ",");
            }
        }
    }
    printf("Changes committed successfully.\n");
}

