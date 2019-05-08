#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argc, char *argv[])
{
  // Parse command line
  char *dir_name;
  // no argument recieved
  if (argc != 2)
  {
    fprintf(stderr, "usage: ./ls8 filename.file\n");
    exit(1);
  }
  else if (argc == 2)
  {
    dir_name = argv[1];
  }

  FILE *fp;
  char line[1024];
  int address = 0;

  fp = fopen(dir_name, "r");

  if (fp == NULL)
  {
    fprintf(stderr, "comp: error opening file\n");
    exit(1);
  }

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char *endptr;
    unsigned int val = strtoul(line, &endptr, 2);

    if (endptr == line)
    {
      //printf("Found no digits\n");
      continue;
    }
    cpu->ram[address] = val;
    address++;
  }
  fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Helper Functions
 */
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address)
{
  return cpu->ram[address];
}

unsigned char cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value)
{
  cpu->ram[address] = value;
  return cpu->ram[address];
}
/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // unsigned char instruction_register = cpu->ram[cpu->pc];
    unsigned char instruction_register = cpu_ram_read(cpu, cpu->pc);
    // 2. Figure out how many operands this next instruction requires
    unsigned int num_operands = instruction_register >> 6;
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);
    // 4. switch() over it to decide on a course of action.
    switch (instruction_register)
    {
    case HLT:
      running = 0;
      break;
    case LDI:
      cpu->registers[operandA] = operandB;
      cpu->pc += num_operands + 1;
      break;
    case PRN:
      printf("Number %d\n", cpu->registers[operandA]);
      cpu->pc += num_operands + 1;
      break;
    default:
      printf("Unknown instruction at %d: %d\n", cpu->pc, instruction_register);
      break;
    }
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  // *cpu->registers = malloc(8 * sizeof(cpu->registers[0]));
  // *cpu->ram = malloc(256 * sizeof(cpu->ram[0]));
  // *cpu->registers = 0;
  // *cpu->ram = 0;
  // same as above just lets use set value to 0
  memset(cpu->registers, 0, 8 * sizeof(cpu->registers[0]));
  memset(cpu->ram, 0, 256 * sizeof(cpu->ram[0]));
}
