#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(char *file_path, int *file_size);
int valid_char(char c);
int valid_brackets(const char *contents, int size);
int valid_syntax(char *content, int size);

int main(int argv, char *args[]) {

//    if (argv < 2) {
//        printf("Usage: ./fuck source_file\n");
//        return 1;
//    }

//    char *source_path = args[1];
//    int file_size;
//    char *file_contents = read_file(source_path, &file_size);

//    printf("%s\n%d\n", file_contents, file_size);

//    free(file_contents);

    char* s = "[[[][][][][]]]";

    printf("%d\n", valid_brackets(s, (int)strlen(s)));

    return 0;
}

char *read_file(char *file_path, int *file_size) {

    FILE *fptr = fopen(file_path, "r");

    if ( fptr == NULL ) {
        fprintf(stderr, "Error opening source file\n");
        return NULL;
    }

    if ( fseek(fptr, 0, SEEK_END) != 0 ) {
        fprintf(stderr, "Error reading source file size\n");
        return NULL;
    }

    *file_size = (int)ftell(fptr);
    rewind(fptr);

    char *contents = malloc(sizeof(char) * (*file_size + 1));

    fread(contents, sizeof(char), *file_size, fptr);
    if ( ferror(fptr) != 0 ) {
        fprintf(stderr, "Error reading source file\n");
        return NULL;
    }

    return contents;
}

int valid_char(char c) {
    return (c == '.' || c == ',' || c == '-' || c == '+' ||
            c == '[' || c == ']' || c == '<' || c == '>' ||
            c == ' ' || c == '\t' || c == '\n');
}

int valid_brackets(const char *contents, int size) {
    
    char stack[size];
    int top = 0;

    for (int i = 0; i < size; ++i) {

        if (contents[i] == '[') {
            stack[top++] = '[';
        }
        else if (contents[i] == ']') {
            if (stack[--top] != '[')
                return 0;
        }
    }

    return top == 0;
}


