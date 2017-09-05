#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
	int roll = 0;
	int counter = 0;
    int pot = 0;
    bool print = 0;
	int numPlayers;
	int winner;
	int seed;
	typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;
	faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
	const char * names[] = { " Whoopi ", " Dale ", " Rosie ", " Jimmie "," Barbara ", " Kyle ", " Raven ", " Tony ", " Jenny ", " Clint " };
	printf("Enter random seed number: \n");
	scanf("%d", &seed);
	srand(seed);
	printf("Enter the number of players: \n");
	scanf("%d", &numPlayers);
	int money[numPlayers - 1];
	for (int i = 0; i < numPlayers; i++) { //Creates an array to track the money corresponding to the position of the person
		money[i] = 3;
	}
	while (1) {
		for (int i = 0; i < numPlayers; i++) { //Who is rolling
                int rollTime = money[i];
                if (rollTime > 3) { //Only roll three times if they have over $3
                    rollTime = 3;
                }
                if (rollTime > 0) {
                    printf("%s rolls...", names[i]);
                    print = 1;
                }
				for (int j = rollTime; j > 0; j--) { //How many times the person rolls
					roll = rand() % 6;
					if (die[roll] == 0) { //Die rolls left
						if (i == 0) {
							money[i] = money[i] - 1;
							money[numPlayers - 1] = money[numPlayers - 1] + 1; //Special case to pass money to the last person
							printf(" gives $1 to %s", names[numPlayers-1]);
						} else {
							money[i] = money[i] - 1; //Normal scenario
							money[i - 1] = money[i - 1] + 1;
							printf(" gives $1 to %s", names[i-1]);
						}
					} else if (die[roll] == 1) { //Die rolls right
						if (i == numPlayers-1) { //Special case to pass money to first person
							money[i] = money[i] - 1;
							money[0] = money[0] + 1;
							printf(" gives $1 to %s", names[0]);
						} else {
							money[i] = money[i] - 1; //Normal scenario
							money[i+1] = money[i+1] + 1;
							printf(" gives $1 to %s", names[i+1]);
						}
					} else if (die[roll == 2]) { //Die rolls center
						money[i] = money[i] - 1;
						pot++;
						printf(" puts $1 in the pot");
					} else {
						printf(" gets a pass"); //Rolls anything else
					}
					for (int m = 0; m < numPlayers; m++) { //Checks to see if only one person has money
						if (money[m] > 0) {
							counter++;
							winner = m;
						}
					}
					if (counter == 1) { //Winning message and stops the program
                        printf("\n");
						printf("%s wins the $%d pot with $%d left in the bank! ", names[winner], pot, money[winner]);
						exit(0);
					} else {
                        counter = 0;
				}
                }
                    if (print == 1) { //Only prints a line if someone rolls
                     printf("\n");
                     print = 0;             
                }
			}
        }
    }
