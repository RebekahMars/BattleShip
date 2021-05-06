#define _CRT_SECURE_NO_WARNINGS
#define MAX_COLUMNS 10
#define MAX_ROWS 10
#define CARRIER_SIZE 5
#define BATTLESHIP_SIZE 4
#define CRUISER_SIZE 3
#define SUB_SIZE 3
#define DESTROYER_SIZE 2
#define HIT '*'
#define MISS 'M'
#define WATER '~'
#define CARRIER 'c'
#define BATTLESHIP 'b'
#define CRUISER 'r'
#define SUBMARINE 's'
#define DESTROYER 'd'

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//struct defined for player and computer. stores the total hits, total misses, total shots, and hit/miss ratio (calculated in main)
typedef struct stats {
	int totalHits;
	int totalMisses;
	int totalShots;
	double hitMissRatio;
}Stats;
//function defintions
void welcome_screen(void);
void initialize_board(char player_board[][MAX_COLUMNS]);
void print_board(char player_board[][MAX_COLUMNS]);
void hidden_board(char player_board[][MAX_COLUMNS]);
int get_starting_player(void);
int generate_direction(void);
int manual_or_random_board(void);
void manual_ship_placement(char player_board[][MAX_COLUMNS], char ship_length[], char ships[], int player_coordinates[], int row_valid, int column_valid);
void random_ship_placement(char player_board[][MAX_COLUMNS], int ship_direction, char ship_length[], char ships[], int valid);
void update_board(char player_board[][MAX_COLUMNS], char ships[], int x_coordinate, int y_coordinate);
char check_if_ship_sunk(char player_board[][MAX_COLUMNS], char ships[], int ship_sunk[]);
int check_if_winner(char player_board[][MAX_COLUMNS]);
void player_stat_output(FILE* outfile, Stats player1, Stats player2);
int player_shot_x(void);
int player_shot_y(void);
int check_player_shot(char player_board[][MAX_COLUMNS], char ships[], int x_coordinate, int y_coordinate);
void output_current_stats(FILE* outfile, int starting_player, int x_coordinate, int y_coordinate, int player_hit, char sunk_player_ship);

