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
#include <bezier.h>
#include "bezier.h"

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
    int i = 1;

    sig_env(&env, 1);
	init_env(&env);
    if (argc >= 3)
    {
        while (1)
        {
            if (!ft_strcmp(argv[i], "-i") || !ft_strcmp(argv[i], "--iterations"))
            {
                i++;
                if (!argv[i])
                    break;
                env.iteration = ft_atoi(argv[i++]);
            }
            else if (!ft_strcmp(argv[i], "-r") || !ft_strcmp(argv[i], "--random"))
            {
                i++;
                if (!argv[i])
                    break;
                env.nrand = ft_atoi(argv[i++]);
            }
            else if (!ft_strcmp(argv[i], "-s") || !ft_strcmp(argv[i], "--sleep"))
            {
                i++;
                if (!argv[i])
                    break;
                env.sleep = ft_atoi(argv[i++]);
            }
            else
                break ;
            if (i >= argc)
                break;
        }
    }
    if (!env.iteration)
        env.iteration = ITER_MAX;

    while (render(&env));
	return (0);
}
