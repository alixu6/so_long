/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:21:32 by axu               #+#    #+#             */
/*   Updated: 2024/03/26 15:01:33 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./sources/so_long.h"
#include "./bonus/so_long_bonus.h"

static char	*ft_read_fd(int fd, char *buffer, char *stock);
static char	*ft_get_line(char *line);

char	*get_next_line(int fd)
{
	static char	*stock = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line = ft_read_fd(fd, buffer, stock);
	free(buffer);
	buffer = NULL;
	if (line == NULL)
		return (NULL);
	stock = ft_get_line(line);
	return (line);
}

static char	*ft_read_fd(int fd, char *buffer, char *stock)
{
	char	*temp;
	int		bytes;

	bytes = 1;
	while (bytes != '\0')
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (stock == NULL)
			stock = ft_strdup("");
		temp = stock;
		stock = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stock);
}

static char	*ft_get_line(char *line)
{
	int		i;
	char	*stock;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	stock = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*stock == '\0')
	{
		free(stock);
		stock = NULL;
	}
	line[i + 1] = '\0';
	return (stock);
}

/*#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);

	if (fd < 0)
	{
		printf("Error");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close (fd);
	return (0);
}*/
