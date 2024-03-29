#include "monty.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: args
 * Return: Success
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char *global_value = MontyGlobals.global_value;
	stack_t *stack = NULL;
	instruction_t instructions[] = {{"push", push}, {"pall", pall}, 
		{"pint", pint}, {"pop", pop}, {"swap", swap}, {"add", add},
		{"nop", nop}, {"sub", sub}, {"div", div_op}, {"mul", mul},
		{"mod", mod}};
	char opcode[100], *fmt = "L%d: %s %s\n";
	unsigned int line_number = 0, i;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while (fscanf(file, "%s", opcode) != EOF)
	{
		line_number++;
		if (opcode[0] == '#')
		{
			char ar;
			while ((ar = fgetc(file)) != EOF && ar != '\n')
				;
			continue;
		}
		for (i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				if (strcmp(instructions[i].opcode, "push") == 0 &&
						fscanf(file, "%s", global_value) != 1)
				{
					fprintf(stderr, fmt, line_number, "usage:", "push integer");
					fclose(file);
					free_stack(&stack);
					return (EXIT_FAILURE);
				}

				instructions[i].f(&stack, line_number);
				break;
			}
		}

		if (i == sizeof(instructions) / sizeof(instructions[0]))
		{
			fprintf(stderr, fmt, line_number, "unknown instruction", opcode);
			fclose(file);
			free_stack(&stack);
			return (EXIT_FAILURE);
		}
	}

	fclose(file);
	free_stack(&stack);

	return (0);
}

