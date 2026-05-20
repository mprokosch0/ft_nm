/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprokosc <mprokosc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:24:19 by mprokosc          #+#    #+#             */
/*   Updated: 2025/05/29 16:22:39 by mprokosc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_and_free(char *dest, char *buffer)
{
	char	*tmp;

	if (dest)
		tmp = dest;
	else
		tmp = "";
	tmp = ft_strjoin(tmp, buffer);
	free(dest);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*fill_buffer(int fd, char *dest)
{
	char	*buffer;
	int		rf;

	rf = 1;
	if (!dest)
	{
		dest = ft_calloc(1, sizeof(char));
		if (!dest)
			return (NULL);
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (rf)
	{
		rf = read(fd, buffer, BUFFER_SIZE);
		if (rf < 0)
			return (free(buffer), NULL);
		buffer[rf] = '\0';
		dest = join_and_free(dest, buffer);
		if (!dest || ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (dest);
}

static char	*fill_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*newb(char *buffer)
{
	char	*new;
	int		j;
	int		i;

	if (!buffer || !ft_strchr(buffer, '\n'))
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!new)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		new[j++] = buffer[i++];
	free(buffer);
	if (new[0] == '\0')
		return (free(new), NULL);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = fill_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = fill_line(buffer);
	buffer = newb(buffer);
	return (line);
}

/*int   main()
{
	int fd2 = open("test.txt", O_RDONLY);
        if (fd2 == -1)
                return (0);
        char    *line;
        int l = 1;
	while (l--)
        {
		line = get_next_line(fd2);
                printf("%s", line);
                free(line);
        }
	get_next_line(9);
	close(fd2);
        return (0);
}*/
