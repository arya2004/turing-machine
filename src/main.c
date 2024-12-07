#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    bool *data;
    size_t data_size;

    size_t head;

}Machine;

typedef enum {
    LEFT = -1,
    STAY = 0,
    RIGHT = 1,

}Direction;


typedef struct 
{
    bool write;
    Direction dir;
    size_t next;
    
}State;

// exprected value, value if true, direction if true,next if true, value if false, directoin if false, nxt if false
typedef struct main
{   
    bool exprected;

    State yes;

    State no;

}Instruction;

typedef struct 
{

    Machine  *machine;
    Instruction *instruction;
    size_t curr;

}Program;


void machine_randoize(Machine *machine)
{   
    srand(time(NULL));
    for(size_t i = 0; i < machine->data_size; i++)
    {
        machine->data[i] = rand() % 2;
    }

}

size_t machine_execute(Machine *machine, Instruction *instruction)
{
    if(machine->data[machine->head] == instruction->exprected)
    {   
        machine->data[machine->head] = instruction->yes.write;
        machine->head += instruction->yes.dir;
        return instruction->yes.next;
    }
    machine->data[machine->head] = instruction->no.write;
    machine->head += instruction->no.dir;
    return instruction->no.next;
}

void machine_print(Machine *machine)
{   
    printf("head: %zu, ", machine->head);
    for(size_t i = 0; i < machine->data_size; i++)
    {
        printf("%d -> ", machine->data[i]);
    }
    printf("\n");
}


int main()
{
    printf("Hellow\n");
    Program program = {0};
    Machine machine = {0};
   
    machine.data_size = 3;
    machine.data = malloc(sizeof(bool)*machine.data_size);
    machine_randoize(&machine);
     program.machine = &machine;

    Instruction inst[] = {
        {0, {1, RIGHT, 2},{ 0, RIGHT, 0}},
        {NULL},
    };

    program.instruction = inst;

    size_t inst_count = sizeof(inst)/ sizeof(*inst);

    machine_print(program.machine);
    while (program.curr <= inst_count - 1)
    {   
        program.curr = machine_execute(program.machine, &inst[program.curr]);
        machine_print(program.machine);
    }
    

    printf("\nWorld\n");
    return 0;
}