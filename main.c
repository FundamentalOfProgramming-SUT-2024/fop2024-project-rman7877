#define _GNU_SOURCE
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>
#define white_color 1
#define yellow_color 6
#define orange_color 8
#define gold_color 6
#define red_color 7
#define green_color 4
#define blue_color 5
#define black_color 9
#define enemy_color 7
#define map_height 40
#define map_width 80
#define min_room_size 6
#define max_room_width 12
#define max_room_height 10
#define min_room_number 6
#define max_room_number 10
#define second_door_probability 50
#define third_door_probability 5
#define pillar_probability1000 15
// #define trap_probability1000 15
#define gold_probability1000 10
#define black_gold_probability1000 3
// #define spell_probability1000 10
// #define food_probability1000 5
#define trap_probability1000treasure 40
#define enemy_probability1000treasure 50
#define pass_door_probability 30
#define hidden_door_probability 30
#define inverse_pass_door_probability 40
#define key_break_probability 10
// #define enemy_probability 60
#define change_pass_door 20
#define max_door_number 2
#define rooms_space 3
#define up 1
#define right 2
#define down 3
#define left 4
#define hero_health 100
#define max_hunger 100
#define trap_damage 5
#define hunger_damage 1
#define spoiled_food_damage 30
#define regular_room_percentage 50
#define nightmare_room_percentage 20
// #define weapon_percentage1000 5
#define main_color 1
#define door_color 4
#define trap_color 7
#define corridor_color 6
#define master_key_color 6
#define used_trap_color 4
#define hidden_door_color 4
#define pass_door_color 5
#define opened_pass_door_color 6
#define pass_door_key_color 4
#define gold_color 6
#define black_gold_color 6
#define stairs_color 4
#define regular_room_color 1
#define nightmare_room_color 7
#define treasure_room_color 6
// #define hero_deafualt_color 10
#define gold_min 5
#define gold_max 20
#define max_food_number 5
#define treasure_room_width 30
#define treasure_room_height 20
#define min_treasure_enemy 10
#define max_treasure_enemy 20

#define black_gold_times 5
#define message_time 3
#define pass_time 30
#define change_pass_time 10
#define heal_after_attack_time 5
// #define heal_amount 5
#define heal_interval_time 2
#define message_pass_space -1

#define spell_step 10
#define food_step 10
#define food_change_step 100

#define mace_key 'e'
#define dagger_key 't'
#define sword_key 'r'
#define magic_wand_key 'y'
#define normal_arrow_key 'u'
#define health_spell_key 'h'
#define speed_spell_key 's'
#define damage_spell_key 'd'
#define regular_food_key 'r'
#define excellent_food_key 'e'
#define magic_food_key 'm'

void game_menu();
void game_menu_input();

int trap_probability1000 = 15, spell_probability1000 = 10, food_probability1000 = 5, enemy_probability = 60, weapon_percentage1000 = 5;
int hero_deafualt_color = 10;
int delay = 100000;
char login_panel_items[4][20] = {"Sign in", "Sign up", "Enter as guest", "Exit"};
char sign_up_panel_textbox[4][30] = {"Username:", "Password:", "Confirm Password:", "Email:"};
char sign_in_panel_textbox[2][30] = {"Username:", "Password:"};
char menu_items[6][30] = {"New Game", "Load Game", "Leaderboard", "Settings", "Profile", "Log Out"};
char settings_items[2][30] = {"Difficulty Level", "Hero Color"};
int menu_items_count = 6, selected_menu = 0;
int settings_count = 2;
char difficulty_levels[3][20] = {"Easy", "Normal", "Hard"};
int difficulty_count = 3, selected_difficulty = 0;
char hero_colors[5][20] = {"Red", "Blue", "Green", "Yellow", "White"};
int hero_color_count = 5, selected_hero_color = 0;
int selected_settings = 0;
int selected_login_panel = 0, panel_items = 4;
int sign_up_panel_textbox_count = 4, sign_in_panel_textbox_count = 2;
int running = 1;
char user_username[100];
int difficulty = 2;
int preesed_f = 0, heal_amount = 5;
char hero_color[20] = "Red";
// int map_height = 150, map_width = 200;

char treasure[20] = "treasure", enchant[20] = "enchant", regular[20] = "regular", nightmare[20] = "nightmare";
int starty_map_draw = 0, startx_map_draw = 0;
int floor_number = 0;
int been[map_height][map_width];
int stairs_room, stairs_location[2][4][2];
int downstairs = 0;
int treasure_room, show_map = 0;
int message_row;
int pick_up = 1;
int last_shot_dir = -1;
int this_room_number[5] = {0, 0, 0, 0, 0};
int terminal_x_size, terminal_y_size;
int first_step = 1;
int is_message[10] = {0, 0, 0, 0, 0};
time_t messag_time[5], pass_timer, change_pass_timer, last_attack, heal_interval;
char flor = '.', door = '+', wall[2] = {'_', '|'}, nothing = ' ', corridor = '#', trap = '^', used_trap = 'a', show_trap = 'b', hidden_door = '?';
char found_door = 'e', stairs = '<', hero_char = 'H';
char pillar = 'O', gold = 'g', black_gold = 'B', pass_door = '@', opened_pass_door = 'd', pass_door_key = '&', master_key = 'K';
char deamon = 'D', fire_breathing = 'F', giant = 'G', snake = 'S', undeed = 'U', mace = 'f', dagger = 'k', magic_wand = 'h', normal_arrow = 'i', sword = 'j';
char dagger_floor = 1, magic_wand_floor = 2, normal_arrow_floor = 3, health_spell = 4, speed_spell = 5, damage_spell = 6, regular_food = 7, excellent_food = 8, magic_food = 9, spoiled_food = 10;
char treasure_char = 11;
wchar_t ucorridor = L'░', uflor = L'∘', udoor = L'+', unothing = L' ', utrap = L'^', uhidden_door = L'?', uwall[2] = {L'━', L'┃'};
wchar_t ustairs = L'⇓', uhero_char = L'🦸', upillar = L'O', ugold = L'💰', ublack_gold = L'🛢', upass_door = L'@', upass_door_key = L'🗝', umaster_key = L'△';
wchar_t umagic_wand = L'✨', umace = L'⚒', usword = L'⚔', udagger = L'🗡', unormal_arrow = L'🏹', uhealth_spell = L'🏥', uspeed_spell = L'⚡', udamage_spell = L'🔥';
wchar_t uregular_food = L'🍞', uexcellant_food = L'🍗', umagic_food = L'🧪', utreasure_char = L'🏆';
int game_is_running = 1;

typedef struct food
{
    char name;
    int step_until_change;
} food_struct;

typedef struct enemy
{
    char enemy_char;
    char enemy_name[20];
    int exist;
    int damage;
    int mov_left;
    int loc[2];
    int health;
} enemy_struct;

typedef struct room
{
    int starty, startx, height, width;
    int door_number;
    int door[max_door_number][2];
    int door_side[max_door_number];
    int show;
    int door_password;
    int change_door_password;
    char theme[20];
    enemy_struct enemy;
} room_struct;

typedef struct game
{
    char map[5][map_height][map_width];
    char show_map[5][map_height][map_width];
    char under_weapon[5][map_height][map_width];
    int room_number[5];
    room_struct room[5][max_room_number];
    room_struct treasure_room;
    enemy_struct treasure_enemy[50];
    int treasure_enemy_number, all_enemy_number;
} game_struct;

typedef struct hero
{
    int health, gold, master_key_number, broken_key_number;
    int mace_number, dagger_number, sword_number, magic_wand_number, normal_arrow_number;
    int health_spell_number, speed_spell_number, damage_spell_number;
    int regular_food_number, excellent_food_number, magic_food_number, spoiled_food_number;
    char weapon;
    int step, health_step, damage_step, speed_step;
    int hunger;
    int score;
    food_struct foods[max_food_number];
    int x, y;

} hero_struct;

int random_number(int min, int max);
int can_go(int x, int y, game_struct *game, int fl);
int remaining_dir(int a, int b, int c);
int go_dir(int x, int y, int x1, int y1, int dir, game_struct *game, int fl);
int calculate_path(int x, int y, int x1, int y1, int dir, game_struct *game, int fl);
void draw_map(game_struct *game, hero_struct *hero);
void attron_theme_item(char item, char first, int show_map);
void attron_theme_room(char theme[]);
void new_game();
void show_message(char message[], game_struct *game, hero_struct *hero);

void print_unicode(int y, int x, char c)
{
    wchar_t final;
    if (c == corridor)
        final = ucorridor;
    else if (c == flor)
        final = uflor;
    else if (c == door)
        final = udoor;
    else if (c == wall[0])
        final = uwall[0];
    else if (c == wall[1])
        final = uwall[1];
    else if (c == nothing)
        final = unothing;
    else if (c == trap)
        final = utrap;
    else if (c == hidden_door)
        final = uhidden_door;
    else if (c == stairs)
        final = ustairs;
    else if (c == hero_char)
        final = uhero_char;
    else if (c == pillar)
        final = upillar;
    else if (c == gold)
        final = ugold;
    else if (c == black_gold)
        final = ublack_gold;
    else if (c == pass_door || c == opened_pass_door)
        final = upass_door;
    else if (c == pass_door_key)
        final = upass_door_key;
    else if (c == master_key)
        final = umaster_key;
    else if (c == mace)
        final = umace;
    else if (c == dagger || c == dagger_floor)
        final = udagger;
    else if (c == magic_wand || c == magic_wand_floor)
        final = umagic_wand;
    else if (c == sword)
        final = usword;
    else if (c == normal_arrow || c == normal_arrow_floor)
        final = unormal_arrow;
    else if (c == health_spell)
        final = uhealth_spell;
    else if (c == speed_spell)
        final = uspeed_spell;
    else if (c == damage_spell)
        final = udamage_spell;
    else if (c == regular_food || c == spoiled_food)
        final = uregular_food;
    else if (c == excellent_food)
        final = uexcellant_food;
    else if (c == magic_food)
        final = umagic_food;
    else if (c == treasure_char)
        final = utreasure_char;
    else if (c == hero_char)
        final = uhero_char;
    else
        mvprintw(y, 2 * x - startx_map_draw, "%c ", c);

    if (final == ucorridor || final == uwall[0])
        mvprintw(y, 2 * x - startx_map_draw, "%lc%lc", final, final);
    else if (wcwidth(final) == 1)
        mvprintw(y, 2 * x - startx_map_draw, "%lc ", final);
    else
        mvprintw(y, 2 * x - startx_map_draw, "%lc", final);
}

void print_sth(char sth[100], int x, int y, int color, int loc)
{
    attron(COLOR_PAIR(color));
    int len = strlen(sth);
    if (loc == 1)
        mvprintw(y / 2, (x + terminal_x_size) / 2 - len / 2, "%s", sth);
    else if (loc == 2)
        mvprintw(y / 2, x / 2 - len / 2, "%s", sth);
    else if (loc == 3)
        mvprintw((y + terminal_y_size) / 2, x / 2 - len / 2, "%s", sth);
    else if (loc == 4)
        mvprintw((y + terminal_y_size) / 2, (x + terminal_x_size) / 2 - len / 2, "%s", sth);
    attroff(COLOR_PAIR(color));
}
int min(int a, int b)
{
    if (a <= b)
        return a;
    return b;
}
int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}
void clear_map(game_struct *game)
{
    for (int i = starty_map_draw; i < starty_map_draw + map_height; i++)
        for (int j = startx_map_draw; j < startx_map_draw + map_width * 2; j++)
            mvprintw(i, j, "  ");
}
int random_number(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
int can_go(int x, int y, game_struct *game, int fl)
{
    if (y < 0 || y > map_height - 1 || x < 0 || x > map_width - 1)
        return 0;
    else if (game->map[fl][y][x] == nothing || game->map[fl][y][x] == corridor)
        return 1;
    else
        return 0;
}
int remaining_dir(int a, int b, int c)
{
    for (int i = 1; i <= 4; i++)
        if (i != a && i != b && i != c)
            return i;
}
int go_dir(int x, int y, int x1, int y1, int dir, game_struct *game, int fl)
{
    if (dir == 1 && can_go(x, y - 1, game, fl) && been[y - 1][x] == 0 && calculate_path(x, y - 1, x1, y1, dir, game, fl))
    {
        game->map[fl][y - 1][x] = corridor;
        return 1;
    }
    else if (dir == 3 && can_go(x, y + 1, game, fl) && been[y + 1][x] == 0 && calculate_path(x, y + 1, x1, y1, dir, game, fl))
    {
        game->map[fl][y + 1][x] = corridor;
        return 1;
    }
    else if (dir == 2 && can_go(x + 1, y, game, fl) && been[y][x + 1] == 0 && calculate_path(x + 1, y, x1, y1, dir, game, fl))
    {
        game->map[fl][y][x + 1] = corridor;
        return 1;
    }
    else if (dir == 4 && can_go(x - 1, y, game, fl) && been[y][x - 1] == 0 && calculate_path(x - 1, y, x1, y1, dir, game, fl))
    {
        game->map[fl][y][x - 1] = corridor;
        return 1;
    }
    return 0;
}
int calculate_path(int x, int y, int x1, int y1, int dir, game_struct *game, int fl)
{
    been[y][x] = 1;
    if (x == x1 && y == y1)
        return 1;
    if ((x == x1 && abs(y1 - y) == 1) || (y == y1 && abs(x1 - x) == 1))
        return 1;
    int diry = 0, dirx = 0;
    if (y1 > y)
        diry = 1;
    else if (y1 < y)
        diry = -1;
    if (x1 > x)
        dirx = 1;
    else if (x1 < x)
        dirx = -1;
    // usleep(80000);
    // mvprintw(2,0,"%d %d %d %d %d %d",x,y,x1,y1,dirx,diry);
    // refresh();
    int canx = can_go(x + dirx, y, game, fl);
    int cany = can_go(x, y + diry, game, fl);
    int opposite = (((dir + 1) % 4) + 1);
    if (dirx && canx == 1 && (diry == 0 || cany == 0))
    {
        if ((3 - dirx != opposite) && go_dir(x, y, x1, y1, 3 - dirx, game, fl))
            return 1;
        if (go_dir(x, y, x1, y1, remaining_dir(opposite, diry + 2, 3 - dirx), game, fl))
            return 1;
    }
    else if (diry && cany == 1 && (dirx == 0 || canx == 0))
    {
        if ((2 + diry != opposite) && go_dir(x, y, x1, y1, 2 + diry, game, fl))
            return 1;
        if (go_dir(x, y, x1, y1, remaining_dir(opposite, 3 - dirx, 2 + diry), game, fl))
            return 1;
    }
    else if (dirx && diry && canx == 1 && cany == 1)
    {
        if (random_number(0, 1))
        {
            if ((3 - dirx != opposite) && go_dir(x, y, x1, y1, 3 - dirx, game, fl))
                return 1;
            if ((2 + diry != opposite) && go_dir(x, y, x1, y1, 2 + diry, game, fl))
                return 1;
        }
        else
        {
            if ((2 + diry != opposite) && go_dir(x, y, x1, y1, 2 + diry, game, fl))
                return 1;
            if ((3 - dirx != opposite) && go_dir(x, y, x1, y1, 3 - dirx, game, fl))
                return 1;
        }
        if (go_dir(x, y, x1, y1, remaining_dir(opposite, 3 - dirx, 2 + diry), game, fl))
            return 1;
    }
    else
    {
        for (int i = 1; i <= 4; i++)
            if (i != opposite && go_dir(x, y, x1, y1, i, game, fl))
                return 1;
    }
    return 0;
}
void make_corridor(game_struct *game, int fl)
{
    for (int i = 0; i < game->room_number[fl]; i++)
    {
        int connected[max_door_number];
        for (int j = 0; j < max_door_number; j++)
            connected[j] = -1;
        for (int j = 0; j < game->room[fl][i].door_number; j++)
        {
            int x = game->room[fl][i].door[j][1];
            int y = game->room[fl][i].door[j][0];
            int new_room, check = 1;
            if (j == 0 && i + 1 < game->room_number[fl])
            {
                new_room = i + 1;
                connected[j] = new_room;
            }
            else
            {
                while (check)
                {
                    check = 0;
                    new_room = random_number(0, game->room_number[fl] - 1);
                    if (new_room != i)
                        for (int k = 0; k < j; k++)
                        {
                            if (new_room == connected[k])
                                check = 1;
                        }
                    else
                        check = 1;
                }
            }
            int x1 = game->room[fl][new_room].door[0][1];
            int y1 = game->room[fl][new_room].door[0][0];
            int direction = game->room[fl][i].door_side[j];
            for (int k = 0; k < map_height; k++)
                for (int h = 0; h < map_width; h++)
                    been[k][h] = 0;
            calculate_path(x, y, x1, y1, direction, game, fl);
        }
    }
}
void set_room_theme(char theme[], int fl, int room_number)
{
    if (fl == 3 && room_number == treasure_room)
        strcpy(theme, treasure);
    else
    {
        int x = random_number(1, 100);
        if (x <= nightmare_room_percentage)
            strcpy(theme, nightmare);
        else
            strcpy(theme, regular);
    }
}
void locate_stairs(game_struct *game, int room, int fl)
{
    int new_loc = 0, room_starty = game->room[fl][room].starty, room_startx = game->room[fl][room].startx;
    int room_height = game->room[fl][room].height, room_width = game->room[fl][room].width;
    while (!new_loc)
    {
        int stair_side = random_number(1, 4);
        if (stair_side == 1)
        {
            stairs_location[1][fl][0] = room_starty;
            stairs_location[1][fl][1] = random_number(room_startx, room_startx + room_width - 1);
        }
        else if (stair_side == 3)
        {
            stairs_location[1][fl][0] = room_starty + room_height - 1;
            stairs_location[1][fl][1] = random_number(room_startx + 1, room_startx + room_width - 2);
        }
        else if (stair_side == 4)
        {
            stairs_location[1][fl][0] = random_number(room_starty, room_starty + room_height - 1);
            stairs_location[1][fl][1] = room_startx;
        }
        else
        {
            stairs_location[1][fl][0] = random_number(room_starty + 1, room_starty + room_height - 2);
            stairs_location[1][fl][1] = room_startx + room_width - 1;
        }
        stairs_location[0][fl + 1][0] = stairs_location[1][fl][0];
        stairs_location[0][fl + 1][1] = stairs_location[1][fl][1];
        if (game->map[fl][stairs_location[1][fl][0]][stairs_location[1][fl][1]] == wall[0] || game->map[fl][stairs_location[1][fl][0]][stairs_location[1][fl][1]] == wall[1])
            new_loc = 1;
    }
}
void locate_item_chance(game_struct *game, room_struct *room, char item, int fl, int probability)
{
    int new_loc = 0, room_starty = room->starty, room_startx = room->startx;
    int room_height = room->height, room_width = room->width;
    for (int i = room_starty + 1; i < room_starty + room_height - 1; i++)
        for (int j = room_startx + 1; j < room_startx + room_width - 1; j++)
            if (game->map[fl][i][j] == flor && random_number(1, 1000) <= probability && ((item != pillar) || (i != room_starty + 1 && i != room_starty + room_height - 2 && j != room_startx + 1 && j != room_startx + room_width - 2)))
                game->map[fl][i][j] = item;
}
void locate_item(game_struct *game, room_struct *room, char item, int fl)
{
    while (1)
    {
        int y = random_number(room->starty + 1, room->starty + room->height - 2);
        int x = random_number(room->startx + 1, room->startx + room->width - 2);
        if (game->map[fl][y][x] == flor)
        {
            game->map[fl][y][x] = item;
            break;
        }
    }
}
void trap_hdoor_check(game_struct *game, hero_struct *hero)
{
    int x = hero->x, y = hero->y;
    for (int i = y - 1; i <= y + 1; i++)
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (game->map[floor_number][i][j] == trap)
                game->map[floor_number][i][j] = show_trap;
            else if (game->map[floor_number][i][j] == hidden_door)
                game->map[floor_number][i][j] = found_door;
        }
}
void show_pass(game_struct *game, hero_struct *hero, int password)
{
    char message[100];
    sprintf(message, "%d", password);
    if (random_number(1, 100) <= inverse_pass_door_probability)
    {
        char save = message[0];
        message[0] = message[3];
        message[3] = save;
        save = message[1];
        message[1] = message[2];
        message[2] = save;
    }
    int x, y;
    getmaxyx(stdscr, y, x);
    int col = x / 2 - strlen(message) / 2;
    move(message_row + message_pass_space, col);
    clrtoeol();
    draw_map(game, hero);
    mvprintw(message_row + message_pass_space, col, "Pass: %s", message);
    pass_timer = time(NULL);
}
int entered_room_number(game_struct *game, int x, int y, int fl)
{
    for (int i = 0; i < game->room_number[fl]; i++)
        for (int j = 0; j < game->room[fl][i].door_number; j++)
            if (game->room[fl][i].door[j][0] == y && game->room[fl][i].door[j][1] == x)
                return i;
}
void damage_hero(int damage, hero_struct *hero, game_struct *game)
{
    last_attack = time(NULL);
    heal_interval = time(NULL);
    hero->health -= damage;
    if (hero->health <= 0)
    {
        show_message("You have been killed!", game, hero);
        hero->health = 0;
        end_game(game, hero, 0);
    }
}
void locate_enemy(game_struct *game, room_struct *room, enemy_struct *enemy, int fl, int probability)
{
    if (random_number(1, 100) <= probability)
    {
        enemy->exist = 1;
        int select = random_number(1, 5);
        if (select == 1)
        {
            enemy->enemy_char = fire_breathing;
            enemy->health = 10;
            enemy->damage = 10;
            strcpy(enemy->enemy_name, "Fire Breathing");
            enemy->mov_left = 5;
        }

        else if (select == 2)
        {
            enemy->enemy_char = giant;
            enemy->health = 15;
            enemy->damage = 15;
            strcpy(enemy->enemy_name, "Giant");
            enemy->mov_left = 5;
        }
        else if (select == 3)
        {
            enemy->enemy_char = snake;
            enemy->health = 20;
            enemy->damage = 20;
            strcpy(enemy->enemy_name, "Snake");
            enemy->mov_left = -1;
        }
        else if (select == 4)
        {
            enemy->enemy_char = undeed;
            enemy->health = 30;
            enemy->damage = 25;
            strcpy(enemy->enemy_name, "Undead");
            enemy->mov_left = -2;
        }
        else
        {
            enemy->enemy_char = deamon;
            enemy->health = 5;
            enemy->damage = 5;
            strcpy(enemy->enemy_name, "Deamon");
            enemy->mov_left = 5;
        }

        while (1)
        {
            int y = random_number(room->starty + 1, room->starty + room->height - 2);
            int x = random_number(room->startx + 1, room->startx + room->width - 2);
            if (game->map[fl][y][x] == flor)
            {
                enemy->loc[0] = y;
                enemy->loc[1] = x;
                break;
            }
        }
    }
    else
        enemy->exist = 0;
}
void show_corridor(game_struct *game, int x, int y, int fl, int remain_count)
{
    if (remain_count == 0)
        return;
    if (game->map[fl][y + 1][x] == corridor)
    {
        game->show_map[fl][y + 1][x] = corridor;
        show_corridor(game, x, y + 1, fl, remain_count - 1);
    }
    if (game->map[fl][y - 1][x] == corridor)
    {
        game->show_map[fl][y - 1][x] = corridor;
        show_corridor(game, x, y - 1, fl, remain_count - 1);
    }
    if (game->map[fl][y][x + 1] == corridor)
    {
        game->show_map[fl][y][x + 1] = corridor;
        show_corridor(game, x + 1, y, fl, remain_count - 1);
    }
    if (game->map[fl][y][x - 1] == corridor)
    {
        game->show_map[fl][y][x - 1] = corridor;
        show_corridor(game, x - 1, y, fl, remain_count - 1);
    }
    if (game->map[fl][y + 1][x] == door || game->map[fl][y + 1][x] == pass_door || game->map[fl][y + 1][x] == opened_pass_door)
        game->show_map[fl][y + 1][x] = game->map[fl][y + 1][x];
    if (game->map[fl][y - 1][x] == door || game->map[fl][y - 1][x] == pass_door || game->map[fl][y - 1][x] == opened_pass_door)
        game->show_map[fl][y - 1][x] = game->map[fl][y - 1][x];
    if (game->map[fl][y][x + 1] == door || game->map[fl][y][x + 1] == pass_door || game->map[fl][y][x + 1] == opened_pass_door)
        game->show_map[fl][y][x + 1] = game->map[fl][y][x + 1];
    if (game->map[fl][y][x - 1] == door || game->map[fl][y][x - 1] == pass_door || game->map[fl][y][x - 1] == opened_pass_door)
        game->show_map[fl][y][x - 1] = game->map[fl][y][x - 1];
}
void enter_room(game_struct *game, int x, int y)
{
    this_room_number[floor_number] = entered_room_number(game, x, y, floor_number);
    game->room[floor_number][this_room_number[floor_number]].show = 1;
    if (game->room[floor_number][this_room_number[floor_number]].enemy.exist)
    {
        char c = game->room[floor_number][this_room_number[floor_number]].enemy.enemy_char;
        if (c == deamon || c == fire_breathing || c == giant)
            game->room[floor_number][this_room_number[floor_number]].enemy.mov_left = 5;
    }
}
int enemy_can_go(game_struct *game, enemy_struct *enemy, hero_struct *hero, int y, int x)
{
    char c = game->map[floor_number][y][x];
    if (c == wall[0] || c == wall[1] || c == pillar || c == door || c == pass_door || c == opened_pass_door || c == hidden_door || c == found_door || c == stairs || c == pass_door_key)
        return 0;
    if (y == hero->y && x == hero->x)
        return 0;
    enemy->loc[0] = y;
    enemy->loc[1] = x;
    return 1;
}
void move_enemy(game_struct *game, hero_struct *hero, enemy_struct *enemy)
{
    int x = enemy->loc[1], y = enemy->loc[0];
    int x1 = hero->x, y1 = hero->y;
    if (abs(x - x1) <= 1 && abs(y - y1) <= 1)
    {
        if (enemy->enemy_char == undeed && enemy->mov_left == -2)
            enemy->mov_left = 2000;
        char message[100];
        sprintf(message, "You have been attacked by %s!", enemy->enemy_name);
        show_message(message, game, hero);
        damage_hero(enemy->damage, hero, game);
        if (enemy->mov_left > 0)
            enemy->mov_left--;
        return;
    }

    if (enemy->mov_left == 0 || enemy->mov_left == -2)
        return;
    else if (enemy->mov_left > 0)
        enemy->mov_left--;
    int x2 = 0, y2 = 0;
    if (x1 > x)
        x2 = 1;
    else if (x1 < x)
        x2 = -1;
    if (y1 > y)
        y2 = 1;
    else if (y1 < y)
        y2 = -1;
    if (x2 != 0 || y2 != 0)
    {
        if (enemy_can_go(game, enemy, hero, y + y2, x + x2))
            return;
    }
}
void attron_theme_room(char theme[])
{
    if (strcmp(theme, regular) == 0)
        attron(COLOR_PAIR(regular_room_color));
    else if (strcmp(theme, nightmare) == 0)
        attron(COLOR_PAIR(nightmare_room_color));
    else if (strcmp(theme, treasure) == 0)
        attron(COLOR_PAIR(treasure_room_color));
    else
        attron(COLOR_PAIR(main_color));
}
void show_message(char message[], game_struct *game, hero_struct *hero)
{
    int i;
    for (i = 0; i < 10; i++)
        if (is_message[i] == 0)
        {
            is_message[i] = 1;
            break;
        }
    int x, y;
    getmaxyx(stdscr, y, x);
    int col = x / 2 - strlen(message) / 2;
    move(message_row + i, 0);
    clrtoeol();
    mvprintw(message_row + i, col, "%s", message);
    messag_time[i] = time(NULL);
}

void game_info(game_struct *game, hero_struct *hero)
{
    char info[200];
    wchar_t wep;
    int x, y;
    getmaxyx(stdscr, y, x);

    sprintf(info, "Health:%d  Gold:%d  Master key:%d  Broken key:%d  Weapon:    Score:%d", hero->health, hero->gold, hero->master_key_number, hero->broken_key_number, hero->score);
    mvprintw(starty_map_draw + map_height + 2, x / 2 - strlen(info) / 2, "%s", info);
    if (hero->weapon != nothing)
    {
        if (hero->weapon == mace)
            wep = umace;
        else if (hero->weapon == dagger)
            wep = udagger;
        else if (hero->weapon == sword)
            wep = usword;
        else if (hero->weapon == magic_wand)
            wep = umagic_wand;
        else if (hero->weapon == normal_arrow)
            wep = unormal_arrow;
        mvprintw(starty_map_draw + map_height + 2, x / 2 - strlen(info) / 2 + strlen("Health:%d  Gold:%d  Master key:%d  Broken key:%d  Weapon:") - 2, "%lc", wep);
    }
}
int password_textbox(int password, game_struct *game, hero_struct *hero, int try_number)
{
    if (try_number == 0)
    {
        move(message_row, 0);
        clrtoeol();
        move(message_row + message_pass_space, 0);
        clrtoeol();
    }
    clear_map(game);
    int x, y;
    getmaxyx(stdscr, y, x);
    int col = (x - strlen("Enter password: ") - 4) / 2, row = y / 2;
    char pass[10], pass_text[100];
    sprintf(pass, "%d", password);
    pass[4] = '\0';
    int i = 0;
    mvprintw(row, col, "Enter password: ");
    if (hero->master_key_number > 0)
        print_sth("Press K to use master key", 0, row, main_color, 4);
    while (1)
    {
        int c = getch();
        if (c == KEY_ENTER || c == '\n')
        {
            pass_text[i] = '\0';
            if (strcmp(pass, pass_text) == 0)
                return 1;
            else
            {
                if (try_number == 0)
                    attron(COLOR_PAIR(gold_color));
                else if (try_number == 1)
                    attron(COLOR_PAIR(red_color));
                else if (try_number == 2)
                    return 0;
                show_message("Wrong password!", game, hero);
                return (password_textbox(password, game, hero, try_number + 1));
            }
        }
        else if (c == KEY_BACKSPACE && i > 0)
        {
            pass_text[i] = '\0';
            i--;
            mvprintw(row, col + strlen("Enter password: ") + i, " ");
        }
        else if (c >= '0' && c <= '9' && i < 4)
        {
            mvprintw(row, col + strlen("Enter password: ") + i, "%c", c);
            pass_text[i] = c;
            i++;
        }
        else if (c == 'k')
        {
            hero->master_key_number--;
            if (random_number(1, 100) <= key_break_probability)
            {
                hero->broken_key_number++;
                if (hero->broken_key_number == 1)
                    show_message("Master key is broken!", game, hero);
                else
                    show_message("Master key is broken again and a key was made!", game, hero);
                if (hero->broken_key_number == 2)
                {
                    hero->broken_key_number = 0;
                    hero->master_key_number++;
                }
                if (hero->master_key_number == 0)
                    print_sth("                         ", 0, row, main_color, 4);
            }
            else
                return 1;
        }
        else if (c == KEY_LEFT)
            return -1;
        game_info(game, hero);
    }
}
void attron_theme_item(char item, char first, int show_map)
{
    if (item == trap && (first == show_trap || show_map))
        attron(COLOR_PAIR(trap_color));
    else if (item == trap && first == used_trap)
        attron(COLOR_PAIR(used_trap_color));
    else if (item == stairs)
        attron(COLOR_PAIR(stairs_color));
    else if (item == door)
        attron(COLOR_PAIR(door_color));
    else if (item == gold)
        attron(COLOR_PAIR(gold_color));
    else if (item == black_gold)
        attron(COLOR_PAIR(black_gold_color));
    else if (first == pass_door)
        attron(COLOR_PAIR(red_color));
    else if (first == opened_pass_door)
        attron(COLOR_PAIR(green_color));
    else if (item == pass_door_key)
        attron(COLOR_PAIR(pass_door_key_color));
    else if (item == master_key)
        attron(COLOR_PAIR(master_key_color));
    else if (item == hidden_door)
        attron(COLOR_PAIR(hidden_door_color));
    else if (item == corridor)
        attron(COLOR_PAIR(corridor_color));
}
void f_button(int dir, hero_struct *hero, game_struct *game)
{
    if (game->map[floor_number][hero->y][hero->x] == corridor || game->map[floor_number][hero->y][hero->x] == door)
    {
        int available = 0, x = hero->x, y = hero->y;
        if (dir != 2 && hero->y - 1 >= 0 && (game->map[floor_number][hero->y - 1][hero->x] == corridor || game->map[floor_number][hero->y - 1][hero->x] == door))
            available++;
        if (dir != 0 && hero->y + 1 < map_height && (game->map[floor_number][hero->y + 1][hero->x] == corridor || game->map[floor_number][hero->y + 1][hero->x] == door))
            available++;
        if (dir != 3 && hero->x + 1 < map_width && (game->map[floor_number][hero->y][hero->x + 1] == corridor || game->map[floor_number][hero->y][hero->x + 1] == door))
            available++;
        if (dir != 1 && hero->x - 1 >= 0 && (game->map[floor_number][hero->y][hero->x - 1] == corridor || game->map[floor_number][hero->y][hero->x - 1] == door))
            available++;
        if (available == 1)
        {
            if (dir != 2 && hero->y - 1 >= 0 && game->map[floor_number][hero->y - 1][hero->x] == corridor)
            {
                hero->y--;
                dir = 0;
            }
            else if (dir != 0 && hero->y + 1 < map_height && game->map[floor_number][hero->y + 1][hero->x] == corridor)
            {
                hero->y++;
                dir = 2;
            }
            else if (dir != 3 && hero->x + 1 < map_width && game->map[floor_number][hero->y][hero->x + 1] == corridor)
            {
                hero->x++;
                dir = 1;
            }
            else if (dir != 1 && hero->x - 1 >= 0 && game->map[floor_number][hero->y][hero->x - 1] == corridor)
            {
                hero->x--;
                dir = 3;
            }

            if (hero->speed_step > 0 && first_step)
                first_step = 0;
            else
            {
                food_step_decrease(hero);
                first_step = 1;
                hero->step++;
                if (hero->hunger < max_hunger)
                    hero->hunger++;
                else
                    damage_hero(hunger_damage, hero, game);
                if (hero->health_step > 0)
                    hero->health_step--;
                if (hero->damage_step > 0)
                    hero->damage_step--;
                if (hero->speed_step > 0)
                    hero->speed_step--;
            }

            show_corridor(game, hero->x, hero->y, floor_number, 5);
            if (x != hero->x || y != hero->y)
                f_button(dir, hero, game);
        }
        // else
        //     draw_map(game, hero);
    }
    draw_map(game, hero);
}
void weapon_name(char weapon_name[], char weapon)
{
    if (weapon == sword)
        strcpy(weapon_name, "Sword");
    else if (weapon == mace)
        strcpy(weapon_name, "Mace");
    else if (weapon == dagger)
        strcpy(weapon_name, "Dagger");
    else if (weapon == magic_wand)
        strcpy(weapon_name, "Magic Wand");
    else if (weapon == normal_arrow)
        strcpy(weapon_name, "Normal Arrow");
}
int weapon_range(char weapon)
{
    if (weapon == mace || weapon == sword)
        return 0;
    else if (weapon == dagger || weapon == normal_arrow)
        return 5;
    else if (weapon == magic_wand)
        return 10;
}
int weapon_damage(char weapon)
{
    if (weapon == mace)
        return 5;
    else if (weapon == sword)
        return 10;
    else if (weapon == dagger)
        return 12;
    else if (weapon == magic_wand)
        return 15;
    else if (weapon == normal_arrow)
        return 5;
}
void change_weapon(game_struct *game, hero_struct *hero, char input)
{
    if (input != mace_key && input != dagger_key && input != magic_wand_key && input != normal_arrow_key && input != sword_key && input != 'w')
    {
        show_message("Invalid input!", game, hero);
        return;
    }

    if (input == 'w')
    {
        if (hero->weapon == nothing)
            show_message("You don't have any defualt weapon!", game, hero);
        else
        {
            char weaponname[100];
            weapon_name(weaponname, hero->weapon);
            char message[100];
            sprintf(message, "You put the %s in the backpack!", weaponname);
            show_message(message, game, hero);
            hero->weapon = nothing;
        }
    }
    else
    {
        if (hero->weapon != nothing)
        {
            show_message("You have already a weapon!", game, hero);
            return;
        }
        if (input == sword_key)
        {
            if (hero->sword_number == 0)
                show_message("You don't have any sword!", game, hero);
            else
            {
                hero->weapon = sword;
                show_message("Default weapon changed to sword!", game, hero);
            }
        }
        else if (input == mace_key)
        {
            if (hero->mace_number == 0)
                show_message("You don't have any mace!", game, hero);
            else
            {
                hero->weapon = mace;
                show_message("Default weapon changed to mace!", game, hero);
            }
        }
        else if (input == dagger_key)
        {
            if (hero->dagger_number == 0)
                show_message("You don't have any dagger!", game, hero);
            else
            {
                hero->weapon = dagger;
                show_message("Default weapon changed to dagger!", game, hero);
            }
        }
        else if (input == magic_wand_key)
        {
            if (hero->magic_wand_number == 0)
                show_message("You don't have any magic wand!", game, hero);
            else
            {
                hero->weapon = magic_wand;
                show_message("Default weapon changed to magic wand!", game, hero);
            }
        }
        else if (input == normal_arrow_key)
        {
            if (hero->normal_arrow_number == 0)
                show_message("You don't have any normal arrow!", game, hero);
            else
            {
                hero->weapon = normal_arrow;
                show_message("Default weapon changed to normal arrow!", game, hero);
            }
        }
    }
}
void collect_weapon(game_struct *game, hero_struct *hero, char weapon)
{
    if (weapon == dagger)
    {
        hero->dagger_number += 10;
        show_message("You have found 10 daggers!", game, hero);
    }
    else if (weapon == sword)
    {
        hero->sword_number = 1;
        show_message("You have found a sword!", game, hero);
    }
    else if (weapon == magic_wand)
    {
        hero->magic_wand_number += 8;
        show_message("You have found 8 magic wands!", game, hero);
    }
    else if (weapon == normal_arrow)
    {
        hero->normal_arrow_number += 20;
        show_message("You have found 20 normal arrows!", game, hero);
    }
    else if (weapon == dagger_floor)
    {
        hero->dagger_number++;
        show_message("You have found a dagger!", game, hero);
    }
    else if (weapon == magic_wand_floor)
    {
        hero->magic_wand_number++;
        show_message("You have found a magic wand!", game, hero);
    }
    else if (weapon == normal_arrow_floor)
    {
        hero->normal_arrow_number++;
        show_message("You have found a normal arrow!", game, hero);
    }
}
void weapon_menu(game_struct *game, hero_struct *hero)
{
    int x, y;
    getmaxyx(stdscr, y, x);
    int col = x / 2, row = y / 2 - 6, interval = 10;
    int unicol = col - 4 * interval, keycol = col - 2 * interval, numcol = col, discol = col + 2 * interval, powercol = col + 4 * interval;
    int rowrow = row - 2, rowmace = row + 2, rowsword = row + 3, rowdagger = row + 9, rowmagic_wand = row + 10, rownormal_arrow = row + 11;
    clear_map(game);

    mvprintw(row - 6, x / 2 - 5, "Weapon menu");

    mvprintw(rowrow, unicol + 1 - strlen("Weapon") / 2, "Weapon");
    mvprintw(rowrow, keycol - strlen("Key") / 2, "Key");
    mvprintw(rowrow, numcol - strlen("Number") / 2, "Number");
    mvprintw(rowrow, discol - strlen("Range") / 2, "Range");
    mvprintw(rowrow, powercol - strlen("Power") / 2, "Power");

    mvprintw(row, x / 2 - strlen("Close-range weapons") / 2, "Close-range weapons");

    mvprintw(row + 7, x / 2 - strlen("Long-range weapons") / 2, "Long-range weapons");

    // print_unicode(rowmace, unicol, mace);
    // print_unicode(rowsword, unicol, sword);
    // print_unicode(rowdagger, unicol, dagger);
    // print_unicode(rowmagic_wand, unicol, magic_wand);
    // print_unicode(rownormal_arrow, unicol, normal_arrow);

    mvprintw(rowmace, unicol, "%lc", umace);
    mvprintw(rowsword, unicol, "%lc", usword);
    mvprintw(rowdagger, unicol, "%lc", udagger);
    mvprintw(rowmagic_wand, unicol, "%lc", umagic_wand);
    mvprintw(rownormal_arrow, unicol, "%lc", unormal_arrow);

    mvprintw(rowmace, keycol, "%c", mace_key);
    mvprintw(rowsword, keycol, "%c", sword_key);
    mvprintw(rowdagger, keycol, "%c", dagger_key);
    mvprintw(rowmagic_wand, keycol, "%c", magic_wand_key);
    mvprintw(rownormal_arrow, keycol, "%c", normal_arrow_key);

    mvprintw(rowmace, numcol, "%d", hero->mace_number);
    mvprintw(rowsword, numcol, "%d", hero->sword_number);
    mvprintw(rowdagger, numcol, "%d", hero->dagger_number);
    mvprintw(rowmagic_wand, numcol, "%d", hero->magic_wand_number);
    mvprintw(rownormal_arrow, numcol, "%d", hero->normal_arrow_number);

    mvprintw(rowmace, discol, "%d", weapon_range(mace));
    mvprintw(rowsword, discol, "%d", weapon_range(sword));
    mvprintw(rowdagger, discol, "%d", weapon_range(dagger));
    mvprintw(rowmagic_wand, discol, "%d", weapon_range(magic_wand));
    mvprintw(rownormal_arrow, discol, "%d", weapon_range(normal_arrow));

    mvprintw(rowmace, powercol, "%d", weapon_damage(mace));
    mvprintw(rowsword, powercol, "%d", weapon_damage(sword));
    mvprintw(rowdagger, powercol, "%d", weapon_damage(dagger));
    mvprintw(rowmagic_wand, powercol, "%d", weapon_damage(magic_wand));
    mvprintw(rownormal_arrow, powercol, "%d", weapon_damage(normal_arrow));

    mvprintw(row + 15, x / 2 - strlen("Press i to exit") / 2, "Press i to exit");
    while (1)
    {
        int c = getch();
        if (c == 'i')
            break;
        else if (c == 'w' || c == mace_key || c == sword_key || c == dagger_key || c == magic_wand_key || c == normal_arrow_key)
        {
            change_weapon(game, hero, c);
            break;
        }
        else if (c >= 'a' && c <= 'z')
            show_message("Invalid input!", game, hero);
    }
    // clear
    draw_map(game, hero);
}
void drop_weapon(game_struct *game, char weapon, int y, int x, hero_struct *hero)
{
    game->under_weapon[floor_number][y][x] = game->map[floor_number][y][x];
    if (weapon == dagger)
        game->map[floor_number][y][x] = dagger_floor;
    else if (weapon == magic_wand)
        game->map[floor_number][y][x] = magic_wand_floor;
    else if (weapon == normal_arrow)
        game->map[floor_number][y][x] = normal_arrow_floor;
    if (hero->x == x && hero->y == y)
        move_hero(game, hero, '5');
}
void delete_food(hero_struct *hero, char food)
{
    for (int i = 0; i < hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number; i++)
        if (hero->foods[i].name == food)
        {
            for (int j = i; j < hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number - 1; j++)
            {
                hero->foods[j] = hero->foods[j + 1];
                hero->foods[j].step_until_change = hero->foods[j + 1].step_until_change;
            }
            break;
        }
}
void food_menu(game_struct *game, hero_struct *hero)
{
    int x, y;
    int hunger_bar_size = 50;
    getmaxyx(stdscr, y, x);
    int col = x / 2, row = y / 2 - 6, interval = 10;
    int unicol = col - 2 * interval, keycol = col, numcol = col + 2 * interval;
    int rowrow = row - 2, rowregular_food = row + 2, rowexcellent_food = row + 6, rowmagic_food = row + 10;
    clear_map(game);

    mvprintw(row - 6, x / 2 - 5, "Food menu");
    mvprintw(row - 4, x / 2 - hunger_bar_size / 2 - 7, "Hunger");
    attron(COLOR_PAIR(11));
    for (int i = 0; i < hunger_bar_size; i++)
        mvprintw(row - 4, x / 2 - hunger_bar_size / 2 + i, " ");
    attron(COLOR_PAIR(12));
    for (int i = 0; i < hero->hunger * hunger_bar_size / max_hunger; i++)
        mvprintw(row - 4, x / 2 - hunger_bar_size / 2 + i, " ");
    attron(COLOR_PAIR(main_color));

    mvprintw(rowrow, unicol + 1 - strlen("Food") / 2, "Food");
    mvprintw(rowrow, keycol - strlen("Key") / 2, "Key");
    mvprintw(rowrow, numcol - strlen("Number") / 2, "Number");

    // print_unicode(rowregular_food, unicol, regular_food);
    // print_unicode(rowexcellent_food, unicol, excellent_food);
    // print_unicode(rowmagic_food, unicol, magic_food);

    mvprintw(rowregular_food, unicol, "%lc", uregular_food);
    mvprintw(rowexcellent_food, unicol, "%lc", uexcellant_food);
    mvprintw(rowmagic_food, unicol, "%lc", umagic_food);

    mvprintw(rowregular_food, keycol, "%c", regular_food_key);
    mvprintw(rowexcellent_food, keycol, "%c", excellent_food_key);
    mvprintw(rowmagic_food, keycol, "%c", magic_food_key);

    mvprintw(rowregular_food, numcol, "%d", hero->regular_food_number + hero->spoiled_food_number);
    mvprintw(rowexcellent_food, numcol, "%d", hero->excellent_food_number);
    mvprintw(rowmagic_food, numcol, "%d", hero->magic_food_number);

    mvprintw(row + 15, x / 2 - strlen("Press k to exit") / 2, "Press k to exit");
    while (1)
    {
        int c = getch();
        if (c == regular_food_key)
        {
            if (hero->regular_food_number + hero->spoiled_food_number == 0)
                show_message("You don't have any regular food!", game, hero);
            else
            {
                if (random_number(1, hero->regular_food_number + hero->spoiled_food_number) <= hero->regular_food_number)
                {
                    delete_food(hero, regular_food);
                    hero->health = hero_health;
                    hero->regular_food_number--;
                    show_message("Regular food used!", game, hero);
                    hero->hunger = 0;
                }
                else
                {
                    delete_food(hero, spoiled_food);
                    hero->spoiled_food_number--;
                    show_message("Spoiled food used!", game, hero);
                    damage_hero(spoiled_food_damage, hero, game);
                }
                return;
            }
        }
        else if (c == excellent_food_key)
        {
            if (hero->excellent_food_number == 0)
                show_message("You don't have any excellent food!", game, hero);
            else
            {
                delete_food(hero, excellent_food);
                hero->damage_step += food_step;
                hero->health = hero_health;
                hero->excellent_food_number--;
                show_message("Excellent food used!", game, hero);
                hero->hunger = 0;
                return;
            }
        }
        else if (c == magic_food_key)
        {
            if (hero->magic_food_number == 0)
                show_message("You don't have any magic food!", game, hero);
            else
            {
                delete_food(hero, magic_food);
                hero->speed_step += food_step;
                hero->health = hero_health;
                hero->magic_food_number--;
                show_message("Magic food used!", game, hero);
                hero->hunger = 0;
                return;
            }
        }
        else if (c == 'k')
            break;
        else if (c >= 'a' && c <= 'z')
            show_message("Invalid input!", game, hero);
    }
}
void spell_menu(game_struct *game, hero_struct *hero)
{
    int x, y;
    getmaxyx(stdscr, y, x);
    int col = x / 2, row = y / 2 - 6, interval = 10;
    int unicol = col - 2 * interval, keycol = col, numcol = col + 2 * interval;
    int rowrow = row - 2, rowhealth_spell = row + 2, rowspeed_spell = row + 5, rowdamage_spell = row + 8;
    clear_map(game);

    mvprintw(row - 6, x / 2 - 5, "Spell menu");

    mvprintw(rowrow, unicol + 1 - strlen("Spell") / 2, "Spell");
    mvprintw(rowrow, keycol - strlen("Key") / 2, "Key");
    mvprintw(rowrow, numcol - strlen("Number") / 2, "Number");

    // print_unicode(rowhealth_spell, unicol, health_spell);
    // print_unicode(rowspeed_spell, unicol, speed_spell);
    // print_unicode(rowdamage_spell, unicol, damage_spell);

    mvprintw(rowhealth_spell, unicol, "%lc", uhealth_spell);
    mvprintw(rowspeed_spell, unicol, "%lc", uspeed_spell);
    mvprintw(rowdamage_spell, unicol, "%lc", udamage_spell);

    mvprintw(rowhealth_spell, keycol, "%c", health_spell_key);
    mvprintw(rowspeed_spell, keycol, "%c", speed_spell_key);
    mvprintw(rowdamage_spell, keycol, "%c", damage_spell_key);

    mvprintw(rowhealth_spell, numcol, "%d", hero->health_spell_number);
    mvprintw(rowspeed_spell, numcol, "%d", hero->speed_spell_number);
    mvprintw(rowdamage_spell, numcol, "%d", hero->damage_spell_number);

    mvprintw(row + 15, x / 2 - strlen("Press j to exit") / 2, "Press j to exit");
    while (1)
    {
        int c = getch();
        if (c == health_spell_key)
        {
            if (hero->health_spell_number == 0)
                show_message("You don't have any health spell!", game, hero);
            else
            {
                hero->health_spell_number--;
                hero->health_step += spell_step;
                show_message("Health spell used!", game, hero);
                return;
            }
        }
        else if (c == speed_spell_key)
        {
            if (hero->speed_spell_number == 0)
                show_message("You don't have any speed spell!", game, hero);
            else
            {
                hero->speed_spell_number--;
                hero->speed_step += spell_step;
                show_message("Speed spell used!", game, hero);
                return;
            }
        }
        else if (c == damage_spell_key)
        {
            if (hero->damage_spell_number == 0)
                show_message("You don't have any damage spell!", game, hero);
            else
            {
                hero->damage_spell_number--;
                hero->damage_step += spell_step;
                show_message("Damage spell used!", game, hero);
                return;
            }
        }
        else if (c == 'j')
            break;
        else if (c >= 'a' && c <= 'z')
            show_message("Invalid input!", game, hero);
    }
}
int collect_food(game_struct *game, hero_struct *hero, char food)
{
    if (hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number == max_food_number)
    {
        show_message("You can't carry more food!", game, hero);
        return 0;
    }
    else
    {
        hero->foods[hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number].name = food;
        hero->foods[hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number].step_until_change = food_change_step;
        if (food == regular_food)
        {
            hero->foods[hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number].name = food;
            hero->regular_food_number++;
            show_message("You have found a regular food!", game, hero);
        }
        else if (food == spoiled_food)
        {
            hero->spoiled_food_number++;
            show_message("You have found a regular food!", game, hero);
        }
        else if (food == excellent_food)
        {
            hero->excellent_food_number++;
            show_message("You have found an excellent food!", game, hero);
        }
        else if (food == magic_food)
        {
            hero->magic_food_number++;
            show_message("You have found a magic food!", game, hero);
        }
        return 1;
    }
}
void food_step_decrease(hero_struct *hero)
{
    for (int i = 0; i < hero->regular_food_number + hero->spoiled_food_number + hero->excellent_food_number + hero->magic_food_number; i++)
    {
        if (hero->foods[i].name != spoiled_food)
            hero->foods[i].step_until_change--;
        if (hero->foods[i].step_until_change == 0)
        {
            if (hero->foods[i].name == regular_food)
            {
                hero->regular_food_number--;
                hero->spoiled_food_number++;
                hero->foods[i].name = spoiled_food;
            }
            else if (hero->foods[i].name == excellent_food)
            {
                hero->excellent_food_number--;
                hero->regular_food_number++;
                hero->foods[i].name = regular_food;
            }
            else if (hero->foods[i].name == magic_food)
            {
                hero->magic_food_number--;
                hero->regular_food_number++;
                hero->foods[i].name = regular_food;
            }
            hero->foods[i].step_until_change = food_change_step;
        }
    }
}
void collect_spell(game_struct *game, hero_struct *hero, char spell)
{
    if (spell == health_spell)
    {
        hero->health_spell_number++;
        show_message("You have found a health spell!", game, hero);
    }
    else if (spell == speed_spell)
    {
        hero->speed_spell_number++;
        show_message("You have found a speed spell!", game, hero);
    }
    else if (spell == damage_spell)
    {
        hero->damage_spell_number++;
        show_message("You have found a damage spell!", game, hero);
    }
}
void long_range_fire(game_struct *game, hero_struct *hero, int y, int x, int move_left, int direction, char weapon)
{
    if (move_left == 0)
    {
        drop_weapon(game, weapon, y, x, hero);
        show_message("You didn't hit anything!", game, hero);
        return;
    }
    int y1 = y, x1 = x;
    if (direction == 0)
        y1--;
    else if (direction == 1)
        x1++;
    else if (direction == 2)
        y1++;
    else
        x1--;
    char next = game->map[floor_number][y1][x1];
    if (next == nothing || next == wall[0] || next == wall[1] || next == pillar || next == door || next == pass_door || next == hidden_door || next == found_door || next == opened_pass_door || next == stairs)
    {
        drop_weapon(game, weapon, y, x, hero);
        show_message("You didn't hit anything!", game, hero);
        return;
    }

    if (floor_number != 4 && this_room_number[floor_number] != -1 && game->room[floor_number][this_room_number[floor_number]].enemy.exist && y1 == game->room[floor_number][this_room_number[floor_number]].enemy.loc[0] && x1 == game->room[floor_number][this_room_number[floor_number]].enemy.loc[1])
    {
        if (weapon == magic_wand)
            game->room[floor_number][this_room_number[floor_number]].enemy.mov_left = 0;
        if (hero->damage_step > 0)
            game->room[floor_number][this_room_number[floor_number]].enemy.health = max(0, game->room[floor_number][this_room_number[floor_number]].enemy.health - weapon_damage(weapon) * 2);
        else
            game->room[floor_number][this_room_number[floor_number]].enemy.health = max(0, game->room[floor_number][this_room_number[floor_number]].enemy.health - weapon_damage(weapon));
        if (game->room[floor_number][this_room_number[floor_number]].enemy.health == 0)
        {
            game->room[floor_number][this_room_number[floor_number]].enemy.exist = 0;
            game->map[floor_number][game->room[floor_number][this_room_number[floor_number]].enemy.loc[0]][game->room[floor_number][this_room_number[floor_number]].enemy.loc[1]] = flor;
            char message[100];
            sprintf(message, "You have killed the %s!", game->room[floor_number][this_room_number[floor_number]].enemy.enemy_name);
            show_message(message, game, hero);
        }
        else
        {
            char message[100];
            sprintf(message, "You have hit the %s!    health:%d", game->room[floor_number][this_room_number[floor_number]].enemy.enemy_name, game->room[floor_number][this_room_number[floor_number]].enemy.health);
            show_message(message, game, hero);
            move_enemy(game, hero, &game->room[floor_number][this_room_number[floor_number]].enemy);
        }
        return;
    }
    else if (floor_number == 4)
    {
        for (int i = 0; i < game->all_enemy_number; i++)
        {
            if (game->treasure_enemy[i].exist && y1 == game->treasure_enemy[i].loc[0] && x1 == game->treasure_enemy[i].loc[1])
            {
                if (weapon == magic_wand)
                    game->treasure_enemy[i].mov_left = 0;
                if (hero->damage_step > 0)
                    game->treasure_enemy[i].health = max(0, game->treasure_enemy[i].health - weapon_damage(weapon) * 2);
                else
                    game->treasure_enemy[i].health = max(0, game->treasure_enemy[i].health - weapon_damage(weapon));
                if (game->treasure_enemy[i].health == 0)
                {
                    game->treasure_enemy[i].exist = 0;
                    game->treasure_enemy_number--;
                    game->map[floor_number][game->treasure_enemy[i].loc[0]][game->treasure_enemy[i].loc[1]] = flor;
                    char message[100];
                    sprintf(message, "You have killed the %s!", game->treasure_enemy[i].enemy_name);
                    show_message(message, game, hero);
                    if (game->treasure_enemy_number == 0)
                    {
                        end_game(game, hero, 1);
                    }
                }
                else
                {
                    char message[100];
                    sprintf(message, "You have hit the %s!    health:%d", game->treasure_enemy[i].enemy_name, game->treasure_enemy[i].health);
                    show_message(message, game, hero);
                }
                return;
            }
        }
    }

    long_range_fire(game, hero, y1, x1, move_left - 1, direction, weapon);
}
void fire(game_struct *game, hero_struct *hero, int last_shot)
{

    if (hero->weapon == nothing)
    {
        show_message("You have no default weapon!", game, hero);
        return;
    }
    else if (hero->weapon == mace || hero->weapon == sword)
    {
        if (floor_number != 4)
        {
            if (this_room_number[floor_number] == -1)
            {
                show_message("You didn't hit anything!", game, hero);
                return;
            }
            if (game->room[floor_number][this_room_number[floor_number]].enemy.exist)
            {
                int enemy_y = game->room[floor_number][this_room_number[floor_number]].enemy.loc[0];
                int enemy_x = game->room[floor_number][this_room_number[floor_number]].enemy.loc[1];
                if (abs(hero->y - enemy_y) <= 1 && abs(hero->x - enemy_x) <= 1)
                {
                    if (hero->damage_step > 0)
                        game->room[floor_number][this_room_number[floor_number]].enemy.health = max(0, game->room[floor_number][this_room_number[floor_number]].enemy.health - weapon_damage(hero->weapon) * 2);
                    else
                        game->room[floor_number][this_room_number[floor_number]].enemy.health = max(0, game->room[floor_number][this_room_number[floor_number]].enemy.health - weapon_damage(hero->weapon));

                    if (game->room[floor_number][this_room_number[floor_number]].enemy.health == 0)
                    {
                        game->room[floor_number][this_room_number[floor_number]].enemy.exist = 0;
                        game->map[floor_number][enemy_y][enemy_x] = flor;
                        char message[100];
                        sprintf(message, "You have killed the %s!", game->room[floor_number][this_room_number[floor_number]].enemy.enemy_name);
                        show_message(message, game, hero);
                    }
                    else
                    {
                        char message[100];
                        sprintf(message, "You have hit the %s!    health:%d", game->room[floor_number][this_room_number[floor_number]].enemy.enemy_name, game->room[floor_number][this_room_number[floor_number]].enemy.health);
                        show_message(message, game, hero);
                        // move_enemy(game, hero, &game->room[floor_number][this_room_number[floor_number]].enemy);
                        // in line
                    }
                }
                else
                    show_message("You didn't hit anything!", game, hero);
            }
        }
        else
        {
            int hit = 0;
            for (int i = 0; i < game->all_enemy_number; i++)
            {
                if (game->treasure_enemy[i].exist && abs(hero->y - game->treasure_enemy[i].loc[0]) <= 1 && abs(hero->x - game->treasure_enemy[i].loc[1]) <= 1)
                {
                    if (hero->damage_step > 0)
                        game->treasure_enemy[i].health = max(0, game->treasure_enemy[i].health - weapon_damage(hero->weapon) * 2);
                    else
                        game->treasure_enemy[i].health = max(0, game->treasure_enemy[i].health - weapon_damage(hero->weapon));

                    if (game->treasure_enemy[i].health == 0)
                    {
                        game->treasure_enemy[i].exist = 0;
                        game->treasure_enemy_number--;
                        game->map[floor_number][game->treasure_enemy[i].loc[0]][game->treasure_enemy[i].loc[1]] = flor;
                        char message[100];
                        sprintf(message, "You have killed the %s!", game->treasure_enemy[i].enemy_name);
                        show_message(message, game, hero);
                        if (game->treasure_enemy_number == 0)
                        {
                            end_game(game, hero, 1);
                        }
                    }
                    else
                    {
                        char message[100];
                        sprintf(message, "You have hit the %s!    health:%d", game->treasure_enemy[i].enemy_name, game->treasure_enemy[i].health);
                        show_message(message, game, hero);
                    }
                    hit = 1;
                }
            }
            if (hit == 0)
                show_message("You didn't hit anything!", game, hero);
            for (int i = 0; i < game->all_enemy_number; i++)
                if (game->treasure_enemy[i].exist)
                    move_enemy(game, hero, &game->treasure_enemy[i]);
        }
    }
    else
    {
        while (1)
        {
            int c = getch();
            if (last_shot == -1)
            {
                show_message("You have to choose a direction!", game, hero);
                return;
            }
            if (last_shot >= 0)
            {
                if (last_shot == 0)
                    c = '8';
                else if (last_shot == 1)
                    c = '6';
                else if (last_shot == 2)
                    c = '2';
                else if (last_shot == 3)
                    c = '4';
            }
            if (c == '8' || c == '6' || c == '2' || c == '4' || c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT)
            {

                if (c == '8' || c == KEY_UP)
                {
                    long_range_fire(game, hero, hero->y, hero->x, weapon_range(hero->weapon), 0, hero->weapon);
                    last_shot_dir = 0;
                }
                else if (c == '6' || c == KEY_RIGHT)
                {
                    long_range_fire(game, hero, hero->y, hero->x, weapon_range(hero->weapon), 1, hero->weapon);
                    last_shot_dir = 1;
                }
                else if (c == '2' || c == KEY_DOWN)
                {
                    long_range_fire(game, hero, hero->y, hero->x, weapon_range(hero->weapon), 2, hero->weapon);
                    last_shot_dir = 2;
                }
                else if (c == '4' || c == KEY_LEFT)
                {
                    long_range_fire(game, hero, hero->y, hero->x, weapon_range(hero->weapon), 3, hero->weapon);
                    last_shot_dir = 3;
                }

                if (hero->weapon == dagger)
                {
                    hero->dagger_number--;
                    if (hero->dagger_number == 0)
                    {
                        hero->weapon = nothing;
                        show_message("You don't have a Dagger anymore!", game, hero);
                    }
                }
                else if (hero->weapon == magic_wand)
                {
                    hero->magic_wand_number--;
                    if (hero->magic_wand_number == 0)
                    {
                        hero->weapon = nothing;
                        show_message("You don't have a Magic Wand anymore!", game, hero);
                    }
                }
                else if (hero->weapon == normal_arrow)
                {
                    hero->normal_arrow_number--;
                    if (hero->normal_arrow_number == 0)
                    {
                        hero->weapon = nothing;
                        show_message("You don't have a Normal Arrow anymore!", game, hero);
                    }
                }
                for (int i = 0; i < game->all_enemy_number; i++)
                    if (game->treasure_enemy[i].exist)
                        move_enemy(game, hero, &game->treasure_enemy[i]);
                break;
            }
            else if (c == ' ')
                break;
        }
    }
}

void end_game(game_struct *game, hero_struct *hero, int win)
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    int row = y / 2;
    hero->score = hero->gold * 10;
    if (win)
    {
        hero->score += 1000;
        hero->gold += 500;
        mvprintw(row - 7, x / 2 - 1, "%lc", L'🏆');
        mvprintw(row - 5, x / 2 - strlen("You won!") / 2, "You won!");
    }
    else
    {
        mvprintw(row - 7, x / 2 - 1, "%lc", L'💀');
        mvprintw(row - 5, x / 2 - strlen("You lost!") / 2, "You lost!");
    }

    mvprintw(row, x / 2 - strlen("Score : ") / 2, "Score : %d", hero->score);
    mvprintw(row + 5, x / 2 - strlen("Gold : ") / 2, "Gold : %d", hero->gold);
    mvprintw(row + 15, x / 2 - strlen("Press q to exit") / 2, "Press q to exit");
    while (1)
    {
        int c = getch();
        if (c == 'q')
            break;
    }
    game_is_running = 0;
}

void make_map(game_struct *game)
{
    for (int fl_number = 0; fl_number < 4; fl_number++)
    {
        int room_number = random_number(min_room_number, max_room_number);
        int stairs_room = random_number(1, room_number - 1);
        int master_key_room = random_number(1, room_number - 1);
        game->room_number[fl_number] = room_number;
        if (fl_number == 3)
            treasure_room = random_number(1, room_number - 1);
        for (int i = 0; i < room_number; i++)
        {
            if (fl_number != 0 && i == 0)
            {
                game->room[fl_number][i].show = 1;
                i++;
            }
            int room_height = random_number(min_room_size, max_room_height), room_width = random_number(min_room_size, max_room_width);
            int room_starty = random_number(rooms_space, map_height - room_height - 1), room_startx = random_number(rooms_space, map_width - room_width - 1);
            int Collision = 0;
            for (int j = 0; j < i; j++)
                if ((room_starty < game->room[fl_number][j].starty + game->room[fl_number][j].height + rooms_space && room_starty + room_height > game->room[fl_number][j].starty - rooms_space) || (room_starty < game->room[fl_number][j].starty - rooms_space && room_starty + room_height > game->room[fl_number][j].starty - rooms_space))
                    if ((room_startx < game->room[fl_number][j].startx + game->room[fl_number][j].width + rooms_space && room_startx + room_width > game->room[fl_number][j].startx - rooms_space) || (room_startx < game->room[fl_number][j].startx - rooms_space && room_startx + room_width > game->room[fl_number][j].startx - rooms_space))
                    {
                        Collision = 1;
                        break;
                    }

            if (!Collision)
            {
                game->room[fl_number][i].starty = room_starty;
                game->room[fl_number][i].startx = room_startx;
                game->room[fl_number][i].height = room_height;
                game->room[fl_number][i].width = room_width;
                game->room[fl_number][i].door_password = 0;
                if (i == 0)
                    game->room[fl_number][i].show = 1;
                else
                    game->room[fl_number][i].show = 0;
                set_room_theme(game->room[fl_number][i].theme, fl_number, i);
                if (random_number(1, 100) <= second_door_probability)
                    game->room[fl_number][i].door_number = 2;
                else
                    game->room[fl_number][i].door_number = 1;

                for (int j = 1; j < room_height - 1; j++)
                    for (int h = 1; h < room_width - 1; h++)
                        game->map[fl_number][room_starty + j][room_startx + h] = flor;
                for (int j = 0; j < room_width; j++)
                {
                    game->map[fl_number][room_starty][room_startx + j] = wall[0];
                    game->map[fl_number][room_starty + room_height - 1][room_startx + j] = wall[0];
                }
                for (int j = 0; j < room_height; j++)
                {
                    game->map[fl_number][room_starty + j][room_startx] = wall[1];
                    game->map[fl_number][room_starty + j][room_startx + room_width - 1] = wall[1];
                }
                for (int j = 0; j < game->room[fl_number][i].door_number; j++)
                {
                    int door_side = random_number(1, 4);
                    char door_char;
                    int selected_door = random_number(1, 100);
                    if (j > 0 && selected_door <= pass_door_probability)
                    {
                        door_char = pass_door;
                        int key_side = random_number(1, 4);
                        if (key_side == 1)
                            game->map[fl_number][room_starty][room_startx] = pass_door_key;
                        else if (key_side == 2)
                            game->map[fl_number][room_starty][room_startx + room_width - 1] = pass_door_key;
                        else if (key_side == 3)
                            game->map[fl_number][room_starty + room_height - 1][room_startx + room_width - 1] = pass_door_key;
                        else
                            game->map[fl_number][room_starty + room_height - 1][room_startx] = pass_door_key;
                        if (random_number(1, 100) <= change_pass_door)
                            game->room[fl_number][i].change_door_password = 1;
                        else
                            game->room[fl_number][i].change_door_password = 0;
                    }
                    else if (j > 0 && selected_door <= pass_door_probability + hidden_door_probability)
                        door_char = hidden_door;
                    else
                    {
                        game->room[fl_number][i].change_door_password = 0;
                        door_char = door;
                    }

                    if (door_side == 1)
                    {
                        game->room[fl_number][i].door[j][0] = room_starty;
                        game->room[fl_number][i].door[j][1] = random_number(room_startx + 1, room_startx + room_width - 2);
                    }
                    else if (door_side == 3)
                    {
                        game->room[fl_number][i].door[j][0] = room_starty + room_height - 1;
                        game->room[fl_number][i].door[j][1] = random_number(room_startx + 1, room_startx + room_width - 2);
                    }
                    else if (door_side == 4)
                    {
                        game->room[fl_number][i].door[j][0] = random_number(room_starty + 1, room_starty + room_height - 2);
                        game->room[fl_number][i].door[j][1] = room_startx;
                    }
                    else
                    {
                        game->room[fl_number][i].door[j][0] = random_number(room_starty + 1, room_starty + room_height - 2);
                        game->room[fl_number][i].door[j][1] = room_startx + room_width - 1;
                    }
                    game->room[fl_number][i].door_side[j] = door_side;
                    int door_collision = 0;
                    for (int h = 0; h < j; h++)
                        if (game->room[fl_number][i].door[j][0] == game->room[fl_number][i].door[h][0] && game->room[fl_number][i].door[j][1] == game->room[fl_number][i].door[h][1])
                        {
                            door_collision = 1;
                            break;
                        }
                    if (door_collision)
                        j--;
                    else
                        game->map[fl_number][game->room[fl_number][i].door[j][0]][game->room[fl_number][i].door[j][1]] = door_char;
                }
                int trap_p = trap_probability1000;
                if (fl_number == 3 && i == treasure_room)
                {
                    trap_p = 200;
                    locate_item(game, &game->room[fl_number][i], treasure_char, fl_number);
                }
                locate_item_chance(game, &game->room[fl_number][i], trap, fl_number, trap_p);
                locate_item_chance(game, &game->room[fl_number][i], pillar, fl_number, pillar_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], gold, fl_number, gold_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], black_gold, fl_number, black_gold_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], dagger, fl_number, weapon_percentage1000);
                locate_item_chance(game, &game->room[fl_number][i], sword, fl_number, weapon_percentage1000);
                locate_item_chance(game, &game->room[fl_number][i], magic_wand, fl_number, weapon_percentage1000);
                locate_item_chance(game, &game->room[fl_number][i], normal_arrow, fl_number, weapon_percentage1000);
                locate_item_chance(game, &game->room[fl_number][i], health_spell, fl_number, spell_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], speed_spell, fl_number, spell_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], damage_spell, fl_number, spell_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], regular_food, fl_number, food_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], spoiled_food, fl_number, food_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], excellent_food, fl_number, food_probability1000);
                locate_item_chance(game, &game->room[fl_number][i], magic_food, fl_number, food_probability1000);
                if (i == master_key_room)
                    locate_item(game, &game->room[fl_number][i], master_key, fl_number);
                locate_enemy(game, &game->room[fl_number][i], &game->room[fl_number][i].enemy, fl_number, enemy_probability);

                if (fl_number < 3 && i == stairs_room)
                {
                    locate_stairs(game, i, fl_number);
                    game->map[fl_number][stairs_location[1][fl_number][0]][stairs_location[1][fl_number][1]] = stairs;
                    game->map[fl_number][stairs_location[0][fl_number + 1][0]][stairs_location[0][fl_number + 1][1]] = stairs;
                    game->room[fl_number + 1][0].startx = game->room[fl_number][i].startx;
                    game->room[fl_number + 1][0].starty = game->room[fl_number][i].starty;
                    game->room[fl_number + 1][0].height = game->room[fl_number][i].height;
                    game->room[fl_number + 1][0].width = game->room[fl_number][i].width;
                    strcpy(game->room[fl_number + 1][0].theme, game->room[fl_number][i].theme);
                    game->room[fl_number + 1][0].door_number = game->room[fl_number][i].door_number;
                    for (int h = 0; h < game->room[fl_number][i].door_number; h++)
                    {
                        game->room[fl_number + 1][0].door[h][0] = game->room[fl_number][i].door[h][0];
                        game->room[fl_number + 1][0].door[h][1] = game->room[fl_number][i].door[h][1];
                        game->room[fl_number + 1][0].door_side[h] = game->room[fl_number][i].door_side[h];
                    }
                    for (int h = room_starty; h < room_starty + room_height; h++)
                        for (int k = room_startx; k < room_startx + room_width; k++)
                            game->map[fl_number + 1][h][k] = game->map[fl_number][h][k];
                }
            }
            else
                i--;
        }
        make_corridor(game, fl_number);
    }

    game->treasure_room.height = treasure_room_height;
    game->treasure_room.width = treasure_room_width;
    game->treasure_room.startx = (map_width - treasure_room_width) / 2;
    game->treasure_room.starty = (map_height - treasure_room_height) / 2;
    strcpy(game->treasure_room.theme, treasure);
    for (int j = 1; j < game->treasure_room.height - 1; j++)
        for (int h = 1; h < game->treasure_room.width - 1; h++)
            game->map[4][game->treasure_room.starty + j][game->treasure_room.startx + h] = flor;
    for (int j = 0; j < game->treasure_room.width; j++)
    {
        game->map[4][game->treasure_room.starty][game->treasure_room.startx + j] = wall[0];
        game->map[4][game->treasure_room.starty + game->treasure_room.height - 1][game->treasure_room.startx + j] = wall[0];
    }
    for (int j = 0; j < game->treasure_room.height; j++)
    {
        game->map[4][game->treasure_room.starty + j][game->treasure_room.startx] = wall[1];
        game->map[4][game->treasure_room.starty + j][game->treasure_room.startx + game->treasure_room.width - 1] = wall[1];
    }
    game->treasure_enemy_number = random_number(min_treasure_enemy, max_treasure_enemy);
    game->all_enemy_number = game->treasure_enemy_number;
    locate_item_chance(game, &game->treasure_room, trap, 4, 50);
    for (int i = 0; i < game->treasure_enemy_number; i++)
        locate_enemy(game, &game->treasure_room, &game->treasure_enemy[i], 4, 100);
}

void draw_map(game_struct *game, hero_struct *hero)
{
    game_info(game, hero);
    clear_map(game);
    // map
    if (floor_number < 4)
        for (int j = 0; j < map_height; j++)
            for (int h = 0; h < map_width; h++)
            {
                char c;
                if (show_map == 0)
                    c = game->show_map[floor_number][j][h];
                else
                    c = game->map[floor_number][j][h];
                attron_theme_item(c, c, show_map);
                // mvprintw(starty_map_draw + j, startx_map_draw + h, "%c", c);
                print_unicode(starty_map_draw + j, startx_map_draw + h, c);
                attron(COLOR_PAIR(main_color));
            }

    if (floor_number < 4)
    {
        for (int i = 0; i < game->room_number[floor_number]; i++)
        {
            if (show_map || game->room[floor_number][i].show)
            {
                attron_theme_room(game->room[floor_number][i].theme);
                int j = 0, savej = 0, j1 = game->room[floor_number][i].height, h = 0, h1 = game->room[floor_number][i].width, change_h = 0;
                if (strcmp(game->room[floor_number][i].theme, nightmare) == 0 && show_map == 0)
                {
                    if (this_room_number[floor_number] == i)
                    {
                        change_h = 1;
                        j = max(0, hero->y - game->room[floor_number][i].starty - 2);
                        savej = j;
                        j1 = min(game->room[floor_number][i].height, hero->y - game->room[floor_number][i].starty + 3);
                        h = max(0, hero->x - game->room[floor_number][i].startx - 2);
                        h1 = min(game->room[floor_number][i].width, hero->x - game->room[floor_number][i].startx + 3);
                    }
                    else
                    {
                        j1 = 0;
                        h1 = 0;
                    }
                }
                for (; j < j1; j++)
                {
                    if (change_h)
                        h = max(0, hero->x - game->room[floor_number][i].startx - 2);
                    else
                        h = 0;
                    for (; h < h1; h++)
                    {
                        attron_theme_room(game->room[floor_number][i].theme);
                        char c = game->map[floor_number][game->room[floor_number][i].starty + j][game->room[floor_number][i].startx + h];
                        if (c == trap && show_map == 0)
                        {
                            c = flor;
                        }
                        else if (c == used_trap || c == show_trap)
                        {
                            c = trap;
                        }
                        else if (c == opened_pass_door)
                        {
                            c = pass_door;
                        }
                        else if (c == hidden_door && show_map == 0)
                        {
                            if (j == 0 || j == j1 - 1)
                                c = wall[0];
                            else
                                c = wall[1];
                        }
                        else if (c == found_door)
                        {
                            c = hidden_door;
                        }
                        attron_theme_item(c, game->map[floor_number][game->room[floor_number][i].starty + j][game->room[floor_number][i].startx + h], show_map);
                        // mvprintw(starty_map_draw + game->room[floor_number][i].starty + j, startx_map_draw + game->room[floor_number][i].startx + h, "%c", c);
                        print_unicode(starty_map_draw + game->room[floor_number][i].starty + j, startx_map_draw + game->room[floor_number][i].startx + h, c);
                        attron_theme_room(game->room[floor_number][i].theme);
                    }
                }
            }
        }
    }
    else
    {
        attron_theme_room(game->treasure_room.theme);
        for (int j = 0; j < game->treasure_room.height; j++)
        {
            for (int h = 0; h < game->treasure_room.width; h++)
            {
                attron_theme_room(game->treasure_room.theme);
                char c = game->map[floor_number][game->treasure_room.starty + j][game->treasure_room.startx + h];
                if (c == trap && show_map == 0)
                {
                    c = flor;
                }
                else if (c == used_trap || c == show_trap)
                {
                    c = trap;
                }
                attron_theme_item(c, game->map[floor_number][game->treasure_room.starty + j][game->treasure_room.startx + h], show_map);
                print_unicode(starty_map_draw + game->treasure_room.starty + j, startx_map_draw + game->treasure_room.startx + h, c);
                attron_theme_room(game->treasure_room.theme);
            }
        }
    }

    // hero
    attron(COLOR_PAIR(hero_deafualt_color));
    mvprintw(hero->y + starty_map_draw, hero->x * 2 + startx_map_draw, "%lc", uhero_char);
    // print_unicode(hero->y + starty_map_draw, hero->x + startx_map_draw, hero_char);
    attron(COLOR_PAIR(main_color));

    // enemy
    if (floor_number < 4)
    {
        for (int i = 0; i < game->room_number[floor_number]; i++)
        {
            if ((game->room[floor_number][i].show || show_map) && game->room[floor_number][i].enemy.exist)
            {
                if (strcmp(game->room[floor_number][i].theme, nightmare) != 0 || show_map || (abs(hero->x - game->room[floor_number][i].enemy.loc[1]) <= 2 && abs(hero->y - game->room[floor_number][i].enemy.loc[0]) <= 2))
                {
                    attron(COLOR_PAIR(enemy_color));
                    mvprintw(game->room[floor_number][i].enemy.loc[0] + starty_map_draw, (game->room[floor_number][i].enemy.loc[1] + startx_map_draw) * 2 - startx_map_draw, "%c", game->room[floor_number][i].enemy.enemy_char);
                    // print_unicode(game->room[floor_number][i].enemy.loc[0] + starty_map_draw, game->room[floor_number][i].enemy.loc[1] + startx_map_draw, game->room[floor_number][i].enemy.enemy_char);
                    attron(COLOR_PAIR(main_color));
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < game->all_enemy_number; i++)
        {
            if (game->treasure_enemy[i].exist)
            {
                attron(COLOR_PAIR(enemy_color));
                mvprintw(game->treasure_enemy[i].loc[0] + starty_map_draw, (game->treasure_enemy[i].loc[1] + startx_map_draw) * 2 - startx_map_draw, "%c", game->treasure_enemy[i].enemy_char);
                attron(COLOR_PAIR(main_color));
            }
        }
    }
    refresh();
}

int move_hero(game_struct *game, hero_struct *hero, int c)
{
    curs_set(0);
    int x = hero->x, y = hero->y;
    char now = game->map[floor_number][y][x];
    if ((c >= '7' && c <= '9') || c == KEY_UP)
        y -= 1;
    if ((c >= '1' && c <= '3') || c == KEY_DOWN)
        y += 1;
    if (c == '3' || c == '6' || c == '9' || c == KEY_RIGHT)
        x += 1;
    if (c == '1' || c == '4' || c == '7' || c == KEY_LEFT)
        x -= 1;
    char next = game->map[floor_number][y][x];
    if (next != nothing && next != pillar && next != wall[0] && next != wall[1] && (game->map[floor_number][hero->y][hero->x] != corridor || next != stairs) && x >= 0 && x < map_width && y >= 0 && y < map_height)
    {
        int loc_changed = 1;
        hero->step++;
        int hunger_damaged = 0;
        if (hero->hunger < max_hunger)
            hero->hunger++;
        else
        {
            damage_hero(hunger_damage, hero, game);
            hunger_damaged = 1;
        }
        if (next == stairs && game->map[floor_number][hero->y][hero->x] != corridor)
        {
            if (floor_number < 3 && y == stairs_location[1][floor_number][0] && x == stairs_location[1][floor_number][1])
                floor_number++;
            else
                floor_number--;
        }
        else
        {

            if (pick_up && (next == dagger || next == sword || next == magic_wand || next == normal_arrow || next == dagger_floor || next == magic_wand_floor || next == normal_arrow_floor))
            {
                if (floor_number == 4 || strcmp(game->room[floor_number][this_room_number[floor_number]].theme, nightmare) != 0)
                {
                    collect_weapon(game, hero, next);
                    if (next == dagger || next == sword || next == magic_wand || next == normal_arrow)
                        game->map[floor_number][y][x] = flor;
                    else
                    {
                        next = game->under_weapon[floor_number][y][x];
                        game->map[floor_number][y][x] = next;
                    }
                }
                else
                    game->map[floor_number][y][x] = flor;
            }
            if (next == door)
            {
                enter_room(game, x, y);
            }
            if (next == corridor)
            {
                this_room_number[floor_number] = -1;
            }
            if (next == door || next == corridor)
            {
                show_corridor(game, x, y, floor_number, 5);
            }
            if (next == trap || next == show_trap)
            {
                damage_hero(trap_damage, hero, game);
                game->map[floor_number][y][x] = used_trap;
                show_message("You have been trapped!", game, hero);
            }
            if (next == gold && pick_up)
            {
                if (strcmp(game->room[floor_number][this_room_number[floor_number]].theme, nightmare) != 0)
                {
                    char message[100];
                    int gain = random_number(gold_min, gold_max);
                    hero->gold += gain;
                    sprintf(message, "You have found %d gold!", gain);
                    show_message(message, game, hero);
                }
                game->map[floor_number][y][x] = flor;
            }
            if (next == black_gold && pick_up)
            {
                if (strcmp(game->room[floor_number][this_room_number[floor_number]].theme, nightmare) != 0)
                {
                    char message[100];
                    int gain = random_number(gold_min, gold_max) * random_number(2, black_gold_times);
                    hero->gold += gain;
                    sprintf(message, "You have found %d gold!", gain);
                    show_message(message, game, hero);
                }
                game->map[floor_number][y][x] = flor;
            }
            if (next == pass_door_key)
            {
                x = hero->x;
                y = hero->y;
                if (now != corridor)
                {
                    change_pass_timer = time(NULL);
                    game->room[floor_number][this_room_number[floor_number]].door_password = random_number(1000, 9999);
                    show_pass(game, hero, game->room[floor_number][this_room_number[floor_number]].door_password);
                }
            }
            if (next == pass_door)
            {
                int open_door = password_textbox(game->room[floor_number][this_room_number[floor_number]].door_password, game, hero, 0);
                if (open_door == 1)
                {
                    enter_room(game, x, y);
                    game->map[floor_number][y][x] = opened_pass_door;
                }
                else
                {
                    // if(open_door==0)
                    // security();
                    loc_changed = 0;
                    hero->step--;
                    if (hero->hunger > 0)
                        hero->hunger--;
                    if (hunger_damaged && hero->health < hero_health)
                        hero->health = min(hero_health, hero->health + hunger_damage);

                    x = hero->x;
                    y = hero->y;
                }
            }
            if (next == opened_pass_door)
            {
                enter_room(game, x, y);
            }
            if (next == master_key)
            {
                if ((game->room[floor_number][this_room_number[floor_number]].theme, nightmare) != 0)
                {
                    hero->master_key_number++;
                    show_message("You have found a master key!", game, hero);
                }
                game->map[floor_number][y][x] = flor;
            }
            if (next == hidden_door)
            {
                enter_room(game, x, y);
                game->map[floor_number][y][x] = found_door;
            }
            if (next == found_door)
            {
                enter_room(game, x, y);
            }
            if (game->room[floor_number][this_room_number[floor_number]].enemy.exist && y == game->room[floor_number][this_room_number[floor_number]].enemy.loc[0] && x == game->room[floor_number][this_room_number[floor_number]].enemy.loc[1])
            {
                x = hero->x;
                y = hero->y;
            }
            if (pick_up && (next == health_spell || next == damage_spell || next == speed_spell))
            {
                if (strcmp(game->room[floor_number][this_room_number[floor_number]].theme, nightmare) != 0)
                    collect_spell(game, hero, next);
                game->map[floor_number][y][x] = flor;
            }
            if (pick_up && (next == regular_food || next == spoiled_food || next == excellent_food || next == magic_food))
            {
                if (strcmp(game->room[floor_number][this_room_number[floor_number]].theme, nightmare) != 0)
                {
                    if (collect_food(game, hero, next))
                        game->map[floor_number][y][x] = flor;
                }
                else
                    game->map[floor_number][y][x] = flor;
            }
            if (next == treasure_char)
            {
                floor_number++;
                x = game->treasure_room.startx + game->treasure_room.width / 2;
                y = game->treasure_room.starty + game->treasure_room.height / 2;
            }

            if (loc_changed)
            {
                if (hero->speed_step > 0 && first_step)
                {
                    hero->step--;
                    if (hero->hunger > 0)
                        hero->hunger--;
                    if (hunger_damaged && hero->health < hero_health)
                        hero->health = min(hero_health, hero->health + hunger_damage);
                    first_step = 0;
                    loc_changed = 0;
                }
                else
                {
                    food_step_decrease(hero);
                    first_step = 1;
                    if (hero->health_step > 0)
                        hero->health_step--;
                    if (hero->damage_step > 0)
                        hero->damage_step--;
                    if (hero->speed_step > 0)
                        hero->speed_step--;
                }
            }

            hero->x = x;
            hero->y = y;
            if (floor_number != 4 && loc_changed && next != door && next != corridor && next != pass_door_key && next != pass_door && next != opened_pass_door && next != hidden_door && next != found_door)
            {
                if (this_room_number[floor_number] != -1 && game->room[floor_number][this_room_number[floor_number]].enemy.exist)
                    move_enemy(game, hero, &game->room[floor_number][this_room_number[floor_number]].enemy);
            }
            else if (floor_number == 4)
            {
                for (int i = 0; i < game->all_enemy_number; i++)
                    if (game->treasure_enemy[i].exist)
                        move_enemy(game, hero, &game->treasure_enemy[i]);
            }
        }
        draw_map(game, hero);
        return 1;
    }
    return 0;
}

void run_game(game_struct *game, hero_struct *hero)
{
    while (game_is_running)
    {
        int x = getch();
        if (x != ERR)
        {
            if ((x >= '1' && x <= '9' && x != '5') || x == KEY_UP || x == KEY_DOWN || x == KEY_LEFT || x == KEY_RIGHT)
            {
                if (move_hero(game, hero, x) && preesed_f)
                {
                    if (x == '8' || x == KEY_UP)
                        f_button(0, hero, game);
                    else if (x == '2' || x == KEY_DOWN)
                        f_button(2, hero, game);
                    else if (x == '6' || x == KEY_RIGHT)
                        f_button(1, hero, game);
                    else if (x == '4' || x == KEY_LEFT)
                        f_button(3, hero, game);
                    preesed_f = 0;
                }
            }
            else if (x == 'f')
            {
                preesed_f = 1;
                // if (preesed_f)
                //     preesed_f = 0;
                // else
                //     preesed_f = 1;
            }
            // else if (x == 'n')
            // {
            //     new_game();
            //     break;
            // }
            // else if (x == 'p' && floor_number < 4)
            // {
            //     floor_number++;
            //     mvprintw(0, 0, "%d", floor_number);
            //     if (floor_number == 4)
            //     {

            //         hero->x = game->treasure_room.startx + game->treasure_room.width / 2;
            //         hero->y = game->treasure_room.starty + game->treasure_room.height / 2;
            //     }
            //     draw_map(game, hero);
            // }
            // else if (x == 'o' && floor_number > 0)
            // {
            //     floor_number--;
            //     mvprintw(0, 0, "%d", floor_number);
            //     draw_map(game, hero);
            // }
            else if (x == 'm')
            {
                if (show_map)
                    show_map = 0;
                else
                    show_map = 1;
                draw_map(game, hero);
            }
            else if (x == 'g')
            {
                if (pick_up)
                    pick_up = 0;
                else
                    pick_up = 1;
            }
            else if (x == 's')
            {
                trap_hdoor_check(game, hero);
                draw_map(game, hero);
            }
            else if (x == 'w' || x == mace_key || x == dagger_key || x == sword_key || x == magic_wand_key || x == normal_arrow_key)
            {
                change_weapon(game, hero, x);
                game_info(game, hero);
            }
            else if (x == 'i')
            {
                weapon_menu(game, hero);
            }
            else if (x == ' ')
            {
                fire(game, hero, -2);
                if (floor_number != 4)
                    if (this_room_number[floor_number] != -1 && game->room[floor_number][this_room_number[floor_number]].enemy.exist)
                        move_enemy(game, hero, &game->room[floor_number][this_room_number[floor_number]].enemy);
                draw_map(game, hero);
            }
            else if (x == 'a')
            {
                fire(game, hero, last_shot_dir);
                if (floor_number != 4)
                    if (this_room_number[floor_number] != -1 && game->room[floor_number][this_room_number[floor_number]].enemy.exist)
                        move_enemy(game, hero, &game->room[floor_number][this_room_number[floor_number]].enemy);
                draw_map(game, hero);
            }
            else if (x == 'j')
            {
                spell_menu(game, hero);
                draw_map(game, hero);
            }
            else if (x == 'k')
            {
                food_menu(game, hero);
                draw_map(game, hero);
            }
            else if (x == 'q')
                break;
        }
        for (int i = 0; i < 10; i++)
        {
            if (time(NULL) - messag_time[i] >= message_time)
            {
                move(message_row + i, 0);
                clrtoeol();
                is_message[i] = 0;
            }
        }
        if (time(NULL) - pass_timer >= pass_time)
        {
            move(message_row + message_pass_space, 0);
            clrtoeol();
        }
        if (time(NULL) - change_pass_timer >= change_pass_time)
        {
            for (int i = 0; i < game->room_number[floor_number]; i++)
                if (game->room[floor_number][i].door_password != 0)
                    game->room[floor_number][i].door_password = random_number(1000, 9999);
        }
        if (hero->health < hero_health && time(NULL) - last_attack >= heal_after_attack_time && time(NULL) - heal_interval >= heal_interval_time)
        {
            heal_interval = time(NULL);
            hero->health += heal_amount;
            if (hero->health_step > 0)
                hero->health += heal_amount;
            if (hero->health > hero_health)
                hero->health = hero_health;
            game_info(game, hero);
        }
    }
}

void set_diffi()
{
    if (difficulty == 1)
    {
        trap_probability1000 = 15;
        spell_probability1000 = 10;
        food_probability1000 = 5;
        enemy_probability=60;
        weapon_percentage1000=5;
    }
    else if (difficulty == 2)
    {
        trap_probability1000 = 20;
        spell_probability1000 = 15;
        food_probability1000 = 4;
        enemy_probability=70;
        weapon_percentage1000=6;
    }
    else if (difficulty == 3)
    {
        trap_probability1000 = 25;
        spell_probability1000 = 15;
        food_probability1000 = 3;
        enemy_probability=80;
        weapon_percentage1000=7;
    }
    
}

void new_game()
{
    set_diffi();
    if (strcmp(hero_color, "Red") == 0)
        hero_deafualt_color = red_color;
    else if (strcmp(hero_color, "Green") == 0)
        hero_deafualt_color = green_color;
    else if (strcmp(hero_color, "Yellow") == 0)
        hero_deafualt_color = yellow_color;
    else if (strcmp(hero_color, "Blue") == 0)
        hero_deafualt_color = blue_color;
    else if (strcmp(hero_color, "White") == 0)
        hero_deafualt_color = white_color;

    game_struct game;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < map_height; j++)
            for (int h = 0; h < map_width; h++)
            {
                game.map[i][j][h] = nothing;
                game.show_map[i][j][h] = nothing;
                game.under_weapon[i][j][h] = nothing;
            }
    floor_number = 0;
    game_is_running = 1;
    int x, y;
    getmaxyx(stdscr, y, x);
    getmaxyx(stdscr, terminal_y_size, terminal_x_size);
    startx_map_draw = (x - map_width * 2) / 2;
    starty_map_draw = (y - map_height) / 2;
    message_row = starty_map_draw / 6;
    clear();
    refresh();
    make_map(&game);
    hero_struct hero;
    hero.health = hero_health;
    hero.gold = 0;
    hero.master_key_number = 0;
    hero.broken_key_number = 0;
    hero.dagger_number = 0;
    hero.sword_number = 0;
    hero.mace_number = 1;
    hero.magic_wand_number = 0;
    hero.normal_arrow_number = 0;
    hero.weapon = mace;
    hero.health_spell_number = 0;
    hero.damage_spell_number = 0;
    hero.speed_spell_number = 0;
    hero.step = 0;
    hero.health_step = 0;
    hero.damage_step = 0;
    hero.speed_step = 0;
    hero.regular_food_number = 0;
    hero.spoiled_food_number = 0;
    hero.excellent_food_number = 0;
    hero.magic_food_number = 0;
    hero.hunger = 0;

    this_room_number[0] = 0;
    hero.x = game.room[floor_number][0].startx + random_number(1, game.room[floor_number][0].width - 2);
    hero.y = game.room[floor_number][0].starty + random_number(1, game.room[floor_number][0].height - 2);

    draw_map(&game, &hero);
    run_game(&game, &hero);
}

typedef struct textbox
{
    int startx[4], starty[4], height, width, selected_box;
    char textbox_values[4][50];
} sign_up_textbox;

typedef struct textbox2
{
    int startx[2], starty[2], height, width, selected_box;
    char textbox_values[2][50];
} sign_in_textbox;

void create_textbox(int starty, int startx, int width, int height, const char *label, int count)
{
    WINDOW *textbox_win = newwin(height, width, starty, startx);
    box(textbox_win, 0, 0);
    mvwprintw(textbox_win, 0, 1, "%s", label);
    wrefresh(textbox_win);
    if (!count)
        move(starty + 1, startx + 1);
}

void print_error(int starty, int startx, const char *error)
{
    move(starty, 0);
    clrtoeol();
    mvprintw(starty, startx, "%s", error);
    refresh();
}

int email_format(char *email)
{
    int i = 0, dot_count = 0;
    while (email[i] != '\0')
    {
        if (email[i] == '@')
            break;
        i++;
    }
    if (email[i] == '\0' || email[0] == '.' || email[i - 1] == '.' || i >= strlen(email) - 3 || email[i + 1] == '.')
        return 0;
    while (email[i] != '\0')
    {
        i++;
        if (email[i] == '.')
            dot_count++;
    }
    if (email[i - 1] == '.' || dot_count != 1)
        return 0;
    return 1;
}

int password_format(char *password)
{
    int a = 0, A = 0, digit = 0;
    for (int i = 0; i < strlen(password); i++)
    {
        if (password[i] >= 'a' && password[i] <= 'z')
            a = 1;
        if (password[i] >= 'A' && password[i] <= 'Z')
            A = 1;
        if (password[i] >= '0' && password[i] <= '9')
            digit = 1;
    }
    if (a && A && digit)
        return 1;
    return 0;
}

int username_taken(char *username)
{
    FILE *file = fopen("username.txt", "r");
    char x[100];
    while (fscanf(file, "%s", x) != -1)
        if (strcmp(x, username) == 0)
        {
            fclose(file);
            return 1;
        }
    return 0;
}

int user_exists(char *username, char *password)
{
    FILE *file = fopen("data.txt", "r");
    char x[100], y[100];
    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%99s %99s", x, y) == 2)
        {
            refresh();
            if (strcmp(x, username) == 0 && strcmp(y, password) == 0)
            {
                fclose(file);
                strcpy(user_username, username);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

void sign_up_panel()
{
    clear();
    refresh();
    int x, y;
    getmaxyx(stdscr, y, x);
    sign_up_textbox sign_up_panel_textboxes;
    sign_up_panel_textboxes.width = 30;
    sign_up_panel_textboxes.height = 3;
    int startx = (x - sign_up_panel_textboxes.width) / 2;
    int starty = (y - (sign_up_panel_textboxes.height + 2) * sign_up_panel_textbox_count) / 2;
    mvprintw(starty + (sign_up_panel_textboxes.height + 2) * 4, (x - strlen("Press Enter to submit")) / 2, "Press Enter to submit");
    for (int i = 0; i < sign_up_panel_textbox_count; i++)
    {
        sign_up_panel_textboxes.startx[i] = startx;
        sign_up_panel_textboxes.starty[i] = starty + (sign_up_panel_textboxes.height + 2) * i;
        sign_up_panel_textboxes.textbox_values[i][0] = '\0';
        create_textbox(starty + (sign_up_panel_textboxes.height + 2) * i, startx, sign_up_panel_textboxes.width, sign_up_panel_textboxes.height, sign_up_panel_textbox[i], i);
    }
    sign_up_panel_textboxes.selected_box = 0;
    noecho();
    while (1)
    {
        int ch = getch();
        if (ch != -1)
        {
            if ((ch == '\t' || ch == KEY_DOWN) && sign_up_panel_textboxes.selected_box < sign_up_panel_textbox_count - 1)
            {
                sign_up_panel_textboxes.selected_box++;
                move(sign_up_panel_textboxes.starty[sign_up_panel_textboxes.selected_box] + 1, sign_up_panel_textboxes.startx[sign_up_panel_textboxes.selected_box] + 1);
            }
            else if (ch == KEY_UP && sign_up_panel_textboxes.selected_box > 0)
            {
                sign_up_panel_textboxes.selected_box--;
                move(sign_up_panel_textboxes.starty[sign_up_panel_textboxes.selected_box] + 1, sign_up_panel_textboxes.startx[sign_up_panel_textboxes.selected_box] + 1);
            }
            else if (ch == KEY_BACKSPACE || ch == 127)
            {
                int len = strlen(sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box]);
                if (len > 0)
                {
                    sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box][len - 1] = '\0';
                    mvwprintw(stdscr, sign_up_panel_textboxes.starty[sign_up_panel_textboxes.selected_box] + 1, sign_up_panel_textboxes.startx[sign_up_panel_textboxes.selected_box] + 1, "%-*s", sign_up_panel_textboxes.width - 2, sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box]);
                    move(sign_up_panel_textboxes.starty[sign_up_panel_textboxes.selected_box] + 1, sign_up_panel_textboxes.startx[sign_up_panel_textboxes.selected_box] + 1 + len - 1);
                    refresh();
                }
            }
            else if (ch == '\n')
            {
                char *username = sign_up_panel_textboxes.textbox_values[0];
                char *password = sign_up_panel_textboxes.textbox_values[1];
                char *confirm_password = sign_up_panel_textboxes.textbox_values[2];
                char *email = sign_up_panel_textboxes.textbox_values[3];
                if (strlen(username) == 0 || strlen(password) == 0 || strlen(confirm_password) == 0 || strlen(email) == 0)
                    print_error(starty - sign_up_panel_textboxes.height, (x - strlen("All fields are required!!!")) / 2, "All fields are required!!!!");
                else if (strcmp(password, confirm_password) != 0)
                    print_error(starty - sign_up_panel_textboxes.height, (x - strlen("Passwords do not match!!!")) / 2, "Passwords do not match!!!");
                else if (strlen(password) < 7)
                    print_error(starty - sign_up_panel_textboxes.height, (x - strlen("Password must be at least 7 characters!!!")) / 2, "Password must be at least 7 characters!!!");
                else if (!password_format(password))
                    print_error(starty - sign_up_panel_textboxes.height,
                                (x - strlen("Password must contain at least one uppercase letter, "
                                            "one lowercase letter and one digit!!!")) /
                                    2,
                                "Password must contain at least one uppercase letter, one "
                                "lowercase letter and one digit!!!");
                else if (!email_format(email))
                    print_error(starty - sign_up_panel_textboxes.height, (x - strlen("Invalid email format!!!")) / 2, "Invalid email format!!!");
                else if (username_taken(username))
                    print_error(starty - sign_up_panel_textboxes.height, (x - strlen("Username already taken!!!")) / 2, "Username already taken!!!");
                else
                {
                    print_error(starty - sign_up_panel_textboxes.height, (x - strlen("User created successfully!!!")) / 2, "User created successfully!!!");
                    FILE *file = fopen("username.txt", "a");
                    fprintf(file, "%s\n", username);
                    fclose(file);
                    file = fopen("data.txt", "a");
                    fprintf(file, "%s %s %s 0 0 0 0\n", username, password, email);
                    fclose(file);
                    sleep(1);
                    game_menu();
                    game_menu_input();
                    break;
                }
            }
            else if (ch == KEY_LEFT)
            {
                break;
            }
            else
            {
                int len = strlen(sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box]);
                if (len < sizeof(sign_up_panel_textboxes.textbox_values[0]) - 1 && len < sign_up_panel_textboxes.width - 2)
                {
                    sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box][len] = ch;
                    sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box][len + 1] = '\0';
                    mvwprintw(stdscr, sign_up_panel_textboxes.starty[sign_up_panel_textboxes.selected_box] + 1, sign_up_panel_textboxes.startx[sign_up_panel_textboxes.selected_box] + 1, "%s", sign_up_panel_textboxes.textbox_values[sign_up_panel_textboxes.selected_box]);
                    move(sign_up_panel_textboxes.starty[sign_up_panel_textboxes.selected_box] + 1, sign_up_panel_textboxes.startx[sign_up_panel_textboxes.selected_box] + 1 + len + 1);
                    refresh();
                }
            }
        }
    }
    noecho();
}

void sign_in_panel()
{
    clear();
    refresh();
    int x, y;
    getmaxyx(stdscr, y, x);
    sign_in_textbox sign_in_panel_textboxes;
    sign_in_panel_textboxes.width = 30;
    sign_in_panel_textboxes.height = 3;
    int startx = (x - sign_in_panel_textboxes.width) / 2;
    int starty = (y - (sign_in_panel_textboxes.height + 2) * sign_in_panel_textbox_count) / 2;
    mvprintw(starty + (sign_in_panel_textboxes.height + 2) * 2, (x - strlen("Press Enter to submit")) / 2, "Press Enter to submit");
    for (int i = 0; i < sign_in_panel_textbox_count; i++)
    {
        sign_in_panel_textboxes.startx[i] = startx;
        sign_in_panel_textboxes.starty[i] = starty + (sign_in_panel_textboxes.height + 2) * i;
        sign_in_panel_textboxes.textbox_values[i][0] = '\0';
        create_textbox(starty + (sign_in_panel_textboxes.height + 2) * i, startx, sign_in_panel_textboxes.width, sign_in_panel_textboxes.height, sign_in_panel_textbox[i], i);
    }
    sign_in_panel_textboxes.selected_box = 0;
    noecho();
    while (1)
    {
        int ch = getch();
        if (ch != -1)
        {
            if ((ch == '\t' || ch == KEY_DOWN) && sign_in_panel_textboxes.selected_box < sign_in_panel_textbox_count - 1)
            {
                sign_in_panel_textboxes.selected_box++;
                move(sign_in_panel_textboxes.starty[sign_in_panel_textboxes.selected_box] + 1, sign_in_panel_textboxes.startx[sign_in_panel_textboxes.selected_box] + 1);
            }
            else if (ch == KEY_UP && sign_in_panel_textboxes.selected_box > 0)
            {
                sign_in_panel_textboxes.selected_box--;
                move(sign_in_panel_textboxes.starty[sign_in_panel_textboxes.selected_box] + 1, sign_in_panel_textboxes.startx[sign_in_panel_textboxes.selected_box] + 1);
            }
            else if (ch == KEY_BACKSPACE || ch == 127)
            {
                int len = strlen(sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box]);
                if (len > 0)
                {
                    sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box][len - 1] = '\0';
                    mvwprintw(stdscr, sign_in_panel_textboxes.starty[sign_in_panel_textboxes.selected_box] + 1, sign_in_panel_textboxes.startx[sign_in_panel_textboxes.selected_box] + 1, "%-*s", sign_in_panel_textboxes.width - 2, sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box]);
                    move(sign_in_panel_textboxes.starty[sign_in_panel_textboxes.selected_box] + 1, sign_in_panel_textboxes.startx[sign_in_panel_textboxes.selected_box] + 1 + len - 1);
                    refresh();
                }
            }
            else if (ch == KEY_LEFT)
                break;
            else if (ch == '\n')
            {
                char *username = sign_in_panel_textboxes.textbox_values[0];
                char *password = sign_in_panel_textboxes.textbox_values[1];
                if (strlen(username) == 0 || strlen(password) == 0)
                    print_error(starty - sign_in_panel_textboxes.height, (x - strlen("All fields are required!!!")) / 2, "All fields are required!!!!");
                else
                {
                    if (user_exists(username, password))
                    {
                        print_error(starty - sign_in_panel_textboxes.height, (x - strlen("Loged in successfully!!!")) / 2, "Loged in successfully!!!");
                        sleep(1);
                        game_menu();
                        game_menu_input();
                        break;
                    }
                    else
                        print_error(starty - sign_in_panel_textboxes.height, (x - strlen("Invalid username or password!!!")) / 2, "Invalid username or password!!!");
                }
            }
            else
            {
                int len = strlen(sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box]);
                if (len < sizeof(sign_in_panel_textboxes.textbox_values[0]) - 1 && len < sign_in_panel_textboxes.width - 2)
                {
                    sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box][len] = ch;
                    sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box][len + 1] = '\0';
                    mvwprintw(stdscr, sign_in_panel_textboxes.starty[sign_in_panel_textboxes.selected_box] + 1, sign_in_panel_textboxes.startx[sign_in_panel_textboxes.selected_box] + 1, "%s", sign_in_panel_textboxes.textbox_values[sign_in_panel_textboxes.selected_box]);
                    move(sign_in_panel_textboxes.starty[sign_in_panel_textboxes.selected_box] + 1, sign_in_panel_textboxes.startx[sign_in_panel_textboxes.selected_box] + 1 + len + 1);
                    refresh();
                }
            }
        }
    }
}

void Hero_color_menu()
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(A_BOLD);
    int option_size = 20;
    init_pair(20, COLOR_RED, COLOR_RED);
    init_pair(21, COLOR_BLUE, COLOR_BLUE);
    init_pair(22, COLOR_GREEN, COLOR_GREEN);
    init_pair(23, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(24, COLOR_WHITE, COLOR_WHITE);
    for (int i = 0; i < hero_color_count; i++)
    {
        if (i == selected_hero_color)
        {
            attron(COLOR_PAIR(1));
            mvprintw(y / 2 + 2 * (i - hero_color_count / 2), (x - option_size) / 2 - 3, ">>");
            mvprintw(y / 2 + 2 * (i - hero_color_count / 2), (x - option_size) / 2 + option_size + 1, "<<");
        }

        if (!strcmp("Red", hero_colors[i]))
            attron(COLOR_PAIR(20));
        else if (!strcmp("Blue", hero_colors[i]))
            attron(COLOR_PAIR(21));
        else if (!strcmp("Green", hero_colors[i]))
            attron(COLOR_PAIR(22));
        else if (!strcmp("Yellow", hero_colors[i]))
            attron(COLOR_PAIR(23));
        else if (!strcmp("White", hero_colors[i]))
            attron(COLOR_PAIR(24));
        move(y / 2 + 2 * (i - hero_color_count / 2), (x - option_size) / 2);
        for (int j = 0; j < option_size; j++)
            printw(" ");
    }
    attron(COLOR_PAIR(1));
    attroff(A_BOLD);
    curs_set(0);
}

void Hero_color_menu_input()
{
    while (1)
    {
        int x = getch();
        if (x != ERR)
        {
            if (x == KEY_UP && selected_hero_color > 0)
            {
                selected_hero_color--;
                Hero_color_menu();
            }
            else if (x == KEY_DOWN && selected_hero_color < hero_color_count - 1)
            {
                selected_hero_color++;
                Hero_color_menu();
            }
            else if (x == '\n' || x == KEY_RIGHT)
            {
                strcpy(hero_color, hero_colors[selected_hero_color]);
                break;
            }
            else if (x == KEY_LEFT)
                break;
        }
    }
}

void difficulty_menu()
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(A_BOLD);
    for (int i = 0; i < difficulty_count; i++)
    {
        if (i == selected_difficulty)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        mvprintw(y / 2 + 2 * (i - difficulty_count / 2), (x - strlen(difficulty_levels[i])) / 2, "%s", difficulty_levels[i]);
    }
    attron(COLOR_PAIR(1));
    attroff(A_BOLD);
    curs_set(0);
}

void difficulty_menu_input()
{
    while (1)
    {
        int x = getch();
        if (x != ERR)
        {
            if (x == KEY_UP && selected_difficulty > 0)
            {
                selected_difficulty--;
                difficulty_menu();
            }
            else if (x == KEY_DOWN && selected_difficulty < difficulty_count - 1)
            {
                selected_difficulty++;
                difficulty_menu();
            }
            else if (x == '\n' || x == KEY_RIGHT)
            {
                difficulty = selected_difficulty + 1;
                break;
            }
            else if (x == KEY_LEFT)
                break;
        }
    }
}

void settings_menu()
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(A_BOLD);
    for (int i = 0; i < settings_count; i++)
    {
        if (i == selected_settings)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        mvprintw(y / 2 + 2 * (i - settings_count / 2), (x - strlen(settings_items[i])) / 2, "%s", settings_items[i]);
    }
    attron(COLOR_PAIR(1));
    attroff(A_BOLD);
    curs_set(0);
}

void settings_menu_input()
{
    while (1)
    {
        int x = getch();
        if (x != ERR)
        {
            if (x == KEY_UP && selected_settings > 0)
            {
                selected_settings--;
                settings_menu();
            }
            else if (x == KEY_DOWN && selected_settings < settings_count - 1)
            {
                selected_settings++;
                settings_menu();
            }
            else if (x == '\n' || x == KEY_RIGHT)
            {
                if (strcmp(settings_items[selected_settings], "Difficulty Level") == 0)
                {
                    difficulty_menu();
                    difficulty_menu_input();
                    settings_menu();
                }
                else if (strcmp(settings_items[selected_settings], "Hero Color") == 0)
                {
                    Hero_color_menu();
                    Hero_color_menu_input();
                    settings_menu();
                }
            }
            else if (x == KEY_LEFT)
                break;
        }
    }
}

void game_menu()
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(A_BOLD);
    for (int i = 0; i < menu_items_count; i++)
    {
        if (i == selected_menu)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        if ((strcmp(menu_items[i], "Profile") == 0 || strcmp(menu_items[i], "Load Game") == 0) && strcmp(user_username, "guest") == 0)
            attron(COLOR_PAIR(3));
        mvprintw(y / 2 + 2 * (i - menu_items_count / 2), (x - strlen(menu_items[i])) / 2, "%s", menu_items[i]);
    }
    attron(COLOR_PAIR(1));
    attroff(A_BOLD);
    curs_set(0);
}

void game_menu_input()
{
    while (1)
    {
        int x = getch();
        if (x != ERR)
        {
            if (x == KEY_UP && selected_menu > 0)
            {
                selected_menu--;
                if ((selected_menu == 1 || selected_menu == 4) && strcmp(user_username, "guest") == 0)
                    selected_menu--;
                game_menu();
            }
            else if (x == KEY_DOWN && selected_menu < menu_items_count - 1)
            {
                selected_menu++;
                if ((selected_menu == 1 || selected_menu == 4) && strcmp(user_username, "guest") == 0)
                    selected_menu++;
                game_menu();
            }
            else if (x == '\n' || x == KEY_RIGHT)
            {
                if (strcmp(menu_items[selected_menu], "Log Out") == 0)
                    break;
                else if (strcmp(menu_items[selected_menu], "New Game") == 0)
                {
                    clear();
                    new_game();
                    game_menu();
                }
                else if (strcmp(menu_items[selected_menu], "Load Game") == 0)
                {
                    // Load Game();
                }
                else if (strcmp(menu_items[selected_menu], "Leaderboard") == 0)
                {
                    // leaderboard();
                }
                else if (strcmp(menu_items[selected_menu], "Profile") == 0)
                {
                    // profile();
                }
                else if (strcmp(menu_items[selected_menu], "Settings") == 0)
                {
                    settings_menu();
                    settings_menu_input();
                    game_menu();
                }
            }
            else if (x == KEY_LEFT)
                break;
        }
    }
}

void login_panel()
{
    clear();
    int x, y;
    getmaxyx(stdscr, y, x);
    attron(A_BOLD);
    for (int i = 0; i < panel_items; i++)
    {
        if (i == selected_login_panel)
            attron(COLOR_PAIR(2));
        else
            attron(COLOR_PAIR(1));
        mvprintw(y / 2 + 2 * (i - panel_items / 2), (x - strlen(login_panel_items[i])) / 2, "%s", login_panel_items[i]);
    }
    attron(COLOR_PAIR(1));
    attroff(A_BOLD);
    curs_set(0);
}

void login_input()
{
    int x = getch();
    if (x != ERR)
    {
        if (x == KEY_UP && selected_login_panel > 0)
        {
            selected_login_panel--;
            login_panel();
        }
        else if (x == KEY_DOWN && selected_login_panel < panel_items - 1)
        {
            selected_login_panel++;
            login_panel();
        }
        else if (x == '\n' || x == KEY_RIGHT || x == KEY_MOUSE)
        {
            if (strcmp(login_panel_items[selected_login_panel], "Exit") == 0)
                running = 0;
            else if (strcmp(login_panel_items[selected_login_panel], "Sign in") == 0)
                sign_in_panel();
            else if (strcmp(login_panel_items[selected_login_panel], "Sign up") == 0)
                sign_up_panel();
            else if (strcmp(login_panel_items[selected_login_panel], "Enter as guest") == 0)
            {
                strcpy(user_username, "guest");
                game_menu();
                game_menu_input();
            }
        }
        else if (x == KEY_LEFT)
            running = 0;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    cbreak();
    timeout(0);
    srand(time(NULL));
    if (has_colors())
    {
        start_color();
        init_color(200, 500, 500, 500);
        init_color(201, 255, 99, 71); // orange
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_GREEN);
        init_pair(3, 200, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);  // green
        init_pair(5, COLOR_BLUE, COLOR_BLACK);   // blue
        init_pair(6, COLOR_YELLOW, COLOR_BLACK); // yellow
        init_pair(7, COLOR_RED, COLOR_BLACK);    // stairs
        init_pair(8, 201, COLOR_BLACK);          // orange
        init_pair(9, COLOR_BLACK, COLOR_BLUE);   // black
        init_pair(10, COLOR_RED, COLOR_BLACK);   // hero
        init_pair(11, COLOR_WHITE, COLOR_WHITE); // hunger bar
        init_pair(12, COLOR_WHITE, COLOR_RED);   // hunger bar
    }

    attron(COLOR_PAIR(1));

    refresh();

    while (running)
    {
        login_panel();
        login_input();
        refresh();
        int x = getch();
        if (x == 'q')
            break;
        usleep(delay);
    }
    endwin();
    return 0;
}