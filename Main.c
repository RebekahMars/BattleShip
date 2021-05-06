#include "Header.h"

int main(void)
{
	//initialize variables used in functions and in main
	char player_board [10][10] = { { '\0' } };
	char player1_board[10][10] = { { '\0' } };
	char player2_board[10][10] = { { '\0' } };
	char ships[5] = { 'c', 'b', 'r', 's', 'd' };
	char ship_length[5] = { CARRIER_SIZE, BATTLESHIP_SIZE, CRUISER_SIZE, SUB_SIZE, DESTROYER_SIZE };
	int ship_sunk[5] = { 0 };
	int ship_direction = 0;
	int player_coordinates[100] = { {0} };
	int row_valid = 1, column_valid = 1;
	int valid = 0;
	int choice = 0;
	int direction = 0;
	int starting_player = 0;
	int player_hit = 0;
	int computer_hit = 0;
	int player_miss = 0;
	char sunk_player_ship = "\0";
	int player_stats = 0;
	int x_coordinate = 0, y_coordinate = 0;
	int computer_x_coordinate = 0, computer_y_coordinate = 0;
	int winning_player = -1;
	Stats player1 = { 0, 0, 0, 0.0}; //struct for player 1 stats
	Stats player2 = { 0, 0, 0, 0.0}; //struct for player 2 stats
	srand(time(NULL)); //allows me to randomize time

	FILE* outfile = NULL; //sets outfile to null
	outfile = fopen("Battleship.log", "w"); //opens the battleship.log outfile

	initialize_board(player1_board); //initializes player 1 board
	initialize_board(player2_board); //initializes player 2 board
	welcome_screen(); //displays welcome screen
	choice = manual_or_random_board(); //function to ask user if they want to set up their board manually randomly
	{
		if (choice == 1)
		{
			manual_ship_placement(player1_board, ship_length, ships, player_coordinates, row_valid, column_valid); //sets board manually
		}
		else
		{
			random_ship_placement(player1_board, ship_direction, ship_length, ships, valid); //sets board randomly
		}
	}
	print_board(player1_board); //prints player board
	system("pause");

	printf("Player 2 is placing their ships...");
	system("pause");
	random_ship_placement(player2_board, ship_direction, ship_length, ships, valid); //randomizes the computer's board
	printf("Player 2 is ready!\n");

	starting_player = get_starting_player(); //randomize the starting player
	printf("The player who gets to start first is Player %d!\n",starting_player+1);

	system("pause"); //pauses
	system("cls"); //clears the screen

	while (winning_player != 1) //while there isn't a winning player (player hits is not 17)-loops until there is a winner
	{
		switch (starting_player)
		{
		case 0: //Player's turn
			printf("Computer's Board\n");
			//print_board(player2_board); //comment this out if you would like to see the computer's board
			hidden_board(player2_board); //comment this out if you want to use the print_board function to see the computers board
			printf("Your Board: \n");
			print_board(player1_board); //prints player's board
			x_coordinate = player_shot_x(); //gets x_coordinate
			y_coordinate = player_shot_y(); //gets y_coordinate
			player1.totalShots++; //increments player1 total shots by 1
			player_hit = check_player_shot(player2_board, ships, x_coordinate, y_coordinate); //checks the player's shot to determine if it is a hit or miss or if it has been used before, returns a value
			update_board(player2_board, ships, x_coordinate, y_coordinate);
			sunk_player_ship = check_if_ship_sunk(player2_board, ships, ship_sunk);

			if (player_hit == 1) //player HITS
			{
				player1.totalHits++;
				printf("Player 1 shot at coordinate (%d, %d), and it was a HIT!\n", x_coordinate, y_coordinate);
			}
			else if (player_hit == 0) //player MISSES
			{
				player1.totalMisses++;
				printf("Player 1 shot at coordinate(%d, %d) and it was a MISS!\n", x_coordinate, y_coordinate);
			}
			else //player used this coordinate already (player_hit == -1)
			{
				printf("You have already used this coordinate.\n");
			}

			system("pause");
			system("cls");

			output_current_stats(outfile, starting_player, x_coordinate, y_coordinate, player_hit, sunk_player_ship); //outputs current stats to the outfile, battleship.log
			winning_player = check_if_winner(player2_board); //checks for winning player

			if (winning_player == 1) //if there is a player with 17 total hits
			{
				system("pause");
				goto endgame; //goes to endgame function in main and breaks out of switch statment
			}
			starting_player = 1;
			break;
		case 1:
			printf("Computer's Board: \n");
			//print_board(player2_board); //comment this out if you would like to see the computer's board, prints visible computer board
			hidden_board(player2_board); //comment this out if you want to use the print_board function to see the computers board, prints invisible computer board
			printf("Your Board: \n");
			print_board(player1_board); //prints player board

			printf("The computer is taking their turn...\n");
			computer_x_coordinate = rand() % 10; //randomizes computer x coordinate
			computer_y_coordinate = rand() % 10; //randomizes computer y coordinate
			player2.totalShots++; //increments computer total shots

			computer_hit = check_player_shot(player1_board, ships, computer_x_coordinate, computer_y_coordinate); //checks computer shot to determine if hit/miss/corodinate already used
			update_board(player1_board, ships, computer_x_coordinate, computer_y_coordinate); //updates player board
			sunk_player_ship= check_if_ship_sunk(player1_board, ships, ship_sunk); //checks if the player's ship has been sunk

			if (computer_hit == 1) //if computer HIT
			{
				player2.totalHits++; //increments computer's hits
				printf("The computer shot at (%d, %d) and it was a HIT!!\n", computer_x_coordinate, computer_y_coordinate);
				
			}
			else if(computer_hit == 0) //if computer MISSED
			{
				player2.totalMisses++; //increments computer's misses
				printf("The computer shot at (%d, %d) and it was a MISS!\n", computer_x_coordinate, computer_y_coordinate);
			}
			else //already used coordinate
			{
				printf("You already used this coordinate.\n");
			}

			system("pause");
			system("cls");

			output_current_stats(outfile, starting_player, x_coordinate, y_coordinate, player_hit, sunk_player_ship); //output computer stats to the outfile
			winning_player = check_if_winner(player1_board); //checks if computer is winner

			if (winning_player == 1) //if player or computer has 17 hits, means all ships have been sunk
			{
				printf("GAME OVER!\n");
				system("pause");
				goto endgame;
			}
			starting_player = 0; //resets starting player to 0, so player then goes
			break;
		}
	}

endgame:
	printf("Let's view the results of today's game!\n");
	if (player1.totalHits == 17) //if all ships have been sunk by player
	{
		printf("You won!\n");
		fprintf(outfile, "Player won!\n");
	}
	else //if all ships have been sunk by computer
	{
		printf("The computer won.\n");
		fprintf(outfile, "Computer won!\n");
	}

	player1.hitMissRatio = (double) player1.totalHits / player1.totalMisses * 100; //calculates the hit/miss ratio of player 
	player2.hitMissRatio = (double) player2.totalHits / player2.totalMisses * 100; //calculates the hit/miss ratio of computer
	player_stat_output(outfile, player1, player2); //sends hit/miss ratio calculated for computer and player to outfile

	fclose(outfile); //closes outfile

	printf("Goodbye!\n");

	return 0;
}