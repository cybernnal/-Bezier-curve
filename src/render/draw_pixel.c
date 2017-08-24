#include "tetris.h"

void        draw_pixel(int x, int y, Uint32 color, t_window *w)
{
    if ((y > WIN_Y || x > WIN_X || x < 0 || y < 0)) {
        return ;
    }
    w->img_ptr[WIN_X * y + x] = color;
}


static void			loop_line(t_line l, t_window *w)
{
    int i;

    i = 0;
    l.dx = abs(l.x1 - l.x0);
    l.sx = l.x0 < l.x1 ? 1 : -1;
    l.dy = abs(l.y1 - l.y0);
    l.sy = l.y0 < l.y1 ? 1 : -1;
    l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
    while (1)
    {
        draw_pixel(l.x0, l.y0, l.color, w);
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
}

void			line(t_line l, t_window *w)
{
     loop_line(l, w);
}
