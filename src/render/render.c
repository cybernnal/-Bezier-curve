/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:50:22 by tbillard          #+#    #+#             */
/*   Updated: 2017/03/18 18:50:23 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bezier.h"

uint32_t color[7] = {0xFF0000, 0x00FFFF, 0xED7F10, 0xFFFF00, 0x00FF00, 0xAFAFAF, 0x0000FF};


static void     get_mouse_coor(int x, int y, t_env *env)
{
    int i = 0;
    t_point *tmp;
    env->point = env->first_point;
    if (x < 0 || x > WIN_X || y < 0 || y > WIN_Y)
        return;
    while (env->point)
    {
        tmp = env->point;
        env->point = env->point->next;
        i++;
    }
    if (i == 0)
    {
        env->point = (t_point*)ft_memalloc(sizeof(t_point));
        env->first_point = env->point;
    }
    else
    {
        env->point = tmp;
        env->point->next = (t_point*)ft_memalloc(sizeof(t_point));
        env->point = env->point->next;
    }
    env->point->x = x;
    env->point->y = y;
}

static void drawcircle(int x0, int y0, int radius, Uint32 color, t_window *w)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        draw_pixel(x0 + x, y0 + y, color, w);
        draw_pixel(x0 + y, y0 + x, color, w);
        draw_pixel(x0 - y, y0 + x, color, w);
        draw_pixel(x0 - x, y0 + y, color, w);
        draw_pixel(x0 - x, y0 - y, color, w);
        draw_pixel(x0 - y, y0 - x, color, w);
        draw_pixel(x0 + y, y0 - x, color, w);
        draw_pixel(x0 + x, y0 - y, color, w);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}

void draw_full_circle(int x0, int y0, int radius, Uint32 color, t_window *w)
{
    for (int i = 0 ; i <= radius ; i++)
        drawcircle(x0, y0, i, color, w);
}

static int      mouse_hit(t_env *env)
{
    int x;
    int y;

    x = 0;
    y = 0;
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        get_mouse_coor(x, y, env);
        env->nb_point++;
        usleep(200000);
        return (1);
    }
    return (0);
}

static void         get_point(t_window *w, t_env *e)
{
    t_line l;
    l.x0 = -1;

    mouse_hit(e);
    e->point = e->first_point;
    while (e->point)
    {
        draw_full_circle(e->point->x, e->point->y, 3, color[1], w);
        if (l.x0 != -1)
        {
            l.y1 = e->point->y;
            l.x1 = e->point->x;
            l.color = color[0];
            line(l,w);
        }
        l.x0 = e->point->x;
        l.y0 = e->point->y;
        e->point = e->point->next;
    }
}

static t_corr     draw_bezier(t_window *w, t_env *e, t_point *point, t_point *first, int rec)
{
    static int i = 0;
    t_point *p2;
    t_point *f2;
    t_corr  coor;
    int     n = 0;

    coor.y = 0;
    coor.x = 0;
    point = first;
    t_line l;

    p2 = NULL;
    if (i > e->iteration)
        i = e->iteration;
    l.x0 = -1;
    while (point)
    {
        if (l.x0 != -1)
        {
            l.y1 = point->y;
            l.x1 = point->x;
            l.color = color[rec % 7];
            line(l, w);
            float dist = (float) sqrt(pow(l.x1 - l.x0, 2) + pow(l.y1 - l.y0, 2));
            if (!p2)
            {
                coor = place_point(l, e, w, dist - L_CF(i, 0, e->iteration, 0, dist), 1, coor);
                p2 = (t_point*)ft_memalloc(sizeof(t_point));
                f2 = p2;
            }
            else
            {
                coor = place_point(l, e, w, dist - L_CF(i, 0, e->iteration, 0, dist), 0, coor);
                p2->next = (t_point*)ft_memalloc(sizeof(t_point));
                p2 = p2->next;
            }
            p2->x = coor.x;
            p2->y = coor.y;
        }
        l.x0 = point->x;
        l.y0 = point->y;
        point = point->next;
        n++;
    }
    if (rec < e->nb_point - 1)
    {
        if (rec < e->nb_point - 2)
            coor = draw_bezier(w, e, p2, f2, rec + 1);
        else
            draw_bezier(w, e, p2, f2, rec + 1);
    }
    i++;
    return (coor);
}

int					render(t_env *env)
{
	static t_window w;
    static t_point *p = NULL;
    static t_point *f = NULL;
    t_corr coor;
    t_line l;

	if (!w.is_init)
	{
		init_window(&w);
		w.is_init = 1;
	}
    bzero(w.img_ptr, sizeof(Uint32) * WIN_Y * WIN_X);
    while (SDL_PollEvent(&w.event)) {
        key_hook(w.event, env);
    }
    if (env->is_init == -1)
    {
        while (f)
        {
            p = f->next;
            ft_memdel((void**)&f);
            f = p;
        }
        f = NULL;
        env->is_init = 1;
    }
    if (env->is_draw == 0)
	    get_point(&w, env);
    else
    {
        coor = draw_bezier(&w, env, env->point, env->first_point, 0);
        p = f;
        while (p && p->next)
            p = p->next;
        if (!p)
        {
            p = (t_point*)ft_memalloc(sizeof(t_point));
            f = p;
        }
        else
        {
            p->next = (t_point*)ft_memalloc(sizeof(t_point));
            p = p->next;
        }
        p->x = coor.x;
        p->y = coor.y;
        p = f;
        while (p)
        {
            if (p != f)
            {
                l.y1 = p->y;
                l.x1 = p->x;
                l.color = 0x8a2be2;
                line(l, &w);
            }
            l.x0 = p->x;
            l.y0 = p->y;
            p = p->next;
        }
    }
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_X * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);

    if (env->iteration > 5000)
        return (1);
    if (env->iteration > 100)
        usleep((useconds_t)(100000 / (env->iteration / 100)));
    else
        usleep((useconds_t)(100000));
	return (1);
}
