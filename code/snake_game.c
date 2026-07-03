#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

/* 뱀 게임. 생명력이 줄지 않도록 계속해서 medicine를 먹어야 한다.
medicine를 먹지 않으면 특정 시간이 지날 때마다 생명력이 하나씩 줄어든다.
*/

#define ROW 20
// N은 Number of rows 행의 수가 20
#define COLUMN 40
// M은 NUmber of columns 열의 수가 40

#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80

int i, j;
// two global variables for counting things
int gameField[ROW][COLUMN] = { 0 };
// initialize all the field array value to 0
int x, y;
// initialize the coordinate points for snake
int Gy, Head, Tail;
int gameStatus;
// check if game is working or not
int medicine = 0;
// initialize the medicine value to 0, 1 means it appears
int medicineX, medicineY;
// coordinate points for medicine
int varKeyboard;
// holds an input from the keyboard
int direction;
// snake-moving direction, whenever key pressed -> called
int vitality, count, speedUpCount = 0, lastDivision;
int highScore;
int lastDivisionSpeed = 0;
clock_t currentTime, start, end, notPlayingTime;

FILE *f;
// file handler

void snakeInitialization() {
	f = fopen("highscore.txt", "r");
	// file open with just read mode
	fscanf(f, "%d", &highScore);
	// scan the open file and assign the file txt to variable called highScore
	fclose(f); 
	// make sure to close file after finishing scanning the file

	x = ROW / 2;
	y = COLUMN / 2;
	// begining points for snake, head of snake

	Gy = y;
	// initial y coordniate point
	Head = 5;
	// WHen array value holds the value 5, It's Head
	Tail = 1;
	// When array value holds the value 1, It's Tail
	gameStatus = 0;
	// set the Game value to 0, which is stopping. 1 -> running
	direction = RIGHT;
	// initialize the direction to where snake moves
	vitality = 5;
	count = 0, lastDivision = 0;

	// setting the snake body (Head+Tail) part
	for (i = 0; i < Head; i++) {
		Gy++;
		// 21, 22, 23, 24, 25
		gameField[x][Gy - Head] = i + 1;
		// initialize the y coordinate points Gy - Head (16, 17, 18, 19, 20)
		// to 1, 2, 3, 4, 5
	}
}

void startScreen() {
	printf("\n");
	printf("                             ##\n");
	printf("   #####                     ##\n");
	printf("  ##   ##                    ##\n");
	printf("  ##       ## ###    ######  ##  ##    #####\n");
	printf("   #####   ###  ##  ##   ##  ## ##    ##   ##\n");
	printf("       ##  ##   ##  ##   ##  ####     #######\n");
	printf("  ##   ##  ##   ##  ##  ###  ## ##    ##\n");
	printf("   #####   ##   ##   ### ##  ##  ##    #####\n");

	printf("\n\n");

	printf("    ####\n");
	printf("   ##  ##\n");
	printf("  ##        ######  ### ##    #####\n");
	printf("  ##       ##   ##  ## # ##  ##   ##\n");
	printf("  ##  ###  ##   ##  ## # ##  #######\n");
	printf("   ##  ##  ##  ###  ## # ##  ##\n");
	printf("    #####   ### ##  ##   ##   #####\n");

	printf("\n\n");

	printf("  Press \" 1 \" to start\n\n");
	printf("  Press \" 2 \" to learn about Snake Game\n\n");

	printf("  >>> ");
	scanf(" %d", &gameStatus);
	system("cls");
}

void howScreen() {
	printf("\n");
	printf("     ##     ##                           ##\n");
	printf("     ##     ##                           ##\n");
	printf("    ####    ######    #####   ##   ##  ######\n");
	printf("    ## #    ##   ##  ##   ##  ##   ##    ##\n");
	printf("   ######   ##   ##  ##   ##  ##   ##    ##\n");
	printf("   ##   #   ##   ##  ##   ##  ##  ###    ##\n");
	printf("  ###   ##  ######    #####    ### ##     ###\n");

	printf("\n\n");

	printf("  ( 1 ) Snake Game is a game where snake needs to survive as much as it can eating a special medicine (+)\n\n");

	printf("  ( 2 ) Developed with ♥ by Park Jeong Eun\n");

	printf("\n\n");

	printf("  ######             ###\n");
	printf("  ##   ##             ##\n");
	printf("  ##   ##  ##   ##    ##      #####    #####\n");
	printf("  ######   ##   ##    ##     ##   ##  ##\n");
	printf("  ## ##    ##   ##    ##     #######   ####\n");
	printf("  ##  ##   ##  ###    ##     ##           ##\n");
	printf("  ##   ##   ### ##   ####     #####   #####\n");
	
	printf("\n\n");
		
	printf("  ( 1 ) As time goes by, nake will be weaker and lose vitality one by one.\n");
	printf("        When snake lose all the vitality, the game is automatically over.\n\n");
	printf("  ( 2 ) The speed of decreasing vitality rate will be getting faster each time the message pops up.\n\n");
	printf("  ( 3 ) When snake hit the wall(*), the game is automatically over.\n\n");
	printf("  ( 4 ) Your playing time is equivalent to your score and your score will be displayed.\n\n");
	printf("  ( 5 ) You're not allowed to use an opposite key while pressing a certain array key.\n");
	printf("        (i.e. when pressing the right arrow key, the left arrow key is inactive.\n");
	
	printf("\n\n  ROWow, press \" 1 \" to start >>> ");
	
	while (1) {
		scanf(" %d", &gameStatus);
		if (gameStatus == 1) break;
	}

	system("cls");
}

void print() {
	// printing out the vitality
	for (i = 0; i < COLUMN - 23; i++) {
		printf("%c", 32);
	}
	printf("【 Vitality : ");
	for (i = 0; i < vitality; i++) {
		printf("♥");
	}
	for (i = 0; i < 5 - vitality; i++) {
		printf("♡");
	}
	printf(" 】\n");

	// printing out the field of play in the first row
	printf("%c", 32);
	for (i = 0; i <= COLUMN + 1; i++) {
		printf("%c", 42);
	}
	printf("\n");

	// printing out the field of play in columns
	for (i = 0; i < ROW; i++) {
		printf("%c", 32);
		printf("%c", 42);
		// SPACE AREA + SNAKE BODY AREA
		for (j = 0; j < COLUMN; j++) {
			if (gameField[i][j] == 0) {
				// SPACE AREA
				printf("%c", 32);
			}
			else if (gameField[i][j] > 0) {
				if (gameField[i][j] != Head) {
					// body part, not head
					printf("%c", 79);
				}
				else {
					// if field[i][j] == Head, Head part
					printf("%c", 64);
				}
			}
			else {
				// field array value less than 0
				if (gameField[i][j] == -1) {
					// if field aarray value is -1, medicine part
					printf("%c", 43);
				}
			}
		}
		printf("%c\n", 42);
	}

	// printing out the field of play in the last row
	printf("%c", 32);
	for (i = 0; i <= COLUMN + 1; i++) {
		printf("%c", 42);
	}
	printf("\n");

	// SCORE TABLE
	printf(" Current Score : %3d | Highest Score : %3d\n", currentTime, currentTime > highScore ? currentTime : highScore);
}

void speedManage() {
	if (currentTime % 30 == 0 && currentTime > 0 && currentTime <= 90) {
		if (lastDivisionSpeed != currentTime / 30) {
			lastDivisionSpeed = currentTime / 30;
			system("cls");
			// remove all the printed messages

			// speed up message
			printf("\n                                           ##\n");
			printf("   #####                                   ##\n");
			printf("  ##   ##                                  ##\n");
			printf("  ##       ######    #####    #####    ######\n");
			printf("   #####   ##   ##  ##   ##  ##   ##  ##   ##\n");
			printf("       ##  ##   ##  #######  #######  ##   ##\n");
			printf("  ##   ##  ##   ##  ##       ##       ##   ##\n");
			printf("   #####   ######    #####    #####    ######\n");
			printf("           ##\n");
			printf("           ##\n\n\n");
			printf("                      ##\n");
			printf("  ##   ##  ######     ##\n");
			printf("  ##   ##  ##   ##    ##\n");
			printf("  ##   ##  ##   ##    ##\n");
			printf("  ##   ##  ######     ##\n");
			printf("  ##   ##  ##         ##\n");
			printf("  ##   ##  ##\n");
			printf("   #####   ##         ##\n");

			Sleep(2000);
			speedUpCount++;
			vitality = 5;

			system("cls");
			// set the vitality to 5, RESET
		}
	}
}

void ResetScreenPosition() {
	// WIndows API functions
	HANDLE hOut;
	// HANDLE TYPE provides handle to the console of our program.
	COORD Position;
	// keeps the coordinate of the console screen.
	// COORD is a structrue to hold screen coordinates X and Y
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
	// Sets the cursor position in the specified console screen buffer.
}

void randomMedicine(){
	// place a medicine in random position
	srand(time(NULL));
	medicineX = rand() % ROW;
	// between 0 ~ 19
	medicineY = rand() % COLUMN;
	// between 0 ~ 39

	if (medicine == 0 && gameField[medicineX][medicineY] == 0) {
		// assign no medicine with empty space
		gameField[medicineX][medicineY] = -1;
		medicine = -1;
		// -1 means that medicine appears on screen
	}
}

void gameOver(clock_t _t) {
	printf("\a");
	system("cls");
	// removel all the previously printed messages

	printf("\n");
	printf("    ####\n");
	printf("   ##  ##\n");
	printf("  ##        ######  ### ##    #####\n");
	printf("  ##       ##   ##  ## # ##  ##   ##\n");
	printf("  ##  ###  ##   ##  ## # ##  #######\n");
	printf("   ##  ##  ##  ###  ## # ##  ##\n");
	printf("    #####   ### ##  ##   ##   #####\n\n\n");
	
	printf("    ###\n");
	printf("   ## ##\n");
	printf("  ##   ##  ### ##    #####   ## ###\n");
	printf("  ##   ##   ## #    ##   ##  ###\n");
	printf("  ##   ##   ## #    #######  ##\n");
	printf("   ## ##     ##     ##       ##\n");
	printf("    ###      ##      #####   ##\n\n\n");

	printf(" 《 Your final score is: %d 》\n", _t);
	if(_t > highScore) {
		printf("  New Highest Score! Congrats :)\n", _t);
		f = fopen("highscore.txt", "w");
		fprintf(f, "%d", _t);
		// previous file text is erased whenever you print something diffrent in file
		fclose(f);
	}
	printf("\n  Enter any key to end game >>> ");
	scanf("");
	scanf(" %d", &gameStatus);
	gameStatus = 3;

}

int getchReturnValue() {
	if (_kbhit()) {
		// if keyboard is hit
		return _getch();
		// _getch() uses console input without input buffer
	}
	else {
		return -1000;
	}
}

void snakeMovement(int direction) {
		switch (direction) {
			case RIGHT:
				// RIGHT
				y++;
				if (y == COLUMN) {
					gameOver(currentTime);
				}
				else if (gameField[x][y] == -1) {
					// eats a medicine
					medicine = 0;
					if (vitality != 5) vitality++;
				}
				Head++;
				gameField[x][y] = Head;
				break;

			case LEFT:
				// LEFT
				y--;
				if (y == -1) {
					gameOver(currentTime);
				}
				else if (gameField[x][y] == -1) {
					// eats a medicine
					medicine = 0;
					if (vitality != 5) vitality++;
				}
				Head++;
				gameField[x][y] = Head;
				break;
			
			case UP:
				// UP
				x--;
				if (x == -1) {
					gameOver(currentTime);
				}
				else if (gameField[x][y] == -1) {
					// eats a medicine
					medicine = 0;
					if (vitality != 5) {
						vitality++;
					}
				}
				Head++;
				gameField[x][y] = Head;
				break;

			case DOWN:
				// DOWN
				x++;
				if (x == ROW) {
					gameOver(currentTime);
				}
				else if (gameField[x][y] == -1) {
					// eats a medicine
					medicine = 0;
					if (vitality != 5) {
						vitality++;
					}
				}
				Head++;
				gameField[x][y] = Head;
				break;
		}

		for (i = 0; i < ROW; i++) {
			for (j = 0; j < COLUMN; j++) {
				if (gameField[i][j] == Tail) {
					gameField[i][j] = 0;
				}
			}
		}

		Tail++;
}

void timeChecking() {
	if (currentTime < 30) {
		if (currentTime % 5 == 0 && currentTime != 0) {
			if (lastDivision != currentTime / 5) {
				--vitality;
				if (vitality == 0) {
					gameOver(currentTime);
				}
				lastDivision = currentTime / 5;
			}
		}
	}

	else if (currentTime < 60) {
		if (currentTime % 4 == 0 && currentTime != 30) {
			if (lastDivision != currentTime / 4) {
				--vitality;
				if (vitality == 0) {
					gameOver(currentTime);
				}
				lastDivision = currentTime / 4;
			}
		}
	}

	else if (currentTime < 90) {
		if (currentTime % 3 == 0 && currentTime != 60) {
			if (lastDivision != currentTime / 3) {
				--vitality;
				if (vitality == 0) {
					gameOver(currentTime);
				}
				lastDivision = currentTime / 3;
			}
		}
	}

	else {
		if (currentTime % 2 == 0 && currentTime != 90) {
			if (lastDivision != currentTime / 2) {
				--vitality;
				if (vitality == 0) {
					gameOver(currentTime);
				}
				lastDivision = currentTime / 2;
			}
		}
	}
}

int main() {
	start = clock();
	
	snakeInitialization();
	startScreen();

	if (gameStatus == 2) {
		howScreen();
	}

	end = clock();
	notPlayingTime = end - start;

	while (gameStatus == 1) {
		// if game value is 0, the game ends.
		currentTime = ((clock() - notPlayingTime) / CLOCKS_PER_SEC) - speedUpCount * 2;
		// continuously checking the current time
		print();
		speedManage();
		ResetScreenPosition();
		randomMedicine();
		
		varKeyboard = getchReturnValue();
		if (varKeyboard == -1000) {
			snakeMovement(direction);
		}
		else if (varKeyboard == 224) {
			varKeyboard = _getch();
			if (abs(direction - varKeyboard) != 2 && abs(direction - varKeyboard) != 8) {
				direction = varKeyboard;
				snakeMovement(direction);
			}
			else {
				snakeMovement(direction);
			}
		}
		timeChecking();
		Sleep(20);
	}
}