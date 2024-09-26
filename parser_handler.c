#include "monty.h"

/**
  * parseline - Parses and tokenizes a line of text, storing
  * the tokens in a line struct.
  * @line: Pointer to the struct containing content and line number.
  * @buffer: String of text read from the script file.
  *
  * Return: Nothing.
  */
void parseline(line_t *line, char *buffer)
{
	unsigned int i;
	char *token = NULL;

	line->content = malloc(sizeof(char *) * 3);
	if (!line->content)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, " '\n'");
	for (i = 0; token && i < 2; i++)
	{
		line->content[i] = token;
		token = strtok(NULL, " \n");
	}

	line->content[i] = NULL;
}

/**
  * parsefile - Reads and parses a file line by line.
  * @file: Pointer to the script file to be read.
  *
  * Return: Nothing.
  */
void parsefile(FILE *file)
{
	size_t size = 0;
	meta_t *meta = NULL;
	line_t line;

	meta = malloc(sizeof(meta_t));
	if (!meta)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	line.number = 0;
	line.content = NULL;

	meta->file = file;
	meta->stack = NULL;
	meta->buf = NULL;

	while (getline(&(meta->buf), &size, meta->file) != -1)
	{
		line.number++;
		parseline(&line, meta->buf);
		if (line.content)
			get_op_func(line, meta)(&(meta->stack), line.number);
	}

	free(meta->buf);
	free_stack(&(meta->stack));
	fclose(meta->file);
	free(meta);
}
