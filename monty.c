#include "monty.h"
#include <stdlib.h>
struct MontyGlobals MontyGlobals;
/**
 * push - entry point
 * @stack: stack
 * @line_number: counter
 */
void push(stack_t **stack, unsigned int line_number)
{
	char *global_value = MontyGlobals.global_value;
	stack_t *new_node;
	char *endptr;  /* For error checking in strtol */

	long num = strtol(global_value, &endptr, 10);

	if (*endptr != '\0' && !isspace((unsigned char)*endptr))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;

}
/**
 * pall - entry point
 * @stack: stack
 * @line_number: counter
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *current;  /* Move declaration to the beginning */

	current = *stack;

	(void)line_number;  /* Suppress unused parameter warning */

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
