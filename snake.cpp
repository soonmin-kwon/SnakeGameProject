#include <iostream>
#include <locale.h>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <ncurses.h>
using namespace std;

int map[40][70] = { 0, };
int stage = 1;
int counter = 0;
WINDOW* screen;
int inputKey;
int currentHead = 2;  // 초기 snake의 방향 : 왼쪽

int headDirection[4][2] = {
  {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};  // snake head가 움직이는 방향; 위, 아래, 왼, 오


vector <int> xPos;  // snake의 x좌표가 있는 벡터
vector <int> yPos;  // snake의 y좌표가 있는 벡터

// snake 좌표 이동
void move(int direction) {
	inputKey = wgetch(stdscr);
	// 그 전 방향에 따라  제약조건 추가
	if (inputKey == KEY_UP && currentHead != 1) {
		currentHead = 0;
	}
	else if (inputKey == KEY_DOWN && currentHead != 0) {
		currentHead = 1;
	}
	else if (inputKey == KEY_LEFT && currentHead != 3) {
		currentHead = 2;
	}
	else if (inputKey == KEY_RIGHT && currentHead != 2) {
		currentHead = 3;
	}
	for (int i = 0; i < xPos.size(); i++) {  // 이전의 snake를 지움
		mvprintw(xPos[i], yPos[i], " ");
	}

	for (int i = xPos.size(); i > 0; i--) {  // head를 제외한 body를 한 칸씩 옮김
		xPos[i] = xPos[i - 1];
		yPos[i] = yPos[i - 1];
		
	}
	xPos[0] = xPos[0] + headDirection[direction][0]; // 방향키에 따라 head의 좌표 재설정
	yPos[0] = yPos[0] + headDirection[direction][1];

	for (int i = 0; i < xPos.size(); i++) {  // 화면상에 출력
		if (i == 0) mvprintw(xPos[i], yPos[i], "O");
		else mvprintw(xPos[i], yPos[i], "o");
	}
}


//stage별 맵 구현
void gmap(int runtime,int stage) {
	srand((unsigned int)time(NULL));
	int maxX, maxY;
	if (stage == 1) {
		wclear(screen);
		screen = newwin(40, 70, 2, 2);
		getmaxyx(stdscr, maxY, maxX);
		for (int y = 0; y < 40; y++) {
			for (int x = 0; x < 70; x++) {
				if (y == 0 && (x == 0 || x == 69) || (y == 39 && (x == 0 || x == 69))) {
					map[y][x] = 2;
					wmove(screen, y, x);
					waddch(screen, '+');
				}
				else if (x == 0 || x == 69) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '|');
				}
				else if (y == 0 || y == 39) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '-');
				}
			}
		}
		//gate 출력(임시)
		if (runtime % 10 >= 1 && runtime <= 2) {
			while (counter < 2) {
				int g1 = rand() % 40;
				int g2 = rand() % 70;
				if (map[g1][g2] == 1) {
					if (counter == 0) {
						map[g1][g2] = 7;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					else {
						map[g1][g2] = 8;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					counter++;
				}
			}
		}
		wrefresh(screen);
	}
	else if(stage == 2) {
		wclear(screen);
		int map[32][56] = { 0, };
		screen = newwin(32, 56, 7,7);
		getmaxyx(stdscr, maxY, maxX);
		for (int y = 0; y < 32; y++) {
			for (int x = 0; x < 56; x++) {
				if (y == 0 && (x == 0 || x == 55) || (y == 31 && (x == 0 || x == 55))) {
					map[y][x] = 2;
					wmove(screen, y, x);
					waddch(screen, '+');
				}
				else if (x == 0 || x == 55) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '|');
				}
				else if (y == 0 || y == 31) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '-');
				}
			}
		}
		if (runtime % 10 >= 1 && runtime <= 2) {
			while (counter < 2) {
				int g1 = rand() % 32;
				int g2 = rand() % 56;
				if (map[g1][g2] == 1) {
					if (counter == 0) {
						map[g1][g2] = 7;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					else {
						map[g1][g2] = 8;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					counter++;
				}
			}
		}
		wrefresh(screen);
	}
	else if (stage == 3) {
		wclear(screen);
		int map[24][42] = { 0, };
		screen = newwin(24, 42, 12, 12);
		getmaxyx(stdscr, maxY, maxX);
		for (int y = 0; y < 24; y++) {
			for (int x = 0; x < 42; x++) {
				if (y == 0 && (x == 0 || x == 41) || (y == 23 && (x == 0 || x == 41))) {
					map[y][x] = 2;
					wmove(screen, y, x);
					waddch(screen, '+');
				}
				else if (x == 0 || x == 41) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '|');
				}
				else if (y == 0 || y == 23) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '-');
				}
			}
		}
		if (runtime % 10 >= 1 && runtime <= 2) {
			while (counter < 2) {
				int g1 = rand() % 24;
				int g2 = rand() % 42;
				if (map[g1][g2] == 1) {
					if (counter == 0) {
						map[g1][g2] = 7;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					else {
						map[g1][g2] = 8;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					counter++;
				}
			}
		}
		wrefresh(screen);
	}
	else if (stage == 4) {
		wclear(screen);
		int map[20][35] = { 0, };
		screen = newwin(20, 35, 17, 17);
		getmaxyx(stdscr, maxY, maxX);
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 35; x++) {
				if (y == 0 && (x == 0 || x == 34) || (y == 19 && (x == 0 || x == 34))) {
					map[y][x] = 2;
					wmove(screen, y, x);
					waddch(screen, '+');
				}
				else if (x == 0 || x == 34) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '|');
				}
				else if (y == 0 || y == 19) {
					map[y][x] = 1;
					wmove(screen, y, x);
					waddch(screen, '-');
				}
			}
		}
		if (runtime % 10 >= 1 && runtime <= 2) {
			while (counter < 2) {
				int g1 = rand() % 20;
				int g2 = rand() % 35;
				if (map[g1][g2] == 1) {
					if (counter == 0) {
						map[g1][g2] = 7;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					else {
						map[g1][g2] = 8;
						wmove(screen, g1, g2);
						waddch(screen, 'G');
					}
					counter++;
				}
			}
		}
	
		wrefresh(screen);
	}

}
//mission창 score창 프린트
void mission_score() {
	WINDOW* score;
	WINDOW* mission;
	mission = newwin(20, 35, 22, 73);
	wborder(mission, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(mission, 2, 2, "Mission");
	mvwprintw(mission, 5, 2, "B: ");
	mvwprintw(mission, 8, 2, "+: ");
	mvwprintw(mission, 11, 2, "-: ");
	mvwprintw(mission, 14, 2, "G: ");
	wrefresh(mission);
	score = newwin(20, 35, 2, 73);
	wborder(score, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(score, 2, 2, "Score Board");
	mvwprintw(score, 5, 2, "B:");
	mvwprintw(score, 8, 2, "+:");
	mvwprintw(score, 11, 2, "-:");
	mvwprintw(score, 14, 2, "G:");
	wrefresh(score);
}
	
int main() {

	initscr(); 
	resize_term(45, 110);
	noecho();
	border('o', 'o', 'o', 'o', 'o', 'o', 'o', 'o');
	refresh();
	gmap(1,5);
	mission_score();
	// Step 5 : mission, socre
	

	setlocale(LC_ALL, "");
	initscr();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);  // 키보드 입력 설정
	curs_set(0);  // 커서 지우기
	noecho();  // 입력한 키 값을 화면에 보이지 않기

	xPos.push_back(10);  // 초기 snake의 위치 지정
	xPos.push_back(10);
	xPos.push_back(10);
	yPos.push_back(55);
	yPos.push_back(56);
	yPos.push_back(57);
	// 초기화면 snake 출력
	for (int i = 0; i < xPos.size(); i++) {
		if (i == 0) mvprintw(xPos[i], yPos[i], "O");
		else mvprintw(xPos[i], yPos[i], "o");
	}
	
	while (true) {
		if (stage == 2) {
			gmap(1,stage);
		}
		mission_score();
		move(currentHead);
		usleep(100000);  // 0.5초마다
	}

	refresh();
	getch();
	endwin();
	return 0;

}