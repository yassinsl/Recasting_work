#include "recaste.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#define PI 3.1415926535
#define R 10
#define PLAYER 'P'

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i]) i++;
    return (i);
}

typedef struct s_texture
{
    void *wall;
    void *space;
    void *player_up;
    void *player_lf;
    void *player_do;
    void *player_rg;
    void *collect;
    void *exit;
    void *exit_open;
    int width;
    int hight;
} t_texture;

struct me {
    void *mlx;
    t_texture texture;
    void *win;
    void *img_win;
    char *buffer;
    int size_pixel;
    int size_line;
    int endian;
    int rows, cols;
    int pos_y;
    int pos_x;
    int ray_x;
    int ray_y;
};

int manage_key(int keycode, struct me *game)
{
    if (keycode == 65307)
        exit(1);
    return (0);
}

void ft_render_map(struct me *game, char **map)
{
    int x, y = 0;
    ft_clear_buffer(game);

    while (y < game->rows)
    {
        x = 0;
        while (x < game->cols)
        {
          ft_put(game, y, x,0x594A3C);
            if (map[y][x] == '1')
                ft_put(game, y, x, 0x6E6055);
            else if (map[y][x] == 'P')
                Draw_cercle(y, x, game,0x386490);
            else if(map[y][x] == 'C')
                Draw_star(x, y, game);
            if(map[y][x] == 'X')
               Draw_cercle(y, x, game,0x781414);
            x++;
        }
        y++;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img_win, 0, 0);
}

void get_size_map(char **map, int *row, int *colmns)
{
    *colmns = ft_strlen(map[0]);
    while (map[(*row)])
        (*row)++;
}

void render_map(struct me *game, char **map)
{
    get_size_map(map, &game->rows, &game->cols);
    game->texture.width = game->cols * 50;
    game->texture.hight = game->rows * 50;

    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->texture.width, game->texture.hight, "eMy 2D Game");
    game->img_win = mlx_new_image(game->mlx, game->texture.width, game->texture.hight);

    game->buffer = mlx_get_data_addr(game->img_win, &game->size_pixel, &game->size_line, &game->endian);
    ft_render_map(game, map);
    mlx_key_hook(game->win, manage_key, game);
    mlx_loop(game->mlx);
}

void get_position_player(struct me *game, char **map)
{
    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == PLAYER)
            {
                game->pos_x = j;
                game->pos_y = i;
                return;
            }
            j++;
        }
        i++;
    }
}

int main(void)
{
    struct me game = {0};

    char *map[] =
    {
        "1111111111101111",
        "110111X110111111",
        "10P0011111101111",
        "1C1011111011111",
        "111111111111111",
        NULL,
    };

    get_position_player(&game, map);
    render_map(&game, map);
}
