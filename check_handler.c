#include "monty.h"

/**
  * is_comment - checks if line is a comment.
  * @line - struct containing line content and number.
  *
  * Return: true if comment otherwise false.
  */
bool is_comment(line_t line)
{
	if (!line.content[0])
	{
		free(line.content);
		return (true);
	}

	if (line.content[0][0] == '#')
	{
		free(line.content);
		return (true);
	}

	return (false);
}

/**
  * check_argument - checks arg validity.
  * @token: argument to be checked.
  *
  * Return: true if valid otherwise false.
  */
bool check_argument(char *token)
{
	unsigned int i;

	if (!token)
		return (false);

	for (i = 0; token[i]; i++)
	{
		if (token[0] == '-')
			continue;
		if (token[i] < '0' || token[i] > '9')
		{
			return (false);
		}
	}

	return (true);
}


/**
  * check_push - check if push opcode is being used and sets
  * global argument variable if true.
  * @line: struct containg line content and number.
  * @opcode: opcode to compare.
  * @meta: struct containing all alocated memory.
  * @arg: struct containing argument parameters.
  *
  * Return: NAIN.
  */
void check_push(line_t line, meta_t *meta, char *opcode, arg_t *arg)
{
	if ((strcmp(opcode, "push") == 0) &&  !check_argument(line.content[1]))
	{
		free(line.content);
		fprintf(stderr, "L%d: usage: push integer\n", line.number);
		free(meta->buf);
		free_stack(&(meta->stack));
		fclose(meta->file);
		free(meta);
		exit(EXIT_FAILURE);
	}
	else if (strcmp(opcode, "push") == 0)
		arg.arg = atoi(line.content[1]);
}

/**
  * is_alpha - checks if int is an alphabet.
  * @c: int
  *
  * Return: 1 if yes, 0 otherwise.
  */
int is_alpha(int c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
		return (1);
	else
		return (0);
}
