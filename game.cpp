//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================
//Name: M.Hammad Irfan
//Roll No : 19i-1994
//Section : M2
#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
string *Player_Names = new string[100] ;//For storing names of the players
int iteration = 0 ; //The first iteration which decides which player will play first.
int DICE_COUNT = 0 ;
int DICE_Roll_1 = 0 ;
int DICE_Roll_2 = 0 ;
int DICE_Roll_3 = 0 ;
int DICE_Roll_4 = 0 ;
int DICE_NET = 0 ;
int Turns = 1 ;//Variable for turns.
int Turn = 1 ;//Variable for deciding first turn.
int buttons = 0 ;//Variable to do movement after keys w , a , s or d are pressed 
int BUTTONS ; 
int menu = 0 ; //Variable for menu choices.
int screen = 0 ;//Variable for change in screen
int xx , yy ;
int DICE = 0 ; //Variable for dice.
//Variables for kill increment.
int Red_kill = 0 ;
int Green_kill = 0 ;
int Blue_kill = 0 ;
int Yellow_kill = 0 ;
//Variables for Kill on 52nd position. Prevent the ludo piece on 52nd position from entering the house.
int Red_kill_52 = 0 ;
int Green_kill_52 = 0 ;
int Blue_kill_52 = 0 ;
int Yellow_kill_52 = 0 ;
//Variabes for position change. 
int Red_1 = 0 ;
int Red_2 = 0 ;
int Red_3 = 0 ;
int Red_4 = 0 ;
int Blue_1 = 0 ;
int Blue_2 = 0 ;
int Blue_3 = 0 ;
int Blue_4 = 0 ;
int Yellow_1 = 0 ;
int Yellow_2 = 0 ;
int Yellow_3 = 0 ;
int Yellow_4 = 0 ;
int Green_1 = 0 ;
int Green_2 = 0 ;
int Green_3 = 0 ;
int Green_4 = 0 ;
//Variables for Scores.
int Red_Score = 0 ;
int Blue_Score = 0 ;
int Yellow_Score = 0 ;
int Green_Score = 0 ;
//For file handling. Stops the record from being updated after being updated once.
int Red = 0 ;
int Blue = 0 ;
int Yellow = 0 ;
int Green = 0 ;
//For winning
int Red_Win = 0 ;
int Green_Win = 0 ;
int Blue_Win = 0 ;
int Yellow_Win = 0 ;
int Win = 0 ;
int FINISH = 0 ; //Variable for finishing the game.
int k = 0 ;
//Strings for storing names in array
string str = "" ;
string str_1 ;
//Function for storing array for names
string name(string array [100] , int k)
{
	cout << "Player Names 0 = " << array[0] << endl ;
	cout << "Player Names 1 = " << array[1] << endl ;
	cout << "Player Names 2 = " << array[2] << endl ;
	cout << "Player Names 3 = " << array[3] << endl ;
	return array [k] ;
}
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity() ;
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity() ;
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	if (menu == 0)
	{
		if (screen == 0)
		{
			DrawString(425 , 550 , "***** MENU *****" , colors [MISTY_ROSE]) ;
			DrawString(425 , 500 , "1.   New Game" , colors [MISTY_ROSE]) ;
			DrawString(425 , 400 , "2.   Help" , colors [MISTY_ROSE]) ;
			DrawString(425 , 300 , "3.   High Scores" , colors [MISTY_ROSE]) ;
			DrawString(400 , 200 , "Esc.   Exit" , colors [MISTY_ROSE]) ;
		}

		else
		{
			DrawString(425 , 550 , "***** MENU *****" , colors [MISTY_ROSE]) ;
			DrawString(425 , 500 , "1.   Resume Game" , colors [MISTY_ROSE]) ;
			DrawString(425 , 400 , "2.   Help" , colors [MISTY_ROSE]) ;
			DrawString(425 , 300 , "3.   High Scores" , colors [MISTY_ROSE]) ;
			DrawString(400 , 200 , "Esc.   Exit" , colors [MISTY_ROSE]) ;
		}
	}

	if (menu == 2)
	{
		DrawString(400, 650 , "************HELP************" , colors [RED]) ;
		DrawString(100 , 550 , "There are a maximum of 4 players. Each player roll a dice first." , colors [MISTY_ROSE]) ;
		DrawString(100 , 500 , "The player with the highest dice will play first." , colors [MISTY_ROSE]) ;
		DrawString(100 , 450 , "If a player throws a six he will keep on throwing the dice." , colors [MISTY_ROSE]) ;
		DrawString(100 , 400 , "A player loses his turn on three consecutive turns." , colors [MISTY_ROSE]) ;
		DrawString(100 , 350 , "Also a player can move a ludo piece onto the board on throwing a six." , colors [MISTY_ROSE]) ;
		DrawString(100 , 300 , "A player can not move into the house if he has not killed any of the ." , colors [MISTY_ROSE]) ;
		DrawString(100 , 250 , "opponents pieces and he will keep on circulating the board on his turn." , colors [MISTY_ROSE]) ;
		DrawString(100 , 200 , "until he has killed another players piece. A player wins after all his." , colors [MISTY_ROSE]) ;
		DrawString(100 , 150 , "pieces enter the house. Also a player cannot kill another players piece" , colors [MISTY_ROSE]) ;
		DrawString(100 , 100 , "on safe points. A player cannot pass or land on pieces who have formed " , colors [MISTY_ROSE]) ;
		DrawString(100 , 50 , "a block safe points." , colors [MISTY_ROSE]) ;
	}

	if (menu == 3)
	{
		DrawString(350 , 750 , "******HIGHSCORES******" , colors [RED] ) ;
		DrawString(275 , 650 , "Name" , colors [GREEN] ) ;
		DrawString(700 , 650 , "Score" , colors [GREEN] ) ;
		DrawString(225 , 600 , "1." , colors [GREEN] ) ;
		DrawString(225 , 550 , "2." , colors [GREEN] ) ;
		DrawString(225 , 500 , "3." , colors [GREEN] ) ;
		DrawString(225 , 450 , "4." , colors [GREEN] ) ;
		DrawString(225 , 400 , "5." , colors [GREEN] ) ;
		DrawString(225 , 350 , "6." , colors [GREEN] ) ;
		DrawString(225 , 300 , "7." , colors [GREEN] ) ;
		DrawString(225 , 250 , "8." , colors [GREEN] ) ;
		DrawString(225 , 200 , "9." , colors [GREEN] ) ;
		DrawString(213 , 150 , "10." , colors [GREEN] ) ;
		
		fstream input_file ;

		string Name [100] ;
		int score [10] ;
		int l = 600 ;
		int i = 0 ;

		input_file.open ("Highscores.txt" , ios :: in) ;

		while (!input_file.eof() and (! input_file.fail()))
		{
			input_file >> Name [i] ;
			input_file >> score [i] ;

			if (i < 10)
			DrawString (700 , l , to_string (score [i]) , colors [OLIVE]) ;

			DrawString (275 , l , Name [i] , colors [OLIVE]) ;

			l -= 50 ;
			cout << "i = " << i << endl ;
			i++ ;
		}
		 
		input_file.close () ;
	}

	if (menu == 1) 
	{

	if (screen == 1)
	{
		DrawString(100 , 700 , "Choose the no of players in the game : " , colors[MISTY_ROSE]) ;

		DrawString(100 , 600 , "Press 5 for 4 players." , colors[MISTY_ROSE]) ;

		DrawString(100 , 550 , "Press 6 for 3 players." , colors[MISTY_ROSE]) ;

		DrawString(100 , 500 , "Press 7 for 2 players." , colors[MISTY_ROSE]) ;

		if (BUTTONS == 53 or BUTTONS == 54 or BUTTONS == 55)
		screen++ ;
	}

	if (screen == 2)
	{	//Entering names for game of 4 players.
		if (BUTTONS == 53)
		{
			if (k <= 3)
			{
				DrawString(100 , 700 , "Enter the name of player " + to_string (k + 1)
				+ " : " + str , colors[MISTY_ROSE]) ;
			}

			if (k == 4)
			screen++ ;
		}

		//Entering names for game of 3 players
		else if (BUTTONS == 54)
			{
				if (k <= 2)
				{
					DrawString(100 , 700 , "Enter the name of player " + to_string (k + 1)
					+ " : " + str , colors[MISTY_ROSE]) ;
				}

				if (k == 3)
				screen++ ;
			}

		//Entering names for game of 2 players
		else if (BUTTONS == 55)
			{
				if (k <= 1)
				{
					DrawString(100 , 700 , "Enter the name of player " + to_string (k + 1)
					+ " : " + str , colors[MISTY_ROSE]) ;
				}

				if (k == 2)
				screen++ ;
			}

	}

	//Game of 4 players
	if (BUTTONS == 53)
	{
	if (screen == 3)
	{
	glClearColor(0/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour

	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//DrawString(425 , 750 , cin.getline (str) , colors [MISTY_ROSE]) ;
	int x , y ;

	//Arrays for storing positions of ludo pieces 
	int Array_Red[4][59][2] ;
	int Array_Blue[4][59][2] ;
	int Array_Yellow[4][59][2] ;
	int Array_Green[4][59][2] ;

        //Main Board
	DrawSquare( 300 , 200 , 400 , colors[GRAY]);

        //Player Houses Squares
        DrawSquare( 300 , 438 , 162 , colors[BLUE]);
        DrawSquare( 538 , 438 , 162 , colors[OLIVE]);
        DrawSquare( 300 , 200 , 162 , colors[RED]);
        DrawSquare( 538 , 200 , 162 , colors[GREEN]);

        //Blue House Squares
        DrawSquare( 320 , 458 , 122 , colors[WHITE]);
        DrawSquare( 337 , 475 , 35 , colors[BLUE]);
        DrawSquare( 390 , 475 , 35 , colors[BLUE]);
        DrawSquare( 337 , 528 , 35 , colors[BLUE]);
        DrawSquare( 390 , 528 , 35 , colors[BLUE]);

        //Yellow House Squares
        DrawSquare( 558 , 458 , 122 , colors[WHITE]);
        DrawSquare( 577 , 475 , 35 , colors[OLIVE]);
        DrawSquare( 627 , 475 , 35 , colors[OLIVE]);
        DrawSquare( 577 , 528 , 35 , colors[OLIVE]);
        DrawSquare( 627 , 528 , 35 , colors[OLIVE]);

        //RED House Squares
        DrawSquare( 320 , 220 , 122 , colors[WHITE]);
        DrawSquare( 337 , 290 , 35 , colors[RED]);
        DrawSquare( 390 , 290 , 35 , colors[RED]);
        DrawSquare( 337 , 238 , 35 , colors[RED]);
        DrawSquare( 390 , 238 , 35 , colors[RED]);

        //Green House Squares
        DrawSquare( 558 , 220 , 122 , colors[WHITE]);
        DrawSquare( 577 , 290 , 35 , colors[GREEN]);
        DrawSquare( 627 , 290 , 35 , colors[GREEN]);
        DrawSquare( 577 , 238 , 35 , colors[GREEN]);
        DrawSquare( 627 , 238 , 35 , colors[GREEN]);

	//Mid houses Square.
        DrawSquare( 461 , 362 , 78 , colors[VIOLET]);
	DrawTriangle( 461 , 362 , 500 , 401 , 539 , 362 , colors[RED]);
	DrawTriangle( 461 , 439 , 500 , 401 , 539 , 439 , colors[OLIVE]);
	DrawTriangle( 461 , 362 , 500 , 401 , 461 , 439 , colors[BLUE]);
	DrawTriangle( 539 , 362 , 500 , 401 , 539 , 439 , colors[GREEN]);
	DrawLine( 461 , 362 , 539 , 439 , 0 , colors[BLACK]);//Diagonal boundary line
	DrawLine( 539 , 362 , 461 , 439 , 0 , colors[BLACK]);//Diagonal boundary line

	//Squares between red and green houses

	DrawSquare( 461 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 228 , 27 , colors[RED]) ;
	DrawSquare( 461 , 254 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 282 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 309 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 335 , 27 , colors[WHITE]) ;

	DrawSquare( 487 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 487 , 228 , 27 , colors[RED]) ;
	DrawSquare( 487 , 254 , 27 , colors[RED]) ;
	DrawSquare( 487 , 282 , 27 , colors[RED]) ;
	DrawSquare( 487 , 309 , 27 , colors[RED]) ;
	DrawSquare( 487 , 335 , 27 , colors[RED]) ;

	DrawSquare( 513 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 228 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 254 , 27 , colors[GRAY]) ;
	DrawSquare( 513 , 282 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 309 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 335 , 27 , colors[WHITE]) ;
	//Horizontal lines between red and green houses
        DrawLine( 461 , 227 ,  538, 227 , 0 , colors[BLACK] );
        DrawLine( 461 , 254 ,  538, 254 , 0 , colors[BLACK] );
	DrawLine( 461 , 281 ,  538, 281 , 0 , colors[BLACK] );
	DrawLine( 461 , 308 ,  538, 308 , 0 , colors[BLACK] );
	DrawLine( 461 , 335 ,  538, 335 , 0 , colors[BLACK] );
	DrawLine( 461 , 361 ,  538, 361 , 0 , colors[BLACK] );
	//Vertical lines between red and green houses
	DrawLine( 461 , 200 ,  461, 362 , 0 , colors[BLACK] );
	DrawLine( 487 , 200 ,  487, 362 , 0 , colors[BLACK] );
	DrawLine( 513 , 200 ,  513, 362 , 0 , colors[BLACK] );
	DrawLine( 539 , 200 ,  539, 362 , 0 , colors[BLACK] );

	//Squares between yellow and blue houses

	DrawSquare( 460 , 439 , 28 , colors[WHITE]) ;
	DrawSquare( 461 , 468 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 494 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 522 , 27 , colors[GRAY]) ;
	DrawSquare( 461 , 548 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 574 , 27 , colors[WHITE]) ;

	DrawSquare( 486 , 439 , 28 , colors[OLIVE]) ;
	DrawSquare( 487 , 468 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 494 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 522 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 548 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 574 , 27 , colors[WHITE]) ;

	DrawSquare( 512 , 439 , 28 , colors[WHITE]) ;
	DrawSquare( 513 , 468 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 494 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 522 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 548 , 27 , colors[OLIVE]) ;
	DrawSquare( 513 , 574 , 27 , colors[WHITE]) ;
	//Horizontal lines between yellow and blue houses
	DrawLine( 461 , 439 ,  538, 439 , 0 , colors[BLACK] );
	DrawLine( 461 , 467 ,  538, 467 , 0 , colors[BLACK] );
	DrawLine( 461 , 494 ,  538, 494 , 0 , colors[BLACK] );
	DrawLine( 461 , 521 ,  538, 521 , 0 , colors[BLACK] );
	DrawLine( 461 , 548 ,  538, 548 , 0 , colors[BLACK] );
	DrawLine( 461 , 575 ,  538, 575 , 0 , colors[BLACK] );
	//Vertical lines between yellow and blue houses
	DrawLine( 461 , 438 ,  461, 600 , 0 , colors[BLACK] );
	DrawLine( 487 , 438 ,  487, 600 , 0 , colors[BLACK] );
	DrawLine( 513 , 438 ,  513, 600 , 0 , colors[BLACK] );
	DrawLine( 539 , 438 ,  539, 600 , 0 , colors[BLACK] );

	//Squares between red and blue houses

	DrawSquare( 301 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 355 , 362 , 27 , colors[GRAY]) ;
	DrawSquare( 382 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 409 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 435 , 362 , 27 , colors[WHITE]) ;

	DrawSquare( 301 , 388 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 355 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 382 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 409 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 435 , 388 , 27 , colors[BLUE]) ;

	DrawSquare( 301 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 413 , 27 , colors[BLUE]) ;
	DrawSquare( 355 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 382 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 409 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 435 , 413 , 27 , colors[WHITE]) ;
	//Vertical lines between red and blue houses
        DrawLine( 328 , 361 ,  328, 438 , 0 , colors[BLACK] );
        DrawLine( 355 , 361 ,  355, 438 , 0 , colors[BLACK] );
	DrawLine( 382 , 361 ,  382, 438 , 0 , colors[BLACK] );
	DrawLine( 409 , 361 ,  409, 438 , 0 , colors[BLACK] );
	DrawLine( 436 , 361 ,  436, 438 , 0 , colors[BLACK] );
	DrawLine( 461 , 361 ,  461, 438 , 0 , colors[BLACK] );
	//Horizontal lines between red and blue houses
	DrawLine( 300 , 361 ,  461, 361 , 0 , colors[BLACK] );
	DrawLine( 300 , 387 ,  461, 387 , 0 , colors[BLACK] );
	DrawLine( 300 , 413 ,  461, 413 , 0 , colors[BLACK] );
	DrawLine( 300 , 439 ,  461, 439 , 0 , colors[BLACK] );
	
	//Squares between yellow and green houses

	DrawSquare( 539 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 566 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 593 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 620 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 647 , 362 , 27 , colors[GREEN]) ;
	DrawSquare( 674 , 362 , 27 , colors[WHITE]) ;

	DrawSquare( 539 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 566 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 593 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 620 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 647 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 674 , 388 , 27 , colors[WHITE]) ;

	DrawSquare( 539 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 566 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 593 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 620 , 413 , 27 , colors[GRAY]) ;
	DrawSquare( 647 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 674 , 413 , 27 , colors[WHITE]) ;


	//Vertical lines between yellow and green houses
        DrawLine( 539 , 361 ,  539, 438 , 0 , colors[BLACK] );
        DrawLine( 566 , 361 ,  566, 438 , 0 , colors[BLACK] );
	DrawLine( 593 , 361 ,  593, 438 , 0 , colors[BLACK] );
	DrawLine( 620 , 361 ,  620, 438 , 0 , colors[BLACK] );
	DrawLine( 647 , 361 ,  647, 438 , 0 , colors[BLACK] );
	DrawLine( 674 , 361 ,  674, 438 , 0 , colors[BLACK] );
	//Horizontal lines between yellow and green houses
	DrawLine( 539 , 361 ,  700, 361 , 0 , colors[BLACK] );
	DrawLine( 539 , 387 ,  700, 387 , 0 , colors[BLACK] );
	DrawLine( 539 , 413 ,  700, 413 , 0 , colors[BLACK] );
	DrawLine( 539 , 439 ,  700, 439 , 0 , colors[BLACK] );


	//Borderlines
	DrawLine( 300 , 200 ,  700, 200 , 0 , colors[BLACK] );
	DrawLine( 300 , 200 ,  300, 600 , 0 , colors[BLACK] );
	DrawLine( 300 , 600 ,  700, 600 , 0 , colors[BLACK] );
	DrawLine( 700 , 200 ,  700, 600 , 0 , colors[BLACK] );
	//DrawSquare( 250 , 250 ,20,colors[WHITE]); 
	//Display Score
	//Spider
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	
	//Storing positions for red house.

        for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j <= 5)
						Array_Red[i][j][k] = 473 ;
					
					else if (j <= 11)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 13)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k];

					else if (j <= 18)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 24)
					{
						if (j == 19)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
						
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

					else if (j <= 26)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 31)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 37)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 39)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 44)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 50)
					{
						if (j == 45)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;
	
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}
					else if (j <= 52)
					Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 58)
					{
						if (j == 53)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

				}

				else if (k == 1)
				{
					if (j <= 5)
					{
						if (j == 1)
						Array_Red[i][j][k] = 228 + 17 ;
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
					}

					else if (j <= 11)
					{
						if (j == 6)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

					else if (j <= 13)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 18)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 24)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 26)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					
					else if (j <= 31)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 37)
						{
							if (j == 32)
							Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

							else
							Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
						}

					else if (j <= 39)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 44)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 50)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 52)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 58)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
				}
			}
		}
	}
        
	//Storing Positions for blue house

	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j == 1)
					Array_Blue[i][j][k] = Array_Red [i][14][k] ;

					else if (j <= 6)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;	
										
					else if (j <= 11)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 13)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 18)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 24)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 26)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 32)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 37)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 39)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 44)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 50)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 52)
					Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 58)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;
				}

				else if (k == 1)
				{
					if (j <= 5)
					Array_Blue[i][j][k] = Array_Blue[i][j][k] = Array_Red [i][14][k] ;
				
					else if (j <= 11)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 13)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 19)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 24)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 26)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 31)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 37)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 39)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 45)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 50)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 52)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j == 53)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 58)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;
				}
			}
		}
	}

	//Storing positions for yellow house
	
	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j <= 5)
					Array_Yellow[i][j][k] = Array_Red [i][27][k] ; 

					else if (j <= 11)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;	
										
					else if (j <= 13)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 19)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 24)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 26)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 31)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 37)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 39)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 45)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 50)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 52)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j == 53)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 58)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;
				}

				else if (k == 1)
				{
					if (j == 1)
					Array_Yellow[i][j][k] = Array_Red [i][27][k] ;
 
					else if (j <= 6)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;
				
					else if (j <= 11)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 13)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 18)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 24)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 26)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 32)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 37)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 39)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 44)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 50)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 52)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;
	
					else if (j <= 58)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;
				}
			}
		}
	}

	//Storing positions for Green

	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j == 1)
					Array_Green[i][j][k] = Array_Red [i][40][k] ;
 
					else if (j <= 6)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;	
										
					else if (j <= 11)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 13)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;

					else if (j <= 18)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 24)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;

					else if (j <= 26)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 32)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 37)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 39)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 44)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 50)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 52)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 58)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;
				}

				else if (k == 1)
				{
					if (j <= 5)
					Array_Green[i][j][k] = Array_Red [i][40][k] ;
				
					else if (j <= 11)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;

					else if (j <= 13)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 19)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 24)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 26)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 31)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 37)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 39)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 45)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;

					else if (j <= 50)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;

					else if (j <= 52)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] - 26 ;

					else if (j == 53)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] + 26 ;

					else if (j <= 58)
						Array_Green[i][j][k] = Array_Green[i][j - 1][k] ;
				}
			}
		}
	}	

	if (DICE_NET == 18)
	{
		DICE_NET = 0 ;
		DICE_COUNT == 0 ;
	}
	//Pieces of blue house
	Array_Blue[0][0][0] = 337 + 17 ;
	Array_Blue[0][0][1] = 475 + 17 ;
	Array_Blue[1][0][0] = 390 + 17 ;
	Array_Blue[1][0][1] = 475 + 17 ;
	Array_Blue[2][0][0] = 337 + 17 ;
	Array_Blue[2][0][1] = 528 + 17 ;
	Array_Blue[3][0][0] = 390 + 17 ;
	Array_Blue[3][0][1] = 528 + 17 ;

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Blue_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_1 != 0 and Blue_1 <= 58)//
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Blue = Blue_1 ;

				Blue_1 = Blue_1 + DICE ;

				if (Blue_1 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_1 > 52)
				{
					Blue_1 = Blue_1 - 52 ;
				}

				else if (Blue_1 > 58 and Blue_kill > 0 and Blue_1 != 52)
				{
					Blue_1 = Blue_1 - DICE ;
				}

				else if (Blue_1 <= 58 and Blue_kill > 0)
				{
					Blue_1 = Blue_1 - DICE ;
					for (int i = Blue_1 ; i <= Blue_1 + DICE ; i++)
					{
						if (i == 52)
						Blue_1++ ;

						if (i == 58 and Blue_1 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_1 = Blue_1 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[0][Blue_1][0] == Array_Red[0][Red_1][0] and Array_Blue[0][Blue_1][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[0][Blue_1][0] == Array_Red[1][Red_2][0] and Array_Blue[0][Blue_1][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Red[2][Red_3][0] and Array_Blue[0][Blue_1][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Red[3][Red_4][0] and Array_Blue[0][Blue_1][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_1 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[0][Green_1][0] and Array_Blue[0][Blue_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_1 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[1][Green_2][0] and Array_Blue[0][Blue_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[2][Green_3][0] and Array_Blue[0][Blue_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[3][Green_4][0] and Array_Blue[0][Blue_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_1 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_1 != 52)
				{
					Blue_1 = Blue_1 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[0][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[0][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[0][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[0][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[0][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[0][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[0][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[0][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_2 or (O_Blue + DICE) == Blue_3 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Blue_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_2 != 0 and Blue_2 <= 58)//
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Blue = Blue_2 ;

				Blue_2 = Blue_2 + DICE ;

				if (Blue_2 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_2 > 52)
				{
					Blue_2 = Blue_2 - 52 ;
				}

				else if (Blue_2 > 58 and Blue_kill > 0 and Blue_2 != 52)
				{
					Blue_2 = Blue_2 - DICE ;
				}

				else if (Blue_2 <= 58 and Blue_kill > 0)
				{
					Blue_2 = Blue_2 - DICE ;
					for (int i = Blue_2 ; i <= Blue_2 + DICE ; i++)
					{
						if (i == 52)
						Blue_2++ ;

						if (i == 58 and Blue_2 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_2 = Blue_2 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[1][Blue_2][0] == Array_Red[0][Red_1][0] and Array_Blue[1][Blue_2][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[1][Blue_2][0] == Array_Red[1][Red_2][0] and Array_Blue[1][Blue_2][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Red[2][Red_3][0] and Array_Blue[1][Blue_2][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Red[3][Red_4][0] and Array_Blue[1][Blue_2][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[0][Green_1][0] and Array_Blue[1][Blue_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[1][Green_2][0] and Array_Blue[1][Blue_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[2][Green_3][0] and Array_Blue[1][Blue_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[3][Green_4][0] and Array_Blue[1][Blue_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_2 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_2 != 52)
				{
					Blue_2 = Blue_2 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				       	if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[1][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[1][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[1][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[1][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[1][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[1][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[1][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[1][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[1][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_1 or (O_Blue + DICE) == Blue_3 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Blue_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_3 != 0 and Blue_3 <= 58)//
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Blue = Blue_3 ;

				Blue_3 = Blue_3 + DICE ;

				if (Blue_3 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_3 > 52)
				{
					Blue_3 = Blue_3 - 52 ;
				}

				else if (Blue_3 > 58 and Blue_kill > 0 and Blue_3 != 52)
				{
					Blue_3 = Blue_3 - DICE ;
				}

				else if (Blue_3 <= 58 and Blue_kill > 0)
				{
					Blue_3 = Blue_3 - DICE ;
					for (int i = Blue_3 ; i <= Blue_3 + DICE ; i++)
					{
						if (i == 52)
						Blue_3++ ;

						if (i == 58 and Blue_3 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_3 = Blue_3 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[2][Blue_3][0] == Array_Red[0][Red_1][0] and Array_Blue[2][Blue_3][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[2][Blue_3][0] == Array_Red[1][Red_2][0] and Array_Blue[2][Blue_3][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Red[2][Red_3][0] and Array_Blue[2][Blue_3][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Red[3][Red_4][0] and Array_Blue[2][Blue_3][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[0][Green_1][0] and Array_Blue[2][Blue_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[1][Green_2][0] and Array_Blue[2][Blue_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[2][Green_3][0] and Array_Blue[2][Blue_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[3][Green_4][0] and Array_Blue[2][Blue_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_3 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_3 != 52)
				{
					Blue_3 = Blue_3 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				       	if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[2][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[2][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[2][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[2][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[2][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[2][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[2][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[2][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[2][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_2 or (O_Blue + DICE) == Blue_1 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Blue_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_4 != 0 and Blue_4 <= 58)//
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Blue = Blue_4 ;

				Blue_4 = Blue_4 + DICE ;

				if (Blue_4 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_4 > 52)
				{
					Blue_4 = Blue_4 - 52 ;
				}

				else if (Blue_4 > 58 and Blue_kill > 0 and Blue_4 != 52)
				{
					Blue_4 = Blue_4 - DICE ;
				}

				else if (Blue_4 <= 58 and Blue_kill > 0)
				{
					Blue_4 = Blue_4 - DICE ;
					for (int i = Blue_4 ; i <= Blue_4 + DICE ; i++)
					{
						if (i == 52)
						Blue_4++ ;

						if (i == 58 and Blue_4 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_4 = Blue_4 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[3][Blue_4][0] == Array_Red[0][Red_1][0] and Array_Blue[3][Blue_4][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[3][Blue_4][0] == Array_Red[1][Red_2][0] and Array_Blue[3][Blue_4][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Red[2][Red_3][0] and Array_Blue[3][Blue_4][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Red[3][Red_4][0] and Array_Blue[3][Blue_4][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[0][Green_1][0] and Array_Blue[3][Blue_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[1][Green_2][0] and Array_Blue[3][Blue_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[2][Green_3][0] and Array_Blue[3][Blue_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[3][Green_4][0] and Array_Blue[3][Blue_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_4 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_4 != 52)
				{
					Blue_4 = Blue_4 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				       	if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[3][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[3][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[3][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[3][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[3][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[3][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[3][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[3][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[3][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_1 or (O_Blue + DICE) == Blue_3 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}
	DrawCircle( Array_Blue[0][Blue_1][0] , Array_Blue[0][Blue_1][1] , 10 , colors[LIGHT_BLUE]);
	DrawCircle( Array_Blue[1][Blue_2][0] , Array_Blue[1][Blue_2][1] , 10 , colors[LIGHT_BLUE]);
	DrawCircle( Array_Blue[2][Blue_3][0] , Array_Blue[2][Blue_3][1] , 10 , colors[LIGHT_BLUE]);
	DrawCircle( Array_Blue[3][Blue_4][0] , Array_Blue[3][Blue_4][1] , 10 , colors[LIGHT_BLUE]);

	DrawString( Array_Blue[0][Blue_1][0] - 9 , Array_Blue[0][Blue_1][1] - 9 , "w" , colors[MIDNIGHT_BLUE]);
	DrawString( Array_Blue[1][Blue_2][0] - 6 , Array_Blue[1][Blue_2][1] - 7 , "a" , colors[MIDNIGHT_BLUE]);
	DrawString( Array_Blue[2][Blue_3][0] - 5 , Array_Blue[2][Blue_3][1] - 7 , "s" , colors[MIDNIGHT_BLUE]);
	DrawString( Array_Blue[3][Blue_4][0] - 8 , Array_Blue[3][Blue_4][1] - 10 , "d" , colors[MIDNIGHT_BLUE]);


	//Pieces of red House.
	Array_Red[0][0][0] = 337 + 17 ;
	Array_Red[0][0][1] = 290 + 17 ;
	Array_Red[1][0][0] = 390 + 17 ;
	Array_Red[1][0][1] = 290 + 17 ;
	Array_Red[2][0][0] = 337 + 17 ;
	Array_Red[2][0][1] = 238 + 17 ;
	Array_Red[3][0][0] = 390 + 17 ;
	Array_Red[3][0][1] = 238 + 17 ;

	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Red_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_1 != 0 and Red_1 <= 58)//For a roll less than 6
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Red = Red_1 ;

				Red_1 = Red_1 + DICE ;
		
				if (Red_1 <= 58)
				{
					Red_Score += DICE ;
				}
				
				//boundary checks for ludo pieces.			
				if (Red_kill == 0 and Red_1 > 52)
				{
					Red_1 = Red_1 - 52 ;
				}

				else if (Red_1 > 58 and Red_kill > 0)
				{	
					Red_1 = Red_1 - DICE ;
				}

				else if (Red_1 <= 58 and Red_kill > 0)
				{
					Red_1 = Red_1 - DICE ;
					for (int i = Red_1 ; i <= Red_1 + DICE ; i++)
					{
						if (i == 52)
						Red_1++ ;

						if (i == 58 and Red_1 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_1 = Red_1 + DICE ;
				}
				
				//Killing conditions
				if ((Array_Red[0][Red_1][0] == Array_Blue[0][Blue_1][0] and Array_Red[0][Red_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[1][Blue_2][0] and Array_Red[0][Red_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[2][Blue_3][0] and Array_Red[0][Red_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[3][Blue_4][0] and Array_Red[0][Red_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[0][Red_1][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[0][Red_1][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[0][Red_1][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[0][Red_1][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[0][Green_1][0] and Array_Red[0][Red_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Green[1][Green_2][0] and Array_Red[0][Red_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[2][Green_3][0] and Array_Red[0][Red_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[3][Green_4][0] and Array_Red[0][Red_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_1 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_1 != 52)
				{
					Red_1 = Red_1 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}


				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}


				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[0][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[0][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[0][i][1] == Array_Green[0][Green_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[0][i][1] == Array_Green[1][Green_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red <= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[0][i][1] == Array_Green[2][Green_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_3 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}


	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Red_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_2 != 0 and Red_2 <= 58)//For a roll less than 6
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Red = Red_2 ;

				Red_2 = Red_2 + DICE ;
		
				if (Red_2 <= 58)
				{
					Red_Score += DICE ;
				}
				
				//Array boundary check			
				if (Red_kill == 0 and Red_2 > 52)
				{
					Red_2 = Red_2 - 52 ;
				}

				else if (Red_2 > 58 and Red_kill > 0)
				{	
					Red_2 = Red_2 - DICE ;
				}

				else if (Red_2 <= 58 and Red_kill > 0)
				{
					Red_2 = Red_2 - DICE ;
					for (int i = Red_2 ; i <= Red_2 + DICE ; i++)
					{
						if (i == 52)
						Red_2++ ;

						if (i == 58 and Red_2 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_2 = Red_2 + DICE ;
				}

				if ((Array_Red[1][Red_2][0] == Array_Blue[0][Blue_1][0] and Array_Red[1][Red_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[1][Blue_2][0] and Array_Red[1][Red_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[2][Blue_3][0] and Array_Red[1][Red_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[3][Blue_4][0] and Array_Red[1][Red_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[1][Red_2][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[1][Red_2][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[1][Red_2][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[1][Red_2][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[0][Green_1][0] and Array_Red[1][Red_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Green[1][Green_2][0] and Array_Red[1][Red_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[2][Green_3][0] and Array_Red[1][Red_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[3][Green_4][0] and Array_Red[1][Red_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_2 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_2 != 52)
				{
					Red_2 = Red_2 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}


				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}


				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[1][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[1][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[1][i][1] == Array_Green[0][Green_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[1][i][1] == Array_Green[1][Green_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[1][i][1] == Array_Green[2][Green_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_3 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}

	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Red_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_3 != 0 and Red_3 <= 58)//For a roll less than 6
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Red = Red_3 ;

				Red_3 = Red_3 + DICE ;

				if (Red_3 <= 58)
				{
					Red_Score = Red_Score + DICE ;
				}

				//Array boundary check			
				if (Red_kill == 0 and Red_3 > 52)
				{
					Red_3 = Red_3 - 52 ;
				}

				else if (Red_3 > 58 and Red_kill > 0)
				{
					
					Red_3 = Red_3 - DICE ;
				}

				else if (Red_3 <= 58 and Red_kill > 0)
				{
					Red_3 = Red_3 - DICE ;
					for (int i = Red_3 ; i <= Red_3 + DICE ; i++)
					{
						if (i == 52)
						Red_3++ ;

						if (i == 58 and Red_3 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_3 = Red_3 + DICE ;
				}

				if ((Array_Red[2][Red_3][0] == Array_Blue[0][Blue_1][0] and Array_Red[2][Red_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[1][Blue_2][0] and Array_Red[2][Red_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[2][Blue_3][0] and Array_Red[2][Red_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[3][Blue_4][0] and Array_Red[2][Red_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[2][Red_3][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[2][Red_3][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[2][Red_3][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[2][Red_3][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[0][Green_1][0] and Array_Red[2][Red_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Green[1][Green_2][0] and Array_Red[2][Red_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[2][Green_3][0] and Array_Red[2][Red_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[3][Green_4][0] and Array_Red[2][Red_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_3 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_3 != 52)
				{
					Red_3 = Red_3 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[2][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[2][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[2][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[2][i][1] == Array_Green[0][Green_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[2][i][1] == Array_Green[1][Green_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[2][i][1] == Array_Green[2][Green_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}
	
	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Red_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_4 != 0 and Red_4 <= 58)//For a roll less than 6
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Red = Red_4 ;

				Red_4 = Red_4 + DICE ;

				if (Red_4 <= 58)
				{
					Red_Score = Red_Score + DICE ;
				}

				//Array boundary check			
				if (Red_kill == 0 and Red_4 > 52)
				{
					Red_4 = Red_4 - 52 ;
				}

				else if (Red_4 > 58 and Red_kill > 0)
				{
					
					Red_4 = Red_4 - DICE ;
				}

				else if (Red_4 <= 58 and Red_kill > 0)
				{
					Red_4 = Red_4 - DICE ;
					for (int i = Red_4 ; i <= Red_4 + DICE ; i++)
					{
						if (i == 52)
						Red_4++ ;

						if (i == 58 and Red_4 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_4 = Red_4 + DICE ;
				}

				if ((Array_Red[3][Red_4][0] == Array_Blue[0][Blue_1][0] and Array_Red[3][Red_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[1][Blue_2][0] and Array_Red[3][Red_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[2][Blue_3][0] and Array_Red[3][Red_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[3][Blue_4][0] and Array_Red[3][Red_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[3][Red_4][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[3][Red_4][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[3][Red_4][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[3][Red_4][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[0][Green_1][0] and Array_Red[3][Red_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Green[1][Green_2][0] and Array_Red[3][Red_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[2][Green_3][0] and Array_Red[3][Red_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[3][Green_4][0] and Array_Red[3][Red_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_4 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_4 != 52)
				{
					Red_4 = Red_4 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[3][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[3][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[3][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[3][i][1] == Array_Green[0][Green_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[3][i][1] == Array_Green[1][Green_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[3][i][1] == Array_Green[2][Green_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_3) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE_NET = DICE_NET - DICE ;
			}

		}

	}
	DrawCircle( Array_Red[0][Red_1][0] , Array_Red[0][Red_1][1] , 10 , colors[DARK_RED]);
        DrawCircle( Array_Red[1][Red_2][0] , Array_Red[1][Red_2][1] , 10 , colors[DARK_RED]);
        DrawCircle( Array_Red[2][Red_3][0] , Array_Red[2][Red_3][1] , 10 , colors[DARK_RED]);	
        DrawCircle( Array_Red[3][Red_4][0] , Array_Red[3][Red_4][1] , 10 , colors[DARK_RED]);

	DrawString( Array_Red[0][Red_1][0] - 8 , Array_Red[0][Red_1][1] - 9 , "w" , colors[INDIAN_RED]);
	DrawString( Array_Red[1][Red_2][0] - 6 , Array_Red[1][Red_2][1] - 7 , "a" , colors[INDIAN_RED]);
	DrawString( Array_Red[2][Red_3][0] - 5 , Array_Red[2][Red_3][1] - 7 , "s" , colors[INDIAN_RED]);
	DrawString( Array_Red[3][Red_4][0] - 8 , Array_Red[3][Red_4][1] - 10 , "d" , colors[INDIAN_RED]);

	//Pieces of Yellow house
	Array_Yellow[0][0][0] = 577 + 17 ;
	Array_Yellow[0][0][1] = 475 + 17 ;
	Array_Yellow[1][0][0] = 627 + 17 ;
	Array_Yellow[1][0][1] = 475 + 17 ;
	Array_Yellow[2][0][0] = 577 + 17 ;
	Array_Yellow[2][0][1] = 528 + 17 ;
	Array_Yellow[3][0][0] = 627 + 17 ;
	Array_Yellow[3][0][1] = 528 + 17 ;

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Yellow_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_1 != 0 and Yellow_1 <= 58)//
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Yellow = Yellow_1 ;

				Yellow_1 = Yellow_1 + DICE ;

				if (Yellow_1 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_1 > 52)
				{
					Yellow_1 = Yellow_1 - 52 ;
				}

				else if (Yellow_1 > 58 and Yellow_kill > 0 and Yellow_1 != 52)
				{
					Yellow_1 = Yellow_1 - DICE ;
				}

				else if (Yellow_1 <= 58 and Yellow_kill > 0)
				{
					Yellow_1 = Yellow_1 - DICE ;
					for (int i = Yellow_1 ; i <= Yellow_1 + DICE ; i++)
					{
						if (i == 52)
						Yellow_1++ ;

						if (i == 58 and Yellow_1 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_1 = Yellow_1 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[0][Yellow_1][0] == Array_Red[0][Red_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[1][Red_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[2][Red_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[3][Red_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[0][Green_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[1][Green_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[2][Green_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[3][Green_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_1 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_1 != 52)
				{
					Yellow_1 = Yellow_1 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[0][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[0][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[0][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 13)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 13 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 - O_Yellow + 1 ;
	
							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							else if (DICE == 1)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[0][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[0][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[0][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_2 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Yellow_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_2 != 0 and Yellow_2 <= 58)//
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Yellow = Yellow_2 ;

				Yellow_2 = Yellow_2 + DICE ;

				if (Yellow_2 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_2 > 52)
				{
					Yellow_2 = Yellow_2 - 52 ;
				}

				else if (Yellow_2 > 58 and Yellow_kill > 0 and Yellow_2 != 52)
				{
					Yellow_2 = Yellow_2 - DICE ;
				}

				else if (Yellow_2 <= 58 and Yellow_kill > 0)
				{
					Yellow_2 = Yellow_2 - DICE ;
					for (int i = Yellow_2 ; i <= Yellow_2 + DICE ; i++)
					{
						if (i == 52)
						Yellow_2++ ;

						if (i == 58 and Yellow_2 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_2 = Yellow_2 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[1][Yellow_2][0] == Array_Red[0][Red_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[1][Red_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[2][Red_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[3][Red_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[0][Green_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[1][Green_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[2][Green_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[3][Green_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_2 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_2 != 52)
				{
					Yellow_2 = Yellow_2 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[1][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[1][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[1][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[1][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[1][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[1][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_2 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Yellow_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_3 != 0 and Yellow_3 <= 58)//
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Yellow = Yellow_3 ;

				Yellow_3 = Yellow_3 + DICE ;

				if (Yellow_3 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_3 > 52)
				{
					Yellow_3 = Yellow_3 - 52 ;
				}

				else if (Yellow_3 > 58 and Yellow_kill > 0 and Yellow_3 != 52)
				{
					Yellow_3 = Yellow_3 - DICE ;
				}

				else if (Yellow_3 <= 58 and Yellow_kill > 0)
				{
					Yellow_3 = Yellow_3 - DICE ;
					for (int i = Yellow_3 ; i <= Yellow_3 + DICE ; i++)
					{
						if (i == 52)
						Yellow_3++ ;

						if (i == 58 and Yellow_3 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_3 = Yellow_3 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[2][Yellow_3][0] == Array_Red[0][Red_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[1][Red_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[2][Red_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[3][Red_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[0][Green_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[1][Green_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[2][Green_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[3][Green_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_3 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_3 != 52)
				{
					Yellow_3 = Yellow_3 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[2][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[2][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[2][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[2][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[2][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[2][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Yellow_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_4 != 0 and Yellow_4 <= 58)//
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Yellow = Yellow_4 ;

				Yellow_4 = Yellow_4 + DICE ;

				if (Yellow_4 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_4 > 52)
				{
					Yellow_4 = Yellow_4 - 52 ;
				}

				else if (Yellow_4 > 58 and Yellow_kill > 0 and Yellow_4 != 52)
				{
					Yellow_4 = Yellow_4 - DICE ;
				}

				else if (Yellow_4 <= 58 and Yellow_kill > 0)
				{
					Yellow_4 = Yellow_4 - DICE ;
					for (int i = Yellow_4 ; i <= Yellow_4 + DICE ; i++)
					{
						if (i == 52)
						Yellow_4++ ;

						if (i == 58 and Yellow_4 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_4 = Yellow_4 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[3][Yellow_4][0] == Array_Red[0][Red_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[1][Red_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[2][Red_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[3][Red_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[0][Green_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[1][Green_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[2][Green_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[3][Green_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_4 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_4 != 52)
				{
					Yellow_4 = Yellow_4 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[3][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[3][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[3][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[3][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[3][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[3][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_4 or (O_Yellow + DICE) == Yellow_4 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}
	DrawCircle( Array_Yellow[0][Yellow_1][0] , Array_Yellow[0][Yellow_1][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[1][Yellow_2][0] , Array_Yellow[1][Yellow_2][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[2][Yellow_3][0] , Array_Yellow[2][Yellow_3][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[3][Yellow_4][0] , Array_Yellow[3][Yellow_4][1] , 10 , colors[YELLOW]);
	
	DrawString( Array_Yellow[0][Yellow_1][0] - 8 , Array_Yellow[0][Yellow_1][1] - 9 , "w" , colors[ORANGE]);
	DrawString( Array_Yellow[1][Yellow_2][0] - 6 , Array_Yellow[1][Yellow_2][1] - 7 , "a" , colors[ORANGE]);
	DrawString( Array_Yellow[2][Yellow_3][0] - 5 , Array_Yellow[2][Yellow_3][1] - 7 , "s" , colors[ORANGE]);
	DrawString( Array_Yellow[3][Yellow_4][0] - 8 , Array_Yellow[3][Yellow_4][1] - 10 , "d" , colors[ORANGE]);


	//Pieces of Green House
	Array_Green[0][0][0] = 577 + 17 ;
	Array_Green[0][0][1] = 290 + 17 ;
	Array_Green[1][0][0] = 627 + 17 ;
	Array_Green[1][0][1] = 290 + 17 ;
	Array_Green[2][0][0] = 577 + 17 ;
	Array_Green[2][0][1] = 238 + 17 ;
	Array_Green[3][0][0] = 627 + 17 ;
	Array_Green[3][0][1] = 238 + 17 ;

	if (Turns == 4 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Green_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Green_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Green_1 != 0 and Green_1 <= 58)//
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Green = Green_1 ;

				Green_1 = Green_1 + DICE ;

				if (Green_1 <= 58)
				{
					Green_Score = Green_Score + DICE ;
				}

				//Array boundary check
			
				if (Green_kill == 0 and Green_1 > 52)
				{
					Green_1 = Green_1 - 52 ;
				}

				else if (Green_1 > 58 and Green_kill > 0 and Green_1 != 52)
				{
					Green_1 = Green_1 - DICE ;
				}

				else if (Green_1 <= 58 and Green_kill > 0)
				{
					Green_1 = Green_1 - DICE ;
					for (int i = Green_1 ; i <= Green_1 + DICE ; i++)
					{
						if (i == 52)
						Green_1++ ;

						if (i == 58 and Green_1 + DICE <= 58)
						Green_Score += 15 ;
					}
					Green_1 = Green_1 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Green[0][Green_1][0] == Array_Red[0][Red_1][0] and Array_Green[0][Green_1][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Green[0][Green_1][0] == Array_Red[1][Red_2][0] and Array_Green[0][Green_1][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Red[2][Red_3][0] and Array_Green[0][Green_1][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Red[3][Red_4][0] and Array_Green[0][Green_1][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Blue[0][Blue_1][0] and Array_Green[0][Green_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Green[0][Green_1][0] == Array_Blue[1][Blue_2][0] and Array_Green[0][Green_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Blue[2][Blue_3][0] and Array_Green[0][Green_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Blue[3][Blue_4][0] and Array_Green[0][Green_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Green[0][Yellow_1][0] and Array_Green[0][Green_1][1] == Array_Green[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Green[0][Green_1][0] == Array_Yellow[1][Yellow_2][0] and Array_Green[0][Green_1][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Yellow[2][Yellow_3][0] and Array_Green[0][Green_1][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Green[0][Green_1][0] == Array_Yellow[3][Yellow_4][0] and Array_Green[0][Green_1][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_4 = 0 ;
					}

				if (Green_kill >= 1 and Green_1 == 52)
				{
					Green_kill_52 = 52 ;
				}

				if (Green_kill_52 == 52 and Green_1 != 52)
				{
					Green_1 = Green_1 - 52 - 1 ;
					
					Green_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Red[0][Red_1][0] 
						and Array_Green[0][i][1] == Array_Red[0][Red_1][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Red[1][Red_2][0] 
						and Array_Green[0][i][1] == Array_Red[1][Red_2][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Red[1][Red_3][0] 
						and Array_Green[0][i][1] == Array_Red[1][Red_3][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Green[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Green[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Green[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Green[0][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Green[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Green_1 ; i >= Green_1 - DICE ; i--)
					{
						if (Array_Green[0][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Green[0][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Green_1 = Green_1 - DICE ;
							Green_Score -= DICE ;

							if (Green_1 - DICE <= 0 and O_Green > 7)
							Green_1 = 52 + (Green_1) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_1 - DICE <= 0)
							Green_1 = Green_1 + O_Green - 1 ;

							if (Green_kill > 0 and Green_1 + DICE >= 52)
							Green_1 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_1 = Green_1 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Green + DICE) == Green_2 or (O_Green + DICE) == Green_3 or (O_Green + DICE) == Green_4) 
				and O_Green != 0 and (O_Green + DICE) != 58 and (O_Green + DICE) != 1 
				and (O_Green + DICE) != 9 and (O_Green + DICE) != 14 and (O_Green + DICE) != 22 
				and (O_Green + DICE) != 27 and (O_Green + DICE) != 35 and (O_Green + DICE) != 40 
				and (O_Green + DICE) != 48)
				Green_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 4 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Green_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Green_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Green_2 != 0 and Green_2 <= 58)//
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Green = Green_2 ;

				Green_2 = Green_2 + DICE ;

				if (Green_2 <= 58)
				{
					Green_Score = Green_Score + DICE ;
				}

				//Array boundary check
			
				if (Green_kill == 0 and Green_2 > 52)
				{
					Green_2 = Green_2 - 52 ;
				}

				else if (Green_2 > 58 and Green_kill > 0 and Green_2 != 52)
				{
					Green_2 = Green_2 - DICE ;
				}

				else if (Green_2 <= 58 and Green_kill > 0)
				{
					Green_2 = Green_2 - DICE ;
					for (int i = Green_2 ; i <= Green_2 + DICE ; i++)
					{
						if (i == 52)
						Green_2++ ;

						if (i == 58 and Green_2 + DICE <= 58)
						Green_Score += 15 ;
					}
					Green_2 = Green_2 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Green[1][Green_2][0] == Array_Red[0][Red_1][0] and Array_Green[1][Green_2][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Green[1][Green_2][0] == Array_Red[1][Red_2][0] and Array_Green[1][Green_2][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Red[2][Red_3][0] and Array_Green[1][Green_2][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Red[3][Red_4][0] and Array_Green[1][Green_2][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Blue[0][Blue_1][0] and Array_Green[1][Green_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Green[1][Green_2][0] == Array_Blue[1][Blue_2][0] and Array_Green[1][Green_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Blue[2][Blue_3][0] and Array_Green[1][Green_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Blue[3][Blue_4][0] and Array_Green[1][Green_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Green[1][Yellow_1][0] and Array_Green[1][Green_2][1] == Array_Green[1][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Green[1][Green_2][0] == Array_Yellow[1][Yellow_2][0] and Array_Green[1][Green_2][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Yellow[2][Yellow_3][0] and Array_Green[1][Green_2][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Green[1][Green_2][0] == Array_Yellow[3][Yellow_4][0] and Array_Green[1][Green_2][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_4 = 0 ;
					}

				if (Green_kill >= 1 and Green_2 == 52)
				{
					Green_kill_52 = 52 ;
				}

				if (Green_kill_52 == 52 and Green_2 != 52)
				{
					Green_2 = Green_2 - 52 - 1 ;
					
					Green_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Red[0][Red_1][0] 
						and Array_Green[1][i][1] == Array_Red[0][Red_1][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Red[1][Red_2][0] 
						and Array_Green[1][i][1] == Array_Red[1][Red_2][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Red[1][Red_3][0] 
						and Array_Green[1][i][1] == Array_Red[1][Red_3][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Green[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Green[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Green[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Green[1][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Green[1][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Green_2 ; i >= Green_2 - DICE ; i--)
					{
						if (Array_Green[1][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Green[1][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Green_2 = Green_2 - DICE ;
							Green_Score -= DICE ;

							if (Green_2 - DICE <= 0 and O_Green > 7)
							Green_2 = 52 + (Green_2) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_2 - DICE <= 0)
							Green_2 = Green_2 + O_Green - 1 ;

							if (Green_kill > 0 and Green_2 + DICE >= 52)
							Green_2 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_2 = Green_2 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Green + DICE) == Green_2 or (O_Green + DICE) == Green_3 or (O_Green + DICE) == Green_4) 
				and O_Green != 0 and (O_Green + DICE) != 58 and (O_Green + DICE) != 1 
				and (O_Green + DICE) != 9 and (O_Green + DICE) != 14 and (O_Green + DICE) != 22 
				and (O_Green + DICE) != 27 and (O_Green + DICE) != 35 and (O_Green + DICE) != 40 
				and (O_Green + DICE) != 48)
				Green_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 4 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Green_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Green_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Green_3 != 0 and Green_3 <= 58)//
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Green = Green_3 ;

				Green_3 = Green_3 + DICE ;

				if (Green_3 <= 58)
				{
					Green_Score = Green_Score + DICE ;
				}

				//Array boundary check
			
				if (Green_kill == 0 and Green_3 > 52)
				{
					Green_3 = Green_3 - 52 ;
				}

				else if (Green_3 > 58 and Green_kill > 0 and Green_3 != 52)
				{
					Green_3 = Green_3 - DICE ;
				}

				else if (Green_3 <= 58 and Green_kill > 0)
				{
					Green_3 = Green_3 - DICE ;
					for (int i = Green_3 ; i <= Green_3 + DICE ; i++)
					{
						if (i == 52)
						Green_3++ ;

						if (i == 58 and Green_3 + DICE <= 58)
						Green_Score += 15 ;
					}
					Green_3 = Green_3 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Green[2][Green_3][0] == Array_Red[0][Red_1][0] and Array_Green[2][Green_3][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Green[2][Green_3][0] == Array_Red[1][Red_2][0] and Array_Green[2][Green_3][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Red[2][Red_3][0] and Array_Green[2][Green_3][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Red[3][Red_4][0] and Array_Green[2][Green_3][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Blue[0][Blue_1][0] and Array_Green[2][Green_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Green[2][Green_3][0] == Array_Blue[1][Blue_2][0] and Array_Green[2][Green_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Blue[2][Blue_3][0] and Array_Green[2][Green_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Blue[3][Blue_4][0] and Array_Green[2][Green_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Green[2][Yellow_1][0] and Array_Green[2][Green_3][1] == Array_Green[2][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Green[2][Green_3][0] == Array_Yellow[1][Yellow_2][0] and Array_Green[2][Green_3][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Yellow[2][Yellow_3][0] and Array_Green[2][Green_3][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Green[2][Green_3][0] == Array_Yellow[3][Yellow_4][0] and Array_Green[2][Green_3][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_4 = 0 ;
					}

				if (Green_kill >= 1 and Green_3 == 52)
				{
					Green_kill_52 = 52 ;
				}

				if (Green_kill_52 == 52 and Green_3 != 52)
				{
					Green_3 = Green_3 - 52 - 1 ;
					
					Green_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Red[0][Red_1][0] 
						and Array_Green[2][i][1] == Array_Red[0][Red_1][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Red[1][Red_2][0] 
						and Array_Green[2][i][1] == Array_Red[1][Red_2][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Red[1][Red_3][0] 
						and Array_Green[2][i][1] == Array_Red[1][Red_3][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Green[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Green[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Green[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Green[2][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Green[2][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Green_3 ; i >= Green_3 - DICE ; i--)
					{
						if (Array_Green[2][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Green[2][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Green_3 = Green_3 - DICE ;
							Green_Score -= DICE ;

							if (Green_3 - DICE <= 0 and O_Green > 7)
							Green_3 = 52 + (Green_3) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_3 - DICE <= 0)
							Green_3 = Green_3 + O_Green - 1 ;

							if (Green_kill > 0 and Green_3 + DICE >= 52)
							Green_3 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_3 = Green_3 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Green + DICE) == Green_3 or (O_Green + DICE) == Green_3 or (O_Green + DICE) == Green_4) 
				and O_Green != 0 and (O_Green + DICE) != 58 and (O_Green + DICE) != 1 
				and (O_Green + DICE) != 9 and (O_Green + DICE) != 14 and (O_Green + DICE) != 22 
				and (O_Green + DICE) != 27 and (O_Green + DICE) != 35 and (O_Green + DICE) != 40 
				and (O_Green + DICE) != 48)
				Green_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 4 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Green_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Green_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Green_4 != 0 and Green_4 <= 58)//
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Green = Green_4 ;

				Green_4 = Green_4 + DICE ;

				if (Green_4 <= 58)
				{
					Green_Score = Green_Score + DICE ;
				}

				//Array boundary check
			
				if (Green_kill == 0 and Green_4 > 52)
				{
					Green_4 = Green_4 - 52 ;
				}

				else if (Green_4 > 58 and Green_kill > 0 and Green_4 != 52)
				{
					Green_4 = Green_4 - DICE ;
				}

				else if (Green_4 <= 58 and Green_kill > 0)
				{
					Green_4 = Green_4 - DICE ;
					for (int i = Green_4 ; i <= Green_4 + DICE ; i++)
					{
						if (i == 52)
						Green_4++ ;

						if (i == 58 and Green_4 + DICE <= 58)
						Green_Score += 15 ;
					}
					Green_4 = Green_4 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Green[3][Green_4][0] == Array_Red[0][Red_1][0] and Array_Green[3][Green_4][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Green[3][Green_4][0] == Array_Red[1][Red_2][0] and Array_Green[3][Green_4][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Red[2][Red_3][0] and Array_Green[3][Green_4][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Red[3][Red_4][0] and Array_Green[3][Green_4][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Blue[0][Blue_1][0] and Array_Green[3][Green_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Green[3][Green_4][0] == Array_Blue[1][Blue_2][0] and Array_Green[3][Green_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Blue[2][Blue_3][0] and Array_Green[3][Green_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Blue[3][Blue_4][0] and Array_Green[3][Green_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Green[3][Yellow_1][0] and Array_Green[3][Green_4][1] == Array_Green[3][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Green_kill++ ;
					Green_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Green[3][Green_4][0] == Array_Yellow[1][Yellow_2][0] and Array_Green[3][Green_4][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Yellow[2][Yellow_3][0] and Array_Green[3][Green_4][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Green[3][Green_4][0] == Array_Yellow[3][Yellow_4][0] and Array_Green[3][Green_4][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Green_kill++ ;
						Green_Score += 10 ;
						Yellow_4 = 0 ;
					}

				if (Green_kill >= 1 and Green_4 == 52)
				{
					Green_kill_52 = 52 ;
				}

				if (Green_kill_52 == 52 and Green_4 != 52)
				{
					Green_4 = Green_4 - 52 - 1 ;
					
					Green_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Red[0][Red_1][0] 
						and Array_Green[3][i][1] == Array_Red[0][Red_1][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Red[1][Red_2][0] 
						and Array_Green[3][i][1] == Array_Red[1][Red_2][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Red[1][Red_3][0] 
						and Array_Green[3][i][1] == Array_Red[1][Red_3][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Green[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Green[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Green[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Green[3][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Green[3][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Green_4 ; i >= Green_4 - DICE ; i--)
					{
						if (Array_Green[3][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Green[3][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Green_4 = Green_4 - DICE ;
							Green_Score -= DICE ;

							if (Green_4 - DICE <= 0 and O_Green > 7)
							Green_4 = 52 + (Green_4) ;

							else if (O_Green >= 1 and O_Green <= 7 and Green_4 - DICE <= 0)
							Green_4 = Green_4 + O_Green - 1 ;

							if (Green_kill > 0 and Green_4 + DICE >= 52)
							Green_4 -= 1 ;

							if (Green_kill > 0 and i == 52)
							{
								Green_4 = Green_4 + DICE + 1 ;
								Green_Score = Green_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Green + DICE) == Green_4 or (O_Green + DICE) == Green_4 or (O_Green + DICE) == Green_4) 
				and O_Green != 0 and (O_Green + DICE) != 58 and (O_Green + DICE) != 1 
				and (O_Green + DICE) != 9 and (O_Green + DICE) != 14 and (O_Green + DICE) != 22 
				and (O_Green + DICE) != 27 and (O_Green + DICE) != 35 and (O_Green + DICE) != 40 
				and (O_Green + DICE) != 48)
				Green_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	DrawCircle( Array_Green[0][Green_1][0] , Array_Green[0][Green_1][1] , 10 , colors[FOREST_GREEN]);
        DrawCircle( Array_Green[1][Green_2][0] , Array_Green[1][Green_2][1] , 10 , colors[FOREST_GREEN]);
        DrawCircle( Array_Green[2][Green_3][0] , Array_Green[2][Green_3][1] , 10 , colors[FOREST_GREEN]);
        DrawCircle( Array_Green[3][Green_4][0] , Array_Green[3][Green_4][1] , 10 , colors[FOREST_GREEN]);

	DrawString( Array_Green[0][Green_1][0] - 8 , Array_Green[0][Green_1][1] - 9 , "w" , colors[GREEN_YELLOW]);
	DrawString( Array_Green[1][Green_2][0] - 6 , Array_Green[1][Green_2][1] - 7 , "a" , colors[GREEN_YELLOW]);
	DrawString( Array_Green[2][Green_3][0] - 5 , Array_Green[2][Green_3][1] - 7 , "s" , colors[GREEN_YELLOW]);
	DrawString( Array_Green[3][Green_4][0] - 8 , Array_Green[3][Green_4][1] - 10 , "d" , colors[GREEN_YELLOW]);

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	
	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Turns == 1 and Red_Win != 0)
	{
		Turns++ ;
	}

	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Turns == 1 and Red_Win == 0)
	{
		Red_Win ++ ;
		Win++ ;
	}

	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red_Win == Win)
	{
		DrawString (300 , 150 , "Red has won the game" , colors[WHITE]) ;
		Red_Win++ ;
		Win++ ;
	}

	else if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red_Win != Win)
	DrawString (300 , 150 , "Red has finished the game" , colors[WHITE]) ;

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Turns == 1 and Blue_Win != 0)
	{
		Turns++ ;
	}

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Turns == 1 and Blue_Win == 0)
	{
		Blue_Win ++ ;
		Win++ ;
	}

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Blue_Win == Win)
	{
		DrawString (300 , 125 , "Blue has won the game" , colors[WHITE]) ;
		Blue_Win++ ;
		Win++ ;
	}

	else if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Blue_Win != Win)
	DrawString (300 , 125 , "Blue has finished the game" , colors[WHITE]) ;

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Turns == 1 and Yellow_Win != 0)
	{
		Turns++ ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Turns == 1 and Yellow_Win == 0)
	{
		Yellow_Win ++ ;
		Win++ ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow_Win == Win)
	{
		DrawString (300 , 100 , "Yellow has won the game" , colors[WHITE]) ;
		Yellow_Win++ ;
		Win++ ;
	}

	else if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow_Win != Win)
	DrawString (300 , 100 , "Yellow has finished the game" , colors[WHITE]) ;

	if (Green_1 == 58 and Green_2 == 58 and Green_3 == 58 and Green_4 == 58 and Turns == 1 and Green_Win != 0)
	{
		Turns -= 3 ;
	}

	if (Green_1 == 58 and Green_2 == 58 and Green_3 == 58 and Green_4 == 58 and Turns == 1 and Green_Win == 0)
	{
		Green_Win ++ ;
		Win++ ;
	}

	if (Green_1 == 58 and Green_2 == 58 and Green_3 == 58 and Green_4 == 58 and Green_Win == Win)
	{
		DrawString (300 , 75 , "Green has won the game" , colors[WHITE]) ;
		Green_Win++ ;
		Win++ ;
	}

	else if (Green_1 == 58 and Green_2 == 58 and Green_3 == 58 and Green_4 == 58 and Green_Win != Win)
	DrawString (300 , 75 , "Green has finished the game" , colors[WHITE]) ;

	DrawSquare( 750 , 250 , 30 , colors[GRAY]);//Square for dice.

	//Dice faces.
	if (DICE == 1)
	  DrawCircle(765 , 265 , 3 , colors[RED]) ;

	else if (DICE == 2)
	{
		DrawCircle(770 , 265 , 3 , colors[RED]) ;
		DrawCircle(760 , 265 , 3 , colors[RED]) ;
        }

	else if (DICE == 3)
        {
		DrawCircle(775 , 275 , 3 , colors[RED]) ;
		DrawCircle(765 , 265 , 3 , colors[RED]) ;
		DrawCircle(755 , 255 , 3 , colors[RED]) ;
        }

	else if (DICE == 4)
        {
		DrawCircle(770 , 270 , 3 , colors[RED]) ;
		DrawCircle(760 , 270 , 3 , colors[RED]) ;
		DrawCircle(770 , 260 , 3 , colors[RED]) ;
		DrawCircle(760 , 260 , 3 , colors[RED]) ;
        }

	else if (DICE == 5)
	{
		DrawCircle(755 , 275 , 3 , colors[RED]) ;
		DrawCircle(775 , 275 , 3 , colors[RED]) ;
		DrawCircle(765 , 265 , 3 , colors[RED]) ;
		DrawCircle(755 , 255 , 3 , colors[RED]) ;
		DrawCircle(775 , 255 , 3 , colors[RED]) ;
        }


	else if (DICE == 6)
	    {
		DrawCircle(770 , 275 , 3 , colors[RED]) ;
		DrawCircle(760 , 275 , 3 , colors[RED]) ;
		DrawCircle(770 , 265 , 3 , colors[RED]) ;
		DrawCircle(760 , 265 , 3 , colors[RED]) ;
		DrawCircle(770 , 255 , 3 , colors[RED]) ;
		DrawCircle(760 , 255 , 3 , colors[RED]) ;
	    }

	if (Turns == 1 or Turns == 0)
	DrawSquare (100 , 300 , 30 , colors[RED]) ;

	else if (Turns ==  2)
	DrawSquare (100 , 300 , 30 , colors[BLUE]) ;

	else if (Turns ==  3)
	DrawSquare (100 , 300 , 30 , colors[OLIVE]) ;

	else if (Turns ==  4 or Turns == 5)
	DrawSquare (100 , 300 , 30 , colors[FOREST_GREEN]) ;
	//For storing score in file.
	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Red_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Red_Score ;
				Names_1 [i] = Player_Names [0] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Red_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Red++ ;
	}

	if (Green_1 == 58 and Green_2 == 58 and Green_3 == 58 and Green_4 == 58 and Green == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Green_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Green_Score ;
				Names_1 [i] = Player_Names [3] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Green_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Green++ ;
	}

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Blue == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Blue_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Blue_Score ;
				Names_1 [i] = Player_Names [1] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Blue_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Blue++ ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Yellow_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Yellow_Score ;
				Names_1 [i] = Player_Names [2] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Yellow_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Yellow++ ;
	}
	
	DrawString( 50 , 800 , "RED" , colors[MINT_CREAM]) ;
	DrawString( 300 , 800 , "BLUE" , colors[MINT_CREAM]) ;
	DrawString( 550 , 800 , "YELLOW" , colors[MINT_CREAM]) ;
	DrawString( 800 , 800 , "GREEN" , colors[MINT_CREAM]) ;

	DrawString( 50 , 775 , Player_Names [0] + " Score = " + to_string (Red_Score), colors[MINT_CREAM]) ;
	DrawString( 300 , 775 , Player_Names [1] + " Score = " + to_string (Blue_Score), colors[MINT_CREAM]) ;
	DrawString( 550 , 775 , Player_Names [2] + " Score = " + to_string (Yellow_Score), colors[MINT_CREAM]) ;
	DrawString( 800 , 775 , Player_Names [3] + " Score = " + to_string (Green_Score), colors[MINT_CREAM]) ;
	buttons = 0 ;

	if (Red_Win > 0 and Blue_Win > 0 and Yellow_Win > 0 and Green_Win > 0)
	{
		FINISH++ ;
		DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
	}

	if (Red_Win > 0 and Blue_Win > 0 and Yellow_Win > 0 and Green_kill == 0)
	{
		FINISH++ ;
		DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
	}

	if (Red_Win > 0 and Blue_Win > 0 and Yellow_kill == 0 and Green_Win > 0)
	{
		FINISH++ ;
		DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
	}

	if (Red_Win > 0 and Blue_kill == 0 and Yellow_Win > 0 and Green_Win > 0)
	{
		FINISH++ ;
		DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
	}

	if (Red_kill == 0 and Blue_Win > 0 and Yellow_Win > 0 and Green_Win > 0)
	{
		FINISH++ ;
		DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
	}

	cout << "\nTurns = " << Turns << endl ;
	cout << "DICE = " << DICE << endl ;
	cout << "xx = "  << xx << endl ;
	cout << "yy = " << yy << endl ;
	cout << "Red_Win = " << Red_Win << endl ;
	cout << "Win = " << Win << endl ;
	cout << "Turn = " << Turn << endl ;
	}
	}

	//For game of 3 players.
	if (BUTTONS == 54)
	{
	if (screen == 3)
	{
	glClearColor(0/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour

	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//DrawString(425 , 750 , cin.getline (str) , colors [MISTY_ROSE]) ;
	int x , y ;

	//Arrays for storing positions of ludo pieces 
	int Array_Red[4][59][2] ;
	int Array_Blue[4][59][2] ;
	int Array_Yellow[4][59][2] ;
	int Array_Green[4][59][2] ;
        //Main Board
	DrawSquare( 300 , 200 , 400 , colors[GRAY]);

        //Player Houses Squares
        DrawSquare( 300 , 438 , 162 , colors[BLUE]);
        DrawSquare( 538 , 438 , 162 , colors[OLIVE]);
        DrawSquare( 300 , 200 , 162 , colors[RED]);
        DrawSquare( 538 , 200 , 162 , colors[GREEN]);

        //Blue House Squares
        DrawSquare( 320 , 458 , 122 , colors[WHITE]);
        DrawSquare( 337 , 475 , 35 , colors[BLUE]);
        DrawSquare( 390 , 475 , 35 , colors[BLUE]);
        DrawSquare( 337 , 528 , 35 , colors[BLUE]);
        DrawSquare( 390 , 528 , 35 , colors[BLUE]);

        //Yellow House Squares
        DrawSquare( 558 , 458 , 122 , colors[WHITE]);
        DrawSquare( 577 , 475 , 35 , colors[OLIVE]);
        DrawSquare( 627 , 475 , 35 , colors[OLIVE]);
        DrawSquare( 577 , 528 , 35 , colors[OLIVE]);
        DrawSquare( 627 , 528 , 35 , colors[OLIVE]);

        //RED House Squares
        DrawSquare( 320 , 220 , 122 , colors[WHITE]);
        DrawSquare( 337 , 290 , 35 , colors[RED]);
        DrawSquare( 390 , 290 , 35 , colors[RED]);
        DrawSquare( 337 , 238 , 35 , colors[RED]);
        DrawSquare( 390 , 238 , 35 , colors[RED]);

        //Green House Squares
        DrawSquare( 558 , 220 , 122 , colors[WHITE]);
        DrawSquare( 577 , 290 , 35 , colors[GREEN]);
        DrawSquare( 627 , 290 , 35 , colors[GREEN]);
        DrawSquare( 577 , 238 , 35 , colors[GREEN]);
        DrawSquare( 627 , 238 , 35 , colors[GREEN]);

	//Mid houses Square.
        DrawSquare( 461 , 362 , 78 , colors[VIOLET]);
	DrawTriangle( 461 , 362 , 500 , 401 , 539 , 362 , colors[RED]);
	DrawTriangle( 461 , 439 , 500 , 401 , 539 , 439 , colors[OLIVE]);
	DrawTriangle( 461 , 362 , 500 , 401 , 461 , 439 , colors[BLUE]);
	DrawTriangle( 539 , 362 , 500 , 401 , 539 , 439 , colors[GREEN]);
	DrawLine( 461 , 362 , 539 , 439 , 0 , colors[BLACK]);//Diagonal boundary line
	DrawLine( 539 , 362 , 461 , 439 , 0 , colors[BLACK]);//Diagonal boundary line

	//Squares between red and green houses

	DrawSquare( 461 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 228 , 27 , colors[RED]) ;
	DrawSquare( 461 , 254 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 282 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 309 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 335 , 27 , colors[WHITE]) ;

	DrawSquare( 487 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 487 , 228 , 27 , colors[RED]) ;
	DrawSquare( 487 , 254 , 27 , colors[RED]) ;
	DrawSquare( 487 , 282 , 27 , colors[RED]) ;
	DrawSquare( 487 , 309 , 27 , colors[RED]) ;
	DrawSquare( 487 , 335 , 27 , colors[RED]) ;

	DrawSquare( 513 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 228 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 254 , 27 , colors[GRAY]) ;
	DrawSquare( 513 , 282 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 309 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 335 , 27 , colors[WHITE]) ;
	//Horizontal lines between red and green houses
        DrawLine( 461 , 227 ,  538, 227 , 0 , colors[BLACK] );
        DrawLine( 461 , 254 ,  538, 254 , 0 , colors[BLACK] );
	DrawLine( 461 , 281 ,  538, 281 , 0 , colors[BLACK] );
	DrawLine( 461 , 308 ,  538, 308 , 0 , colors[BLACK] );
	DrawLine( 461 , 335 ,  538, 335 , 0 , colors[BLACK] );
	DrawLine( 461 , 361 ,  538, 361 , 0 , colors[BLACK] );
	//Vertical lines between red and green houses
	DrawLine( 461 , 200 ,  461, 362 , 0 , colors[BLACK] );
	DrawLine( 487 , 200 ,  487, 362 , 0 , colors[BLACK] );
	DrawLine( 513 , 200 ,  513, 362 , 0 , colors[BLACK] );
	DrawLine( 539 , 200 ,  539, 362 , 0 , colors[BLACK] );

	//Squares between yellow and blue houses

	DrawSquare( 460 , 439 , 28 , colors[WHITE]) ;
	DrawSquare( 461 , 468 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 494 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 522 , 27 , colors[GRAY]) ;
	DrawSquare( 461 , 548 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 574 , 27 , colors[WHITE]) ;

	DrawSquare( 486 , 439 , 28 , colors[OLIVE]) ;
	DrawSquare( 487 , 468 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 494 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 522 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 548 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 574 , 27 , colors[WHITE]) ;

	DrawSquare( 512 , 439 , 28 , colors[WHITE]) ;
	DrawSquare( 513 , 468 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 494 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 522 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 548 , 27 , colors[OLIVE]) ;
	DrawSquare( 513 , 574 , 27 , colors[WHITE]) ;
	//Horizontal lines between yellow and blue houses
	DrawLine( 461 , 439 ,  538, 439 , 0 , colors[BLACK] );
	DrawLine( 461 , 467 ,  538, 467 , 0 , colors[BLACK] );
	DrawLine( 461 , 494 ,  538, 494 , 0 , colors[BLACK] );
	DrawLine( 461 , 521 ,  538, 521 , 0 , colors[BLACK] );
	DrawLine( 461 , 548 ,  538, 548 , 0 , colors[BLACK] );
	DrawLine( 461 , 575 ,  538, 575 , 0 , colors[BLACK] );
	//Vertical lines between yellow and blue houses
	DrawLine( 461 , 438 ,  461, 600 , 0 , colors[BLACK] );
	DrawLine( 487 , 438 ,  487, 600 , 0 , colors[BLACK] );
	DrawLine( 513 , 438 ,  513, 600 , 0 , colors[BLACK] );
	DrawLine( 539 , 438 ,  539, 600 , 0 , colors[BLACK] );

	//Squares between red and blue houses

	DrawSquare( 301 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 355 , 362 , 27 , colors[GRAY]) ;
	DrawSquare( 382 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 409 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 435 , 362 , 27 , colors[WHITE]) ;

	DrawSquare( 301 , 388 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 355 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 382 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 409 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 435 , 388 , 27 , colors[BLUE]) ;

	DrawSquare( 301 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 413 , 27 , colors[BLUE]) ;
	DrawSquare( 355 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 382 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 409 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 435 , 413 , 27 , colors[WHITE]) ;
	//Vertical lines between red and blue houses
        DrawLine( 328 , 361 ,  328, 438 , 0 , colors[BLACK] );
        DrawLine( 355 , 361 ,  355, 438 , 0 , colors[BLACK] );
	DrawLine( 382 , 361 ,  382, 438 , 0 , colors[BLACK] );
	DrawLine( 409 , 361 ,  409, 438 , 0 , colors[BLACK] );
	DrawLine( 436 , 361 ,  436, 438 , 0 , colors[BLACK] );
	DrawLine( 461 , 361 ,  461, 438 , 0 , colors[BLACK] );
	//Horizontal lines between red and blue houses
	DrawLine( 300 , 361 ,  461, 361 , 0 , colors[BLACK] );
	DrawLine( 300 , 387 ,  461, 387 , 0 , colors[BLACK] );
	DrawLine( 300 , 413 ,  461, 413 , 0 , colors[BLACK] );
	DrawLine( 300 , 439 ,  461, 439 , 0 , colors[BLACK] );
	
	//Squares between yellow and green houses

	DrawSquare( 539 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 566 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 593 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 620 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 647 , 362 , 27 , colors[GREEN]) ;
	DrawSquare( 674 , 362 , 27 , colors[WHITE]) ;

	DrawSquare( 539 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 566 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 593 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 620 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 647 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 674 , 388 , 27 , colors[WHITE]) ;

	DrawSquare( 539 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 566 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 593 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 620 , 413 , 27 , colors[GRAY]) ;
	DrawSquare( 647 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 674 , 413 , 27 , colors[WHITE]) ;


	//Vertical lines between yellow and green houses
        DrawLine( 539 , 361 ,  539, 438 , 0 , colors[BLACK] );
        DrawLine( 566 , 361 ,  566, 438 , 0 , colors[BLACK] );
	DrawLine( 593 , 361 ,  593, 438 , 0 , colors[BLACK] );
	DrawLine( 620 , 361 ,  620, 438 , 0 , colors[BLACK] );
	DrawLine( 647 , 361 ,  647, 438 , 0 , colors[BLACK] );
	DrawLine( 674 , 361 ,  674, 438 , 0 , colors[BLACK] );
	//Horizontal lines between yellow and green houses
	DrawLine( 539 , 361 ,  700, 361 , 0 , colors[BLACK] );
	DrawLine( 539 , 387 ,  700, 387 , 0 , colors[BLACK] );
	DrawLine( 539 , 413 ,  700, 413 , 0 , colors[BLACK] );
	DrawLine( 539 , 439 ,  700, 439 , 0 , colors[BLACK] );


	//Borderlines
	DrawLine( 300 , 200 ,  700, 200 , 0 , colors[BLACK] );
	DrawLine( 300 , 200 ,  300, 600 , 0 , colors[BLACK] );
	DrawLine( 300 , 600 ,  700, 600 , 0 , colors[BLACK] );
	DrawLine( 700 , 200 ,  700, 600 , 0 , colors[BLACK] );
	//DrawSquare( 250 , 250 ,20,colors[WHITE]); 
	//Display Score
	//Spider
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	
	//Storing positions for red house.

        for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j <= 5)
						Array_Red[i][j][k] = 473 ;
					
					else if (j <= 11)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 13)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k];

					else if (j <= 18)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 24)
					{
						if (j == 19)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
						
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

					else if (j <= 26)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 31)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 37)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 39)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 44)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 50)
					{
						if (j == 45)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;
	
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}
					else if (j <= 52)
					Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 58)
					{
						if (j == 53)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

				}

				else if (k == 1)
				{
					if (j <= 5)
					{
						if (j == 1)
						Array_Red[i][j][k] = 228 + 17 ;
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
					}

					else if (j <= 11)
					{
						if (j == 6)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

					else if (j <= 13)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 18)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 24)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 26)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					
					else if (j <= 31)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 37)
						{
							if (j == 32)
							Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

							else
							Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
						}

					else if (j <= 39)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 44)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 50)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 52)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 58)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
				}
			}
		}
	}
        
	//Storing Positions for blue house

	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j == 1)
					Array_Blue[i][j][k] = Array_Red [i][14][k] ;

					else if (j <= 6)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;	
										
					else if (j <= 11)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 13)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 18)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 24)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 26)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 32)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 37)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 39)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 44)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 50)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 52)
					Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 58)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;
				}

				else if (k == 1)
				{
					if (j <= 5)
					Array_Blue[i][j][k] = Array_Blue[i][j][k] = Array_Red [i][14][k] ;
				
					else if (j <= 11)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 13)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 19)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 24)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 26)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 31)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 37)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 39)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 45)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j <= 50)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;

					else if (j <= 52)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] + 26 ;

					else if (j == 53)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] - 26 ;

					else if (j <= 58)
						Array_Blue[i][j][k] = Array_Blue[i][j - 1][k] ;
				}
			}
		}
	}

	//Storing positions for yellow house
	
	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j <= 5)
					Array_Yellow[i][j][k] = Array_Red [i][27][k] ; 

					else if (j <= 11)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;	
										
					else if (j <= 13)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 19)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 24)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 26)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 31)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 37)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 39)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 45)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 50)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 52)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j == 53)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 58)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;
				}

				else if (k == 1)
				{
					if (j == 1)
					Array_Yellow[i][j][k] = Array_Red [i][27][k] ;
 
					else if (j <= 6)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;
				
					else if (j <= 11)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 13)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 18)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 24)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 26)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 32)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 37)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 39)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 44)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 50)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 52)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;
	
					else if (j <= 58)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;
				}
			}
		}
	}	

	if (DICE_NET == 18)
	{
		DICE_NET = 0 ;
		DICE_COUNT == 0 ;
	}
	//Pieces of blue house
	Array_Blue[0][0][0] = 337 + 17 ;
	Array_Blue[0][0][1] = 475 + 17 ;
	Array_Blue[1][0][0] = 390 + 17 ;
	Array_Blue[1][0][1] = 475 + 17 ;
	Array_Blue[2][0][0] = 337 + 17 ;
	Array_Blue[2][0][1] = 528 + 17 ;
	Array_Blue[3][0][0] = 390 + 17 ;
	Array_Blue[3][0][1] = 528 + 17 ;

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Blue_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_1 != 0 and Blue_1 <= 58)//
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Blue = Blue_1 ;

				Blue_1 = Blue_1 + DICE ;

				if (Blue_1 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_1 > 52)
				{
					Blue_1 = Blue_1 - 52 ;
				}

				else if (Blue_1 > 58 and Blue_kill > 0 and Blue_1 != 52)
				{
					Blue_1 = Blue_1 - DICE ;
				}

				else if (Blue_1 <= 58 and Blue_kill > 0)
				{
					Blue_1 = Blue_1 - DICE ;
					for (int i = Blue_1 ; i <= Blue_1 + DICE ; i++)
					{
						if (i == 52)
						Blue_1++ ;

						if (i == 58 and Blue_1 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_1 = Blue_1 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[0][Blue_1][0] == Array_Red[0][Red_1][0] and Array_Blue[0][Blue_1][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[0][Blue_1][0] == Array_Red[1][Red_2][0] and Array_Blue[0][Blue_1][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Red[2][Red_3][0] and Array_Blue[0][Blue_1][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Red[3][Red_4][0] and Array_Blue[0][Blue_1][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_1 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[0][Blue_1][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[0][Green_1][0] and Array_Blue[0][Blue_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_1 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[1][Green_2][0] and Array_Blue[0][Blue_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[2][Green_3][0] and Array_Blue[0][Blue_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[0][Blue_1][0] == Array_Green[3][Green_4][0] and Array_Blue[0][Blue_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_1 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_1 != 52)
				{
					Blue_1 = Blue_1 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[0][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[0][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[0][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[0][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[0][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[0][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[0][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_1 ; i >= Blue_1 - DICE ; i--)
					{
						if (Array_Blue[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[0][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_1 = Blue_1 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_1 - DICE <= 0 and O_Blue > 7)
							Blue_1 = 52 + (Blue_1) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_1 - DICE <= 0)
							Blue_1 = Blue_1 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_1 + DICE >= 52)
							Blue_1 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_1 = Blue_1 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_2 or (O_Blue + DICE) == Blue_3 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Blue_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_2 != 0 and Blue_2 <= 58)//
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Blue = Blue_2 ;

				Blue_2 = Blue_2 + DICE ;

				if (Blue_2 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_2 > 52)
				{
					Blue_2 = Blue_2 - 52 ;
				}

				else if (Blue_2 > 58 and Blue_kill > 0 and Blue_2 != 52)
				{
					Blue_2 = Blue_2 - DICE ;
				}

				else if (Blue_2 <= 58 and Blue_kill > 0)
				{
					Blue_2 = Blue_2 - DICE ;
					for (int i = Blue_2 ; i <= Blue_2 + DICE ; i++)
					{
						if (i == 52)
						Blue_2++ ;

						if (i == 58 and Blue_2 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_2 = Blue_2 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[1][Blue_2][0] == Array_Red[0][Red_1][0] and Array_Blue[1][Blue_2][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[1][Blue_2][0] == Array_Red[1][Red_2][0] and Array_Blue[1][Blue_2][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Red[2][Red_3][0] and Array_Blue[1][Blue_2][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Red[3][Red_4][0] and Array_Blue[1][Blue_2][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[1][Blue_2][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[0][Green_1][0] and Array_Blue[1][Blue_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[1][Green_2][0] and Array_Blue[1][Blue_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[2][Green_3][0] and Array_Blue[1][Blue_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[1][Blue_2][0] == Array_Green[3][Green_4][0] and Array_Blue[1][Blue_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_2 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_2 != 52)
				{
					Blue_2 = Blue_2 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				       	if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[1][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[1][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[1][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[1][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[1][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[1][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[1][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[1][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_2 ; i >= Blue_2 - DICE ; i--)
					{
						if (Array_Blue[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[1][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_2 = Blue_2 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_2 - DICE <= 0 and O_Blue > 7)
							Blue_2 = 52 + (Blue_2) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_2 - DICE <= 0)
							Blue_2 = Blue_2 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_2 + DICE >= 52)
							Blue_2 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_2 = Blue_2 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_1 or (O_Blue + DICE) == Blue_3 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Blue_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_3 != 0 and Blue_3 <= 58)//
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Blue = Blue_3 ;

				Blue_3 = Blue_3 + DICE ;

				if (Blue_3 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_3 > 52)
				{
					Blue_3 = Blue_3 - 52 ;
				}

				else if (Blue_3 > 58 and Blue_kill > 0 and Blue_3 != 52)
				{
					Blue_3 = Blue_3 - DICE ;
				}

				else if (Blue_3 <= 58 and Blue_kill > 0)
				{
					Blue_3 = Blue_3 - DICE ;
					for (int i = Blue_3 ; i <= Blue_3 + DICE ; i++)
					{
						if (i == 52)
						Blue_3++ ;

						if (i == 58 and Blue_3 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_3 = Blue_3 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[2][Blue_3][0] == Array_Red[0][Red_1][0] and Array_Blue[2][Blue_3][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[2][Blue_3][0] == Array_Red[1][Red_2][0] and Array_Blue[2][Blue_3][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Red[2][Red_3][0] and Array_Blue[2][Blue_3][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Red[3][Red_4][0] and Array_Blue[2][Blue_3][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[2][Blue_3][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[0][Green_1][0] and Array_Blue[2][Blue_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[1][Green_2][0] and Array_Blue[2][Blue_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[2][Green_3][0] and Array_Blue[2][Blue_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[2][Blue_3][0] == Array_Green[3][Green_4][0] and Array_Blue[2][Blue_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_3 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_3 != 52)
				{
					Blue_3 = Blue_3 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				       	if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[2][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[2][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[2][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[2][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[2][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[2][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[2][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[2][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_3 ; i >= Blue_3 - DICE ; i--)
					{
						if (Array_Blue[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[2][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_3 = Blue_3 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_3 - DICE <= 0 and O_Blue > 7)
							Blue_3 = 52 + (Blue_3) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_3 - DICE <= 0)
							Blue_3 = Blue_3 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_3 + DICE >= 52)
							Blue_3 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_3 = Blue_3 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_2 or (O_Blue + DICE) == Blue_1 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Blue_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Blue_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Blue_4 != 0 and Blue_4 <= 58)//
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Blue = Blue_4 ;

				Blue_4 = Blue_4 + DICE ;

				if (Blue_4 <= 58)
				{
					Blue_Score = Blue_Score + DICE ;
				}

				//Array boundary check
			
				if (Blue_kill == 0 and Blue_4 > 52)
				{
					Blue_4 = Blue_4 - 52 ;
				}

				else if (Blue_4 > 58 and Blue_kill > 0 and Blue_4 != 52)
				{
					Blue_4 = Blue_4 - DICE ;
				}

				else if (Blue_4 <= 58 and Blue_kill > 0)
				{
					Blue_4 = Blue_4 - DICE ;
					for (int i = Blue_4 ; i <= Blue_4 + DICE ; i++)
					{
						if (i == 52)
						Blue_4++ ;

						if (i == 58 and Blue_4 + DICE <= 58)
						Blue_Score += 15 ;
					}
					Blue_4 = Blue_4 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Blue[3][Blue_4][0] == Array_Red[0][Red_1][0] and Array_Blue[3][Blue_4][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Blue[3][Blue_4][0] == Array_Red[1][Red_2][0] and Array_Blue[3][Blue_4][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Red[2][Red_3][0] and Array_Blue[3][Blue_4][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Red[3][Red_4][0] and Array_Blue[3][Blue_4][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[0][Yellow_1][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[1][Yellow_2][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[2][Yellow_3][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Yellow[3][Yellow_4][0] and Array_Blue[3][Blue_4][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[0][Green_1][0] and Array_Blue[3][Blue_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Blue_kill++ ;
					Blue_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[1][Green_2][0] and Array_Blue[3][Blue_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[2][Green_3][0] and Array_Blue[3][Blue_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Blue[3][Blue_4][0] == Array_Green[3][Green_4][0] and Array_Blue[3][Blue_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Blue_kill++ ;
						Blue_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Blue_kill >= 1 and Blue_4 == 52)
				{
					Blue_kill_52 = 52 ;
				}

				if (Blue_kill_52 == 52 and Blue_4 != 52)
				{
					Blue_4 = Blue_4 - 52 - 1 ;
					
					Blue_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				       	if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Red[0][Red_1][0] 
						and Array_Blue[3][i][1] == Array_Red[0][Red_1][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Red[1][Red_2][0] 
						and Array_Blue[3][i][1] == Array_Red[1][Red_2][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Red[1][Red_3][0] 
						and Array_Blue[3][i][1] == Array_Red[1][Red_3][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Yellow[0][Yellow_1][0]
						and Array_Blue[3][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Blue[3][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Blue[3][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Blue[3][i][1] == Array_Green[0][Green_1][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Blue[3][i][1] == Array_Green[1][Green_2][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Blue_4 ; i >= Blue_4 - DICE ; i--)
					{
						if (Array_Blue[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Blue[3][i][1] == Array_Green[2][Green_3][1])
						{
							Blue_4 = Blue_4 - DICE ;
							Blue_Score -= DICE ;

							if (Blue_4 - DICE <= 0 and O_Blue > 7)
							Blue_4 = 52 + (Blue_4) ;

							else if (O_Blue >= 1 and O_Blue <= 7 and Blue_4 - DICE <= 0)
							Blue_4 = Blue_4 + O_Blue - 1 ;

							if (Blue_kill > 0 and Blue_4 + DICE >= 52)
							Blue_4 -= 1 ;

							if (Blue_kill > 0 and i == 52)
							{
								Blue_4 = Blue_4 + DICE + 1 ;
								Blue_Score = Blue_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Blue + DICE) == Blue_1 or (O_Blue + DICE) == Blue_3 or (O_Blue + DICE) == Blue_4) and O_Blue != 0 
				and (O_Blue + DICE) != 58 and (O_Blue + DICE) != 1 and (O_Blue + DICE) != 9
				and (O_Blue + DICE) != 14 and (O_Blue + DICE) != 22 and (O_Blue + DICE) != 27 
				and (O_Blue + DICE) != 35 and (O_Blue + DICE) != 40 and (O_Blue + DICE) != 48)
				Blue_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}
	DrawCircle( Array_Blue[0][Blue_1][0] , Array_Blue[0][Blue_1][1] , 10 , colors[LIGHT_BLUE]);
	DrawCircle( Array_Blue[1][Blue_2][0] , Array_Blue[1][Blue_2][1] , 10 , colors[LIGHT_BLUE]);
	DrawCircle( Array_Blue[2][Blue_3][0] , Array_Blue[2][Blue_3][1] , 10 , colors[LIGHT_BLUE]);
	DrawCircle( Array_Blue[3][Blue_4][0] , Array_Blue[3][Blue_4][1] , 10 , colors[LIGHT_BLUE]);

	DrawString( Array_Blue[0][Blue_1][0] - 9 , Array_Blue[0][Blue_1][1] - 9 , "w" , colors[MIDNIGHT_BLUE]);
	DrawString( Array_Blue[1][Blue_2][0] - 6 , Array_Blue[1][Blue_2][1] - 7 , "a" , colors[MIDNIGHT_BLUE]);
	DrawString( Array_Blue[2][Blue_3][0] - 5 , Array_Blue[2][Blue_3][1] - 7 , "s" , colors[MIDNIGHT_BLUE]);
	DrawString( Array_Blue[3][Blue_4][0] - 8 , Array_Blue[3][Blue_4][1] - 10 , "d" , colors[MIDNIGHT_BLUE]);


	//Pieces of red House.
	Array_Red[0][0][0] = 337 + 17 ;
	Array_Red[0][0][1] = 290 + 17 ;
	Array_Red[1][0][0] = 390 + 17 ;
	Array_Red[1][0][1] = 290 + 17 ;
	Array_Red[2][0][0] = 337 + 17 ;
	Array_Red[2][0][1] = 238 + 17 ;
	Array_Red[3][0][0] = 390 + 17 ;
	Array_Red[3][0][1] = 238 + 17 ;

	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Red_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_1 != 0 and Red_1 <= 58)//For a roll less than 6
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Red = Red_1 ;

				Red_1 = Red_1 + DICE ;
		
				if (Red_1 <= 58)
				{
					Red_Score += DICE ;
				}
				
				//boundary checks for ludo pieces.			
				if (Red_kill == 0 and Red_1 > 52)
				{
					Red_1 = Red_1 - 52 ;
				}

				else if (Red_1 > 58 and Red_kill > 0)
				{	
					Red_1 = Red_1 - DICE ;
				}

				else if (Red_1 <= 58 and Red_kill > 0)
				{
					Red_1 = Red_1 - DICE ;
					for (int i = Red_1 ; i <= Red_1 + DICE ; i++)
					{
						if (i == 52)
						Red_1++ ;

						if (i == 58 and Red_1 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_1 = Red_1 + DICE ;
				}
				
				//Killing conditions
				if ((Array_Red[0][Red_1][0] == Array_Blue[0][Blue_1][0] and Array_Red[0][Red_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[1][Blue_2][0] and Array_Red[0][Red_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[2][Blue_3][0] and Array_Red[0][Red_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[3][Blue_4][0] and Array_Red[0][Red_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[0][Red_1][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[0][Red_1][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[0][Red_1][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[0][Red_1][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[0][Green_1][0] and Array_Red[0][Red_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Green[1][Green_2][0] and Array_Red[0][Red_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[2][Green_3][0] and Array_Red[0][Red_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[3][Green_4][0] and Array_Red[0][Red_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_1 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_1 != 52)
				{
					Red_1 = Red_1 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}


				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}


				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[0][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[0][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[0][i][1] == Array_Green[0][Green_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[0][i][1] == Array_Green[1][Green_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red <= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[0][i][1] == Array_Green[2][Green_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_3 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}


	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Red_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_2 != 0 and Red_2 <= 58)//For a roll less than 6
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Red = Red_2 ;

				Red_2 = Red_2 + DICE ;
		
				if (Red_2 <= 58)
				{
					Red_Score += DICE ;
				}
				
				//Array boundary check			
				if (Red_kill == 0 and Red_2 > 52)
				{
					Red_2 = Red_2 - 52 ;
				}

				else if (Red_2 > 58 and Red_kill > 0)
				{	
					Red_2 = Red_2 - DICE ;
				}

				else if (Red_2 <= 58 and Red_kill > 0)
				{
					Red_2 = Red_2 - DICE ;
					for (int i = Red_2 ; i <= Red_2 + DICE ; i++)
					{
						if (i == 52)
						Red_2++ ;

						if (i == 58 and Red_2 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_2 = Red_2 + DICE ;
				}

				if ((Array_Red[1][Red_2][0] == Array_Blue[0][Blue_1][0] and Array_Red[1][Red_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[1][Blue_2][0] and Array_Red[1][Red_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[2][Blue_3][0] and Array_Red[1][Red_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[3][Blue_4][0] and Array_Red[1][Red_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[1][Red_2][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[1][Red_2][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[1][Red_2][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[1][Red_2][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[0][Green_1][0] and Array_Red[1][Red_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Green[1][Green_2][0] and Array_Red[1][Red_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[2][Green_3][0] and Array_Red[1][Red_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[3][Green_4][0] and Array_Red[1][Red_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_2 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_2 != 52)
				{
					Red_2 = Red_2 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}


				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}


				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[1][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[1][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[1][i][1] == Array_Green[0][Green_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[1][i][1] == Array_Green[1][Green_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[1][i][1] == Array_Green[2][Green_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_3 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}

	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Red_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_3 != 0 and Red_3 <= 58)//For a roll less than 6
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Red = Red_3 ;

				Red_3 = Red_3 + DICE ;

				if (Red_3 <= 58)
				{
					Red_Score = Red_Score + DICE ;
				}

				//Array boundary check			
				if (Red_kill == 0 and Red_3 > 52)
				{
					Red_3 = Red_3 - 52 ;
				}

				else if (Red_3 > 58 and Red_kill > 0)
				{
					
					Red_3 = Red_3 - DICE ;
				}

				else if (Red_3 <= 58 and Red_kill > 0)
				{
					Red_3 = Red_3 - DICE ;
					for (int i = Red_3 ; i <= Red_3 + DICE ; i++)
					{
						if (i == 52)
						Red_3++ ;

						if (i == 58 and Red_3 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_3 = Red_3 + DICE ;
				}

				if ((Array_Red[2][Red_3][0] == Array_Blue[0][Blue_1][0] and Array_Red[2][Red_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[1][Blue_2][0] and Array_Red[2][Red_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[2][Blue_3][0] and Array_Red[2][Red_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[3][Blue_4][0] and Array_Red[2][Red_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[2][Red_3][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[2][Red_3][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[2][Red_3][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[2][Red_3][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[0][Green_1][0] and Array_Red[2][Red_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Green[1][Green_2][0] and Array_Red[2][Red_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[2][Green_3][0] and Array_Red[2][Red_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[3][Green_4][0] and Array_Red[2][Red_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_3 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_3 != 52)
				{
					Red_3 = Red_3 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[2][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[2][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[2][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[2][i][1] == Array_Green[0][Green_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[2][i][1] == Array_Green[1][Green_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[2][i][1] == Array_Green[2][Green_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}
	
	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Red_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_4 != 0 and Red_4 <= 58)//For a roll less than 6
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Red = Red_4 ;

				Red_4 = Red_4 + DICE ;

				if (Red_4 <= 58)
				{
					Red_Score = Red_Score + DICE ;
				}

				//Array boundary check			
				if (Red_kill == 0 and Red_4 > 52)
				{
					Red_4 = Red_4 - 52 ;
				}

				else if (Red_4 > 58 and Red_kill > 0)
				{
					
					Red_4 = Red_4 - DICE ;
				}

				else if (Red_4 <= 58 and Red_kill > 0)
				{
					Red_4 = Red_4 - DICE ;
					for (int i = Red_4 ; i <= Red_4 + DICE ; i++)
					{
						if (i == 52)
						Red_4++ ;

						if (i == 58 and Red_4 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_4 = Red_4 + DICE ;
				}

				if ((Array_Red[3][Red_4][0] == Array_Blue[0][Blue_1][0] and Array_Red[3][Red_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[1][Blue_2][0] and Array_Red[3][Red_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[2][Blue_3][0] and Array_Red[3][Red_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[3][Blue_4][0] and Array_Red[3][Red_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[3][Red_4][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[3][Red_4][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[3][Red_4][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[3][Red_4][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[0][Green_1][0] and Array_Red[3][Red_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Green[1][Green_2][0] and Array_Red[3][Red_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[2][Green_3][0] and Array_Red[3][Red_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[3][Green_4][0] and Array_Red[3][Red_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_4 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_4 != 52)
				{
					Red_4 = Red_4 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[3][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[3][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[3][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[3][i][1] == Array_Green[0][Green_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[3][i][1] == Array_Green[1][Green_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[3][i][1] == Array_Green[2][Green_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_3) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE_NET = DICE_NET - DICE ;
			}

		}

	}
	DrawCircle( Array_Red[0][Red_1][0] , Array_Red[0][Red_1][1] , 10 , colors[DARK_RED]);
        DrawCircle( Array_Red[1][Red_2][0] , Array_Red[1][Red_2][1] , 10 , colors[DARK_RED]);
        DrawCircle( Array_Red[2][Red_3][0] , Array_Red[2][Red_3][1] , 10 , colors[DARK_RED]);	
        DrawCircle( Array_Red[3][Red_4][0] , Array_Red[3][Red_4][1] , 10 , colors[DARK_RED]);

	DrawString( Array_Red[0][Red_1][0] - 8 , Array_Red[0][Red_1][1] - 9 , "w" , colors[INDIAN_RED]);
	DrawString( Array_Red[1][Red_2][0] - 6 , Array_Red[1][Red_2][1] - 7 , "a" , colors[INDIAN_RED]);
	DrawString( Array_Red[2][Red_3][0] - 5 , Array_Red[2][Red_3][1] - 7 , "s" , colors[INDIAN_RED]);
	DrawString( Array_Red[3][Red_4][0] - 8 , Array_Red[3][Red_4][1] - 10 , "d" , colors[INDIAN_RED]);

	//Pieces of Yellow house
	Array_Yellow[0][0][0] = 577 + 17 ;
	Array_Yellow[0][0][1] = 475 + 17 ;
	Array_Yellow[1][0][0] = 627 + 17 ;
	Array_Yellow[1][0][1] = 475 + 17 ;
	Array_Yellow[2][0][0] = 577 + 17 ;
	Array_Yellow[2][0][1] = 528 + 17 ;
	Array_Yellow[3][0][0] = 627 + 17 ;
	Array_Yellow[3][0][1] = 528 + 17 ;

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Yellow_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_1 != 0 and Yellow_1 <= 58)//
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Yellow = Yellow_1 ;

				Yellow_1 = Yellow_1 + DICE ;

				if (Yellow_1 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_1 > 52)
				{
					Yellow_1 = Yellow_1 - 52 ;
				}

				else if (Yellow_1 > 58 and Yellow_kill > 0 and Yellow_1 != 52)
				{
					Yellow_1 = Yellow_1 - DICE ;
				}

				else if (Yellow_1 <= 58 and Yellow_kill > 0)
				{
					Yellow_1 = Yellow_1 - DICE ;
					for (int i = Yellow_1 ; i <= Yellow_1 + DICE ; i++)
					{
						if (i == 52)
						Yellow_1++ ;

						if (i == 58 and Yellow_1 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_1 = Yellow_1 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[0][Yellow_1][0] == Array_Red[0][Red_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[1][Red_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[2][Red_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[3][Red_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[0][Green_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[1][Green_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[2][Green_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[3][Green_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_1 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_1 != 52)
				{
					Yellow_1 = Yellow_1 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[0][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[0][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[0][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 13)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 13 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 - O_Yellow + 1 ;
	
							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							else if (DICE == 1)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[0][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[0][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[0][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_2 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Yellow_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_2 != 0 and Yellow_2 <= 58)//
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Yellow = Yellow_2 ;

				Yellow_2 = Yellow_2 + DICE ;

				if (Yellow_2 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_2 > 52)
				{
					Yellow_2 = Yellow_2 - 52 ;
				}

				else if (Yellow_2 > 58 and Yellow_kill > 0 and Yellow_2 != 52)
				{
					Yellow_2 = Yellow_2 - DICE ;
				}

				else if (Yellow_2 <= 58 and Yellow_kill > 0)
				{
					Yellow_2 = Yellow_2 - DICE ;
					for (int i = Yellow_2 ; i <= Yellow_2 + DICE ; i++)
					{
						if (i == 52)
						Yellow_2++ ;

						if (i == 58 and Yellow_2 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_2 = Yellow_2 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[1][Yellow_2][0] == Array_Red[0][Red_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[1][Red_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[2][Red_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[3][Red_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[0][Green_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[1][Green_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[2][Green_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[3][Green_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_2 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_2 != 52)
				{
					Yellow_2 = Yellow_2 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[1][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[1][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[1][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[1][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[1][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[1][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_2 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Yellow_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_3 != 0 and Yellow_3 <= 58)//
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Yellow = Yellow_3 ;

				Yellow_3 = Yellow_3 + DICE ;

				if (Yellow_3 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_3 > 52)
				{
					Yellow_3 = Yellow_3 - 52 ;
				}

				else if (Yellow_3 > 58 and Yellow_kill > 0 and Yellow_3 != 52)
				{
					Yellow_3 = Yellow_3 - DICE ;
				}

				else if (Yellow_3 <= 58 and Yellow_kill > 0)
				{
					Yellow_3 = Yellow_3 - DICE ;
					for (int i = Yellow_3 ; i <= Yellow_3 + DICE ; i++)
					{
						if (i == 52)
						Yellow_3++ ;

						if (i == 58 and Yellow_3 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_3 = Yellow_3 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[2][Yellow_3][0] == Array_Red[0][Red_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[1][Red_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[2][Red_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[3][Red_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[0][Green_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[1][Green_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[2][Green_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[3][Green_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_3 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_3 != 52)
				{
					Yellow_3 = Yellow_3 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[2][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[2][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[2][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[2][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[2][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[2][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 3 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Yellow_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_4 != 0 and Yellow_4 <= 58)//
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Yellow = Yellow_4 ;

				Yellow_4 = Yellow_4 + DICE ;

				if (Yellow_4 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_4 > 52)
				{
					Yellow_4 = Yellow_4 - 52 ;
				}

				else if (Yellow_4 > 58 and Yellow_kill > 0 and Yellow_4 != 52)
				{
					Yellow_4 = Yellow_4 - DICE ;
				}

				else if (Yellow_4 <= 58 and Yellow_kill > 0)
				{
					Yellow_4 = Yellow_4 - DICE ;
					for (int i = Yellow_4 ; i <= Yellow_4 + DICE ; i++)
					{
						if (i == 52)
						Yellow_4++ ;

						if (i == 58 and Yellow_4 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_4 = Yellow_4 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[3][Yellow_4][0] == Array_Red[0][Red_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[1][Red_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[2][Red_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[3][Red_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[0][Green_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[1][Green_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[2][Green_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[3][Green_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_4 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_4 != 52)
				{
					Yellow_4 = Yellow_4 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[3][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[3][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[3][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[3][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[3][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[3][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_4 or (O_Yellow + DICE) == Yellow_4 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}
	DrawCircle( Array_Yellow[0][Yellow_1][0] , Array_Yellow[0][Yellow_1][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[1][Yellow_2][0] , Array_Yellow[1][Yellow_2][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[2][Yellow_3][0] , Array_Yellow[2][Yellow_3][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[3][Yellow_4][0] , Array_Yellow[3][Yellow_4][1] , 10 , colors[YELLOW]);
	
	DrawString( Array_Yellow[0][Yellow_1][0] - 8 , Array_Yellow[0][Yellow_1][1] - 9 , "w" , colors[ORANGE]);
	DrawString( Array_Yellow[1][Yellow_2][0] - 6 , Array_Yellow[1][Yellow_2][1] - 7 , "a" , colors[ORANGE]);
	DrawString( Array_Yellow[2][Yellow_3][0] - 5 , Array_Yellow[2][Yellow_3][1] - 7 , "s" , colors[ORANGE]);
	DrawString( Array_Yellow[3][Yellow_4][0] - 8 , Array_Yellow[3][Yellow_4][1] - 10 , "d" , colors[ORANGE]);

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	
	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Turns == 1 and Red_Win != 0)
	{
		Turns++ ;
	}

	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Turns == 1 and Red_Win == 0)
	{
		Red_Win ++ ;
		Win++ ;
	}

	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red_Win == Win)
	{
		DrawString (300 , 150 , "Red has won the game" , colors[WHITE]) ;
		Red_Win++ ;
		Win++ ;
	}

	else if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red_Win != Win)
	DrawString (300 , 150 , "Red has finished the game" , colors[WHITE]) ;

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Turns == 1 and Blue_Win != 0)
	{
		Turns++ ;
	}

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Turns == 1 and Blue_Win == 0)
	{
		Blue_Win ++ ;
		Win++ ;
	}

	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Blue_Win == Win)
	{
		DrawString (300 , 125 , "Blue has won the game" , colors[WHITE]) ;
		Blue_Win++ ;
		Win++ ;
	}

	else if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Blue_Win != Win)
	DrawString (300 , 125 , "Blue has finished the game" , colors[WHITE]) ;

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Turns == 1 and Yellow_Win != 0)
	{
		Turns -= 2 ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Turns == 1 and Yellow_Win == 0)
	{
		Yellow_Win ++ ;
		Win++ ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow_Win == Win)
	{
		DrawString (300 , 100 , "Yellow has won the game" , colors[WHITE]) ;
		Yellow_Win++ ;
		Win++ ;
	}

	else if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow_Win != Win)
	DrawString (300 , 100 , "Yellow has finished the game" , colors[WHITE]) ;

	DrawSquare( 750 , 250 , 30 , colors[GRAY]);//Square for dice.

	//Dice faces.
	if (DICE == 1)
	  DrawCircle(765 , 265 , 3 , colors[RED]) ;

	else if (DICE == 2)
	{
		DrawCircle(770 , 265 , 3 , colors[RED]) ;
		DrawCircle(760 , 265 , 3 , colors[RED]) ;
        }

	else if (DICE == 3)
        {
		DrawCircle(775 , 275 , 3 , colors[RED]) ;
		DrawCircle(765 , 265 , 3 , colors[RED]) ;
		DrawCircle(755 , 255 , 3 , colors[RED]) ;
        }

	else if (DICE == 4)
        {
		DrawCircle(770 , 270 , 3 , colors[RED]) ;
		DrawCircle(760 , 270 , 3 , colors[RED]) ;
		DrawCircle(770 , 260 , 3 , colors[RED]) ;
		DrawCircle(760 , 260 , 3 , colors[RED]) ;
        }

	else if (DICE == 5)
	{
		DrawCircle(755 , 275 , 3 , colors[RED]) ;
		DrawCircle(775 , 275 , 3 , colors[RED]) ;
		DrawCircle(765 , 265 , 3 , colors[RED]) ;
		DrawCircle(755 , 255 , 3 , colors[RED]) ;
		DrawCircle(775 , 255 , 3 , colors[RED]) ;
        }


	else if (DICE == 6)
	    {
		DrawCircle(770 , 275 , 3 , colors[RED]) ;
		DrawCircle(760 , 275 , 3 , colors[RED]) ;
		DrawCircle(770 , 265 , 3 , colors[RED]) ;
		DrawCircle(760 , 265 , 3 , colors[RED]) ;
		DrawCircle(770 , 255 , 3 , colors[RED]) ;
		DrawCircle(760 , 255 , 3 , colors[RED]) ;
	    }

	if (Turns == 1 or Turns == 0)
	DrawSquare (100 , 300 , 30 , colors[RED]) ;

	else if (Turns ==  2)
	DrawSquare (100 , 300 , 30 , colors[BLUE]) ;

	else if (Turns ==  3 or 4)
	DrawSquare (100 , 300 , 30 , colors[OLIVE]) ;

	//For storing score in file.
	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Red_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Red_Score ;
				Names_1 [i] = Player_Names [0] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Red_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Red++ ;
	}
	
	if (Blue_1 == 58 and Blue_2 == 58 and Blue_3 == 58 and Blue_4 == 58 and Blue == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Blue_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Blue_Score ;
				Names_1 [i] = Player_Names [1] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Blue_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Blue++ ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Yellow_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Yellow_Score ;
				Names_1 [i] = Player_Names [2] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Yellow_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Yellow++ ;
	}	
		DrawString( 0 , 800 , "RED" , colors[MINT_CREAM]) ;
		DrawString( 350 , 800 , "BLUE" , colors[MINT_CREAM]) ;
		DrawString( 700 , 800 , "YELLOW" , colors[MINT_CREAM]) ;
	
		DrawString( 0 , 775 , Player_Names [0] + " Score = " + to_string (Red_Score), colors[MINT_CREAM]) ;
		DrawString( 350 , 775 , Player_Names [1] + " Score = " + to_string (Blue_Score), colors[MINT_CREAM]) ;
		DrawString( 700 , 775 , Player_Names [2] + " Score = " + to_string (Yellow_Score), colors[MINT_CREAM]) ;
		buttons = 0 ;

		if (Red_Win > 0 and Blue_Win > 0 and Yellow_Win > 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}

		if (Red_Win > 0 and Blue_Win > 0 and Yellow_kill == 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}

		if (Red_Win > 0 and Blue_kill == 0 and Yellow_Win > 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}

		if (Red_kill == 0 and Blue_Win > 0 and Yellow_Win > 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}

	}
	}

	//For game of 2 players
	if (BUTTONS == 55)
	{
	if (screen == 3)
	{
	glClearColor(0/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour

	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//DrawString(425 , 750 , cin.getline (str) , colors [MISTY_ROSE]) ;
	int x , y ;

	//Arrays for storing positions of ludo pieces 
	int Array_Red[4][59][2] ;
	int Array_Blue[4][59][2] ;
	int Array_Yellow[4][59][2] ;
	int Array_Green[4][59][2] ;
        //Main Board
	DrawSquare( 300 , 200 , 400 , colors[GRAY]);

        //Player Houses Squares
        DrawSquare( 300 , 438 , 162 , colors[BLUE]);
        DrawSquare( 538 , 438 , 162 , colors[OLIVE]);
        DrawSquare( 300 , 200 , 162 , colors[RED]);
        DrawSquare( 538 , 200 , 162 , colors[GREEN]);

        //Blue House Squares
        DrawSquare( 320 , 458 , 122 , colors[WHITE]);
        DrawSquare( 337 , 475 , 35 , colors[BLUE]);
        DrawSquare( 390 , 475 , 35 , colors[BLUE]);
        DrawSquare( 337 , 528 , 35 , colors[BLUE]);
        DrawSquare( 390 , 528 , 35 , colors[BLUE]);

        //Yellow House Squares
        DrawSquare( 558 , 458 , 122 , colors[WHITE]);
        DrawSquare( 577 , 475 , 35 , colors[OLIVE]);
        DrawSquare( 627 , 475 , 35 , colors[OLIVE]);
        DrawSquare( 577 , 528 , 35 , colors[OLIVE]);
        DrawSquare( 627 , 528 , 35 , colors[OLIVE]);

        //RED House Squares
        DrawSquare( 320 , 220 , 122 , colors[WHITE]);
        DrawSquare( 337 , 290 , 35 , colors[RED]);
        DrawSquare( 390 , 290 , 35 , colors[RED]);
        DrawSquare( 337 , 238 , 35 , colors[RED]);
        DrawSquare( 390 , 238 , 35 , colors[RED]);

        //Green House Squares
        DrawSquare( 558 , 220 , 122 , colors[WHITE]);
        DrawSquare( 577 , 290 , 35 , colors[GREEN]);
        DrawSquare( 627 , 290 , 35 , colors[GREEN]);
        DrawSquare( 577 , 238 , 35 , colors[GREEN]);
        DrawSquare( 627 , 238 , 35 , colors[GREEN]);

	//Mid houses Square.
        DrawSquare( 461 , 362 , 78 , colors[VIOLET]);
	DrawTriangle( 461 , 362 , 500 , 401 , 539 , 362 , colors[RED]);
	DrawTriangle( 461 , 439 , 500 , 401 , 539 , 439 , colors[OLIVE]);
	DrawTriangle( 461 , 362 , 500 , 401 , 461 , 439 , colors[BLUE]);
	DrawTriangle( 539 , 362 , 500 , 401 , 539 , 439 , colors[GREEN]);
	DrawLine( 461 , 362 , 539 , 439 , 0 , colors[BLACK]);//Diagonal boundary line
	DrawLine( 539 , 362 , 461 , 439 , 0 , colors[BLACK]);//Diagonal boundary line

	//Squares between red and green houses

	DrawSquare( 461 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 228 , 27 , colors[RED]) ;
	DrawSquare( 461 , 254 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 282 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 309 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 335 , 27 , colors[WHITE]) ;

	DrawSquare( 487 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 487 , 228 , 27 , colors[RED]) ;
	DrawSquare( 487 , 254 , 27 , colors[RED]) ;
	DrawSquare( 487 , 282 , 27 , colors[RED]) ;
	DrawSquare( 487 , 309 , 27 , colors[RED]) ;
	DrawSquare( 487 , 335 , 27 , colors[RED]) ;

	DrawSquare( 513 , 201 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 228 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 254 , 27 , colors[GRAY]) ;
	DrawSquare( 513 , 282 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 309 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 335 , 27 , colors[WHITE]) ;
	//Horizontal lines between red and green houses
        DrawLine( 461 , 227 ,  538, 227 , 0 , colors[BLACK] );
        DrawLine( 461 , 254 ,  538, 254 , 0 , colors[BLACK] );
	DrawLine( 461 , 281 ,  538, 281 , 0 , colors[BLACK] );
	DrawLine( 461 , 308 ,  538, 308 , 0 , colors[BLACK] );
	DrawLine( 461 , 335 ,  538, 335 , 0 , colors[BLACK] );
	DrawLine( 461 , 361 ,  538, 361 , 0 , colors[BLACK] );
	//Vertical lines between red and green houses
	DrawLine( 461 , 200 ,  461, 362 , 0 , colors[BLACK] );
	DrawLine( 487 , 200 ,  487, 362 , 0 , colors[BLACK] );
	DrawLine( 513 , 200 ,  513, 362 , 0 , colors[BLACK] );
	DrawLine( 539 , 200 ,  539, 362 , 0 , colors[BLACK] );

	//Squares between yellow and blue houses

	DrawSquare( 460 , 439 , 28 , colors[WHITE]) ;
	DrawSquare( 461 , 468 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 494 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 522 , 27 , colors[GRAY]) ;
	DrawSquare( 461 , 548 , 27 , colors[WHITE]) ;
	DrawSquare( 461 , 574 , 27 , colors[WHITE]) ;

	DrawSquare( 486 , 439 , 28 , colors[OLIVE]) ;
	DrawSquare( 487 , 468 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 494 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 522 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 548 , 27 , colors[OLIVE]) ;
	DrawSquare( 487 , 574 , 27 , colors[WHITE]) ;

	DrawSquare( 512 , 439 , 28 , colors[WHITE]) ;
	DrawSquare( 513 , 468 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 494 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 522 , 27 , colors[WHITE]) ;
	DrawSquare( 513 , 548 , 27 , colors[OLIVE]) ;
	DrawSquare( 513 , 574 , 27 , colors[WHITE]) ;
	//Horizontal lines between yellow and blue houses
	DrawLine( 461 , 439 ,  538, 439 , 0 , colors[BLACK] );
	DrawLine( 461 , 467 ,  538, 467 , 0 , colors[BLACK] );
	DrawLine( 461 , 494 ,  538, 494 , 0 , colors[BLACK] );
	DrawLine( 461 , 521 ,  538, 521 , 0 , colors[BLACK] );
	DrawLine( 461 , 548 ,  538, 548 , 0 , colors[BLACK] );
	DrawLine( 461 , 575 ,  538, 575 , 0 , colors[BLACK] );
	//Vertical lines between yellow and blue houses
	DrawLine( 461 , 438 ,  461, 600 , 0 , colors[BLACK] );
	DrawLine( 487 , 438 ,  487, 600 , 0 , colors[BLACK] );
	DrawLine( 513 , 438 ,  513, 600 , 0 , colors[BLACK] );
	DrawLine( 539 , 438 ,  539, 600 , 0 , colors[BLACK] );

	//Squares between red and blue houses

	DrawSquare( 301 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 355 , 362 , 27 , colors[GRAY]) ;
	DrawSquare( 382 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 409 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 435 , 362 , 27 , colors[WHITE]) ;

	DrawSquare( 301 , 388 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 355 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 382 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 409 , 388 , 27 , colors[BLUE]) ;
	DrawSquare( 435 , 388 , 27 , colors[BLUE]) ;

	DrawSquare( 301 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 328 , 413 , 27 , colors[BLUE]) ;
	DrawSquare( 355 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 382 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 409 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 435 , 413 , 27 , colors[WHITE]) ;
	//Vertical lines between red and blue houses
        DrawLine( 328 , 361 ,  328, 438 , 0 , colors[BLACK] );
        DrawLine( 355 , 361 ,  355, 438 , 0 , colors[BLACK] );
	DrawLine( 382 , 361 ,  382, 438 , 0 , colors[BLACK] );
	DrawLine( 409 , 361 ,  409, 438 , 0 , colors[BLACK] );
	DrawLine( 436 , 361 ,  436, 438 , 0 , colors[BLACK] );
	DrawLine( 461 , 361 ,  461, 438 , 0 , colors[BLACK] );
	//Horizontal lines between red and blue houses
	DrawLine( 300 , 361 ,  461, 361 , 0 , colors[BLACK] );
	DrawLine( 300 , 387 ,  461, 387 , 0 , colors[BLACK] );
	DrawLine( 300 , 413 ,  461, 413 , 0 , colors[BLACK] );
	DrawLine( 300 , 439 ,  461, 439 , 0 , colors[BLACK] );
	
	//Squares between yellow and green houses

	DrawSquare( 539 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 566 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 593 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 620 , 362 , 27 , colors[WHITE]) ;
	DrawSquare( 647 , 362 , 27 , colors[GREEN]) ;
	DrawSquare( 674 , 362 , 27 , colors[WHITE]) ;

	DrawSquare( 539 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 566 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 593 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 620 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 647 , 388 , 27 , colors[GREEN]) ;
	DrawSquare( 674 , 388 , 27 , colors[WHITE]) ;

	DrawSquare( 539 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 566 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 593 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 620 , 413 , 27 , colors[GRAY]) ;
	DrawSquare( 647 , 413 , 27 , colors[WHITE]) ;
	DrawSquare( 674 , 413 , 27 , colors[WHITE]) ;


	//Vertical lines between yellow and green houses
        DrawLine( 539 , 361 ,  539, 438 , 0 , colors[BLACK] );
        DrawLine( 566 , 361 ,  566, 438 , 0 , colors[BLACK] );
	DrawLine( 593 , 361 ,  593, 438 , 0 , colors[BLACK] );
	DrawLine( 620 , 361 ,  620, 438 , 0 , colors[BLACK] );
	DrawLine( 647 , 361 ,  647, 438 , 0 , colors[BLACK] );
	DrawLine( 674 , 361 ,  674, 438 , 0 , colors[BLACK] );
	//Horizontal lines between yellow and green houses
	DrawLine( 539 , 361 ,  700, 361 , 0 , colors[BLACK] );
	DrawLine( 539 , 387 ,  700, 387 , 0 , colors[BLACK] );
	DrawLine( 539 , 413 ,  700, 413 , 0 , colors[BLACK] );
	DrawLine( 539 , 439 ,  700, 439 , 0 , colors[BLACK] );


	//Borderlines
	DrawLine( 300 , 200 ,  700, 200 , 0 , colors[BLACK] );
	DrawLine( 300 , 200 ,  300, 600 , 0 , colors[BLACK] );
	DrawLine( 300 , 600 ,  700, 600 , 0 , colors[BLACK] );
	DrawLine( 700 , 200 ,  700, 600 , 0 , colors[BLACK] );
	//DrawSquare( 250 , 250 ,20,colors[WHITE]); 
	//Display Score
	//Spider
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	
	//Storing positions for red house.

        for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j <= 5)
						Array_Red[i][j][k] = 473 ;
					
					else if (j <= 11)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 13)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k];

					else if (j <= 18)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 24)
					{
						if (j == 19)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
						
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

					else if (j <= 26)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 31)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 37)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 39)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 44)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 50)
					{
						if (j == 45)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;
	
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}
					else if (j <= 52)
					Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 58)
					{
						if (j == 53)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

				}

				else if (k == 1)
				{
					if (j <= 5)
					{
						if (j == 1)
						Array_Red[i][j][k] = 228 + 17 ;
						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
					}

					else if (j <= 11)
					{
						if (j == 6)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

						else
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					}

					else if (j <= 13)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 18)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 24)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;

					else if (j <= 26)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
					
					else if (j <= 31)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 37)
						{
							if (j == 32)
							Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

							else
							Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;
						}

					else if (j <= 39)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 44)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 50)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] - 26 ;

					else if (j <= 52)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] ;

					else if (j <= 58)
						Array_Red[i][j][k] = Array_Red[i][j - 1][k] + 26 ;
				}
			}
		}
	}

	//Storing positions for yellow house
	
	for (int i = 0 ; i < 4 ; i++)
	{
		for (int j = 1 ; j < 59 ; j++)
		{
			for (int k = 0 ; k < 2 ; k++)
			{
				if (k == 0)
				{
					if (j <= 5)
					Array_Yellow[i][j][k] = Array_Red [i][27][k] ; 

					else if (j <= 11)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;	
										
					else if (j <= 13)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 19)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 24)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 26)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 31)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 37)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 39)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 45)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 50)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 52)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j == 53)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 58)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;
				}

				else if (k == 1)
				{
					if (j == 1)
					Array_Yellow[i][j][k] = Array_Red [i][27][k] ;
 
					else if (j <= 6)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;
				
					else if (j <= 11)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 13)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 18)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 24)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;

					else if (j <= 26)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 32)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 37)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 39)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 44)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;

					else if (j <= 50)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] + 26 ;

					else if (j <= 52)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] ;
	
					else if (j <= 58)
						Array_Yellow[i][j][k] = Array_Yellow[i][j - 1][k] - 26 ;
				}
			}
		}
	}	

	if (DICE_NET == 18)
	{
		DICE_NET = 0 ;
		DICE_COUNT == 0 ;
	}

	//Pieces of red House.
	Array_Red[0][0][0] = 337 + 17 ;
	Array_Red[0][0][1] = 290 + 17 ;
	Array_Red[1][0][0] = 390 + 17 ;
	Array_Red[1][0][1] = 290 + 17 ;
	Array_Red[2][0][0] = 337 + 17 ;
	Array_Red[2][0][1] = 238 + 17 ;
	Array_Red[3][0][0] = 390 + 17 ;
	Array_Red[3][0][1] = 238 + 17 ;

	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Red_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_1 != 0 and Red_1 <= 58)//For a roll less than 6
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Red = Red_1 ;

				Red_1 = Red_1 + DICE ;
		
				if (Red_1 <= 58)
				{
					Red_Score += DICE ;
				}
				
				//boundary checks for ludo pieces.			
				if (Red_kill == 0 and Red_1 > 52)
				{
					Red_1 = Red_1 - 52 ;
				}

				else if (Red_1 > 58 and Red_kill > 0)
				{	
					Red_1 = Red_1 - DICE ;
				}

				else if (Red_1 <= 58 and Red_kill > 0)
				{
					Red_1 = Red_1 - DICE ;
					for (int i = Red_1 ; i <= Red_1 + DICE ; i++)
					{
						if (i == 52)
						Red_1++ ;

						if (i == 58 and Red_1 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_1 = Red_1 + DICE ;
				}
				
				//Killing conditions
				if ((Array_Red[0][Red_1][0] == Array_Blue[0][Blue_1][0] and Array_Red[0][Red_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[1][Blue_2][0] and Array_Red[0][Red_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[2][Blue_3][0] and Array_Red[0][Red_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Blue[3][Blue_4][0] and Array_Red[0][Red_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[0][Red_1][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[0][Red_1][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[0][Red_1][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[0][Red_1][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[0][Green_1][0] and Array_Red[0][Red_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[0][Red_1][0] == Array_Green[1][Green_2][0] and Array_Red[0][Red_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[2][Green_3][0] and Array_Red[0][Red_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[0][Red_1][0] == Array_Green[3][Green_4][0] and Array_Red[0][Red_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_1 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_1 != 52)
				{
					Red_1 = Red_1 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}


				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}


				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[0][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[0][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[0][i][1] == Array_Green[0][Green_1][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[0][i][1] == Array_Green[1][Green_2][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red <= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_1 ; i >= Red_1 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[0][i][1] == Array_Green[2][Green_3][1])
						{
							Red_1 = Red_1 - DICE ;
							Red_Score -= DICE ;

							if (Red_1 - DICE <= 0 and O_Red > 7)
							Red_1 = 52 + (Red_1) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_1 - DICE <= 0)
							Red_1 = Red_1 + O_Red - 1 ;

							if (Red_kill > 0 and Red_1 + DICE >= 52)
							Red_1 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_1 = Red_1 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_3 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}


	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Red_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_2 != 0 and Red_2 <= 58)//For a roll less than 6
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Red = Red_2 ;

				Red_2 = Red_2 + DICE ;
		
				if (Red_2 <= 58)
				{
					Red_Score += DICE ;
				}
				
				//Array boundary check			
				if (Red_kill == 0 and Red_2 > 52)
				{
					Red_2 = Red_2 - 52 ;
				}

				else if (Red_2 > 58 and Red_kill > 0)
				{	
					Red_2 = Red_2 - DICE ;
				}

				else if (Red_2 <= 58 and Red_kill > 0)
				{
					Red_2 = Red_2 - DICE ;
					for (int i = Red_2 ; i <= Red_2 + DICE ; i++)
					{
						if (i == 52)
						Red_2++ ;

						if (i == 58 and Red_2 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_2 = Red_2 + DICE ;
				}

				if ((Array_Red[1][Red_2][0] == Array_Blue[0][Blue_1][0] and Array_Red[1][Red_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[1][Blue_2][0] and Array_Red[1][Red_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[2][Blue_3][0] and Array_Red[1][Red_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Blue[3][Blue_4][0] and Array_Red[1][Red_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[1][Red_2][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[1][Red_2][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[1][Red_2][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[1][Red_2][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[0][Green_1][0] and Array_Red[1][Red_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[1][Red_2][0] == Array_Green[1][Green_2][0] and Array_Red[1][Red_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[2][Green_3][0] and Array_Red[1][Red_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[1][Red_2][0] == Array_Green[3][Green_4][0] and Array_Red[1][Red_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_2 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_2 != 52)
				{
					Red_2 = Red_2 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}


				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}


				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[1][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[0][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[0][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[1][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[1][i][1] == Array_Green[0][Green_1][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[1][i][1] == Array_Green[1][Green_2][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_2 ; i >= Red_2 - DICE ; i--)
					{
						if (Array_Red[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[1][i][1] == Array_Green[2][Green_3][1])
						{
							Red_2 = Red_2 - DICE ;
							Red_Score -= DICE ;

							if (Red_2 - DICE <= 0 and O_Red > 7)
							Red_2 = 52 + (Red_2) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_2 - DICE <= 0)
							Red_2 = Red_2 + O_Red - 1 ;

							if (Red_kill > 0 and Red_2 + DICE >= 52)
							Red_2 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_2 = Red_2 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_3 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}

	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Red_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_3 != 0 and Red_3 <= 58)//For a roll less than 6
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Red = Red_3 ;

				Red_3 = Red_3 + DICE ;

				if (Red_3 <= 58)
				{
					Red_Score = Red_Score + DICE ;
				}

				//Array boundary check			
				if (Red_kill == 0 and Red_3 > 52)
				{
					Red_3 = Red_3 - 52 ;
				}

				else if (Red_3 > 58 and Red_kill > 0)
				{
					
					Red_3 = Red_3 - DICE ;
				}

				else if (Red_3 <= 58 and Red_kill > 0)
				{
					Red_3 = Red_3 - DICE ;
					for (int i = Red_3 ; i <= Red_3 + DICE ; i++)
					{
						if (i == 52)
						Red_3++ ;

						if (i == 58 and Red_3 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_3 = Red_3 + DICE ;
				}

				if ((Array_Red[2][Red_3][0] == Array_Blue[0][Blue_1][0] and Array_Red[2][Red_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[1][Blue_2][0] and Array_Red[2][Red_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[2][Blue_3][0] and Array_Red[2][Red_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Blue[3][Blue_4][0] and Array_Red[2][Red_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[2][Red_3][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[2][Red_3][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[2][Red_3][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[2][Red_3][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[0][Green_1][0] and Array_Red[2][Red_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[2][Red_3][0] == Array_Green[1][Green_2][0] and Array_Red[2][Red_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[2][Green_3][0] and Array_Red[2][Red_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[2][Red_3][0] == Array_Green[3][Green_4][0] and Array_Red[2][Red_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_3 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_3 != 52)
				{
					Red_3 = Red_3 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[2][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[2][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[2][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[2][i][1] == Array_Green[0][Green_1][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[2][i][1] == Array_Green[1][Green_2][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_3 ; i >= Red_3 - DICE ; i--)
					{
						if (Array_Red[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[2][i][1] == Array_Green[2][Green_3][1])
						{
							Red_3 = Red_3 - DICE ;
							Red_Score -= DICE ;

							if (Red_3 - DICE <= 0 and O_Red > 7)
							Red_3 = 52 + (Red_3) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_3 - DICE <= 0)
							Red_3 = Red_3 + O_Red - 1 ;

							if (Red_kill > 0 and Red_3 + DICE >= 52)
							Red_3 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_3 = Red_3 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_4) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE = 0 ;
			}

		}

	}
	
	if (Turns == 1 and iteration > 0 and DICE != 0)
	{
		if (DICE == 6 and Red_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Red_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Red_4 != 0 and Red_4 <= 58)//For a roll less than 6
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Red = Red_4 ;

				Red_4 = Red_4 + DICE ;

				if (Red_4 <= 58)
				{
					Red_Score = Red_Score + DICE ;
				}

				//Array boundary check			
				if (Red_kill == 0 and Red_4 > 52)
				{
					Red_4 = Red_4 - 52 ;
				}

				else if (Red_4 > 58 and Red_kill > 0)
				{
					
					Red_4 = Red_4 - DICE ;
				}

				else if (Red_4 <= 58 and Red_kill > 0)
				{
					Red_4 = Red_4 - DICE ;
					for (int i = Red_4 ; i <= Red_4 + DICE ; i++)
					{
						if (i == 52)
						Red_4++ ;

						if (i == 58 and Red_4 + DICE <= 58)
						Red_Score += 15 ;
					}
					Red_4 = Red_4 + DICE ;
				}

				if ((Array_Red[3][Red_4][0] == Array_Blue[0][Blue_1][0] and Array_Red[3][Red_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[1][Blue_2][0] and Array_Red[3][Red_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[2][Blue_3][0] and Array_Red[3][Red_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Blue[3][Blue_4][0] and Array_Red[3][Red_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[0][Yellow_1][0] and Array_Red[3][Red_4][1] == Array_Yellow[0][Yellow_1][1] and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 and Yellow_1 != 48 and Yellow_1 != Yellow_2 and Yellow_1 != Yellow_3 and Yellow_1 != Yellow_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Yellow_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[1][Yellow_2][0] and Array_Red[3][Red_4][1] == Array_Yellow[1][Yellow_2][1] and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 and Yellow_2 != 48 and Yellow_2 != Yellow_1 and Yellow_2 != Yellow_3 and Yellow_2 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[2][Yellow_3][0] and Array_Red[3][Red_4][1] == Array_Yellow[2][Yellow_3][1] and Yellow_3 != 1 and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 != Yellow_1 and Yellow_3 != Yellow_2 and Yellow_3 != Yellow_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Yellow[3][Yellow_4][0] and Array_Red[3][Red_4][1] == Array_Yellow[3][Yellow_4][1] and Yellow_4 != 1 and Yellow_4 != 9 and Yellow_4 != 14 and Yellow_4 != 22 and Yellow_4 != 27 and Yellow_4 != 35 and Yellow_4 != 40 and Yellow_4 != 48 and Yellow_4 != Yellow_1 and Yellow_4 != Yellow_2 and Yellow_4 != Yellow_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Yellow_4 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[0][Green_1][0] and Array_Red[3][Red_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Red_kill++ ;
					Red_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Red[3][Red_4][0] == Array_Green[1][Green_2][0] and Array_Red[3][Red_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[2][Green_3][0] and Array_Red[3][Red_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Red[3][Red_4][0] == Array_Green[3][Green_4][0] and Array_Red[3][Red_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Red_kill++ ;
						Red_Score += 10 ;
						Green_4 = 0 ;
					}

				//Block for kill on 52nd position.
				if (Red_kill >= 1 and Red_4 == 52)
				{
					Red_kill_52 = 52 ;
				}

				if (Red_kill_52 == 52 and Red_4 != 52)
				{
					Red_4 = Red_4 - 52 - 1 ;
					
					Red_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces.

				if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[0][Blue_1][0] 
						and Array_Red[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) and (Blue_2 != 0 and Blue_2 != 1 
				and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 
				and Blue_2 != 40 and Blue_2 != 48 and Blue_2 <= 52))
				{									
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Red[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{									
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Red[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_1 == Yellow_2 or Yellow_1 == Yellow_3 or Yellow_1 == Yellow_4) 
				and (Yellow_1 != 0 and Yellow_1 != 1 and Yellow_1 != 9 and Yellow_1 != 14 
				and Yellow_1 != 22 and Yellow_1 != 27 and Yellow_1 != 35 and Yellow_1 != 40 
				and Yellow_1 != 48 and Yellow_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[0][Yellow_1][0] 
						and Array_Red[3][i][1] == Array_Yellow[0][Yellow_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_2 == Yellow_3 or Yellow_2 == Yellow_4) 
				and (Yellow_2 != 0 and Yellow_2 != 1 and Yellow_2 != 9 and Yellow_2 != 14 
				and Yellow_2 != 22 and Yellow_2 != 27 and Yellow_2 != 35 and Yellow_2 != 40 
				and Yellow_2 != 48 and Yellow_2 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[1][Yellow_2][0] 
						and Array_Red[3][i][1] == Array_Yellow[1][Yellow_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Yellow_3 == Yellow_4) and (Yellow_3 != 0 and Yellow_3 != 1 
				and Yellow_3 != 9 and Yellow_3 != 14 and Yellow_3 != 22 and Yellow_3 != 27 
				and Yellow_3 != 35 and Yellow_3 != 40 and Yellow_3 != 48 and Yellow_3 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Yellow[2][Yellow_3][0] 
						and Array_Red[3][i][1] == Array_Yellow[2][Yellow_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Red[3][i][1] == Array_Green[0][Green_1][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Red[3][i][1] == Array_Green[1][Green_2][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Red_4 ; i >= Red_4 - DICE ; i--)
					{
						if (Array_Red[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Red[3][i][1] == Array_Green[2][Green_3][1])
						{
							Red_4 = Red_4 - DICE ;
							Red_Score -= DICE ;

							if (Red_4 - DICE <= 0 and O_Red > 7)
							Red_4 = 52 + (Red_4) ;

							else if (O_Red >= 1 and O_Red<= 7 and Red_4 - DICE <= 0)
							Red_4 = Red_4 + O_Red - 1 ;

							if (Red_kill > 0 and Red_4 + DICE >= 52)
							Red_4 -= 1 ;

							if (Red_kill > 0 and i == 52)
							{
								Red_4 = Red_4 + DICE + 1 ;
								Red_Score = Red_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Red + DICE) == Red_1 or (O_Red + DICE) == Red_2 or (O_Red + DICE) == Red_3) and O_Red != 0 
				and (O_Red + DICE) != 58 and (O_Red + DICE) != 1 and (O_Red + DICE) != 9
				and (O_Red + DICE) != 14 and (O_Red + DICE) != 22 and (O_Red + DICE) != 27 
				and (O_Red + DICE) != 35 and (O_Red + DICE) != 40 and (O_Red + DICE) != 48)
				Red_Score += 2 ;

				DICE_NET = DICE_NET - DICE ;
			}

		}

	}
	DrawCircle( Array_Red[0][Red_1][0] , Array_Red[0][Red_1][1] , 10 , colors[DARK_RED]);
        DrawCircle( Array_Red[1][Red_2][0] , Array_Red[1][Red_2][1] , 10 , colors[DARK_RED]);
        DrawCircle( Array_Red[2][Red_3][0] , Array_Red[2][Red_3][1] , 10 , colors[DARK_RED]);	
        DrawCircle( Array_Red[3][Red_4][0] , Array_Red[3][Red_4][1] , 10 , colors[DARK_RED]);

	DrawString( Array_Red[0][Red_1][0] - 8 , Array_Red[0][Red_1][1] - 9 , "w" , colors[INDIAN_RED]);
	DrawString( Array_Red[1][Red_2][0] - 6 , Array_Red[1][Red_2][1] - 7 , "a" , colors[INDIAN_RED]);
	DrawString( Array_Red[2][Red_3][0] - 5 , Array_Red[2][Red_3][1] - 7 , "s" , colors[INDIAN_RED]);
	DrawString( Array_Red[3][Red_4][0] - 8 , Array_Red[3][Red_4][1] - 10 , "d" , colors[INDIAN_RED]);

	//Pieces of Yellow house
	Array_Yellow[0][0][0] = 577 + 17 ;
	Array_Yellow[0][0][1] = 475 + 17 ;
	Array_Yellow[1][0][0] = 627 + 17 ;
	Array_Yellow[1][0][1] = 475 + 17 ;
	Array_Yellow[2][0][0] = 577 + 17 ;
	Array_Yellow[2][0][1] = 528 + 17 ;
	Array_Yellow[3][0][0] = 627 + 17 ;
	Array_Yellow[3][0][1] = 528 + 17 ;

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_1 == 0)
		{
			if (buttons == 87 or buttons == 119)
			{
				Yellow_1++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_1 != 0 and Yellow_1 <= 58)//
		{
			if (buttons == 87 or buttons == 119)
			{
				int O_Yellow = Yellow_1 ;

				Yellow_1 = Yellow_1 + DICE ;

				if (Yellow_1 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_1 > 52)
				{
					Yellow_1 = Yellow_1 - 52 ;
				}

				else if (Yellow_1 > 58 and Yellow_kill > 0 and Yellow_1 != 52)
				{
					Yellow_1 = Yellow_1 - DICE ;
				}

				else if (Yellow_1 <= 58 and Yellow_kill > 0)
				{
					Yellow_1 = Yellow_1 - DICE ;
					for (int i = Yellow_1 ; i <= Yellow_1 + DICE ; i++)
					{
						if (i == 52)
						Yellow_1++ ;

						if (i == 58 and Yellow_1 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_1 = Yellow_1 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[0][Yellow_1][0] == Array_Red[0][Red_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[1][Red_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[2][Red_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Red[3][Red_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[0][Green_1][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[1][Green_2][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[2][Green_3][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[0][Yellow_1][0] == Array_Green[3][Green_4][0] and Array_Yellow[0][Yellow_1][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_1 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_1 != 52)
				{
					Yellow_1 = Yellow_1 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[0][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[0][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[0][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[0][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 13)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 13 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 - O_Yellow + 1 ;
	
							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[0][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[0][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							else if (DICE == 1)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[0][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[0][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_1 ; i >= Yellow_1 - DICE ; i--)
					{
						if (Array_Yellow[0][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[0][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_1 = Yellow_1 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_1 - DICE <= 0 and O_Yellow > 7)
							Yellow_1 = 52 + (Yellow_1) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_1 - DICE <= 0)
							Yellow_1 = Yellow_1 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_1 + DICE >= 52)
							Yellow_1 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_1 = Yellow_1 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_2 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_2 == 0)
		{
			if (buttons == 65 or buttons == 97)
			{
				Yellow_2++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_2 != 0 and Yellow_2 <= 58)//
		{
			if (buttons == 65 or buttons == 97)
			{
				int O_Yellow = Yellow_2 ;

				Yellow_2 = Yellow_2 + DICE ;

				if (Yellow_2 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_2 > 52)
				{
					Yellow_2 = Yellow_2 - 52 ;
				}

				else if (Yellow_2 > 58 and Yellow_kill > 0 and Yellow_2 != 52)
				{
					Yellow_2 = Yellow_2 - DICE ;
				}

				else if (Yellow_2 <= 58 and Yellow_kill > 0)
				{
					Yellow_2 = Yellow_2 - DICE ;
					for (int i = Yellow_2 ; i <= Yellow_2 + DICE ; i++)
					{
						if (i == 52)
						Yellow_2++ ;

						if (i == 58 and Yellow_2 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_2 = Yellow_2 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[1][Yellow_2][0] == Array_Red[0][Red_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[1][Red_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[2][Red_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Red[3][Red_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[0][Green_1][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[1][Green_2][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[2][Green_3][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[1][Yellow_2][0] == Array_Green[3][Green_4][0] and Array_Yellow[1][Yellow_2][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_2 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_2 != 52)
				{
					Yellow_2 = Yellow_2 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[1][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[1][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[1][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[1][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[1][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[1][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[1][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[1][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_2 ; i >= Yellow_2 - DICE ; i--)
					{
						if (Array_Yellow[1][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[1][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_2 = Yellow_2 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_2 - DICE <= 0 and O_Yellow > 7)
							Yellow_2 = 52 + (Yellow_2) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_2 - DICE <= 0)
							Yellow_2 = Yellow_2 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_2 + DICE >= 52)
							Yellow_2 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_2 = Yellow_2 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_2 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_3 == 0)
		{
			if (buttons == 83 or buttons == 115)
			{
				Yellow_3++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_3 != 0 and Yellow_3 <= 58)//
		{
			if (buttons == 83 or buttons == 115)
			{
				int O_Yellow = Yellow_3 ;

				Yellow_3 = Yellow_3 + DICE ;

				if (Yellow_3 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_3 > 52)
				{
					Yellow_3 = Yellow_3 - 52 ;
				}

				else if (Yellow_3 > 58 and Yellow_kill > 0 and Yellow_3 != 52)
				{
					Yellow_3 = Yellow_3 - DICE ;
				}

				else if (Yellow_3 <= 58 and Yellow_kill > 0)
				{
					Yellow_3 = Yellow_3 - DICE ;
					for (int i = Yellow_3 ; i <= Yellow_3 + DICE ; i++)
					{
						if (i == 52)
						Yellow_3++ ;

						if (i == 58 and Yellow_3 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_3 = Yellow_3 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[2][Yellow_3][0] == Array_Red[0][Red_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[1][Red_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[2][Red_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Red[3][Red_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[0][Green_1][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[1][Green_2][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[2][Green_3][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[2][Yellow_3][0] == Array_Green[3][Green_4][0] and Array_Yellow[2][Yellow_3][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_3 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_3 != 52)
				{
					Yellow_3 = Yellow_3 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[2][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[2][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[2][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[2][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[2][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[2][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[2][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[2][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_3 ; i >= Yellow_3 - DICE ; i--)
					{
						if (Array_Yellow[2][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[2][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_3 = Yellow_3 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_3 - DICE <= 0 and O_Yellow > 7)
							Yellow_3 = 52 + (Yellow_3) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_3 - DICE <= 0)
							Yellow_3 = Yellow_3 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_3 + DICE >= 52)
							Yellow_3 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_3 = Yellow_3 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_3 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}

	if (Turns == 2 and iteration > 0 and DICE != 0)
	{
	        if (DICE == 6 and Yellow_4 == 0)
		{
			if (buttons == 68 or buttons == 100)
			{
				Yellow_4++ ;

				DICE = 0 ;
			}

		}

	        else if (DICE <= 6 and Yellow_4 != 0 and Yellow_4 <= 58)//
		{
			if (buttons == 68 or buttons == 100)
			{
				int O_Yellow = Yellow_4 ;

				Yellow_4 = Yellow_4 + DICE ;

				if (Yellow_4 <= 58)
				{
					Yellow_Score = Yellow_Score + DICE ;
				}

				//Array boundary check
			
				if (Yellow_kill == 0 and Yellow_4 > 52)
				{
					Yellow_4 = Yellow_4 - 52 ;
				}

				else if (Yellow_4 > 58 and Yellow_kill > 0 and Yellow_4 != 52)
				{
					Yellow_4 = Yellow_4 - DICE ;
				}

				else if (Yellow_4 <= 58 and Yellow_kill > 0)
				{
					Yellow_4 = Yellow_4 - DICE ;
					for (int i = Yellow_4 ; i <= Yellow_4 + DICE ; i++)
					{
						if (i == 52)
						Yellow_4++ ;

						if (i == 58 and Yellow_4 + DICE <= 58)
						Yellow_Score += 15 ;
					}
					Yellow_4 = Yellow_4 + DICE ;
				}

				//Conditions for killing another piece
				if ((Array_Yellow[3][Yellow_4][0] == Array_Red[0][Red_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[0][Red_1][1] and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 and Red_1 != 48 and Red_1 != Red_2 and Red_1 != Red_3 and Red_1 != Red_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Red_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[1][Red_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[1][Red_2][1] and Red_2 != 1 and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 and Red_2 != 40 and Red_2 != 48 and Red_2 != Red_1 and Red_2 != Red_3 and Red_2 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[2][Red_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[2][Red_3][1] and Red_3 != 1 and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 != Red_1 and Red_3 != Red_2 and Red_3 != Red_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Red[3][Red_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Red[3][Red_4][1] and Red_4 != 1 and Red_4 != 9 and Red_4 != 14 and Red_4 != 22 and Red_4 != 27 and Red_4 != 35 and Red_4 != 40 and Red_4 != 48 and Red_4 != Red_1 and Red_4 != Red_2 and Red_4 != Red_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Red_4 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[0][Blue_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[0][Blue_1][1] and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 and Blue_1 != 48 and Blue_1 != Blue_2 and Blue_1 != Blue_3 and Blue_1 != Blue_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Blue_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[1][Blue_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[1][Blue_2][1] and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 and Blue_2 != 48 and Blue_2 != Blue_1 and Blue_2 != Blue_3 and Blue_2 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[2][Blue_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[2][Blue_3][1] and Blue_3 != 1 and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 != Blue_1 and Blue_3 != Blue_2 and Blue_3 != Blue_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Blue[3][Blue_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Blue[3][Blue_4][1] and Blue_4 != 1 and Blue_4 != 9 and Blue_4 != 14 and Blue_4 != 22 and Blue_4 != 27 and Blue_4 != 35 and Blue_4 != 40 and Blue_4 != 48 and Blue_4 != Blue_1 and Blue_4 != Blue_2 and Blue_4 != Blue_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Blue_4 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[0][Green_1][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[0][Green_1][1] and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 and Green_1 != 48 and Green_1 != Green_2 and Green_1 != Green_3 and Green_1 != Green_4))
				{
					Yellow_kill++ ;
					Yellow_Score += 10 ;
					Green_1 = 0 ;
				}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[1][Green_2][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[1][Green_2][1] and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 and Green_2 != 48 and Green_2 != Green_1 and Green_2 != Green_3 and Green_2 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_2 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[2][Green_3][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[2][Green_3][1] and Green_3 != 1 and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 != Green_1 and Green_3 != Green_2 and Green_3 != Green_4))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_3 = 0 ;
					}

				else if ((Array_Yellow[3][Yellow_4][0] == Array_Green[3][Green_4][0] and Array_Yellow[3][Yellow_4][1] == Array_Green[3][Green_4][1] and Green_4 != 1 and Green_4 != 9 and Green_4 != 14 and Green_4 != 22 and Green_4 != 27 and Green_4 != 35 and Green_4 != 40 and Green_4 != 48 and Green_4 != Green_1 and Green_4 != Green_2 and Green_4 != Green_3))
					{
						Yellow_kill++ ;
						Yellow_Score += 10 ;
						Green_4 = 0 ;
					}

				if (Yellow_kill >= 1 and Yellow_4 == 52)
				{
					Yellow_kill_52 = 52 ;
				}

				if (Yellow_kill_52 == 52 and Yellow_4 != 52)
				{
					Yellow_4 = Yellow_4 - 52 - 1 ;
					
					Yellow_kill_52 = 0 ;
				}

				//Condition for stacked ludo pieces
				if ((Red_1 == Red_2 or Red_1 == Red_3 or Red_1 == Red_4) 
				and (Red_1 != 0 and Red_1 != 1 and Red_1 != 9 and Red_1 != 14 
				and Red_1 != 22 and Red_1 != 27 and Red_1 != 35 and Red_1 != 40 
				and Red_1 != 48 and Red_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[0][Red_1][0] 
						and Array_Yellow[3][i][1] == Array_Red[0][Red_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_2 == Red_3 or Red_2 == Red_4) and (Red_2 != 0 and Red_2 != 1 
				and Red_2 != 9 and Red_2 != 14 and Red_2 != 22 and Red_2 != 27 and Red_2 != 35 
				and Red_2 != 40 and Red_2 != 48 and Red_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[1][Red_2][0] 
						and Array_Yellow[3][i][1] == Array_Red[1][Red_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Red_3 == Red_4) and (Red_3 != 0 and Red_3 != 1 
				and Red_3 != 9 and Red_3 != 14 and Red_3 != 22 and Red_3 != 27 
				and Red_3 != 35 and Red_3 != 40 and Red_3 != 48 and Red_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Red[1][Red_3][0] 
						and Array_Yellow[3][i][1] == Array_Red[1][Red_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_1 == Blue_2 or Blue_1 == Blue_3 or Blue_1 == Blue_4) 
				and (Blue_1 != 0 and Blue_1 != 1 and Blue_1 != 9 and Blue_1 != 14 
				and Blue_1 != 22 and Blue_1 != 27 and Blue_1 != 35 and Blue_1 != 40 
				and Blue_1 != 48 and Blue_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[0][Blue_1][0]
						and Array_Yellow[3][i][1] == Array_Blue[0][Blue_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_2 == Blue_3 or Blue_2 == Blue_4) 
				and (Blue_2 != 0 and Blue_2 != 1 and Blue_2 != 9 and Blue_2 != 14 
				and Blue_2 != 22 and Blue_2 != 27 and Blue_2 != 35 and Blue_2 != 40 
				and Blue_2 != 48 and Blue_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[1][Blue_2][0] 
						and Array_Yellow[3][i][1] == Array_Blue[1][Blue_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Blue_3 == Blue_4) and (Blue_3 != 0 and Blue_3 != 1 
				and Blue_3 != 9 and Blue_3 != 14 and Blue_3 != 22 and Blue_3 != 27 
				and Blue_3 != 35 and Blue_3 != 40 and Blue_3 != 48 and Blue_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Blue[2][Blue_3][0] 
						and Array_Yellow[3][i][1] == Array_Blue[2][Blue_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_1 == Green_2 or Green_1 == Green_3 or Green_1 == Green_4) 
				and (Green_1 != 0 and Green_1 != 1 and Green_1 != 9 and Green_1 != 14 
				and Green_1 != 22 and Green_1 != 27 and Green_1 != 35 and Green_1 != 40 
				and Green_1 != 48 and Green_1 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[0][Green_1][0] 
						and Array_Yellow[3][i][1] == Array_Green[0][Green_1][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_2 == Green_3 or Green_2 == Green_4) 
				and (Green_2 != 0 and Green_2 != 1 and Green_2 != 9 and Green_2 != 14 
				and Green_2 != 22 and Green_2 != 27 and Green_2 != 35 and Green_2 != 40 
				and Green_2 != 48 and Green_2 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[1][Green_2][0] 
						and Array_Yellow[3][i][1] == Array_Green[1][Green_2][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				else if ((Green_3 == Green_4) and (Green_3 != 0 and Green_3 != 1 
				and Green_3 != 9 and Green_3 != 14 and Green_3 != 22 and Green_3 != 27 
				and Green_3 != 35 and Green_3 != 40 and Green_3 != 48 and Green_3 <= 52))
				{					
					for (int i = Yellow_4 ; i >= Yellow_4 - DICE ; i--)
					{
						if (Array_Yellow[3][i][0] == Array_Green[2][Green_3][0] 
						and Array_Yellow[3][i][1] == Array_Green[2][Green_3][1])
						{
							Yellow_4 = Yellow_4 - DICE ;
							Yellow_Score -= DICE ;

							if (Yellow_4 - DICE <= 0 and O_Yellow > 7)
							Yellow_4 = 52 + (Yellow_4) ;

							else if (O_Yellow >= 1 and O_Yellow <= 7 and Yellow_4 - DICE <= 0)
							Yellow_4 = Yellow_4 + O_Yellow - 1 ;

							if (Yellow_kill > 0 and Yellow_4 + DICE >= 52)
							Yellow_4 -= 1 ;

							if (Yellow_kill > 0 and i == 52)
							{
								Yellow_4 = Yellow_4 + DICE + 1 ;
								Yellow_Score = Yellow_Score + DICE ;
							}

							break ;
						}

					}

				}

				//Score update for stacked pieces.
				if (((O_Yellow + DICE) == Yellow_4 or (O_Yellow + DICE) == Yellow_4 or (O_Yellow + DICE) == Yellow_4)
				and O_Yellow != 0 and (O_Yellow + DICE) != 58 and (O_Yellow + DICE) != 1 
				and (O_Yellow + DICE) != 9 and (O_Yellow + DICE) != 14 and (O_Yellow + DICE) != 22 
				and (O_Yellow + DICE) != 27 and (O_Yellow + DICE) != 35 and (O_Yellow + DICE) != 40 
				and (O_Yellow + DICE) != 48)
				Yellow_Score += 2 ;

				DICE = 0 ;
			}

		}
	
	}
	DrawCircle( Array_Yellow[0][Yellow_1][0] , Array_Yellow[0][Yellow_1][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[1][Yellow_2][0] , Array_Yellow[1][Yellow_2][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[2][Yellow_3][0] , Array_Yellow[2][Yellow_3][1] , 10 , colors[YELLOW]);
        DrawCircle( Array_Yellow[3][Yellow_4][0] , Array_Yellow[3][Yellow_4][1] , 10 , colors[YELLOW]);
	
	DrawString( Array_Yellow[0][Yellow_1][0] - 8 , Array_Yellow[0][Yellow_1][1] - 9 , "w" , colors[ORANGE]);
	DrawString( Array_Yellow[1][Yellow_2][0] - 6 , Array_Yellow[1][Yellow_2][1] - 7 , "a" , colors[ORANGE]);
	DrawString( Array_Yellow[2][Yellow_3][0] - 5 , Array_Yellow[2][Yellow_3][1] - 7 , "s" , colors[ORANGE]);
	DrawString( Array_Yellow[3][Yellow_4][0] - 8 , Array_Yellow[3][Yellow_4][1] - 10 , "d" , colors[ORANGE]);

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	
	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Turns == 1 and Red_Win != 0)
	{
		Turns++ ;
	}

	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Turns == 1 and Red_Win == 0)
	{
		Red_Win ++ ;
		Win++ ;
	}

	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red_Win == Win)
	{
		DrawString (300 , 150 , "Red has won the game" , colors[WHITE]) ;
		Red_Win++ ;
		Win++ ;
	}

	else if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red_Win != Win)
	DrawString (300 , 150 , "Red has finished the game" , colors[WHITE]) ;

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Turns == 1 and Yellow_Win != 0)
	{
		Turns-- ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Turns == 1 and Yellow_Win == 0)
	{
		Yellow_Win ++ ;
		Win++ ;
	}

	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow_Win == Win)
	{
		DrawString (300 , 100 , "Yellow has won the game" , colors[WHITE]) ;
		Yellow_Win++ ;
		Win++ ;
	}

	else if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow_Win != Win)
	DrawString (300 , 100 , "Yellow has finished the game" , colors[WHITE]) ;

	DrawSquare( 750 , 250 , 30 , colors[GRAY]);//Square for dice.

	//Dice faces.
	if (DICE == 1)
	  DrawCircle(765 , 265 , 3 , colors[RED]) ;

	else if (DICE == 2)
	{
		DrawCircle(770 , 265 , 3 , colors[RED]) ;
		DrawCircle(760 , 265 , 3 , colors[RED]) ;
        }

	else if (DICE == 3)
        {
		DrawCircle(775 , 275 , 3 , colors[RED]) ;
		DrawCircle(765 , 265 , 3 , colors[RED]) ;
		DrawCircle(755 , 255 , 3 , colors[RED]) ;
        }

	else if (DICE == 4)
        {
		DrawCircle(770 , 270 , 3 , colors[RED]) ;
		DrawCircle(760 , 270 , 3 , colors[RED]) ;
		DrawCircle(770 , 260 , 3 , colors[RED]) ;
		DrawCircle(760 , 260 , 3 , colors[RED]) ;
        }

	else if (DICE == 5)
	{
		DrawCircle(755 , 275 , 3 , colors[RED]) ;
		DrawCircle(775 , 275 , 3 , colors[RED]) ;
		DrawCircle(765 , 265 , 3 , colors[RED]) ;
		DrawCircle(755 , 255 , 3 , colors[RED]) ;
		DrawCircle(775 , 255 , 3 , colors[RED]) ;
        }


	else if (DICE == 6)
	    {
		DrawCircle(770 , 275 , 3 , colors[RED]) ;
		DrawCircle(760 , 275 , 3 , colors[RED]) ;
		DrawCircle(770 , 265 , 3 , colors[RED]) ;
		DrawCircle(760 , 265 , 3 , colors[RED]) ;
		DrawCircle(770 , 255 , 3 , colors[RED]) ;
		DrawCircle(760 , 255 , 3 , colors[RED]) ;
	    }

	if (Turns == 1 or Turns == 0)
	DrawSquare (100 , 300 , 30 , colors[RED]) ;

	else if (Turns ==  2 or Turns == 3)
	DrawSquare (100 , 300 , 30 , colors[OLIVE]) ;

	//For storing score in file.
	if (Red_1 == 58 and Red_2 == 58 and Red_3 == 58 and Red_4 == 58 and Red == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Red_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Red_Score ;
				Names_1 [i] = Player_Names [0] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Red_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Red++ ;
	}
	
	if (Yellow_1 == 58 and Yellow_2 == 58 and Yellow_3 == 58 and Yellow_4 == 58 and Yellow == 0)
	{
		fstream io_file ;

		io_file.open ("Highscores.txt" , ios :: in) ;

		int Score [10] ;
		int i = 0 ;
		int position ; 
		string Names [100] ;

		while (!io_file.eof() and !io_file.fail())
		{
			io_file >> Names [i] ;
			io_file >> Score [i] ;

			i++ ;
		}

		for (int i = 0 , occurence = 0 ; i < 10 ; i++)
		{
			if (Yellow_Score >= Score [i] and occurence == 0)
			{
				position = i ;
				occurence++ ;
			}

		}

		int Score_1 [10] ;
		string Names_1 [100] ;

		for (int i = 0 ; i < 10 ; i++)
		{
			Score_1 [i] = Score [i] ;
			Names_1 [i] = Names [i] ;

			if (i == position)
			{
				Score_1 [i] = Yellow_Score ;
				Names_1 [i] = Player_Names [1] ;
			}

		}

		for (int i = position ; i < 10 ; i++)
		{
			if (Yellow_Score >= Score_1 [i])
			{
				Score_1 [i + 1] = Score [i] ;
				Names_1 [i + 1] = Names [i] ;
			}

		}

		io_file.close () ;

		ofstream o_file ;

		o_file.open ("Highscores.txt") ;
	        i = 0 ;

		while (i < 10)
		{
			o_file << Names_1 [i] << ' ' << Score_1 [i] << endl;

			i++ ;
		}

		o_file.close () ;
		Yellow++ ;
	}	
		DrawString( 50 , 800 , "RED" , colors[MINT_CREAM]) ;
		DrawString( 750 , 800 , "YELLOW" , colors[MINT_CREAM]) ;
	
		DrawString( 50 , 775 , Player_Names [0] + " Score = " + to_string (Red_Score), colors[MINT_CREAM]) ;
		DrawString( 750 , 775 , Player_Names [1] + " Score = " + to_string (Blue_Score), colors[MINT_CREAM]) ;

		if (Red_Win > 0 and Yellow_Win > 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}

		if (Red_Win > 0 and Yellow_kill == 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}

		if (Red_kill == 0 and Yellow_Win > 0)
		{
			FINISH++ ;
			DrawString (400 , 400 , "The game has finished." , colors[BLACK]) ;
		}		
	}
	}
	}
	glutSwapBuffers(); // do not modify this line..

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
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	
	if (screen == 3)
	{
	//For game of 4 players
	if (BUTTONS == 53)
	{
	if (key == 32 and FINISH == 0) //For space key
	  {
		DICE = rand () % 6 + 1 ; //For the DICE.
		//Block for deciding player with the highest roll for playing first.
		if (iteration == 0)
		{
			if (Turns == 1)
			{
				DICE_Roll_1 = DICE ;
				Turns++ ;
			}
		
			else if (Turns == 2)
				{
					DICE_Roll_2 = DICE ;
					Turns++ ;
				}

			else if (Turns == 3)
				{
					DICE_Roll_3 = DICE ;
					Turns++ ;
				}

			else if (Turns == 4)
				{
					DICE_Roll_4 = DICE ;
					Turns++ ;
				}

			else if (Turns == 5)
				{
					iteration++ ;
				}

			//Block for deciding which player gets first turn
			if (DICE_Roll_1 > DICE_Roll_2 and DICE_Roll_1 > DICE_Roll_3 and DICE_Roll_1 > DICE_Roll_4 and iteration == 1)
				Turn = 1 ;

		        if (DICE_Roll_2 > DICE_Roll_1 and DICE_Roll_2 > DICE_Roll_3 and DICE_Roll_2 > DICE_Roll_4 and iteration == 1)
				Turn = 2 ;

			if (DICE_Roll_3 > DICE_Roll_1 and DICE_Roll_3 > DICE_Roll_2 and DICE_Roll_3 > DICE_Roll_4 and iteration == 1)
				Turn = 3 ;

			if (DICE_Roll_4 > DICE_Roll_1 and DICE_Roll_4 > DICE_Roll_2 and DICE_Roll_4 > DICE_Roll_3 and iteration == 1)
				Turn = 4 ;

			cout << "First Turn = " << Turn << endl ;
		}

		if (iteration > 0)
		{
			if (iteration == 1)//For allotiing the player who will play first
			{
				Turns = Turn ;
			}

			//Block for changing turns
			if ((Turns == 1 or Turn == 0 ) and iteration != 1)
			Turns++ ;

			else if (Turns == 2 and iteration != 1)
				Turns++ ;

			else if (Turns == 3 and iteration != 1)
				Turns++ ;

			else if (Turns == 4 and iteration != 1)
				Turns = 1 ;

			iteration++ ;
		}
	   	//GameDisplay() ;	   
	  }

	}

	//For game of 3 players
	if (BUTTONS == 54)
	{
	if (key == 32 and FINISH == 0) //For space key
	  {
		DICE = rand () % 6 + 1 ; //For the DICE.
		//Block for deciding player with the highest roll for playing first.
		if (iteration == 0)
		{
			if (Turns == 1)
			{
				DICE_Roll_1 = DICE ;
				Turns++ ;
			}
		
			else if (Turns == 2)
				{
					DICE_Roll_2 = DICE ;
					Turns++ ;
				}

			else if (Turns == 3)
				{
					DICE_Roll_3 = DICE ;
					Turns++ ;
				}

			else if (Turns == 4)
				{
					iteration++ ;
				}

			//Block for deciding which player gets first turn
			if (DICE_Roll_1 > DICE_Roll_2 and DICE_Roll_1 > DICE_Roll_3 and DICE_Roll_1 > DICE_Roll_4 and iteration == 1)
				Turn = 1 ;

		        if (DICE_Roll_2 > DICE_Roll_1 and DICE_Roll_2 > DICE_Roll_3 and DICE_Roll_2 > DICE_Roll_4 and iteration == 1)
				Turn = 2 ;

			if (DICE_Roll_3 > DICE_Roll_1 and DICE_Roll_3 > DICE_Roll_2 and DICE_Roll_3 > DICE_Roll_4 and iteration == 1)
				Turn = 3 ;

			cout << "First Turn = " << Turn << endl ;
		}

		if (iteration > 0)
		{
			if (iteration == 1)//For allotiing the player who will play first
			{
				Turns = Turn ;
			}

			//Block for changing turns
			if ((Turns == 1 or Turn == 0 ) and iteration != 1)
			Turns++ ;

			else if (Turns == 2 and iteration != 1)
				Turns++ ;

			else if (Turns == 3 and iteration != 1)
				Turns = 1 ;

			iteration++ ;
		}
	   	//GameDisplay() ;	   
	  }

	}

	//For game of 2 players
	if (BUTTONS == 55)
	{
	if (key == 32 and FINISH == 0) //For space key
	  {
		DICE = rand () % 6 + 1 ; //For the DICE.
		//Block for deciding player with the highest roll for playing first.
		if (iteration == 0)
		{
			if (Turns == 1)
			{
				DICE_Roll_1 = DICE ;
				Turns++ ;
			}
		
			else if (Turns == 2)
				{
					DICE_Roll_2 = DICE ;
					Turns++ ;
				}

			else if (Turns == 3)
				{
					iteration++ ;
				}

			//Block for deciding which player gets first turn
			if (DICE_Roll_1 > DICE_Roll_2 and DICE_Roll_1 > DICE_Roll_3 and DICE_Roll_1 > DICE_Roll_4 and iteration == 1)
				Turn = 1 ;

		        if (DICE_Roll_2 > DICE_Roll_1 and DICE_Roll_2 > DICE_Roll_3 and DICE_Roll_2 > DICE_Roll_4 and iteration == 1)
				Turn = 2 ;

			cout << "First Turn = " << Turn << endl ;
		}

		if (iteration > 0)
		{
			if (iteration == 1)//For allotiing the player who will play first
			{
				Turns = Turn ;
			}

			//Block for changing turns
			if ((Turns == 1 or Turn == 0 ) and iteration != 1)
			Turns++ ;

			else if (Turns == 2 and iteration != 1)
				Turns = 1 ;

			iteration++ ;
		}
	   	//GameDisplay() ;	   
	  }

	}
	}

	if (key == 49)
	{
		menu = 1 ;
		screen = 1 ;

		buttons = key ;
	}

	if (screen == 1)
	{
		if (key == 53)
		{
			BUTTONS = key ;
		}

		if (key == 54)
		{
			BUTTONS = key ;
		}

		if (key == 55)
		{
			BUTTONS = key ;
		}
	}

	if (screen == 2)
	{
		if ((key >= 65 and key <= 90) or (key >= 97 and key <= 122) or key == 94)
		{
			str_1 = key ;
			str = str + str_1 ;
			Player_Names [k] = str ;
			Player_Names [k] = name(Player_Names , k) ;
		}

		if (key == 13)
		{
			k++ ;
			str = "" ;
		}
	}

	if (key == 50)
	{
		menu = 2 ;
	}

	//keys for movement of ludo pieces
	if (FINISH == 0)
	{
		if ((key == 'W' or key == 'w') and screen == 3)
		{
			buttons = key ;
		}

		else if ((key == 'A' or key == 'a') and screen == 3)
		{
			buttons = key ;
		}

		else if ((key == 'S' or key == 's') and screen == 3)
		{
			buttons = key ;
		}

		else if ((key == 'D' or key == 'd') and screen == 3)
		{
			buttons = key ;
		}
	}

	if (key == 51)
	{
		menu = 3 ;
	}

	if (key == 8)
	{
		menu = 0;
	}
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
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

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(10000.0, Timer, 0);
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
	xx = x ;
	yy = 740 - y ;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	//glutPostRedisplay();
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
		xx = x ;
		yy = 740 - y ;
		glutPostRedisplay();
	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Ludo Game"); // set the title of our game window
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
#endif /* AsteroidS_CPP_ */
