/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils_built_in.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:23:43 by trarijam          #+#    #+#             */
/*   Updated: 2024/12/15 20:25:22 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_UTILS_BUILT_IN_H
# define MNS_UTILS_BUILT_IN_H

# include "../libft/libft.h"

void	handle_built_in_cmd(t_ast_node *ast, char ***envp, t_data *data);
void	handle_ast(t_data *data);
char	**list_to_tab(t_list *env_lst);
void	sort_env_lst(t_list	**env_lst);
t_list	*get_env_lst(char **envp);
t_list	*get_env_lst(char **envp);
char	**list_to_tab(t_list *env_lst);
void	print_export(t_list *env_lst);
void	print_var_value(char *value, int i, t_list *env_lst);
int		check_var_name(char *name);
char	*get_var_name(char *var);
char	*get_var_value(char *var);

#endif