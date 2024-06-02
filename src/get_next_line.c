/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxborde <maxborde@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:25:25 by maxborde          #+#    #+#             */
/*   Updated: 2024/06/02 20:28:34 by maxborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxborde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:46:14 by maxborde          #+#    #+#             */
/*   Updated: 2023/11/07 23:52:07 by maxborde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen_m(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr_m(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin_m(char *left_str, char *buff)
{
	char	*string;
	int		i;
	int		k;

	if (!left_str)
	{
		left_str = malloc(sizeof(char) * 1);
		left_str[0] = 0;
	}
	if (!buff)
		return (NULL);
	string = malloc(sizeof(char) * (ft_strlen(left_str) + ft_strlen(buff) + 1));
	if (!string)
		return (NULL);
	i = -1;
	k = -1;
	while (left_str[++i])
		string[i] = left_str[i];
	while (buff[++k])
		string[i + k] = buff[k];
	free(left_str);
	string[i + k] = 0;
	return (string);
}

char	*get_dirty_line(int fd, char *buffer)
{
	char	*dirtyline;
	int		charsread;

	charsread = 1;
	dirtyline = NULL;
	dirtyline = ft_strjoin_m(dirtyline, buffer);
	while (!ft_strchr_m(dirtyline, '\n') && charsread != 0)
	{
		charsread = read(fd, buffer, BUFFER_SIZE);
		if (charsread == -1)
		{
			buffer[0] = 0;
			free(dirtyline);
			return (NULL);
		}
		buffer[charsread] = 0;
		dirtyline = ft_strjoin_m(dirtyline, buffer);
	}
	if (!ft_strlen_m(dirtyline) && charsread == 0)
	{
		free(dirtyline);
		return (NULL);
	}
	return (dirtyline);
}

char	*get_clean_line(char *remainder)
{
	char	*str;
	int		i;
	int		y;	

	i = 0;
	y = -1;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (++y < i)
		str[y] = remainder[y];
	str[y] = 0;
	free(remainder);
	return (str);
}

void	clean_up_buffer(char *buffer)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i])
		buffer[k++] = buffer[i++];
	buffer[k] = 0;
}

char	*get_next_line_m(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*dirtyline;
	char		*cleanline;

	dirtyline = get_dirty_line(fd, buffer);
	if (!dirtyline)
		return (NULL);
	cleanline = get_clean_line(dirtyline);
	if (!cleanline)
	{
		free(dirtyline);
		return (NULL);
	}
	clean_up_buffer(buffer);
	return (cleanline);
}
