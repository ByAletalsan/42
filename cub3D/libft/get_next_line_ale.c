/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:10:45 by atalaver          #+#    #+#             */
/*   Updated: 2023/09/21 15:05:28 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_ale.h"

//Los calloc no hacen falta con if ya que la propia funcion lo hace 
//
//Concatenamos y liberamos el antiguo
static char	*ft_add_and_free(char *str, char *buff)
{
	char	*r;

	r = ft_strjoin_ale(str, buff);
	free(str);
	return (r);
}

//Funcion que acumula de buffer_size en buffer_size hasta encontrar un \n o fin
static char	*ft_read_buffer_to_n(int fd, char *str)
{
	char	*buff;
	int		read_char;

	if (!str)
		str = ft_calloc_ale(1, sizeof(char));
	buff = ft_calloc_ale((BUFFER_SIZE + 1), sizeof(char));
	read_char = 1;
	while (read_char > 0)
	{
		read_char = read(fd, buff, BUFFER_SIZE);
		if (read_char < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[read_char] = '\0';
		str = ft_add_and_free(str, buff);
		if (ft_chr_exist_ale(buff, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

//De la acumulacion anterior intentamos sacar una linea acabada en \n o fin
static char	*ft_read_line(char *str)
{
	char	*r;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	r = ft_calloc_ale((i + 2), sizeof(char));
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		r[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
		r[i++] = '\n';
	return (r);
}

//Quitamos la linea encontrada y dejamos lo sobrante
static char	*ft_remove_line(char *str)
{
	int		i;
	int		j;
	char	*r;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	r = ft_calloc_ale((ft_strlen_ale(str) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (str[i] != '\0')
		r[j++] = str[i++];
	free(str);
	if (r[0] == '\0')
	{
		free(r);
		return (NULL);
	}
	return (r);
}

//Funcion principal
char	*get_next_line_ale(int fd)
{
	static char	*str;
	char		*r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str != NULL)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	str = ft_read_buffer_to_n(fd, str);
	r = ft_read_line(str);
	str = ft_remove_line(str);
	return (r);
}
