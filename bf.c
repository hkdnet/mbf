#include <stdio.h>
#include <stdlib.h>

#define TAPE_SIZE 30000

typedef struct tape {
    int size;
    int head;
    char* tape;
} tape_t;

char read_tape_bang(tape_t* t)
{
    char c = t->tape[t->head];
    t->head++;
    return c;
}

int tape_end_p(tape_t* t)
{
    return t->tape[t->head] == '\0';
}

int process(tape_t* t, int idx, char* b, FILE*in, FILE* out)
{
    char c;
    c = read_tape_bang(t);
    switch (c) {
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
    int idx, status;
    char* b;
    tape_t* t;
    idx = 0;
    b = malloc(30000);
    t = malloc(sizeof(tape_t));
    t->size = TAPE_SIZE;
    t->head = 0;
    t->tape = malloc(t->size);
    status = fread(t->tape, t->size, 1, f);
    if (!feof(f)) {
        return 1; // read error or too long
    }
    while(!tape_end_p(t)) {
        idx = process(t, idx, b, stdin, stdout);
    }
    free(b);
    free(t->tape);
    free(t);
    return 0;
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
