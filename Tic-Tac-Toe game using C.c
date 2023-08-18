#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

//function to show the remaining options out of 9
void showRem(char *n){

	int i;
	for(i = 0; i < 9; i++){
		if( n[i] != 'O' && n[i] != 'X' ){
			printf("%c ",n[i]);
		}
	}
}

//function to count the remaining options
int countRem(char *n){

	int i,rem = 0;
	for(i = 0; i < 9; i++){
		if( n[i] != 'O' && n[i] != 'X' ){
			rem++;
		}
	}

	return rem;
}

//function to write the win record in record.txt file
void write_record(int userWins, int cmpWins){

	//Opening/Creating the file
	FILE *file = fopen("record.txt","w");

	//If file can't be created or opened
	if(file == NULL){

		//printing error
		printf("\nUnable to create the File!");
		//exiting the program
		exit(1);
	}


	//writing the record of the Human player and the Computer
	fprintf(file,"U : %d | C : %d",userWins,cmpWins);
	//closing the file
	fclose(file);

}

//function to read the existing win record from the file
void read_record(int *userWins, int *cmpWins ){

	//opening the record.txt file for reading
	FILE *file = fopen("record.txt","r");

	//If the file does not exist already, this means the program is running for the first time
	if(file == NULL){
		//then record should be 0,0 for both
		*userWins = 0;
		*cmpWins = 0;

		//Creating the record.txt file now
		write_record(*userWins, *cmpWins);
	}
	else{
		//If file exists then read and store the wins in userWins and cmpWins variables
		fscanf(file,"U : %d | C : %d", userWins, cmpWins);
	}

	//closing the file
	fclose(file);
}

//function to print the board of the Tic Tac Toe Game
void printTable(char *n, int userWins, int cmpWins){

	system("cls");
	printf("\n\tUser : %d  | Computer : %d", userWins, cmpWins);
    printf("\n\n\n\t     |     |     ");
    printf("\n\t  %c  |  %c  |  %c \n", n[0], n[1], n[2]);

    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");

    printf("\t  %c  |  %c  |  %c \n", n[3], n[4], n[5]);

    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");

    printf("\t  %c  |  %c  |  %c \n", n[6], n[7], n[8]);

    printf("\t     |     |     \n\n");
}

//function to detect and declare win
int checkWin(char *n, int *userWins, int *cmpWins){

	//variable that will contain the winner's letter i.e. Human : 'X', Computer : 'O', Draw : 'N'
	char winner = ' ';

	//Winning Scenarios

	//Horizontal Matches
	if( n[0] == n[1] && n[1] == n[2]){
		winner = n[0];
	} else if( n[3] == n[4] && n[4] == n[5]){
		winner = n[3];
	} else if( n[6] == n[7] && n[7] == n[8]){
		winner = n[6];
	}

	//Vertical Matches
	else if( n[0] == n[3] && n[3] == n[6]){
		winner = n[0];
	} else if( n[1] == n[4] && n[4] == n[7]){
		winner = n[1];
	} else if( n[2] == n[5] && n[5] == n[8]){
		winner = n[2];
	}
	//Diagonal Matches
	else if( n[0] == n[4] && n[4] == n[8]){
		winner = n[0];
	} else if( n[2] == n[4] && n[4] == n[6]){
		winner = n[6];
	}
	//If no move is remaining then no one is the winner
	else if( countRem(n) == 0){
		winner = 'N';
	}

	// winner variable is not empty then announcing the winner
	if( winner != ' '){

		//Human is the Winner
		if(winner == 'X'){

			//increment the user wins
	    	*userWins = *userWins + 1;
	    	//Show the Updated Game Screen

			printTable(n,*userWins, *cmpWins);
			//Also update the record in the file
			write_record(*userWins, *cmpWins);

			//printing a Congratulatory Message
			printf("\n\t****************************************************\n");
			printf("\tYou Won! Congratulations! You are a True Champion!");
			printf("\n\t****************************************************\n");


		}
		//Computer is the Winner
		else if(winner == 'O'){

			//increment the computer Wins
			*cmpWins = *cmpWins + 1;
			//Displaying the updated game screen

			printTable(n,*userWins, *cmpWins);
			//also writing the new record in the file
			write_record( *userWins, *cmpWins);

			//printing the message
			printf("\n\t**********************************************************************\n");
			printf("\tComputer Won! It's Okay to Lose a game! After All, It's just a Game.");
			printf("\n\t**********************************************************************\n");


		}
		//Draw
		else {
			printf("\n\t**********************************\n");
			printf("\tNo one Won! This Game is a Draw!");
			printf("\n\t**********************************\n");
		}
		//Return 1 means that the game has ended
		return 1;
	}
	else{
		//Return 0 means the game should continue
		return 0;
	}


}

//This function will initialize the Values of the Tic Tac Toe Game
//when Game starts for the first time
// or when game ends and user plays the game again
void init(char *n){

	n[0] = '1';
	n[1] = '2';
	n[2] = '3';
	n[3] = '4';
	n[4] = '5';
	n[5] = '6';
	n[6] = '7';
	n[7] = '8';
	n[8] = '9';
}


//Main function
void main(){

	//These Variables will store the Win Count of the human player and the computer
	int userWins, cmpWins;

	//Values for the Tic Tac Toe Game using the char pointer
	char *n;

	//Seeding to get Random numbers
	srand(time(0));


	//Dynamically allocating the memory for 9 characters
	n = (char*)malloc(9*sizeof(char));

	// initializing the values of the game
	init(n);

	//reading the previous record from the file
	read_record(&userWins, &cmpWins);

	//Loop for the Main Game
	while(1){

		//First Menu
		int choice;
		printf("\n\t1. Play Game");
		printf("\n\t2. Quit");

		//Taking choice from user until a valid input is given
		while(1){
			printf("\n\tEnter your Choice : ");
			scanf("%d",&choice);
			//if choice is not 1 or 2, show error message
			if(choice > 2 || choice < 1){
				printf("\n\tInvalid Choice!!!");
			}
			//Input is valid then break the loop
			else{
				break;
			}
		}

		// If user chose option 2 (Quit) then break the loop and exit the program
		if( choice == 2){
			break;
		}
		else{
		// If option 1 (Play Game) is selected

			//initializing the values of the game again for each game
			init(n);

			// Loop for turns in a Single Game
			while(1){

				//Variable Choice
				int ch;

				// Display Game

			printTable(n,userWins, cmpWins);
				//Detect for win and if win is detected, Break the Loop and End the Game
				if(checkWin(n,&userWins, &cmpWins) == 1)
				break;

				//show the Remaining Options to the user
				printf("\n\n\tPossible Options: ");
				showRem(n);

				//Loop to Keep Taking Input Choice from User until a valid choice is entered
				while(1){
					printf("\n\tEnter your choice: ");
					scanf("%d",&ch);

					//If choice is already marked then ask user to enter again
					if(n[ch - 1] == 'X' || n[ch - 1] == 'O' || n[ch - 1] <= '0' || n[ch - 1] > '9' ){
						printf("\n\t### Invalid Choice!!! ###");
					}
					//If choice is Valid then Stop asking for choice input
					else{
						break;
					}
				}

				//Marked the chosen place with 'X' Symbol for the Human Player
				n[ch - 1] = 'X';


				//  *** Computers Turn ***

				//show the game
			printTable(n, userWins, cmpWins);

				//Detect for win
				if(checkWin(n,&userWins, &cmpWins) == 1)
				break;

				//Keep taking random number from the computer until a valid choice comes up
				while(1){
					//generating a random number from 0-8
					ch = rand() % 9;

					//If number is not marked then break the loop
					if( n[ch] != 'X' && n[ch] != 'O'){
						break;
					}
				}

				//Mark the computers choice (Randomly generated) with symbol 'O'
				n[ch] = 'O';

			}
			//Single Game Loop ends here
		}
	}
	free(n);
	n = NULL;

}
