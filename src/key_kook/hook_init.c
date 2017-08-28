/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:16:40 by tbillard          #+#    #+#             */
/*   Updated: 2017/03/18 16:17:38 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bezier.h"

int             ft_exit(t_env *e)
{
    exit (0);
}


int		nil(t_env *env)
{
    return (0);
}

int     ft_start(t_env *e)
{
    e->is_draw = 1;
    return (0);
}


int     ft_restart(t_env *e)
{
    int it = e->iteration;
    int sleep = e->sleep;
    int nrand = e->nrand;

    if (e->first_point)
    {
        e->point = e->first_point;
        while (e->first_point->next)
        {
            e->point = e->point->next;
            ft_memdel((void**)&e->first_point);
            e->first_point = e->point;
        }
        ft_memdel((void**)&e->first_point);
    }
    ft_bzero(e, sizeof(t_env));
    e->is_init = -1;

    e->iteration = it;
    e->sleep = sleep;
    e->nrand = nrand;
    return (0);
}


void		ft_tab_ft_init_1(int (**tab_ft)(t_env*))
{
	tab_ft[SDLK_ESCAPE] = &ft_exit;
    tab_ft[SDLK_s] = &ft_start;
    tab_ft[SDLK_r] = &ft_restart;
}
