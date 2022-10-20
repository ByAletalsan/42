/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:10:45 by atalaver          #+#    #+#             */
/*   Updated: 2022/10/20 20:16:19 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//Los calloc no hacen falta con if ya que la propia funcion lo hace 
//
//Concatenamos y liberamos el antiguo
static char	*ft_add_and_free(char *str, char *buff)
{
	char	*r;

	r = ft_strjoin(str, buff);
	free(str);
	return (r);
}

//Funcion que acumula de buffer_size en buffer_size hasta encontrar un \n o fin
static char	*ft_read_buffer_to_n(int fd, char *str)
{
	char	*buff;
	int		read_char;

	if (!str)
		str = calloc(1, sizeof(char));
	buff = calloc((BUFFER_SIZE + 1), sizeof(char));
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
		if (ft_chr_exist(buff, '\n'))
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
	r = calloc((i + 2), sizeof(char));
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
	r = calloc((ft_strlen(str) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (str[i] != '\0')
		r[j++] = str[i++];
	free(str);
	return (r);
}

//Funcion principal
char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*r;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd > 1024)
		return (NULL);
	str[fd] = ft_read_buffer_to_n(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	r = ft_read_line(str[fd]);
	str[fd] = ft_remove_line(str[fd]);
	return (r);
}
