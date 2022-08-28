#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>

#define zoneWidth 32
#define zoneHeight 16

int gameOver, snakeLength, score;

struct coordinates {
	int x;
	int y;
	int direction;	// 1->up 2->left 3->down 4->right
};
typedef struct coordinates coordinates;
coordinates snakeBod[zoneWidth * zoneHeight], food;

void generateFood() {
	food.x = (rand() % zoneWidth-2);
	food.y = (rand() % zoneHeight-2);

	if(food.x <= 1 || food.y <= 0) {
		generateFood();
	}
	for(int a = 0; a < snakeLength; a++) {
		if(snakeBod[a].x == food.x && snakeBod[a].y == food.y) {
			generateFood();
		}
	}
}

void setup()
{
	gameOver = false;
	snakeLength = 3;
	score = 0;
	snakeBod[0].x = zoneWidth/2;
	snakeBod[0].y = zoneHeight/2;
	snakeBod[0].direction = 2;

	for(int a = 1; a < snakeLength; a++) {
		snakeBod[a].x = snakeBod[0].x+a;
		snakeBod[a].y = snakeBod[0].y;
	}
}

void input()
{
	switch(getch()) {
		case 'w':
			if(snakeBod[0].y-1 != snakeBod[1].y)
			{
				snakeBod[0].direction = 1;
			}
			break;
		case 'a':
			if(snakeBod[0].x-1 != snakeBod[1].x)
			{
				snakeBod[0].direction = 2;
			}
			break;
		case 's':
			if(snakeBod[0].y+1 != snakeBod[1].y)
			{
				snakeBod[0].direction = 3;
			}
			break;
		case 'd':
			if(snakeBod[0].x+1 != snakeBod[1].x)
			{
				snakeBod[0].direction = 4;
			}
			break;
	}
}

void snakeUpdate() {	
	int preX = snakeBod[0].x;
	int preY = snakeBod[0].y;
	int pre2X, pre2Y;

	for(int a = 1; a < snakeLength; a++) {
		pre2X = snakeBod[a].x;
		pre2Y = snakeBod[a].y;
		snakeBod[a].x = preX;
		snakeBod[a].y = preY;
		preX = pre2X;
		preY = pre2Y;
	}

	for(int a = 0; a < snakeLength; a++) {
		switch(snakeBod[a].direction) {
			case 1: 
				snakeBod[a].y--;
				break;
			case 2:
				snakeBod[a].x--;
				break;
			case 3:
				snakeBod[a].y++;
				break;
			case 4:
				snakeBod[a].x++;
				break;
		}
	}

	for(int a = 1; a < snakeLength; a++) {
		if(snakeBod[0].x == snakeBod[a].x && snakeBod[0].y == snakeBod[a].y) {
			gameOver = true;
		}
	}
	if(snakeBod[0].x < 1 || snakeBod[0].x > zoneWidth-2 || snakeBod[0].y < 0 || snakeBod[0].y > zoneHeight-3) {
		gameOver = true;	
	}
	if(snakeBod[0].x == food.x && snakeBod[0].y == food.y) {
		score++;
		snakeLength++;
		generateFood();
	}
}

void gameUpdate()
{
	input();
	snakeUpdate();
}

void draw() 
{
	clear();
	
	printw("Ncurses Snake\n--------------\n\n");

	for (int a = 0; a < zoneWidth; a++) {
		printw("#");
	}
	printw("\n");

	for (int a = 0; a < zoneHeight-2; a++) {
		for (int b = 0; b < zoneWidth; b++) {
			if(b == 0 || b == zoneWidth-1) {
				printw("#");
			}else if(a == food.y && b == food.x) {
				printw("Q");
			}else {
				bool d = false;
				for(int c = 0; c < snakeLength; c++) {
					if(a == snakeBod[c].y && b == snakeBod[c].x) {
						printw("@");
						d = true;
					}
				}
				if(!d) {
					printw(" ");
				}
			}
		}
		printw("\n");
	}

	for (int a = 0; a < zoneWidth; a++) {
		printw("#");
	}
	printw("\n\n");	
	printw("score: %i\n",score);
	refresh();
}

int main(int arc, char ** argv) 
{
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	setup();
	generateFood();

	while(gameOver == false) {
		gameUpdate();
		draw();
		usleep(150000);
	}

	endwin();
	return 0;
}
