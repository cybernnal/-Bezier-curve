/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BEZIER.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 15:40:53 by tbillard          #+#    #+#             */
/*   Updated: 2016/06/19 20:13:54 by tbillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BEZIER_H
# define BEZIER_H

#include "../libft/libft.h"
#include <errno.h>
#include <time.h>
#include "SDL.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <SDL_ttf.h>

#include <netdb.h>
#define WIN_X   1900
#define WIN_Y   1050

#define ITER_MAX 100

#define POINT_COLOR 0x00FFFF


# define L_CF(X, x1, x2, y1, y2) ((float)(((float)((X - x1) * (y2 - y1))) / (float)(x2 - x1)) + y1)

//uint32_t     col[7] = {0xFF0000, 0x00FFFF, 0xED7F10, 0xFFFF00, 0x00FF00, 0xAFAFAF, 0x0000FF};

typedef struct 				s_line
{
    int 					x0;
    int 					x1;
    int 					y0;
    int 					y1;
    int						dx;
    int						sx;
    int						dy;
    int						sy;
    int						err;
    int						e2;
    Uint32					color;
}							t_line;


typedef struct          s_window
{
    SDL_Window          *window;
    SDL_Event           event;
    SDL_Renderer        *renderer;
    SDL_Texture         *image;
    Uint32              *img_ptr;
    int                 is_init;
}                       t_window;

typedef struct 				s_coor
{
    int 					x;
    int 					y;
}							t_corr;




typedef struct 				s_point
{
    int 					x;
    int 					y;
    struct s_point          *next;
}							t_point;

typedef struct		    s_env
{
    t_point              *point;
    t_point              *first_point;
    int                  nb_point;
    int                  is_draw;
    int                  is_init;
    int                 iteration;
    int                 nrand;
    int                 sleep;
}			    		t_env;

void    			    init_env(t_env *env);
void                    init_window(t_window *window);
int                     render(t_env *env);
int					    ft_error(char *str);
int             		key_hook(SDL_Event k, t_env *e);
void		            ft_tab_ft_init_1(int (**tab_ft)(t_env*));
void                    draw_pixel(int x, int y, Uint32 color, t_window *w);
int                     nil(t_env *env);
void        			line(t_line l, t_window *w);
t_corr      			place_point(t_line l, t_env *e, t_window *w, float dist, int f_c, t_corr c, int rec);
void                    draw_full_circle(int x0, int y0, int radius, Uint32 color, t_window *w);
#endif
