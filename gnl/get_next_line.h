/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:53:28 by gdaignea          #+#    #+#             */
/*   Updated: 2024/05/30 18:13:51 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../include/minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//UTILS
char	*ft_strjoin_and_free(char *s1, char *s2);

//FONCTION
char	*get_next_line(int fd);
char	*extract_line(char *stash);
char	*free_stash(char *stash);
char	*read_fd(int fd, char *stash);

#endif