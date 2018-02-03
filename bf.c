#include <stdio.h>
#include <stdlib.h>

int process(char c, int idx, char* b, FILE*in, FILE* out)
{
    switch (c) {
        case 'a':
            break;
        case '>':
            return idx + 1;
        case '<':
            return idx - 1;
        case '+':
            b[idx]++;
            return idx;
        case '-':
            b[idx]--;
            return idx;
        case '.':
            fputc(b[idx], out); // TODO: error handling
            return idx;
        case ',':
            b[idx] = fgetc(out); // TODO: error handling
            return idx;
        case '[':
        case ']':
            return idx;
    }
    return idx;
}

int run(FILE* f)
{
    int c, idx;
    char* b;
    idx = 0;
    b = malloc(30000);
    while((c = fgetc(f)) != EOF) {
        idx = process(c, idx, b, stdin, stdout);
    }
    free(b);
    if (feof(f)) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char const* argv[])
{
    FILE* f;
    f = fopen("./input/hoge", "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }
    int status = run(f);
    if (status != 0) {
        exit(1);
    }
    exit(0);
}
