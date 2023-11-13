#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 10000

int main() {
    char *home_pathname = getenv("HOME");
    size_t len = strlen(home_pathname) + strlen("/.diary.txt") + 1;
    char *pathname = malloc(len);
    snprintf(pathname, len, "%s/.diary.txt", home_pathname);

    FILE *file = fopen(pathname, "r");

    char line[MAX_LINE_LENGTH];
    while ((fgets(line, MAX_LINE_LENGTH, file) != NULL)) {
        printf("%s", line);
    }

    fclose(file);
    free(pathname);

    return 0;
}