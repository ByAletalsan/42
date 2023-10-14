/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:33 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/03/31 01:34:06 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_fd(int fd, char *buff, size_t *eof, ssize_t bytes_read)
{
	if (!buff)
	{
		buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buff == NULL)
			return (NULL);
		*buff = '\0';
	}
	if (fd < 0 || BUFFER_SIZE < 0)
	{
		if (buff != NULL)
			free(buff);
		return (NULL);
	}
	if (*buff == '\0' && *eof == 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == 0)
				*eof = 1;
			return (free(buff), NULL);
		}
		buff[bytes_read] = '\0';
	}
	return (buff);
}

char	*save_line(char *line, char *buff, size_t i)
{
	char	*aux;
	char	*aux_line;

	if (line == NULL)
	{
		line = (char *)malloc(1);
		if (line == NULL)
			return (NULL);
		line[0] = '\0';
	}
	aux = ft_substr(buff, 0, i);
	if (aux == NULL)
	{
		if (line != NULL)
			free(line);
		return (NULL);
	}
	aux_line = line;
	line = ft_strjoin(line, aux);
	free(aux);
	if (line == NULL)
		return (free(aux_line), NULL);
	return (free(aux_line), line);
}

char	*make_line(char *line, char *buff, size_t size, size_t eof)
{
	size_t	j;

	if (eof == 1)
	{
		line = save_line(line, buff, size);
		if (*line == '\0')
			return (free (line), NULL);
		if (line == NULL)
			return (NULL);
	}
	else
	{
		line = save_line(line, buff, size);
		if (line == NULL)
			return (NULL);
		j = 0;
		while (buff[size] != '\0')
			buff[j++] = buff[size++];
		buff[j] = '\0';
	}
	return (line);
}

char	*build_line(char *buff, char *line, ssize_t *line_complete, size_t eof)
{
	size_t	i;

	i = 0;
	while ((buff[i] != '\0' && buff != NULL) && *line_complete == 0)
	{
		if (buff[i] == '\n')
		{
			line = make_line(line, buff, i + 1, eof);
			if (line == NULL)
				return (NULL);
			*line_complete = 1;
		}
		i++;
	}
	if (*line_complete == 0)
	{
		if (eof)
			line = make_line(line, "\0", 1, eof);
		else
			line = make_line(line, buff, i, eof);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	ssize_t		line_complete;
	size_t		eof;

	eof = 0;
	line_complete = 0;
	line = NULL;
	while (line_complete == 0 && !eof)
	{
		buff = read_fd(fd, buff, &eof, 0);
		if (buff == NULL && !eof)
		{
			if (line != NULL)
				free(line);
			return (NULL);
		}
		if (eof)
			line = build_line("\0", line, &line_complete, eof);
		else
			line = build_line(buff, line, &line_complete, eof);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}
