#include <stdio.h>
#include <stdlib.h>
#include "all_thingies.h"
#include <string.h>

table_row *row = NULL;  
int columns = 0;        
int rows = 0;           
char **master_memory_headers = NULL;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Invalid Argument: Correct Argument Syntax: main <tablename>\n");
        return 1;
    }

    char filename[256];
    snprintf(filename, sizeof(filename), "%s.csv", argv[1]);

    int n;
    printf("For read, type 1 \nFor write, type 2 \n");
    scanf("%d", &n);

    FILE *file = fopen(filename, "r");
    if (n == 1) {
        if (file == NULL) {
            printf("No such table exists.\n");
            return 1;
        }
        head_reader(file);
        read(file);
        fclose(file);
    } 
    else if (n == 2) {
        if (file == NULL) {
            printf("No such table found, creating new table...\n");
            printf("Enter headers first\n");
        } 
        else {
            printf("Table found. Opening table: %s\n", filename);
            head_reader(file);
            fclose(file); 
        }
        file = fopen(filename, "w"); 
        if (file == NULL) {
            printf("Unexpected error\n");
            return 1;
        }
        write(file);
        fclose(file);
    } 
    else {
        printf("Wrong argument, please try again!\n");
        return 1;
    }
    return 0;
}
