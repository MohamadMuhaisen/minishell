/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:37:18 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/10 20:15:31 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		buffer = NULL;
	}
	if (!buffer)
		return (NULL);
	line = extract_line(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = fill_stash(line);
	return (line);
}

char	*fill_stash(char *str)
{
	char	*stash;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
		return (0);
	stash = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	str[i + 1] = 0;
	return (stash);
}

char	*extract_line(int fd, char *stash, char *buffer)
{
	ssize_t	chars_read;
	char	*str;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{	
			free(stash);
			return (0);
		}
		else if (chars_read == 0)
			break ;
		buffer[chars_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		str = stash;
		stash = ft_strjoin(str, buffer);
		free(str);
		str = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len++;
	return (len);
}

// int main(void)
// {
//     int fd;
//     char *line;
//     fd = open("test.txt", O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return 1;
//     }
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line); 
//     }
//     close(fd);
//     return 0;
// }
