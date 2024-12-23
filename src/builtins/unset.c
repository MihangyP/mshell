/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:33:31 by pmihangy          #+#    #+#             */
/*   Updated: 2024/12/23 13:51:51 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_var_name(char *var)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '+' && var[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	while (j < i)
	{
		name[j] = var[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

int	my_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int lst_srch_var(t_lst *lst, char *var_name)
{
    char *tmp;
    t_lst *start;

    if (!lst || !var_name)
        return (0);

    start = lst; // Sauvegarde du point de départ
    while (1)
    {
        tmp = get_var_name((char *)lst->text);
        if (my_strcmp(tmp, var_name) == 0)
        {
            free(tmp);
            return (1); // Variable trouvée
        }
        free(tmp);

        lst = lst->next;
        if (lst == start) // Si on revient au début, on arrête
            break;
    }
    return (0); // Variable non trouvée
}

void remove_one(t_lst **env_lst, char *to_remove)
{
    t_lst *tmp;
    t_lst *prev;
    char *content;

    if (!env_lst || !*env_lst || !to_remove)
        return;

    tmp = *env_lst;
    while (1)
    {
        content = get_var_name((char *)tmp->text);
        if (my_strcmp(to_remove, content) == 0)
        {
            if (tmp->next == tmp) // Cas où il ne reste qu'un seul élément
            {
                free(content);
                free(tmp->text);
                free(tmp);
                *env_lst = NULL;
                return;
            }

            prev = tmp->prev;
            prev->next = tmp->next;
            tmp->next->prev = prev;

            if (*env_lst == tmp) // Cas où on supprime le premier élément
                *env_lst = tmp->next;

            free(content);
            free(tmp->text);
            free(tmp);
            return;
        }
        free(content);

        tmp = tmp->next;

        // Fin de la boucle si on a parcouru toute la liste sans trouver l'élément
        if (tmp == *env_lst)
            break;
    }
}

int unset_minishell(char **str, t_lst **env)
{
    int i;
    int exit_code;

    i = 1;
    exit_code = 0;
    if (!str || !env)
        return (1);
    while (str[i])
    {
        remove_one(env, str[i]);
        ++i;
    }
    return (exit_code);
}
/*
int	ft_unset(char **cmd, char ***env)
{
	t_list	*env_lst;
	int		i;

	i = 1;
	env_lst = get_env_lst(*env);
	while (cmd[i])
	{
		remove_one(&env_lst, cmd[i]);
		i++;
	}
	free_split(*env);
	*env = list_to_tab(env_lst);
	free_env_lst(env_lst);
	return (EXIT_SUCCESS);
}
*/

#if 0
bool syntax(char *str)
{
    int i;

    if (str[0] != '_' && !ft_isalpha(str[0]))
        return (false);
    i = 0;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (false);
        i++;
    }
    return (true);
}

void check_env(t_lst *tmp, t_lst **env)
{
    if (!tmp || !env || !(*env))  // Vérification de NULL
        return;

    if (tmp == (*env))
        (*env) = tmp->next;
    if (tmp->next == tmp)  // Vérification de la boucle infinie (seul élément dans la liste)
        (*env) = NULL;
}

t_lst *get_tmp(t_lst *env, char *str)
{
    t_lst *tmp = NULL;
    t_lst *curr = env;

    if (!env)  // Vérification si l'environnement est NULL
        return NULL;

    while (curr->next != env)  // Traversée de la liste chaînée circulaire
    {
        if (curr->text && !ft_strncmp(str, get_key(curr->text), INT_MAX))
        {
            tmp = curr;
            break;
        }
        curr = curr->next;
    }
    if (curr->text && !ft_strncmp(str, get_key(curr->text), INT_MAX))  // Dernière comparaison
        tmp = curr;

    return tmp;
}

t_status unset(char *str, t_lst **env)
{
    t_lst *tmp;

    if (!str || !(*str))  // Vérification si str est vide ou NULL
        return (FAIL);

    if (!syntax(str))  // Vérification de la syntaxe de la variable
    {
        print_error("unset: not a valid identifier\n");
        return (FAIL);
    }

    if (!exist_in_env(str, *env))  // Si la variable n'existe pas dans l'environnement
        return (SUCCESS);

    tmp = get_tmp(*env, str);
    if (!tmp)  // Vérification si tmp est NULL (au cas où l'élément n'a pas été trouvé)
        return (FAIL);

    // Re-link the surrounding elements to bypass the one being deleted
    if (tmp->prev)
        tmp->prev->next = tmp->next;  // Previous element points to next
    if (tmp->next)
        tmp->next->prev = tmp->prev;  // Next element points to previous

    // Si on supprime le premier ou le dernier élément (c'est une liste circulaire)
    if (tmp == *env)
    {
        // Si l'élément à supprimer est le seul dans la liste
        if (tmp->next == tmp)
        {
            *env = NULL;  // Liste devient vide
        }
        else
        {
            *env = tmp->next;  // Mise à jour du pointeur vers le premier élément
        }
    }

    free(tmp->text);  // Libérer la mémoire de la variable
    check_env(tmp, env);  // Mise à jour de l'environnement
    free(tmp);  // Libération de la mémoire de la structure

    return (SUCCESS);
}


int unset_minishell(char **str, t_lst **env)
{
    int exit_code = 0;
    int i = 1;  // Démarrer à 1 pour ignorer le premier argument (nom de la commande)

    if (!str || !env)  // Vérification si les arguments sont NULL
        return (FAIL);

    while (str[i])  // Traitement de chaque argument
    {
        if (!unset(str[i], env))  // Si la suppression échoue
            exit_code = 1;
        i++;
    }
    return (exit_code);
}
#endif