#include <stdio.h>
#include <stdlib.h>

#define STATE_MEM_SIZE 30000
#define TAPE_SIZE 30000

typedef struct state {
    int idx;
    char* mem;
} state_t;

typedef struct tape {
    int size;
    int head;
    char* tape;
} tape_t;

state_t* malloc_state()
{
    state_t* s;
    s = malloc(sizeof(state_t));
    s->idx = 0;
    s->mem = malloc(STATE_MEM_SIZE);
    return s;
}

void free_state(state_t* s)
{
    free(s->mem);
    free(s);
}

tape_t* malloc_tape(FILE* f)
{
    int status;
    tape_t* t;
    t = malloc(sizeof(tape_t));
    t->size = TAPE_SIZE;
    t->head = 0;
    t->tape = malloc(t->size);
    status = fread(t->tape, t->size, 1, f);
    if (!feof(f)) {
        exit(1); // read error or too long
    }
    return t;
}
void free_tape(tape_t* t)
{
    free(t->tape);
    free(t);
}

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

void  process(tape_t* t, state_t* s, FILE*in, FILE* out)
{
    char c;
    c = read_tape_bang(t);
    switch (c) {
        case '>':
            s->idx++;
            return;
        case '<':
            s->idx--;
            return;
        case '+':
            s->mem[s->idx]++;
            return;
        case '-':
            s->mem[s->idx]--;
            return;
        case '.':
            fputc(s->mem[s->idx], out); // TODO: error handling
            return;
        case ',':
            s->mem[s->idx] = fgetc(out); // TODO: error handling
            return;
        // case '[':
        // case ']':
    }
}

int run(FILE* f)
{
    state_t* s;
    tape_t* t;
    s = malloc_state();
    t = malloc_tape(f);
    while(!tape_end_p(t)) {
        process(t, s, stdin, stdout);
    }
    free_tape(t);
    free_state(s);
    return 0;
}

int main(int argc, char const* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s PATH\n", argv[0]);
        exit(1);
    }
    FILE* f;
    f = fopen(argv[1], "r");
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
