#ifndef ALL_THINGIES_H
#define ALL_THINGIES_H
#include<stdio.h>

#define GOOD_BUFFER 255
#define DELIM " \t\n"
#define MAX_CHAR_LENGTH 255

typedef struct {
    int id;
    char **column_data;
} table_row;

extern table_row *row;

extern int columns;
extern int rows;

extern char **master_memory_headers;

void read(FILE *filename);
void write(FILE *filename);
char *line_reader();
char **arg_reader(char *line);
void exe_writer(char **arguments, FILE *filename);
void head_reader(FILE *filename);
void body_reader(FILE *filename, int heads);
void printer(char **arguments, FILE *filename);
void commit(FILE *filename);
#endif
