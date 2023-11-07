// Print lines containing specified substring from the files specified as arguments

#include <stdio.h>
#include <string.h>

#define MAX_CHARS_PER_LINE 6000

void read_stream_and_print(FILE *file, char string[]);

int main(int argc, char *argv[]) {

    if (argc == 1) {
        fprintf(stderr, "Usage error: no <string> to look for\n");
    }

    if (argc == 2) {
        read_stream_and_print(stdin, argv[1]);
    } else if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                fprintf(stderr, "Error opening file %s\n", argv[i]);
            }
            read_stream_and_print(file, argv[1]);
        }
    }


    return 0;
}

// reads every line in the stream and prints the line if it includes "string"
void read_stream_and_print(FILE *file, char string[]) {
    char line[MAX_CHARS_PER_LINE];
    int line_num = 1;

    while (fgets(line, MAX_CHARS_PER_LINE, file) != NULL) {
        if (strstr(line, string) != NULL) { // found the string in line
            printf("%d: %s\n", line_num, line);
        }
        line_num++;
    }

    fclose(file);
}
