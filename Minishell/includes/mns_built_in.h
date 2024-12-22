/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_built_in.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:16:19 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/17 10:34:37 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_BUILT_IN_H
# define MNS_BUILT_IN_H

# include "../libft/libft.h"
# include "mns_struct_define.h"

int	mns_cd(char **cmd, char ***env);
int	ft_pwd(char **args, char **env);
int	ft_echo(char **args);
int	ft_env(char **env, char **cmd);
int	ft_export(char **cmd, char ***env);
int	ft_unset(char **cmd, char ***env);
int	ft_exit(char **cmd, t_ast_node *ast, char **envp, int flag);

#endif