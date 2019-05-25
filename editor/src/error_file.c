/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkachano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 20:59:53 by mkachano          #+#    #+#             */
/*   Updated: 2019/05/25 20:59:55 by mkachano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/level_editor.h"

void		error_open_file(char *path)
{
	char	*str;
	char	*tmp;

	str = ft_strnew(1);
	tmp = ft_strjoin(str, "[ERROR]: ");
	free(str);
	str = ft_strjoin(tmp, "File is not exist");
	free(tmp);
	tmp = ft_strjoin(str, " File name: ");
	free(str);
	str = ft_strjoin(tmp, path);
	free(tmp);
	tmp = ft_strjoin(str, "\n");
	free(str);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	exit(1);
}

void		error_folder(char *path)
{
	char	*str;
	char	*tmp;

	str = ft_strnew(1);
	tmp = ft_strjoin(str, "[ERROR]: File can't be a folder. ");
	free(str);
	str = ft_strjoin(tmp, path);
	free(tmp);
	tmp = ft_strjoin(str, "\n");
	free(str);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	exit(1);
}

