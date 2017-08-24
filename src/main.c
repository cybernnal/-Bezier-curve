/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:46:15 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:28:40 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <tetris.h>
#include "tetris.h"

void    init_env(t_env *env)
{
    ft_bzero(env, sizeof(t_env));
}

t_env   *sig_env(t_env *env, int i)
{
    static t_env *e;

    if (i == 1)
        e = env;
    return (e);
}


int		main(int argc, char  **argv)
{
	t_env	env;

    sig_env(&env, 1);
	init_env(&env);
    if (argc >= 3)
    {
        if (!ft_strcmp(argv[1], "-i") || !ft_strcmp(argv[1], "--iterations"))
            env.iteration = ft_atoi(argv[2]);
        else
            env.iteration = ITER_MAX;
    }
    else
        env.iteration = ITER_MAX;
    while (render(&env));
	return (0);
}
