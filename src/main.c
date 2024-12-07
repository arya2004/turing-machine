#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    bool *data;
    size_t data_size;

    size_t head;

} Machine;

typedef enum
{
    LEFT = -1,
    STAY = 0,
    RIGHT = 1,

} Direction;

typedef struct
{
    bool write;
    Direction dir;
    size_t next;

} State;

// exprected value, value if true, direction if true,next if true, value if false, directoin if false, nxt if false
typedef struct main
{
    bool exprected;

    State yes;

    State no;

} Instruction;

typedef struct
{

    Machine *machine;
    Instruction *instruction;
    size_t curr;
    size_t inst_count;

} Program;

void machine_randomize(Machine *machine)
{
    srand(time(NULL));
    for (size_t i = 0; i < machine->data_size; i++)
    {
        machine->data[i] = rand() % 2;
    }
}

void machine_initialize_data(Machine *machine, char *tape_data)
{
    for (size_t i = 0; i < machine->data_size; i++)
    {
        if (tape_data[i] == '0')
        {
            machine->data[i] = 0;
        }
        else if (tape_data[i] == '1')
        {
            machine->data[i] = 1;
        }
        else
        {
            fprintf(stderr, "Error: Invalid character '%c' in tape data. Only '0' or '1' are allowed.\n", tape_data[i]);
            exit(EXIT_FAILURE);
        }
    }
}

size_t machine_execute(Machine *machine, Instruction *instruction, size_t inst_count)
{
    if (machine->head >= machine->data_size)
        return inst_count;

    if (machine->data[machine->head] == instruction->exprected)
    {
        machine->data[machine->head] = instruction->yes.write;
        if (machine->head == 0 && instruction->yes.dir < 0)
            return inst_count;
        machine->head += instruction->yes.dir;
        return instruction->yes.next;
    }

    machine->data[machine->head] = instruction->no.write;
    if (machine->head == 0 && instruction->no.dir < 0)
        return inst_count;
    machine->head += instruction->no.dir;

    return instruction->no.next;
}

void machine_print(Machine *machine)
{
    printf("head: %zu, ", machine->head);
    for (size_t i = 0; i < machine->data_size; i++)
    {
        printf("%d -> ", machine->data[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    /*
        Check if run configurations are given
        turing_machine <instruction_file.turing> <optional_initial_tape>
    */

    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, "Usage: %s <instruction_file.turing> [optional_initial_tape]\n", argv[0]);
        return 1;
    }

    char *instruction_file = argv[1];
    printf("Instruction file: %s\n", instruction_file);

    // TODO : Read Instruction file and parse the instructions
    // <state> <expected_symbol> <write_symbol> <direction> <next_state>

    // Initial Tape
    char *initial_tape;
    size_t tape_length = 8;

    if (argc == 3)
    {
        initial_tape = argv[2];
        tape_length = strlen(initial_tape);
        printf("Initial tape: %s\n", initial_tape);
    }
    else
    {
        printf("Initial tape not provided. Generating randomized tape..\n");
        initial_tape = NULL;
    }

    Program program = {0};
    Machine machine = {0};

    // Machine Configuration
    machine.data_size = tape_length;
    machine.data = malloc(sizeof(bool) * machine.data_size);
    if (initial_tape)
    {
        machine_initialize_data(&machine, initial_tape);
    }
    else
    {
        machine_randomize(&machine);
    }

    program.machine = &machine;

    Instruction inst[] = {
        {0, {1, RIGHT, 2}, {0, RIGHT, 0}},
        {NULL},
    };

    program.instruction = inst;

    program.inst_count = sizeof(inst) / sizeof(*inst);

    machine_print(program.machine);
    while (program.curr <= program.inst_count - 1)
    {
        program.curr = machine_execute(program.machine, &inst[program.curr], program.inst_count);
        machine_print(program.machine);
    }

    return 0;
}