//
// Created by tom billard on 24/08/2017.
//

#include "bezier.h"

static t_corr		loop_line(t_line l, t_window *w, float dist, int first_call, t_corr c)
{
    int i;
    float d2;
    t_corr coor0;
    t_line li;

    i = 0;
    l.dx = abs(l.x1 - l.x0);
    l.sx = l.x0 < l.x1 ? 1 : -1;
    l.dy = abs(l.y1 - l.y0);
    l.sy = l.y0 < l.y1 ? 1 : -1;
    l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
    while (1)
    {
        d2 = (float)sqrt(pow(l.x1 - l.x0, 2) + pow(l.y1 - l.y0, 2));
        if ((int)dist == (int)d2 || (int)dist == (int)d2 + 1)// || (int)dist == (int)d2 - 1)
        {
            draw_full_circle(l.x0, l.y0, 3, l.color, w);
            break;
        }
        if (l.x0 == l.x1 && l.y0 == l.y1)
            break ;
        l.e2 = l.err;
        if (l.e2 > -l.dx)
        {
            l.err -= l.dy;
            l.x0 += l.sx;
        }
        if (l.e2 < l.dy)
        {
            l.err += l.dx;
            l.y0 += l.sy;
        }
        i++;
    }
    if (first_call != 1)
    {
        li.x0 = c.x;
        li.y0 = c.y;
        li.x1 = l.x0;
        li.y1 = l.y0;
        line(li, w);
    }
    coor0.x = l.x0;
    coor0.y = l.y0;
    return (coor0);
}

t_corr			place_point(t_line l, t_env *e, t_window *w, float dist, int f_c, t_corr c)
{
    return(loop_line(l, w, dist, f_c, c));
}