#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 2048
/**
  * input_buf - entry point
  * Return: 0 on success
  */
char *input_buf(const char *file_r_path, char *buf)
{
	int buffer_size = BUFSIZE;
	int offset = 0;
	int total, bytes_read;
	int file_r;
	char *tmp_ptr;

	total = bytes_read = 1;
	file_r = open(file_r_path, O_RDONLY);
	if (file_r == -1)
		perror("Could Not Open."), exit(98);
	while(bytes_read > 0)
	{
		bytes_read = read(file_r, buf + offset, BUFSIZE);
		total += bytes_read;
		if (total + bytes_read >= buffer_size)
		{
			offset += BUFSIZE;
			buffer_size += BUFSIZE;
			tmp_ptr = realloc(buf, buffer_size * sizeof(char));
			if (tmp_ptr)
				buf = tmp_ptr;
			else
				exit(97);
		}
	}
	buf[total] = '\0';
	close(file_r);
	return (buf);
}
/**
  * main - entry point
  * Return: 0 on success
  */
int main(int ac, char *av[])
{
	char *buf, *filepath;

	if (ac != 2)
		printf("Usage: %s <filepath>/file\n", av[0]), exit(1);
	else if (access(av[1], W_OK))
		printf("Error: File Not Found\n"), exit(2);

	filepath = av[1];
	buf = malloc(BUFSIZE * sizeof(char));
	if (!buf)
		exit(97);
	buf = input_buf(filepath, buf);
	if (!buf)
		exit(99);
	printf("%s", buf);
	free(buf);
	return (0);
}
