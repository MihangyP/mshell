/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:26:37 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/22 09:07:32 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_MINISHELL_H
# define UTILS_MINISHELL_H

# include "../libft/libft.h"

char	**cpy_env(char **env);
int		mns_strcmp(char *s1, char *s2);
t_list	*get_env_lst(char **envp);
void	free_env_lst(t_list *env_lst);
int		lst_srch_var(t_list *lst, char *var_name);
void	mns_close_fds(int fd1, int fd2);

#endif
