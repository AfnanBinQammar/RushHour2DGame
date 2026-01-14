//============================================================================
// Name        : .cpp
// Author      : Dr. Sibt Ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

///9999: buildings, 9998: objects, 9997: passengers, 9991: dabba, 9996: fuelstations, 1000: maincar, 9995: othercars, 9994: destination, 9990: garage

int counter=0;
bool menuCheck=true;

class Game {
int x;
int y;

public:
Game() {

}
};

class Menu : public Game{
	int x;
	int y;

public:
	int getx() {
		return x;
	}

	int gety() {
		return y;
	}

	void setX(int X) {
		x=X;
	}

	void sety(int Y) {
		y=Y;
	}
};

Menu menu;

class Score : public Game {
	int score;

public:
	Score() {
		score=0;
	}

	int getScore() {
		return score;
	}

	void setScore() {
		score+=10;
	}

	void tCar() {
		score-=3;
	}

	void tObstacle() {
		score-=2;
	}

	void tPerson() {
		score-=5;
	}
};

class Money : public Game {
	int cash;

public:
	Money() {
		cash=0;
	}

	int get() {
		return cash;
	}

	void add() {
		cash+=10;
	}

	void decrease() {
		cash-=10;
	}
};

class Timer : public Game {
	double t=180;

public:
	Timer() {}

	int timer() {
		if (t>0)
			t-=0.01;
		return t;
	}
};

class Fuel : public Game {
	double fuelbar=100;

public:
	Fuel() {}

	int fuel() {
		if (fuelbar>0)
			fuelbar-=0.2;
		return fuelbar;
	}

	int getFuel() {
		return fuelbar;
	}

	void setFuel() {
		fuelbar=100;
	}
};


class Board : public Game{
     static const int row=25;
     static const int col=20;
     int grid[row][col];

public:      
     Board() {  

     }
     
     int getRow() {
          return row;
     }
     
     int getCol() {
          return col;
     }
     
     int getGrid(int i, int j) {
          return grid[i][j];
     }
     
     void generateGrid () {
     for (int i=0 ; i<row ; i++) {
	  for (int j=0 ; j<col ; j++) 
	       if (grid[i][j]!=1000)
	    	   grid[i][j]=(rand()%100<20)?1:0;
	  }
     }
     
    void setGrid(int i, int j, int temp) {
          grid[i][j]=temp;
     }
};

class Dropoffs ;

class Garage : public Game{
	int x;
	int y;
	Board *board;
	Dropoffs *items;
	string role;

public:
	Garage(Board *b) {
		board=b;
		x=0;
		y=0;
		int n=rand()%(1-0+1)+0;
		role=(n==0)?"pickup":"taxi";
	}

	void placeGarage () {
		board->setGrid(x,y,9990);
	}

	string getRole() {
		return role;
	}

	void setRole(string r) {
		role=r;
	}

	void switchRole (int x, int y) {
		if (board->getGrid(x,y)==1000) {
			board->setGrid(x,y,2000);
			for (int i=0 ; i<board->getRow() ; i++) {
				for (int j=0 ; j<board->getCol() ; j++) {
					if (board->getGrid(i,j)==9997)
						board->setGrid(i,j,9991);
				}
			}
		}
		else {
			board->setGrid(x,y,1000);
			for (int i=0 ; i<board->getRow() ; i++) {
				for (int j=0 ; j<board->getCol() ; j++) {
					if (board->getGrid(i,j)==9991)
						board->setGrid(i,j,9997);
				}
			}
		}
	}
};

class Dropoffs: public Game {
	int x;
	int y;
	string type;
	Board *board;
	Garage *garage;
	int count=0;

public:
	Dropoffs (Board *b, Garage *g) {
		board=b;
		garage=g;
	}

    void placeDropoffs () {
    	int n=rand()%(4-2+1)+2;
    while (count<n) {
    do {
    x=rand()%board->getRow();
    y=rand()%board->getCol();
    }
    while (board->getGrid(x,y)==1 || board->getGrid(x,y)==1000 || board->getGrid(x,y)==9996);
    if (garage->getRole()=="taxi")
    board->setGrid(x,y,9997);
    else
    	board->setGrid(x,y,9991);
    count++;
    }
    }

    void updateRole() {
        for (int i = 0; i < board->getRow(); ++i) {
            for (int j = 0; j < board->getCol(); ++j) {
                if (board->getGrid(i, j) == 9997 || board->getGrid(i, j) == 9991) {
                    if (garage->getRole() == "taxi") {
                        board->setGrid(i, j, 9997);
                    } else {
                        board->setGrid(i, j, 9991);
                    }
                }
            }
        }
    }

    int Count() {
    	return count;
    };

    void decreaseCount() {
    	count--;
    }

    void checkCount() {
    	if (count==0)
    	placeDropoffs();
    }

};

class Destination {
	int x;
	int y;
	Board *board;

public:
	Destination(Board *b) {
		board=b;
	}

	void  spawnDestination() {
		if (counter==1) {
		    x=rand()%board->getRow();
		    y=rand()%board->getCol();
		    board->setGrid(x,y,9994);
		}
	}

};

class mainCar : public Board {
	int x;
	int y;
	Board *board;
	Garage *garage;

public:
    mainCar (Board *b, Garage *g) {
    board=b;
    garage=g;
    }

    void placeCar () {
    x=0;
    y=board->getCol() -1;
    if (garage->getRole()=="taxi")
    board->setGrid(x,y,1000);
    else if (garage->getRole()=="pickup")
    board->setGrid(x,y,2000);
    }

    void moveCar () {

    }

    int X() {
    return x;
    }

    int Y() {
    return y;
    }

};

class otherCars {
    int x;
    int y;
    int num=2;
    Board *board;
    
public:
    otherCars (Board *b) {
    board=b;
    }
  
    void placeCar () {
    	int count=0;
    	while (count<num) {
    do {
    x=rand()%board->getRow();
    y=rand()%board->getCol();
    }
    while (board->getGrid(x,y)==1 || board->getGrid(x,y)==1000 || board->getGrid(x,y)==9999 || board->getGrid(x,y)==9998 || board->getGrid(x,y)==9997 || board->getGrid(x,y)==9996);
    board->setGrid(x,y,9995);
    count++;
    	}
    }
    
    void moveCar () {

    }
    
    int addCars() {
    	return num;
    }

    int X() {
    return x;
    }
    
    int Y() {
    return y;
    }

};

class Objects: public Board {
	int x;
	int y;
	string color;
	Board *board;

public:
	Objects (Board *b) {
		board=b;
	}

    void placeObject () {
    	int n=rand()%(10-4+1)+4;
    	int count=0;
    while (count<n) {
    do {
    x=rand()%board->getRow();
    y=rand()%board->getCol();
    }
    while (board->getGrid(x,y)==1 || board->getGrid(x,y)==1000 || board->getGrid(x,y)==9996);
    board->setGrid(x,y,9998);
    count++;
    }
    }

};

class fuelStation : public Board {
	int x;
	int y;
	string color;
	Board *board;

public:
	fuelStation (Board *b) {
		board=b;
	}

    void placeFuelstation () {
    	int n=rand()%(3-2+1)+2;
    	int count=0;
    while (count<n) {
    do {
    x=rand()%board->getRow();
    y=rand()%board->getCol();
    }
    while (board->getGrid(x,y)==1 || board->getGrid(x,y)==9999 || board->getGrid(x,y)==9998 || board->getGrid(x,y)==9997 || board->getGrid(x,y)==1000 || board->getGrid(x,y)==2000);
    board->setGrid(x,y,9996);
    count++;
    }
    }

};

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

Board board;
otherCars c(&board);
Objects o(&board);
Garage g(&board);
Dropoffs d(&board,&g);
fuelStation f(&board);
mainCar C(&board,&g);
Destination D(&board);
Money money;

void drawCar() {


	
	glutPostRedisplay();
}


bool flag = true;
void moveCar() {

	int row=board.getRow();
	int col=board.getCol();
	int temp[row][col];
	for (int i=0 ; i<board.getRow() ; i++) {
		for (int j=0 ; j<board.getCol() ; j++)
			temp[i][j]=board.getGrid(i,j);
	}

	for (int i=0 ; i<board.getRow() ; i++) {
		for (int j=0 ; j<board.getCol() ; j++) {
		if (temp[i][j]==9995) {
			if (board.getGrid(i+1,j)==0 && i+1<board.getRow()) {
				board.setGrid(i,j,0);
				board.setGrid(i+1,j,9995);
			}
			else if (board.getGrid(i,j+1)==0 && j+1<board.getCol()) {
				board.setGrid(i,j,0);
				board.setGrid(i,j+1,9995);
			}
			else if (board.getGrid(i-1,j)==0 && i-1>=0) {
				board.setGrid(i,j,0);
				board.setGrid(i-1,j,9995);
			}
			else if (board.getGrid(i,j-1)==0 && j-1>=0) {
				board.setGrid(i,j,0);
				board.setGrid(i,j-1,9995);
			}
		}
		}
	}
}

/*
 * Main Canvas drawing function.
 * */

Timer t;
Fuel F;
Score S;
bool game=true;


void MousePressedAndMoved(int x, int y);
void gameBoard();
void gameMenu();

void endGame() {
	glClearColor(0/*Red Component*/,0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0/*Alpha component*/); // Red==Green==Blue==1 --> White Colour

	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	DrawString( 380, 500, "G A M E   E N D E D", colors[BROWN]);
	if (S.getScore()>=100)
	DrawString( 450, 400, "You won", colors[RED]);
	else
		DrawString( 450, 400, "You lose", colors[RED]);
	DrawString( 450, 350, "Play Again", colors[RED]);
	if((menu.getx()>=450 && menu.getx()<=565) & (menu.gety()>=470 && menu.gety()<=490))  {
		gameMenu();
	}
}

void gameMenu() {
	glClearColor(0/*Red Component*/,0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0/*Alpha component*/); // Red==Green==Blue==1 --> White Colour

	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	DrawString( 380, 700, "R U S H   H O U R   G A M E", colors[BROWN]);
	DrawString( 450, 500, "Start Game", colors[RED]);
	DrawString( 450, 450, "PLay as Pickup Driver", colors[RED]);
	DrawString( 450, 400, "Play as Taxi driver", colors[RED]);
	DrawString( 450, 350, "Exit Game", colors[RED]);

	//if ((menu.getx()==450 || menu.getx()==560) && (menu.gety()==300 || menu.gety()==350)) {
	if ((menu.getx()>=450 && menu.getx()<=565) & (menu.gety()>=310 && menu.gety()<=335)) {
		gameBoard();
	}
	else if((menu.getx()>=450 && menu.getx()<=565) & (menu.gety()>=420 && menu.gety()<=445)) {
		for (int i=0 ; i<board.getRow() ; i++) {
		     for (int j=0 ; j<board.getCol() ; j++) {
		    		if (board.getGrid(i,j)==2000)
		               board.setGrid(i,j,1000);
		    		if (board.getGrid(i,j)==9991)
		    			board.setGrid(i,j,9997);
		          }
		     }
		gameBoard();
	}
	else if((menu.getx()>=450 && menu.getx()<=565) & (menu.gety()>=370 && menu.gety()<=390)) {
		for (int i=0 ; i<board.getRow() ; i++) {
		     for (int j=0 ; j<board.getCol() ; j++) {
		    		if (board.getGrid(i,j)==1000)
		               board.setGrid(i,j,2000);
		    		if (board.getGrid(i,j)==9997)
		    			board.setGrid(i,j,9991);
		          }
		     }
		gameBoard();
	}
	else if((menu.getx()>=450 && menu.getx()<=565) & (menu.gety()>=470 && menu.gety()<=490)) {
		exit(1);
	}
	if (!game) {
		endGame();
	}
//	glutSwapBuffers(); // do not modify this line..
//	glutPostRedisplay();
}

void gameBoard() {

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1.0/*Blue Component*/, 1/*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		
	for (int i=0 ; i<board.getRow() ; i++) {
	     for (int j=0 ; j<board.getCol() ; j++) {
	           if (board.getGrid(i,j)==1)
	               DrawSquare( i*40, j*40 ,40,colors[BLACK]);
	          }
	     }

int fuel=F.getFuel();

	//Display Score
	DrawString( 20, 810, "Score="+to_string(S.getScore()), colors[RED]);
	DrawString( 450, 810, "Timer="+to_string(t.timer())+"sec", colors[RED]);
	DrawString( 800, 810, "Fuel="+to_string(fuel)+"%", colors[RED]);
	DrawString( 200, 810, "Money="+to_string(money.get())+"$", colors[RED]);

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 0 , 800 ,  1100 , 800 , 4 , colors[BROWN] );
	DrawLine( 0 , 0 ,  1100 , 0 , 4 , colors[BROWN] );
	DrawLine( 0 , 0 ,  0 , 800 , 4 , colors[BROWN] );
	DrawLine( 1020 , 0 ,  1020 , 800 , 5 , colors[BROWN] );
	DrawLine( 1000 , 0 ,  1000, 800 , 10000 , colors[BLACK] );
	DrawLine( 1005 , 0 ,  1005, 800 , 10000 , colors[BLUE] );
	DrawLine( 1010 , 0 ,  1010, 800 , 10000 , colors[BLUE] );
	DrawLine( 1015 , 0 ,  1015, 800 , 10000 , colors[BLUE] );
	
	int t=40;
	for (int i=0 ; i<25 ; i++) {
		int a=0,b=10;
		for (int j=0 ; j<54 ; j++) {
			DrawLine( t , a ,  t ,  b ,2, colors[BLACK] );
			if (j!=52) {
			a+=15;
			b+=15;
			}
			else {
				a+=10;
				b+=10;
			}
		}
	     t+=40;
	}

	int cont=0;

    for (int i=0 ; i<board.getRow() ; i++) {
         for (int j=0 ; j<board.getCol() ; j++) {
        	 //buildings
 	           if (board.getGrid(i,j)==1) {
       		    DrawSquare( i*40, j*40,40,colors[BROWN]);
       		    DrawSquare( i*40+10, j*40,20,colors[BLUE]);
       		    DrawSquare( i*40+10, j*40+10,20,colors[BLUE]);
       		    DrawLine( i*40, j*40+40,  i*40+40, j*40+40, 3, colors[BLACK]);
 	           }
        	 //person
       	  if (board.getGrid(i,j)==9997) {
       		DrawLine(i*40+10, j*40+35, i*40+10, j*40+10, 2, colors[RED]);//main
       		DrawLine(i*40, j*40+20, i*40+20, j*40+20, 2, colors[RED]);//rem parts
       		DrawLine(i*40, j*40, i*40+10, j*40+10, 2, colors[RED]);//rem parts
       		DrawLine(i*40+10, j*40+10, i*40+20, j*40, 2, colors[RED]);//rem parts
       		DrawCircle(i*40+10,j*40+40,10,colors[RED]);//face
       		DrawCircle(i*40-4+10,j*40+42,2,colors[BLACK]);//eyes
       		DrawCircle(i*40+14,j*40+42,2,colors[BLACK]);//eyes
       		DrawTriangle( i*40, j*40+48 , i*40+20, j*40+48, i*40+10, j*40+70, colors[YELLOW] );//topi
       		DrawLine(i*40+5, j*40+34, i*40+15, j*40+34, 2, colors[BLACK]);//moustache
       	  }
       	  //othercars
       	    	           if (board.getGrid(i,j)==9995) {
      	            DrawSquare( i*40, j*40 ,40,colors[GREEN]);
      	            DrawSquare( i*40+5, j*40+8 ,30,colors[BLACK]);
      	            DrawCircle(i*40+4,j*40+2,4,colors[YELLOW]);
      	            DrawCircle(i*40+28,j*40+2,4,colors[YELLOW]);
   	           }
       	  //box
       	  if (board.getGrid(i,j)==9991) {
       	    DrawSquare( i*40, j*40,30,colors[YELLOW]);
       	    DrawSquare( i*40+10, j*40+10,30,colors[YELLOW]);
       	    DrawLine( i*40, j*40,  i*40+10, j*40+10, 3, colors[ORANGE]);
       	    DrawLine( i*40, j*40+30,  i*40+10, j*40+40, 3, colors[ORANGE]);
       	    DrawLine( i*40+30, j*40,  i*40+40, j*40+10, 3, colors[ORANGE]);
       	    DrawLine( i*40+30, j*40+30,  i*40+40, j*40+40, 3, colors[ORANGE]);
       	    DrawString( i*40+10, j*40, "P", colors[ORANGE]);
       	  }
       	  //tree
       	  if (board.getGrid(i,j)==9998) {
       		DrawLine( i*40+15, j*40,  i*40+15, j*40+20, 5, colors[BROWN]);
       		DrawTriangle( i*40, j*40+20, i*40+30, j*40+20, i*40+15 , j*40+35, colors[GREEN]);
       		DrawTriangle( i*40, j*40+34, i*40+30, j*40+34, i*40+15 , j*40+49, colors[GREEN]);
       		DrawTriangle( i*40, j*40+48, i*40+30, j*40+48, i*40+15 , j*40+63, colors[GREEN]);
       	  }
       	  //fuelstations
       	  if (board.getGrid(i,j)==9996) {
       	    DrawCircle(i*40+20,j*40+38,20,colors[RED]);
       	    DrawSquare( i*40, j*40,40,colors[RED]);
       	    DrawSquare( i*40+6, j*40+10,25,colors[ORANGE]);
       	    DrawLine( i*40+35, j*40+10,  i*40+35, j*40+30, 3, colors[BLACK]);
       	  }
       	  //destiantion
       	  if (board.getGrid(i,j)==9994 && counter==1) {
       		  if (cont<counter) {
       		DrawSquare( i*40, j*40 ,40,colors[LIME_GREEN]);
       		  cont++;}}
       	  //garage
       	  if (board.getGrid(i,j)==9990) {
      		DrawSquare( i*40, j*40,40,colors[GREEN]);
      		DrawTriangle( i*40, j*40+39, i*40+40, j*40+39, i*40+20, j*40+70, colors[YELLOW] );
      		DrawCircle(i*40+20,j*40+50,9,colors[GREEN]);
      		DrawSquare( i*40+10, j*40,20,colors[BROWN]);
      		DrawSquare( i*40+10, j*40+10,20,colors[BROWN]);
       	  }
       	  //taxicar
       	  if (board.getGrid(i,j)==1000) {
	            DrawSquare( i*40, j*40 ,40,colors[YELLOW]);
	            DrawSquare( i*40+5, j*40+8 ,30,colors[BLACK]);
	            DrawCircle(i*40+4,j*40+2,4,colors[GREEN]);
	            DrawCircle(i*40+28,j*40+2,4,colors[GREEN]);
       	  }
       	  //pickupcar
       	  if (board.getGrid(i,j)==2000) {
	            DrawSquare( i*40, j*40 ,40,colors[RED]);
	            DrawSquare( i*40+5, j*40+8 ,30,colors[BLACK]);
	            DrawCircle(i*40+4,j*40+2,4,colors[GREEN]);
	            DrawCircle(i*40+28,j*40+2,4,colors[GREEN]);
       	  }
       	  if (S.getScore()<=-30) {
       		  endGame();
       	  }
       	  if (t==0 || F.getFuel()==0)
       		  endGame();
         }
    }
	//glutSwapBuffers(); // do not modify this line..
	//glutPostRedisplay();

}

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/,0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0/*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

if (menuCheck) {
	gameMenu();
}
else
	gameBoard();
//	drawCar();
	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */


void NonPrintableKeys(int key, int x, int y) {

	bool move=false;
	bool fuel=1;

	for (int i=0 ; i<board.getRow() && !move ; i++) {
		for (int j=0 ; j<board.getCol() && !move ; j++) {
			if (F.getFuel()==0)
				fuel=0;
			else if (fuel) {
		 if (board.getGrid(i,j)==1000) {
			if (board.getGrid(i-1,j)==0 && key==GLUT_KEY_LEFT && i-1>=0) {
				board.setGrid(i,j,0);
				board.setGrid(i-1,j,1000);
				move=true;
				F.fuel();
			}
			else if (board.getGrid(i+1,j)==0 && key==GLUT_KEY_RIGHT && i+1<board.getRow()) {
				board.setGrid(i,j,0);
				board.setGrid(i+1,j,1000);
				move=true;
				F.fuel();
			}
			else if (board.getGrid(i,j+1)==0 && key==GLUT_KEY_UP && j+1<board.getCol()) {
				board.setGrid(i,j,0);
				board.setGrid(i,j+1,1000);
				move=true;
				F.fuel();
			}
			else if (board.getGrid(i,j-1)==0 && key==GLUT_KEY_DOWN && j-1>=0) {
				board.setGrid(i,j,0);
				board.setGrid(i,j-1,1000);
				move=true;
				F.fuel();
			}
			if (board.getGrid(i,j-1)==9994) {
				board.setGrid(i,j,0);
				board.setGrid(i,j-1,1000);
				move=true;
				counter--;
				S.setScore();
				money.add();
			}
			else if (board.getGrid(i,j+1)==9994) {
				board.setGrid(i,j,0);
				board.setGrid(i,j+1,1000);
				move=true;
				counter--;
				S.setScore();
				money.add();
			}
			else if (board.getGrid(i-1,j)==9994) {
				board.setGrid(i,j,0);
				board.setGrid(i-1,j,1000);
				move=true;
				counter--;
				S.setScore();
				money.add();
			}
			else if (board.getGrid(i+1,j)==9994) {
				board.setGrid(i,j,0);
				board.setGrid(i+1,j,1000);
				move=true;
				counter--;
				S.setScore();
				money.add();
			}
		 }

			 if (board.getGrid(i,j)==2000) {
				if (board.getGrid(i-1,j)==0 && key==GLUT_KEY_LEFT && i-1>=0) {
					board.setGrid(i,j,0);
					board.setGrid(i-1,j,2000);
					move=true;
					F.fuel();
				}
				else if (board.getGrid(i+1,j)==0 && key==GLUT_KEY_RIGHT && i+1<board.getRow()) {
					board.setGrid(i,j,0);
					board.setGrid(i+1,j,2000);
					move=true;
					F.fuel();
				}
				else if (board.getGrid(i,j+1)==0 && key==GLUT_KEY_UP && j+1<board.getCol()) {
					board.setGrid(i,j,0);
					board.setGrid(i,j+1,2000);
					move=true;
					F.fuel();
				}
				else if (board.getGrid(i,j-1)==0 && key==GLUT_KEY_DOWN && j-1>=0) {
					board.setGrid(i,j,0);
					board.setGrid(i,j-1,2000);
					move=true;
					F.fuel();
				}

				if (board.getGrid(i,j-1)==9994) {
					board.setGrid(i,j,0);
					board.setGrid(i,j-1,2000);
					move=true;
					counter--;
					S.setScore();
					money.add();
				}
				else if (board.getGrid(i,j+1)==9994) {
					board.setGrid(i,j,0);
					board.setGrid(i,j+1,2000);
					move=true;
					counter--;
					S.setScore();
					money.add();
				}
				else if (board.getGrid(i-1,j)==9994) {
					board.setGrid(i,j,0);
					board.setGrid(i-1,j,2000);
					move=true;
					counter--;
					S.setScore();
					money.add();
				}
				else if (board.getGrid(i+1,j)==9994) {
					board.setGrid(i,j,0);
					board.setGrid(i+1,j,2000);
					move=true;
					counter--;
					S.setScore();
					money.add();
				}
			}

		 if (board.getGrid(i,j)==1000 || board.getGrid(i,j)==2000) {
				if (board.getGrid(i,j-1)==9996 && key==GLUT_KEY_DOWN) {
					if (money.get()>=10) {
					F.setFuel();
					money.decrease();}
					move=true;
				}
				else if (board.getGrid(i,j+1)==9996 && key==GLUT_KEY_UP) {
					if (money.get()>=10) {
					F.setFuel();
					money.decrease();}
					move=true;
				}

				if (board.getGrid(i-1,j)==9996 && key==GLUT_KEY_LEFT) {
					if (money.get()>=10) {
					F.setFuel();
					money.decrease();}
					move=true;
				}
				else if (board.getGrid(i+1,j)==9996 && key==GLUT_KEY_RIGHT) {
					if (money.get()>=10) {
					F.setFuel();
					money.decrease();}
					move=true;
				}
				if (board.getGrid(i,j-1)==9997 && key==GLUT_KEY_DOWN) {
					S.tPerson();
				}
				else if (board.getGrid(i,j+1)==9997 && key==GLUT_KEY_UP) {
					S.tPerson();
				}
				else if (board.getGrid(i-1,j)==9997 && key==GLUT_KEY_LEFT) {
					S.tPerson();
				}
				else if (board.getGrid(i+1,j)==9997 && key==GLUT_KEY_RIGHT) {
					S.tPerson();
				}

				if (board.getGrid(i,j-1)==9998 && key==GLUT_KEY_DOWN) {
					S.tObstacle();
				}
				else if (board.getGrid(i,j+1)==9998 && key==GLUT_KEY_UP) {
					S.tObstacle();
				}
				else if (board.getGrid(i-1,j)==9998 && key==GLUT_KEY_LEFT) {
					S.tObstacle();
				}
				else if (board.getGrid(i+1,j)==9998 && key==GLUT_KEY_RIGHT) {
					S.tObstacle();
				}

				if (board.getGrid(i,j-1)==9995 && key==GLUT_KEY_DOWN) {
					S.tCar();
				}
				else if (board.getGrid(i,j+1)==9995 && key==GLUT_KEY_UP) {
					S.tCar();
				}
				else if (board.getGrid(i-1,j)==9995 && key==GLUT_KEY_LEFT) {
					S.tCar();
				}
				else if (board.getGrid(i+1,j)==9995 && key==GLUT_KEY_RIGHT) {
					S.tCar();
				}
		 }
		 }

		 if (move)
			 F.fuel();
		}
	}
}


	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/


/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}

	for (int i=0 ; i<board.getRow() ; i++) {
		for (int j=0 ; j<board.getCol() ; j++) {
			if ((board.getGrid(i,j)==1000 || board.getGrid(i,j)==2000) && key==32 && counter<1) {
				cout<<"SPace "<<endl;
			if ((board.getGrid(i,j-1)==9997 || board.getGrid(i,j-1)==9991)) {
				board.setGrid(i,j-1,0);
				counter++;
				d.decreaseCount();
				d.checkCount();
				S.setScore();
			}
			else if ((board.getGrid(i,j+1)==9997) || board.getGrid(i,j+1)==9991) {
				board.setGrid(i,j+1,0);
				counter++;
				d.decreaseCount();
				d.checkCount();
				S.setScore();
			}
			else if ((board.getGrid(i-1,j)==9997 || board.getGrid(i-1,j)==9991)) {
				board.setGrid(i-1,j,0);
				counter++;
				d.decreaseCount();
				d.checkCount();
				S.setScore();
			}
			else if ((board.getGrid(i+1,j)==9997 || board.getGrid(i+1,j)==9991)) {
				board.setGrid(i+1,j,0);
				counter++;
				d.decreaseCount();
				d.checkCount();
				S.setScore();
			}
			D.spawnDestination();
			}
			if ((key=='s'|| key=='S') && (board.getGrid(i,j)==1000 || board.getGrid(i,j)==2000)) {
				if (board.getGrid(i+1,j)==9990 || board.getGrid(i-1,j)==9990 || board.getGrid(i,j+1)==9990 || board.getGrid(i,j-1)==9990) {
					 g.switchRole(i,j);
				}
			}
		}
	}


	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	
	moveCar();
	c.moveCar();
	t.timer();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();

}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
		menu.setX(x);
		menu.sety(y);
	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;
			menu.setX(x);
			menu.sety(y);
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
        srand(time(0));
        
        board.generateGrid();
        c.placeCar();
        o.placeObject();
        d.placeDropoffs();
        f.placeFuelstation();
        C.placeCar();
        D.spawnDestination();
        g.placeGarage();
        
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project :)"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.


	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
