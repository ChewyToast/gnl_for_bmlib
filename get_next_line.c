/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:24 by bmoll-pe          #+#    #+#             */
/*   Updated: 2022/07/12 23:25:45 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(const int fd)
{
	char		*rtrn_buff;
	static char	*total_buff;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (!total_buff || !check_nl(total_buff))
		total_buff = ft_read(fd, total_buff);
	if (!total_buff)
		return (NULL);
	rtrn_buff = copy_line(total_buff);
	if (!rtrn_buff)
	{
		free(total_buff);
		return (NULL);
	}
	total_buff = cut_static(total_buff);
	if (!total_buff)
		free(total_buff);
	return (rtrn_buff);
}

char	*ft_read(const int fd, char *total_buff)
{
	char	*tmp;
	ssize_t	chk;

	chk = 1;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	while (chk > 0 && !check_nl(total_buff))
	{
		chk = read(fd, tmp, BUFFER_SIZE);
		if (chk > 0)
		{
			tmp[chk] = '\0';
			total_buff = ft_strjoin(total_buff, tmp,
					ft_strlen(total_buff), ft_strlen(tmp));
		}
	}
	free(tmp);
	if (chk == -1)
		return (NULL);
	return (total_buff);
}

char	*copy_line(char *total_buff)
{
	char	*rtrn_buff;
	size_t	size;

	size = 0;
	while (total_buff[size] && total_buff[size] != '\n')
		size++;
	if (total_buff[size] == '\n')
		rtrn_buff = ft_substr(total_buff, 0, size + 1);
	else
		rtrn_buff = ft_substr(total_buff, 0, size);
	return (rtrn_buff);
}

char	*cut_static(char *total_buff)
{
	char	*new_buff;
	size_t	indx;

	indx = 0;
	while (total_buff[indx] != '\n' && total_buff[indx] != '\0')
		indx++;
	if (total_buff[indx] == '\n' && total_buff[indx + 1] != '\0')
	{
		indx++;
		new_buff = ft_substr(total_buff, indx, ft_strlen(total_buff) - indx);
	}
	else
		new_buff = NULL;
	free (total_buff);
	return (new_buff);
}
