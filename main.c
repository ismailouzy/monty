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
	stack_t *stack = NULL;
	instruction_t instructions[] = {{"push", push}, {"pall", pall}};
	char opcode[100], *fmt = "L%d: %s %s\n";
	unsigned int line_number = 0, i;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE); }
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE); }
	while (fscanf(file, "%s", opcode) != EOF)
	{
		line_number++;
		for (i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++)
		{
			if (strcmp(opcode, instructions[i].opcode) == 0)
			{
				if (strcmp(instructions[i].opcode, "push") == 0 &&
						fscanf(file, "%s", global_value) != 1) {
					fprintf(stderr, fmt, line_number, "usage:", "push integer");
					return (EXIT_FAILURE); }
				instructions[i].f(&stack, line_number);
				break; }}
		if (i == sizeof(instructions) / sizeof(instructions[0]))
		{
			fprintf(stderr, fmt, line_number, "unknown instruction", opcode);
			return (EXIT_FAILURE); }}
	fclose(file);
	while (stack)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp); }
	return (0); }
