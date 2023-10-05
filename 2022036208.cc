#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define DINO_HEIGHT 	13 
#define CACTUS_HEIGHT 	5
#define CACTUS_SPEED 	3
#define GRAVITY 	3
#define CEILING 	0

#define SPACE 		32 // JUMP 
#define ENTER 		10 // QUIT

void DrawDinosaur(int);  
void displayScore(int);
void DrawCactus(int, int);
int _kbhit(void);
int GetKeyDown(void);
bool isHitten(const int x, const int y);

int _kbhit(void)
{
	struct timeval tv = { 0L, 0L }; // 두개의 변수를 가지는 구조체, long 변수로 형변환 
	fd_set fds; // fd => 얘는 구조체가 아니에요 변수인데, 

	FD_ZERO(&fds); 
	FD_SET(0 ,&fds);

	return select(1, &fds, NULL, NULL, &tv); 
}

int GetKeyDown(void)
{
		 if(_kbhit()){
		 	return getch();
		 }
}

void displayScore(int score)
{
		
	mvprintw(5, 120, "Score : %d", score);
	
}

int main(int argc, char* argv[], char* env[])
{	
	initscr();
	
	int winWidth 	 = 0, winHeight = 0;
	int dinosaurHead = 0;
	int cactusHead 	 = 0, cactusPos = 0;
	bool isBottom 	= true;
	bool isJumping 	= false;
	bool ishitten 	= false;
	int getKey 	= 0;
	int score 	= 0;

	getmaxyx(stdscr, winHeight, winWidth);
	dinosaurHead 	= winHeight - DINO_HEIGHT;
	cactusHead 	= winHeight - CACTUS_HEIGHT;
	cactusPos 	= winWidth - 20;

	while(true){
		if(isHitten(cactusPos, dinosaurHead)){ // 3. 충돌체크
			ishitten = true;
			break;
		}
	
		getKey = GetKeyDown();		
		if(SPACE == getKey && isBottom){
			isJumping = true;
			isBottom = false;
		} else if(ENTER == getKey ){
			break;
		}
		
		if(isJumping){
			dinosaurHead -= GRAVITY;
		} else{
			dinosaurHead += GRAVITY;
		}

		if(winHeight <= (dinosaurHead + DINO_HEIGHT)){
			dinosaurHead = winHeight - DINO_HEIGHT;
			isBottom = true;		
		}
		
		if(dinosaurHead <= CEILING){
			isJumping = false;
		
		}

		if(score >= 500) // 2. 500점 이상에서 난이도 증가 
			cactusPos -= CACTUS_SPEED + 2;	
		else cactusPos -= CACTUS_SPEED;
		
		if(cactusPos <= 0){
			cactusPos =  winWidth - 20;
			score += 50;	
		}

		
	
		clear();

		DrawDinosaur(dinosaurHead);
		DrawCactus(cactusHead, cactusPos);	
		displayScore(score);	// 1. 점수표시
		usleep(100000);
		refresh();
 
}
	if(ishitten){
		clear();
		printw("\n\n\n\t\t\t\t|||||||||||||||||||||||||\n");
		printw("\t\t\t\t||||||||GAME-OVER||||||||\n");
		printw("\t\t\t\t|||||||||||||||||||||||||\n");
		printw("\n\n\n\t\t\t\t SCORE : %d\n", score);
		printw("\t\t\t\t Press Any ENTER Key to QUIT!");
		refresh();
		while(1){
		int pressEnterKey = GetKeyDown();
		if( pressEnterKey == ENTER ) break;
}
}	
	endwin();
	return 0;
	
}

void DrawDinosaur(int dinosaurHead)
{
	move(dinosaurHead, 0);  
	static bool legDraw = true;

	printw("        &&&&&&& \n");
	printw("       && &&&&&&\n");
	printw("       &&&&&&&&&\n");
	printw("&      &&&      \n");
	printw("&&     &&&&&&&  \n");
	printw("&&&   &&&&&     \n");
	printw(" &&  &&&&&&&&&& \n");
	printw(" &&&&&&&&&&&    \n");
	printw("  &&&&&&&&&&    \n");
	printw("    &&&&&&&&    \n");
	printw("     &&&&&&     \n");

	if (legDraw) {
		printw("     &    &&&     \n");
		printw("     &&           ");
		legDraw = false;
	}else {
		printw("     &&&  &       \n");
		printw("          &&      ");
		legDraw = true;
	}


}

void DrawCactus(int cactusHead, int cactusPos)
{
	move(cactusHead, cactusPos);
	printw("$$$$");
	move(cactusHead + 1, cactusPos);
	printw(" $$ ");
	move(cactusHead + 2, cactusPos);
	printw(" $$ ");
	move(cactusHead + 3, cactusPos);
        printw(" $$ ");
	move(cactusHead + 4, cactusPos);
        printw(" $$ ");


}

bool isHitten(const int cactusX, const int dinosaurY)
{
	
	if(cactusX >= 5 && cactusX <= 11 && dinosaurY > 8 ){
		return true;
	}
	else
		return false;
}
