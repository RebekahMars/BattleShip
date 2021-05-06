#include "Header.h"

void welcome_screen(void) //prints the welcome screen
{
	printf("***BATTLESHIP***\n\n");
	system("pause");
	system("cls");

	printf("Welcome to Battleship!\n");
	printf("This is a two player Navy game. Player 1 is YOU and Player 2 is the computer.\n");
	printf("The objective of the game is to sink all ships in your enemy's fleet.\n");
	printf("Both players' fleets consists of 5 ships hidden from the enemy.\n");
	printf("Each ship varies in size. The Carrier is 5 units long, Battleship 4 units, Cruiser 3 units, Submarine 3 units, and Destroyer 2 units. \n");
	printf("Each player will have the choice to randomly or manually set their ship fleet on their 10x10 board.\n");
	printf("Each ship can only be placed vertically or horizonatlly, not diagonally.\n");
	printf("The player to go first will be randomized.\n");
	printf("Players will then take turns guessing the locations of their enemy's ship fleet.\n");
	printf("If a player correctly guess the location of one of their enermys ship's units, the board is marked as being 'hit' with the 'H' symbol in that location.\n");
	printf("If a player incorrectly guesses the location of one of their enemys ship's units, the board is marked as a 'miss' with the 'M' symbol in that location\n");
	printf("A ship is sunk if all of the ship's units have been hit.\n");
	printf("The Player to sink his/her enermy's fleet first wins!\n\n");
	printf("Alright, let's play Battleship!\n");

	system("pause");
	system("cls");
	
}
void initialize_board(char player_board[][MAX_COLUMNS]) //Initializes the game board
{
	for (int column_num = 0; column_num < MAX_COLUMNS; ++column_num)
	{
		for (int row_num = 0; row_num < MAX_ROWS; ++row_num)
		{
			player_board[column_num][row_num] = WATER;
		}
	}
}
void print_board(char player_board[][MAX_COLUMNS]) //Displays the game board
{
	printf("  0 1 2 3 4 5 6 7 8 9 \n");

	for (int row_num = 0; row_num < MAX_ROWS; ++row_num)
	{
		printf("%d", row_num);

		for (int column_num = 0; column_num < MAX_COLUMNS; ++column_num)
		{
			printf(" %c", player_board[row_num][column_num]);
		}
		putchar('\n');
	}
}
void hidden_board(char player_board[][MAX_COLUMNS]) //hidden game board function
{
	printf("  0 1 2 3 4 5 6 7 8 9 \n");

	for (int row_num = 0; row_num < MAX_ROWS; ++row_num)
	{
		printf("%d", row_num);

		for (int column_num = 0; column_num < MAX_COLUMNS; ++column_num)
		{
			if (player_board[row_num][column_num] >= 'b' && player_board[row_num][column_num] <= 's') //if the board has the ships on it (not hit or miss value)
			{
				printf(" %c", WATER);
			}
			else
			{
				printf(" %c", player_board[row_num][column_num]);
			}
		}
		putchar('\n');
	}
}
int get_starting_player(void) //randomizes that starting player, between 0 and 1 (I add 1 to the print statement to account for this)
{
	return rand() % 2;
}
int generate_direction(void) //generates a random ship direction for random ship placement function
{
	int ship_direction = 0;
	
	ship_direction = rand() % 2;
	return ship_direction;
}

int manual_or_random_board(void) //function that asks user if they would like to manually or randomly set the board
{
	int choice = 0;
	do
	{
		printf("Would you like to set the board manually or randomly? Enter 1 for MANUAL or 2 for RANDOM: ");
		(void)scanf(" %d", &choice);
	} while (!(choice == 1 || choice == 2));

	return choice;
	
}

void manual_ship_placement(char player_board[][MAX_COLUMNS], char ship_length[], char ships[], int player_coordinates[], int row_valid, int column_valid) //manually sets the board
{
	int row = 0, column = 0;
	int pos_x = 0, pos_y = 0;
	int direction = 0;
	for (int i = 0; i < 5; i++)
	{
		printf("Would you like to place the Ship %c in the horizontal direction or vertical direction? \n Enter 1 for VERTICAL and 2 for HORIZONTAL: \n", ships[i]);
		(void)scanf("%d", &direction);
	}
	for (int i = 0; i < 5; i++)
	{
		if (direction == 1)//VERTICAL direction
		{
			int check = 0;
			do 
			{
				check = 0;
				do
				{
					printf("Please enter the row you would like to place the ship %c in: ", ships[i]);
					(void)scanf("%d", &row);
					printf("Please enter the column you would like to place the ship %c in: ", ships[i]);
					(void)scanf("%d", &column);

				} while (!(row >= 0 && row <= 9 && column >= 0 && column <= 9)); //row and column has to be between 0 and 9
				for (int j = 0; j < ship_length[i]; j++)
				{
					if(player_board[column + j][row] != WATER) //if there is a ship in this location
					{
						check = 1;//player_board[row][column + j] = ships[i];
						printf("There is a ship already at (%d, %d).\n", column + j, row);

					}
				}
			} while (check == 1);
			for (int a = 0; a < ship_length[i]; a++) //otherwise if there is water there, places the ship
			{
				player_board[column+a][row] = ships[i];
			}
		}

		if (direction == 2)//HORIZONTAL
		{
			int check = 0;
			do
			{
				check = 0;
				do
				{
					printf("Please enter the row you would like to place the ship in: ");
					(void)scanf("%d", &row);
					printf("Please enter the column you would like to place the ship in: ");
					(void)scanf("%d", &column);

				} while (!(row >= 0 && row <= 9 && column >= 0 && column <= 9)); //row and column has to be between 0 and 9
				for (int j = 0; j < ship_length[i]; j++)
				{
					if(player_board[column][row+j] != WATER) //if there is a ship in this location
					{
						check = 1;//player_board[row + j][column] = ships[i];
						printf("There is a ship already in this location.\n");

					}

				}
			} while (check == 1);
			for (int a = 0; a < ship_length[i]; a++) //if there is water in the row and column location the player entered
			{
				player_board[column][row +a] = ships[i];
			}
		}
	}
}
void random_ship_placement(char player_board[][MAX_COLUMNS], int ship_direction, char ship_length[], char ships[], int valid) //randomizes the placement of the ships
{
	int pos_y = 0, pos_x = 0;

	for (int i = 0; i < 5; i++) //for loop to cycle through numbers 0-4
	{
		ship_direction = generate_direction(); //generate a direction. 0 is horizontal, 1 is vertical.
		if (ship_direction == 0) //horiztonal, moves left to right
		{
			int check = 0;
			do
			{
				check = 0;
				pos_x = rand() % (10 - ship_length[i]); //randomize starting X coordinate, ship length cannot exceed board-this could result in negative numbers?
				pos_y = rand() % 10; //randomize starting Y coordinate
				for (int j = 0; j < ship_length[i]; j++) //for loop to cycle through ship_length array at location i
				{
					if (player_board[pos_x + j][pos_y] != WATER)
					{
						check = 1;//player_board[pos_x + j][pos_y] = ships[i]; //places ship symbol i at location 					
					}
				}
			} while (check == 1);
			for (int a = 0; a < ship_length[i]; a++) //if there is water in this location
			{
				player_board[pos_x + a][pos_y] = ships[i];
			}
		}
		if (ship_direction == 1) //vertical, moves top to bottom
		{
			int check = 0;
			do
			{
				check = 0;
				pos_x = rand() % 10; //randomize starting X coordinate
				pos_y = rand() % (10 - ship_length[i]); //randomize starting Y cordinate, ship length cannot exceed board
				for (int j = 0; j < ship_length[i]; j++)//for loop to cycle through ship_length array starting at location i
				{
					if (player_board[pos_x][pos_y + j] != WATER)
					{
						check = 1;//player_board[pos_x][pos_y + j] = ships[i]; //places ship symbol i at location
					}
				}
			} while (check == 1);
			for (int a = 0; a < ship_length[i]; a++) //if there is water in this location
			{
				player_board[pos_x][pos_y + a] = ships[i];
			}
		}
	}
}
 void update_board(char player_board[][MAX_COLUMNS], char ships[], int x_coordinate, int y_coordinate) //updates board based on player moves
{

	 for (int ship_index = 0; ship_index < 5; ship_index++)
	 {
		 if (player_board[x_coordinate][y_coordinate] == ships[ship_index]) //if there is a ship in this location
		 {
			 player_board[x_coordinate][y_coordinate] = HIT; //HIT
		 }
		 else if (player_board[x_coordinate][y_coordinate] == WATER) //if there is water in this location
		 {
			 player_board[x_coordinate][y_coordinate] = MISS; //MISS
		 }
	
	 }
}

char check_if_ship_sunk(char player_board[][MAX_COLUMNS], char ships[], int ship_sunk[]) //checks if the ship has been sunk
{ 
	char ship_sunked = '\0';
	int found = 0;
	for (int ship_index = 0; ship_index < 5; ship_index++)
	{
		found = 0;
		for (int i = 0; i < MAX_ROWS && found == 0; i++) //iterate through rows of board
		{
			for (int j = 0; j < MAX_COLUMNS && found == 0; j++) //iterate through columns of board
			{
				if (player_board[i][j] == ships[ship_index]) //if there is a ship
				{
					found = 1;
				}
			}
		}
		if (found == 0 && ship_sunk[ship_index] == 0) //if there are no ships of a specific symbol on the board
		{
			ship_sunk[ship_index] = 1; //set to 1 in array so ship doesn't "sink" every roung, only once
			printf("Ship %c has been sunk!\n", ships[ship_index]);
			ship_sunked = ships[ship_index];
		}
	}
	return ship_sunked;
}
int check_if_winner(char player_board[][MAX_COLUMNS]) //checks to see if a player has won by number of hits, if number of hits is 17 then all ships have been sunk
{
	int number_hits = 0;
	int winner = 0;
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLUMNS; j++)
		{
			if (player_board[i][j] == HIT)
			{
				number_hits++; //number of hits counter
			}
		}
	}
	if (number_hits == 17)
	{
		winner = 1;
	}
	return winner;
}	
void player_stat_output(FILE* outfile, Stats player1, Stats player2) //prints the player's stats the the Battleship.log
{
	fprintf(outfile, "Player STATS: \n\n");
	fprintf(outfile, "Total Number of Hits: %d\n", player1.totalHits);
	fprintf(outfile, "Total Number of Misses: %d\n", player1.totalMisses);
	fprintf(outfile, "Total Number of Shots Taken: %d\n", player1.totalShots);
	fprintf(outfile, "Ratio of Hits to Misses: %.2lf\n", player1.hitMissRatio);

	fprintf(outfile, "Computer STATS: \n\n");
	fprintf(outfile, "Total Number of Hits: %d\n", player2.totalHits);
	fprintf(outfile, "Total Number of Misses: %d\n", player2.totalMisses);
	fprintf(outfile, "Total Number of Shots Taken: %d\n", player2.totalShots);
	fprintf(outfile, "Ratio of Hits to Misses: %.2lf\n", player2.hitMissRatio);
}
int player_shot_x(void) //gets the row from the user to shoot at
{
	int coordinate = 0;
	printf("Please enter a row number to shoot at: ");
	(void)scanf("%d", &coordinate);
	return coordinate;
}
int player_shot_y(void) //gets the coordinate from the user to shoot at
{
	int coordinate = 0;
	printf("Please enter a column number to shoot at: ");
	(void)scanf("%d", &coordinate);
	return coordinate;
}
int check_player_shot(char player_board[][MAX_COLUMNS], char ships[], int x_coordinate, int y_coordinate) //checks the player's shot to determine if its a hit, miss, or if it has been used before
{
	int shot;
	for (int ship_index = 0; ship_index < 5; ship_index++)
	{
		if (player_board[x_coordinate][y_coordinate] == ships[ship_index]) //HIT
		{
			shot = 1;
		}
		else if (player_board[x_coordinate][y_coordinate] == WATER) //MISS
		{
			shot = 0;
		}
		else //coordinate has already been used
		{
			if (player_board[x_coordinate][y_coordinate] == HIT || player_board[x_coordinate][y_coordinate] == MISS)
			{
				shot = -1;
			}
		}
	}
	return shot;
}
void output_current_stats(FILE* outfile, int starting_player, int x_coordinate, int y_coordinate, int player_hit, char sunk_player_ship) //function to print stats to outfile
{
	switch (starting_player)
	{
	case 0:
		if (player_hit == 1) //if there is a hit for player
		{
			if (sunk_player_ship != '\0') //if the sunk_player_ship has a character stored, means a ship has been sunk
			{
				fprintf(outfile, "Player 1 attacked at (%d, %d). It was a hit, and the player's ship %c was SUNK!\n", x_coordinate, y_coordinate, sunk_player_ship);
			}
			else //if the ship is still present on the board
			{
				fprintf(outfile, "Player 1 attacked at (%d, %d). It was a hit.\n", x_coordinate, y_coordinate);
			}
		}
		else //player missed
		{
			fprintf(outfile, "Player 1 attacked at (%d, %d). It was a miss.\n", x_coordinate, y_coordinate);
		}
		break;
	case 1:
		if (player_hit == 1) //if there is a hit for the computer
		{
			if (sunk_player_ship == 1) //if the sunk_player_ship has a character stored, means a ship has been sunk
			{
				fprintf(outfile, "The Computer attacked at (%d, %d). It was a hit, and the player's ship %c was SUNK!\n", x_coordinate, y_coordinate, sunk_player_ship);
			}
			else //if the ship is still present on the board
			{
				fprintf(outfile, "The Computer attacked at (%d, %d). It was a hit.\n", x_coordinate, y_coordinate);
			}
		}
		else //computer missed
		{
			fprintf(outfile, "The Computer attacked at (%d, %d). It was a miss.\n", x_coordinate, y_coordinate);
		}
		break;
	}
}
		