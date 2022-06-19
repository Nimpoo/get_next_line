/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayoub <mayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:22:58 by mayoub            #+#    #+#             */
/*   Updated: 2022/01/28 12:09:07 by mayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ini_getline(int fd, char *save)
{
	int			ret;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	ret = 1;
	while (ret != 0 && ft_strchr(save, '\n') == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*get_line(char *save)
{
	char	*str;
	int		i;

	i = 0;
	if (save[0] == '\0')
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = malloc(i + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*new_line(char *save)
{
	char			*buf;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	buf = malloc(ft_strlen(save) - i + 1);
	if (buf == NULL)
		return (NULL);
	i++;
	while (save[i])
		buf[j++] = save[i++];
	buf[j] = '\0';
	free(save);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ini_getline(fd, save);
	if (save == NULL)
		return (NULL);
	line = get_line(save);
	if (!save)
		return (line);
	save = new_line(save);
	return (line);
}
