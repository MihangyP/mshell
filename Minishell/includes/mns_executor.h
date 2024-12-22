/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_executor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:35:46 by trarijam          #+#    #+#             */
/*   Updated: 2024/10/22 09:11:31 by traveloa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_EXECUTOR_H
# define MNS_EXECUTOR_H

# include "mns_struct_define.h"

int		check_redirection_exec(t_ast_node *ast, char **envp,
			int in_pipe, int flag);
char	**find_path_list(char **env);
char	*find_path(char **path_list, char *cmd);
void	free_split(char **str);
void	exec_cmd(char **envp, t_ast_node *ast, t_exec_status *status);
void	executor(char **envp, t_ast_node *ast, t_exec_status *status);
int		check_n_exec_built_in1(char **cmd, char **env, int *flag);
int		check_n_exec_built_in(char **cmd, char **env,
			t_ast_node *ast, int *flag);
char	**check_void_cmd(char **cmd, char **envp, t_ast_node *ast);
void	execute(t_ast_node *ast, char **envp, char **cmd, int *flag);
int		check_directory_error(char *path, char *cmd);
void	wait_pipe_cmd(int fd[2], t_exec_status *status, int pid, int pid1);

#endif
