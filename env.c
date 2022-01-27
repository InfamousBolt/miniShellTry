/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshav <keshav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:00:57 by amalecki          #+#    #+#             */
/*   Updated: 2022/01/27 22:36:41 by keshav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_environment	g_env;

void	env(t_instructions instructions)
{
	int	i;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		if (ft_strlen(*(g_env.env_var + i)))
			printf("%s\n", *(g_env.env_var + i));
		i++;
	}
	g_env.exit_status = 0;
	clean_up_and_exit(instructions, true, true);
}

void	env_extended(void)
{
	int	i;

	i = 0;
	while (g_env.env_var && *(g_env.env_var + i))
	{
		if (ft_strlen(*(g_env.env_var + i)))
		{
			printf("%s", "declare -x ");
			printf("%s\n", *(g_env.env_var + i));
		}
		i++;
	}
	g_env.exit_status = 1;
}
