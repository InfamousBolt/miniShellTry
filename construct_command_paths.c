/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_command_paths.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:06:55 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/22 11:58:13 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

char	*command_not_found(char *command)
{
	if (! is_builtin(command))
		printf("\nCommand '%s' not found!\n", command);
	g_env.exit_status = 127;
	return (NULL);
}

char	*find_path(char *system_paths, char *command)
{
	struct stat	info;
	char		temp[1000];
	char		*ptr;
	int			i;

	ptr = temp;
	memset(temp, 0, 1000);
	if (stat(command, &info) != -1)
		return (ft_strdup(command));
	while (*system_paths && !is_builtin(command))
	{
		*(ptr++) = *(system_paths++);
		if (*system_paths == ':' || *system_paths == '\0')
		{
			if (*system_paths == ':')
				system_paths++;
			i = 0;
			*(ptr++) = '/';
			while (*(command + i))
				*(ptr++) = *(command + i++);
			ptr = temp;
			if (stat(ptr, &info) != -1)
				return (ft_strdup(ptr));
			memset(temp, 0, 1000);
		}
	}
	return (command_not_found(command));
}

char	*find_system_paths(char *variable)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		if (!ft_strncmp(*(g_env.env_var + i), variable, ft_strlen(variable)))
		{
			j = 0;
			while (j < ft_strlen(variable) + 1 && *(*(g_env.env_var + i) + j))
				j++;
			return (strdup(*(g_env.env_var + i) + j));
		}
		i++;
	}
	return (NULL);
}

void	allocate_paths(t_instructions *instructions)
{
	instructions->command_paths
		= (char **)ft_calloc(instructions->n_commands + 1, sizeof(char *));
	if (! instructions->command_paths)
	{
		perror("Problem allocating command paths");
		exit(1);
	}
}

int	construct_paths(t_instructions *instructions)
{
	char	*system_paths;
	char	**paths_ptr;
	int		i;

	system_paths = find_system_paths("PATH");
	allocate_paths(instructions);
	paths_ptr = instructions->command_paths;
	i = 0;
	while (i < instructions->n_commands)
	{
		*(paths_ptr + i) = find_path(system_paths,
				**(instructions->tokens + i));
		if (!*(paths_ptr + i) && !is_builtin(**(instructions->tokens + i)))
		{
			free(system_paths);
			return (0);
		}
		i++;
	}
	free(system_paths);
	return (1);
}
