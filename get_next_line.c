/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:32:22 by erivero-          #+#    #+#             */
/*   Updated: 2023/05/11 13:17:44 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char	*str)
{
	char	*line;
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] != '\0' && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*ft_acumclean(char *acum)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (acum[i] != '\0' && acum[i] != '\n')
		i++;
	if (acum[i] == '\0')
	{
		free(acum);
		return (NULL);
	}
	new_line = ft_calloc((ft_strlen(acum) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (acum[i] != '\0')
		new_line[j++] = acum[i++];
	free(acum);
	if (new_line[0] == '\0')
	{
		free(new_line);
		return (NULL);
	}
	return (new_line);
}

static char	*ft_acum(char *st_ac, char *tmp)
{
	char	*acum;

	acum = ft_strjoin(st_ac, tmp);
	free(st_ac);
	return (acum);
}

static char	*ft_get_piece(char *st_ac, int fd)
{
	char	*tmp;
	int		read_return;

	if (!st_ac)
		st_ac = ft_calloc(1, sizeof(char));
	read_return = 1;
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (read_return > 0)
	{
		read_return = read(fd, tmp, BUFFER_SIZE);
		if (read_return < 0)
		{
			free(tmp);
			return (NULL);
		}
		tmp[read_return] = '\0';
		st_ac = ft_acum(st_ac, tmp);
		if (search_nline(tmp, '\n') != 0)
			break ;
	}
	free(tmp);
	return (st_ac);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*st_acum;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (st_acum != NULL)
		{
			free(st_acum);
			st_acum = NULL;
		}
		return (NULL);
	}	
	st_acum = ft_get_piece(st_acum, fd);
	line = ft_get_line(st_acum);
	st_acum = ft_acumclean(st_acum);
	return (line);
}
