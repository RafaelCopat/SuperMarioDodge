#include <Windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <cmath>
#include <vector>
#include <fstream>
#include "Image.h"
#include "Layer.h"
#include "Element.h"

//Initialize Images
Image initialScreen("initialscreen.ptm");
Image winScreen("winscreen.ptm");
Image back("background.ptm");
Image middle("middleground.ptm");
Image fore("foreground.ptm");
Image mario2("Mario1.ptm");
Image mario3("Mario2.ptm");
Image mario1("Mario3.ptm");
Image mario2Mid("Mario1mid.ptm");
Image mario3Mid("Mario2mid.ptm");
Image mario1Mid("Mario3mid.ptm");
Image mario1Back("mario1back.ptm");
Image mario2Back("mario2back.ptm");
Image shell("ShellShock_SPM.ptm");
Image shellBack("shellBack.ptm");
Image shellMiddle("shellMiddle.ptm");
Image rshell("rShellFore.ptm");
Image rshellBack("rshellBack.ptm");
Image rshellMiddle("rShellMiddle.ptm");



Image gameover("gameover.ptm");
Image coinFore("coinFore.ptm");
Image coinMiddle("coinMiddle.ptm");
Image coinBack("coinBack.ptm");

const int GAME_ON_FOREGROUND = 2;
const int GAME_ON_MIDDLEGROUND = 1;
const int GAME_ON_BACKGROUND = 0;

const int GAME_STARTED = 1;
const int GAME_NOT_STARTED = 0;
const int GAME_RESTARTED = 2;

const bool IS_MARIO = true;
const bool IS_NOT_MARIO = false;
const bool IS_STATIONARY = false;
const bool IS_MOBILE = true;

int GAME_STATE = GAME_NOT_STARTED;
int GAME_MODE = GAME_ON_FOREGROUND;
int coins = 0;

int backNumberOfElements = 15;
int middleNumberOfElements = 14;
int foreNumberOfElements = 16;

Element *elementsBack = new Element[backNumberOfElements];
Element *elementsMiddle = new Element[middleNumberOfElements];
Element *elementsFore = new Element[foreNumberOfElements];
Image *mariosBack = new Image[3];
Image *mariosMiddle = new Image[3];
Image *marios = new Image[3];


Image lastScreen;
Layer camadas[3];
int gameWidth = 800;
int gameHeight = 600;
bool GAMESTOPPED;
int timeGlut = 20;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(gameWidth, gameHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE,
		lastScreen.getPixels());
	glFlush();

}

void init(void)
{
	coins = 0;
	timeGlut = 20;
	if (GAME_STATE == GAME_RESTARTED) {
		GAME_STATE = GAME_STARTED;
	}
	else {
		GAME_STATE = GAME_NOT_STARTED;
	}
	GAME_MODE = GAME_ON_FOREGROUND;
	GAMESTOPPED = false;
					  
	marios[0] = mario1.getSubImage();
	marios[1] = mario2.getSubImage();
	marios[2] = mario3.getSubImage();

	mariosMiddle[0] = mario1Mid.getSubImage();
	mariosMiddle[1] = mario2Mid.getSubImage();
	mariosMiddle[2] = mario3Mid.getSubImage();

	mariosBack[0] = mario1Back.getSubImage();
	mariosBack[1] = mario2Back.getSubImage();
	mariosBack[2] = mario1Back.getSubImage();
	//initialize elements
	//mario always on [0]

	Layer background(back.getSubImage(), fore.getWidth(), fore.getHeight(), elementsBack, backNumberOfElements);
	Layer middleground(middle.getSubImage(), fore.getWidth(), fore.getHeight(), elementsMiddle, middleNumberOfElements);
	Layer foreground(fore.getSubImage(), fore.getWidth(), fore.getHeight(), elementsFore, foreNumberOfElements);

	elementsBack[0] = Element(mariosBack, 365, 450, IS_MARIO, IS_MOBILE);
	elementsBack[0].setVisible(false);
	elementsBack[1] = Element(coinBack , rand() % 700 + 500, 450, IS_NOT_MARIO, IS_STATIONARY);
	elementsBack[2] = Element(coinBack, rand() % 700 + 500, 450, IS_NOT_MARIO, IS_STATIONARY);
	elementsBack[3] = Element(coinBack, rand() % 700 + 500, 450, IS_NOT_MARIO, IS_STATIONARY);
	elementsBack[4] = Element(shellBack, rand() % 2000 + 500, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[5] = Element(shellBack, rand() % 2000 + 500, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[6] = Element(shellBack, rand() % 2000 + 500, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[7] = Element(shellBack, rand() % 2000 + 500, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[8] = Element(shellBack, rand() % 2000 + 500, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[9] = Element(shellBack, rand() % 2000 + 500, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[10] = Element(shellBack, rand() % 2000 + 1000, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[11] = Element(shellBack, rand() % 2000 + 1000, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[12] = Element(shellBack, rand() % 2000 + 1000, 450, IS_NOT_MARIO, IS_MOBILE);
	elementsBack[13] = Element(rshellBack, rand() % 3000 + 1000, 450, IS_NOT_MARIO, IS_MOBILE, rand() % 5 + 4);
	elementsBack[14] = Element(rshellBack, rand() % 3000 + 1000, 450, IS_NOT_MARIO, IS_MOBILE, rand() % 5 + 4);

	elementsMiddle[0] = Element(mariosMiddle, 365, 306, IS_MARIO,  IS_MOBILE);
	elementsMiddle[0].setVisible(false);
	elementsMiddle[1] = Element(coinMiddle, rand() % 1800 + 500, 306, IS_NOT_MARIO, IS_STATIONARY);
	elementsMiddle[2] = Element(coinMiddle, rand() % 1800 + 500, 306, IS_NOT_MARIO, IS_STATIONARY);
	elementsMiddle[3] = Element(coinMiddle, rand() % 1800 + 500, 306, IS_NOT_MARIO, IS_STATIONARY);
	elementsMiddle[4] = Element(shellMiddle, rand() % 4000 + 500, 306,  IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[5] = Element(shellMiddle, rand() % 4000 + 500, 306, IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[6] = Element(shellMiddle, rand() % 4000 + 500, 306, IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[7] = Element(shellMiddle, rand() % 4000 + 500, 306, IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[8] = Element(shellMiddle, rand() % 4000 + 1000, 306, IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[9] = Element(shellMiddle, rand() % 4000 + 1000, 306, IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[10] = Element(shellMiddle, rand() % 4000 + 1000, 306,IS_NOT_MARIO, IS_MOBILE);
	elementsMiddle[11] = Element(rshellMiddle, rand() % 5000 + 500, 306, IS_NOT_MARIO, IS_MOBILE, rand() % 4 + 3);
	elementsMiddle[12] = Element(rshellMiddle, rand() % 5000 + 500, 306, IS_NOT_MARIO, IS_MOBILE, rand() % 4 + 3);
	elementsMiddle[13] = Element(rshellMiddle, rand() % 5000 + 100, 306, IS_NOT_MARIO, IS_MOBILE, rand() % 4 + 3);
	

	elementsFore[0] = Element(marios, 365, 39, IS_MARIO, IS_MOBILE);
	elementsFore[0].setVisible(true);
	elementsFore[1] = Element(coinFore, rand() % 2700 + 500, 39, IS_NOT_MARIO, IS_STATIONARY);
	elementsFore[2] = Element(coinFore, rand() % 2700 + 500, 39, IS_NOT_MARIO, IS_STATIONARY);
	elementsFore[3] = Element(coinFore, rand() % 2700 + 500, 39, IS_NOT_MARIO, IS_STATIONARY);
	elementsFore[4] = Element(shell, rand() % 5000 + 500, 39,  IS_NOT_MARIO, IS_MOBILE);
	elementsFore[5] = Element(shell, rand() % 5000 + 500, 39, IS_NOT_MARIO, IS_MOBILE);
	elementsFore[6] = Element(shell, rand() % 5000 + 500, 39, IS_NOT_MARIO, IS_MOBILE);
	elementsFore[7] = Element(shell, rand() % 5000 + 500, 39, IS_NOT_MARIO, IS_MOBILE);
	elementsFore[8] = Element(shell, rand() % 5000 + 500, 39, IS_NOT_MARIO, IS_MOBILE);
	elementsFore[9] = Element(shell, rand() % 4000 + 1000, 39, IS_NOT_MARIO, IS_MOBILE);
	elementsFore[10] = Element(shell, rand() % 4500 + 1000, 39, IS_NOT_MARIO, IS_MOBILE);
	elementsFore[11] = Element(shell, rand() % 4000 + 2000, 39,IS_NOT_MARIO, IS_MOBILE);
	elementsFore[12] = Element(rshell, rand() % 8000 + 500, 39, IS_NOT_MARIO, IS_MOBILE, rand() % 3 + 2);
	elementsFore[13] = Element(rshell, rand() % 8000 + 1000, 39, IS_NOT_MARIO, IS_MOBILE, rand() % 3 + 2);
	elementsFore[14] = Element(rshell, rand() % 8000 + 1500, 39, IS_NOT_MARIO, IS_MOBILE, rand() % 3 + 2);
	elementsFore[15] = Element(rshell, rand() % 9000 + 1000, 39, IS_NOT_MARIO, IS_MOBILE, rand() % 3 + 2);
	

	//Initialize Layers

	camadas[0] = background;
	camadas[1] = middleground;
	camadas[2] = foreground;
	lastScreen = initialScreen.getSubImage(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, gameWidth, gameHeight);
	gluOrtho2D(0, gameWidth, gameHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

}
void loadToMainScreen() {
	if (camadas[GAME_MODE].checkIfGrabsCoin()) {
		coins++;

	}
	if (camadas[GAME_MODE].checkIfMarioIsDead()) {
		lastScreen.plot(gameover.getPixels(), 74, 216, gameover.getWidth(), gameover.getHeight());
		GAMESTOPPED = true;
		GAME_STATE = GAME_NOT_STARTED;

	}
	else if (camadas[2].checkWin()) {
		GAMESTOPPED = true;
		GAME_STATE = GAME_NOT_STARTED;
		lastScreen = winScreen.getSubImage(0, 0, 800, 600);
	}
	else {
		int *sub1 = camadas[0].getCroppedImage().getPixels();
		int *sub2 = camadas[1].getCroppedImage().getPixels();
		int *sub3 = camadas[2].getCroppedImage().getPixels();
		lastScreen.plot(sub1, 0, 0, gameWidth, gameHeight);
		lastScreen.plot(sub2, 0, 0, gameWidth, gameHeight);
		lastScreen.plot(sub3, 0, 0, gameWidth, gameHeight);
		for (int i = 0; i < coins; i++) {
			lastScreen.plot(coinMiddle.getPixels(), i*coinMiddle.getWidth()+5, 590-coinMiddle.getHeight(), coinMiddle.getWidth(), coinMiddle.getHeight());
		}
		delete[] sub1;
		delete[] sub2;
		delete[] sub3;
	}
	glutPostRedisplay();

}

void Scroll() {

	int * sub1 = camadas[0].ScrollH(true);
	int * sub2 = camadas[1].ScrollH(true);
	int * sub3 = camadas[2].ScrollH(true);
	loadToMainScreen();
	delete[] sub1;
	delete[] sub2;
	delete[] sub3;

}
void timer(int value)
{
	if (GAME_STATE == GAME_STARTED) {
		if (!GAMESTOPPED) {
			Scroll();
			glutPostRedisplay();
			glutTimerFunc(timeGlut, timer, 0);
		}
	}

}
void changeGameMode(unsigned char key) {
	if (GAME_MODE == GAME_ON_BACKGROUND) {
		if (key == 's') {

			GAME_MODE = GAME_ON_MIDDLEGROUND;
			camadas[0].setMarioVisibility(false);
			camadas[1].setMarioVisibility(true);
		}

	}
	else if (GAME_MODE == GAME_ON_MIDDLEGROUND) {
		if (key == 'w') {
			GAME_MODE = GAME_ON_BACKGROUND;
			camadas[0].setMarioVisibility(true);
			camadas[1].setMarioVisibility(false);
		}
		else {
			GAME_MODE = GAME_ON_FOREGROUND;
			camadas[1].setMarioVisibility(false);
			camadas[2].setMarioVisibility(true);
		}
	}
	else { // FOREGROUND
		if (key == 'w') {
			GAME_MODE = GAME_ON_MIDDLEGROUND;
			camadas[1].setMarioVisibility(true);
			camadas[2].setMarioVisibility(false);
		}
	}
	loadToMainScreen();
}
void restart() {
	for (int i = 0; i < 3; i++) {
		camadas[i].clearMemory();
	}
	init();
}
void keyboard(unsigned char key, int x, int y) {

	if (!GAMESTOPPED) {
		if (GAME_STATE == GAME_STARTED) {
			if (key == 'w' || key == 's') {
				changeGameMode(key);
		

			}
		}
		if (key == ' ' && GAME_STATE == GAME_NOT_STARTED) {
			GAME_STATE = GAME_STARTED;
			glutTimerFunc(timeGlut, timer, 0);
		}
	}
	if (key == 'r') {
		GAME_STATE = GAME_NOT_STARTED;
		restart();
		glutPostRedisplay();
	}
}



void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char** argv) {
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(gameWidth, gameHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SuperMarioDodge");
	init();
	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
