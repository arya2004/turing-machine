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


// exprected value, value if true, direction if true,next if true, value if false, directoin if false, nxt if false
typedef struct main
{   
    bool exprected;

    bool write_yes;
    Direction dir_yes;
    size_t next_yes;

    bool write_no;
    Direction dir_no;
    size_t next_no;

}Instruction;

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
        machine->data[machine->head] = instruction->write_yes;
        machine->head += instruction->dir_yes;
        return instruction->next_yes;
    }
    machine->data[machine->head] = instruction->write_no;
    machine->head += instruction->dir_no;
    return instruction->next_no;
}

void machine_print(Machine *machine)
{
    for(size_t i = 0; i < machine->data_size; i++)
    {
        printf("%d -> ", machine->data[i]);
    }
    printf("\n");
}


int main()
{
    printf("Hellow\n");
    Machine machine = {0};
    machine.data_size = 3;
    machine.data = malloc(sizeof(bool)*machine.data_size);
    machine_randoize(&machine);

    Instruction inst[] = {
        {0, 1, RIGHT, 2, 0, RIGHT, 0},
        {NULL},
    };

    size_t inst_count = sizeof(inst)/ sizeof(*inst);
    size_t cur = 0;

    machine_print(&machine);
    while (cur <= inst_count - 1)
    {   
        cur = machine_execute(&machine, &inst[cur]);
        machine_print(&machine);
    }
    

    printf("\nWorld\n");
    return 0;
}