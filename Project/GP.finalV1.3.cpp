#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include <cstring>
#include <stdlib.h>
#include<ctime>
	using namespace std;

bool exit_flag = false;
int mapsize = 10;//default size
int map[10][10];
int scores = 0;
int highest_mark = 0;//The highest of player
string winner = "Null";//The winner of highest mark
bool game_over_flag = false;//To check the gameover
bool overlapchecking = true;//check the overlapcheck
bool overrangechecking = true;//check the overrangecheck
int Time_Bomb_Appear_Count = 0;
int Time_Bomb_Initial_vaule = 9;//The inital value of bomb
bool gamemode = false;//false is normal game , true is bomb game 
bool Aimode = false;//falseis player ,true is PC player
const int Row[19] = { 1,1,1,1,1,2,3,4,5,2,2,2,2,3,3,3,3,2,3 };//for all block row size
const int Col[19] = { 1,2,3,4,5,1,1,1,1,2,2,2,2,3,3,3,3,2,3 };//for all block colum size
															  //block[blocktype][row][col]
const int Block[19][5][5] = {
	{ { 1 } ,{} },//case0
	{ { 1,1 },{} },//case1
	{ { 1, 1 ,1 },{} },//case2
	{ { 1, 1, 1,1 },{} },//case3
	{ { 1, 1, 1, 1,1 },{} },//case4
	{ { 1 },{ 1 } },//case5
	{ { 1 },{ 1 },{ 1 } },//case6
	{ { 1 },{ 1 },{ 1 },{ 1 } },//case7
	{ { 1 },{ 1 },{ 1 },{ 1 },{ 1 } },//case8
	{ { 1 } ,{ 1, 1 } },//case9
	{ { 0 , 1 } ,{ 1, 1 } },//case10
	{ { 1 , 1 } ,{ 1 } },//case11
	{ { 1 , 1 } ,{ 0 , 1 } },//case12
	{ { 1 } ,{ 1 },{ 1 , 1 , 1 } },//case13
	{ { 0,0,1 } ,{ 0,0,1 },{ 1,1,1 } },//case14
	{ { 1 ,1,1 } ,{ 1 },{ 1 } },//case15
	{ { 1,1,1 } ,{ 0,0, 1 },{ 0,0, 1 } },//case16
	{ { 1,1 } ,{ 1 ,1 } },//case17
	{ { 1 ,1,1 } ,{ 1,1,1 },{ 1,1,1 } }//case18
};
const int mark[19] = { 10,20,30,40,50,20,30,40,50,30,30,30,30,50,50,50,50,40,90 };
void Welcome_Message();
void PC_Game_Demo();
void Timer_Bomb_Mode();
void Change_Board_Size();
void Change_Bomb_Timer();
void Setting();
void Instructions();
void Credits();
void check_exit();
void initialize_board();
void print_board();
void clear_board();
void put_block(int shapetype, int y, int x);
void get_mark(int shapeType);
void show_block(int x);
void checking_error(int shapeType, int y, int x);
bool check_input_shape(int shapeType, int y, int x);
void wrong_input();
void put_shape_into_board(int shapeType, int y, int x);
void refresh_board();
void clear_full_lines();
void Locate_Time_Bomb();
void Time_Bomb();
void Changing_Bomb_Vaule();
void Bomb_gameover_checking();
class block {
public:
	block() {
		shapeType = rand() % 19; //generate the blcok type
	}
	void showblock() {
		show_block(shapeType);
		cout << endl << "score of the block is :" << mark[shapeType] << endl << endl;
	}
	void resetblock() {
		shapeType = rand() % 19;
	}
	bool block_check_input_shape(int y, int x) {
		bool error_checking;
		error_checking = check_input_shape(shapeType, y, x);
		if (overrangechecking == false) {
			cout << "you have over the range, please input again";
			system("pause");
		}
		else if (overlapchecking == false) {
			cout << "you have overlap the block,please input again";
			system("pause");
		}
		if (error_checking == false) {
			return false;
		}
		return true;
	}
	void block_put_shape_into_board(int y, int x) {
		put_shape_into_board(shapeType, y, x);
	}

	int shapeType;
};
void process_choose0(block &choose0, int y, int x);
void process_choose1(block &choose1, int y, int x);
void process_choose2(block &choose2, int y, int x);
void change_char_to_int(char c_y, int&y);
void check_game_over(block &choose0, block &choose1, block&choose2);
void game_quit(block &choose0, block &choose1, block&choose2);
void normal_game_process(block &choose0, block &choose1, block&choose2);
void Ai_game_process(block &choose0, block &choose1, block&choose2);
bool is_game_over();
void play_normal_mode();
void Start_Game();


int main()
{
	Welcome_Message();
	srand((unsigned)time(0));
	int game_choice;
	do {
		system("cls");
		game_choice = -1;
		cout << "*** Game Menu ***" << endl;
		cout << "[1] Start Game" << endl;
		cout << "[2] Setting" << endl;
		cout << "[3] Instructions" << endl;
		cout << "[4] Credits" << endl;
		cout << "[5] Exit" << endl;
		cout << "*****************" << endl;
		cout << "Option (1 - 5): ";
		cin >> game_choice;
		cin.clear();
		cin.ignore(10000, '\n');
		switch (game_choice) {
		case 1: Start_Game(); break;
		case 2: Setting(); break;
		case 3: Instructions(); break;
		case 4: Credits(); break;
		case 5: check_exit(); break;
		default:
			cout << "Please enter choice 1 - 5 only." << endl;
			system("pause");
			system("cls");
			break;
		}
	} while (exit_flag != true);

	return 0;
}

void Welcome_Message() {
	for (int i = 0; i < 51; i++) {
		cout << "*";
	}
	cout << endl;
	for(int i=0;i<2;i++){
		cout << "*" << setw(50) << "*" << endl;
	}
	cout << "*"<<setw(41)<<"Welcome to BlockPuzzle Game World" <<setw(9)<<"*"<< endl;

	for (int i = 0; i<2; i++) {
		cout << "*" << setw(50) << "*" << endl;
	}
	for (int i = 0; i < 51; i++) {
		cout << "*";
	}
	cout << endl;
	system("pause");

}
void PC_Game_Demo() {
	int setting;
	do {
		system("cls");
		cout << "Now Gamemode is " << (Aimode ? " PC plays a demo game" : "the player plays the game") << endl << endl;//telling which mode are on or off now

		cout << "Whcih mode you want to play?\n(0 for the player plays the game,1 for PC plays a demo game):";
		cin >> setting;
		cin.clear();
		cin.ignore(10000, '\n');
		if (setting == 1)
		{
			Aimode = true;
		}//AI mode on
		else if (setting == 0) {
			Aimode = false;
		}//AI mode off
		else
		{
			cout << "You input a wrong value! Please input again!" << endl;
			system("pause");
		}//error checking
	} while (setting != 0 && setting != 1);
	cout << "The setting has been updataed";
	system("pause");
	system("cls");
}
void Timer_Bomb_Mode() {
	int setting;
	do {
		system("cls");
		cout << "Now Timer Bomb Mode is " << (gamemode ? " on " : "off") << endl << endl;//telling the TimeBomb Mode is on or off now
		cout << "Will you want turn " << (gamemode ? "off" : " on ") << " the Timer Bomb Mode ?" << endl;
		cout << "(Hint:Turn off ,please input 0, Turn on ,please input 1)";
		cin >> setting;
		cin.clear();
		cin.ignore(10000, '\n');
		if (setting == 1)
		{
			gamemode = true;
		}//turn on the TimbBomb mode 
		else if (setting == 0) {
			gamemode = false;
		}
		else
		{
			cout << "You input a wrong value! Please input again!" << endl;
			system("pause");
		}//turn off the TimeBomb mode
	} while (setting != 0 && setting != 1);
	cout << "The setting has been updataed";
	system("pause");
	system("cls");
}
void Change_Board_Size() {
	int setting;
	do {
		system("cls");
		cout << "Now Board_Size is " << mapsize << endl << endl;//telling the board is what size now
		cout << "please input the new Board size (7-10):";
		cin >> setting;
		cin.clear();
		cin.ignore(10000, '\n');
		if (setting >= 7 && setting <= 10) {
			mapsize = setting;
		}//changing mapsize
		else {
			cout << "You input a wrong value! Please input again!" << endl;
			system("pause");
		}

	} while (setting < 7 || setting >10);
	cout << "The setting has been updataed";
	system("pause");
	system("cls");
}
void Change_Bomb_Timer() {
	int setting;
	do {
		system("cls");
		cout << "Now the starting bomb timer value is " << Time_Bomb_Initial_vaule << endl << endl;
		cout << "please input the new Time_Bomb_Initial_vaule (6-9):";
		cin >> setting;
		cin.clear();
		cin.ignore(10000, '\n');
		if (setting >= 6 && setting <= 9) {
			Time_Bomb_Initial_vaule = setting;
		}
		else {
			cout << "You input a wrong value! Please input again!" << endl;
			system("pause");
		}

	} while (setting < 6 || setting >9);
	cout << "The setting has been updataed";
	system("pause");
	system("cls");
}
void Setting()
{
	int settings_choice;
	do {
		system("cls");
		cout << "*** Settings Menu ***" << endl;
		cout << "[1] PC Game Demo" << endl;
		cout << "[2] Timer Bomb Mode" << endl;
		cout << "[3] Change Board Size" << endl;
		cout << "[4] Change Bomb Timer" << endl;
		cout << "[5] Return to Game Menu" << endl;
		cout << "*********************" << endl;
		cout << "Option (1 - 5): ";
		cin >> settings_choice;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (settings_choice) {
		case 1: PC_Game_Demo(); break;
		case 2: Timer_Bomb_Mode(); break;
		case 3: Change_Board_Size(); break;
		case 4: Change_Bomb_Timer(); break;
		case 5:; break;
		default:
			cout << "Please enter choice 1 - 5 only." << endl;

			system("pause");
			system("cls");
			break;
		}
	} while (settings_choice != 5);
}
void Instructions()
{
	system("cls");
	cout << "BlockPuzzle Game World" << endl;
	cout << "Player scores by putting blocks of different shapes onto a square game board, " << endl;
	cout << "and by producing complete horizontal or vertical lines of blocks and clear those lines.  " << endl << endl;
	cout << "When game started, there are a game board with default size 10x10. 3 random block out of 19 types will generated." << endl;
	cout << "Player need to choose one of those and place it on the game board with the aim of creating a horizontal or vertical line without gaps." << endl;
	cout << "When such a lines or blocks is created, marks will be scored and the lines will be cleared. The game will be ended when the player " << endl;
	cout << "fails to put any blocks onto the game board and return back to Game Menu." << endl << endl;
	cout << "Number of complete lines formed in one move   |   Marks " << endl;
	cout << "_______________________________________________________" << endl;
	cout << "                   1                          |   100 " << endl;
	cout << "                   2                          |   300 " << endl;
	cout << "                   3                          |   600 " << endl;
	cout << "                   4                          |   1000 " << endl;
	cout << "                   5                          |   1500" << endl;
	cout << "(page 1 of 4)" << endl;
	system("pause");
	system("cls");
	cout << "How to start:" << endl;
	cout << "1. input 1 to start game (original game mode)" << endl;
	cout << "2. select your block you wanted to place" << endl;
	cout << "3. input the location you wanted to place the block" << endl;
	cout << "4. repeat the step 2-3 to continue" << endl;
	cout << "5. input command \"Quit\" and 'y' or 'Y' for game ends or 'n' or 'N' for return to game " << endl;
	cout << "(page 2 of 4)" << endl;
	system("pause");
	system("cls");
	cout << "In Time Bomb Mode, for every 5 player's move, a bomb will be placed randomly on " << endl;
	cout << "any board location that has been occupied by a block (i.e X). The bomb will represented by a digit" << endl;
	cout << "and will decreases by 1 on each player move.The player needs to place blocks in order to form a complete line across" << endl;
	cout << "the bomb to clear it before the bomb timer decreases to 0. Otherwise, the player will lose." << endl << endl;
	cout << "How to enable Timer Bomb Mode: " << endl;
	cout << "1. Back to Menu" << endl;
	cout << "2. input 2 into setting" << endl;
	cout << "3. puint 2 again into Timer Bomb Mode setting" << endl;
	cout << "4. enable it by input 1 or disable it by input 0" << endl;
	cout << "5. input 5 back to Menu" << endl << endl;
	cout << "How to change Bomb Timer:" << endl;
	cout << "1. Back to Menu" << endl;
	cout << "2. input 2 into setting" << endl;
	cout << "3. input 4 into change Bomb Timer setting" << endl;
	cout << "4. input the new value in a range of 6 to 9 (default 9)" << endl;
	cout << "5. input 5 back to Menu" << endl;
	cout << "(page 3 of 4)" << endl;
	system("pause");
	system("cls");
	cout << "In PC Gane Demo, the user doesn't need to enter any block choice or block location. The PC will automatically select" << endl;
	cout << "a block and place it on the game board within the game rule. Informaion of the PC's move will be shown clearly." << endl;
	cout << "1. Back to Menu" << endl;
	cout << "2. input 1 into setting" << endl;
	cout << "3. input 1 into PC Game Demo setting" << endl;
	cout << "4. enable it by input 1 or disable it by input 0" << endl;
	cout << "5. input 5 back to Menu" << endl;
	cout << "(page 4 of 4)" << endl;
	system("pause");
	system("cls");
}
void Credits()
{
	system("cls");
	cout << left;
	cout << "Credit:" << endl;
	cout << setw(15) << "Student Name" << setw(15) << "Student ID" << "Class and Group" << endl;
	cout << setw(15) << "############" << setw(15) << "############" << "############" << endl;
	cout << setw(15) << "############" << setw(15) << "############" << "############" << endl;
	cout << setw(15) << "############" << setw(15) << "############" << "############" << endl;
	cout << setw(15) << "############" << setw(15) << "############" << "############" << endl;
	cout << setw(15) << "############" << setw(15) << "############" << "############" << endl;
	cout << setw(15) << "############" << setw(15) << "############" << "############" << endl;

	system("pause");
	system("cls");
}
void check_exit() {
	string confirm;
	do {
		cout << "Are you sure to exit the game?" << endl;
		cout << "Please input 'y' or 'Y' if you want to exit." << endl;
		cout << "Please input 'n' or 'N' if you want to return the main menu." << endl;
		cout << "Confirm : ";
		cin >> confirm;
		cin.clear();
		cin.ignore(10000, '\n');

		if (confirm == "y" || confirm == "Y")
		{
			cout << "Thanks for the playing!~ See you next time :) " << endl;
			exit_flag = true;
			system("pause");

		}//quit
		else if (confirm == "n" || confirm == "N") {
			system("cls");
		}//not quit

		else
		{
			cout << "You input a wrong answer! Please input again!" << endl;
		}
	} while (confirm != "y" && confirm != "Y" && confirm != "n" && confirm != "N");
}//For reset the map
void initialize_board()
{
	scores = 0;
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			map[y][x] = 0;
		}
	}
}
void print_board()
{
	cout << right;
	cout << "The total mark is " << scores << endl << endl;
	cout << setw(3) << " ";
	for (int x_aixs = 0; x_aixs < mapsize; x_aixs++)
	{
		cout << setw(2) << x_aixs;
	}
	cout << endl << "  +";
	for (int x_aixs = 0; x_aixs < mapsize; x_aixs++)
	{
		cout << "--";
	}
	cout << "-+" << endl;

	char start = 'A';
	for (int y = 0; y < mapsize; y++)
	{
		cout << start << " |";
		start++;

		for (int x = 0; x < mapsize; x++)
		{
			if (map[y][x] == 1)
				cout << setw(2) << "X";
			else if (map[y][x] == 0)
				cout << setw(2) << " ";
			else
				cout << setw(2) << map[y][x] - 2;//print TimeBomb
		}

		cout << " |" << endl;
	}
	cout << "  +";
	for (int x_aixs = 0; x_aixs < mapsize; x_aixs++)
	{
		cout << "--";
	}
	cout << "-+" << endl;

}
void clear_board()
{
	system("cls");
}//putblock into map
void put_block(int shapetype, int y, int x) {

	if (shapetype == 10) {

		map[y - 1][x + 1] = 1;
		map[y][x] = 1;
		map[y][x + 1] = 1;
	}

	else if (shapetype == 14) {
		map[y][x] = 1;
		map[y][x + 1] = 1;
		map[y][x + 2] = 1;
		map[y - 1][x + 2] = 1;
		map[y - 2][x + 2] = 1;
	}
	else
		for (int r = 0; r < Row[shapetype]; r++) {
			for (int c = 0; c < Col[shapetype]; c++) {
				if (Block[shapetype][r][c] == 1)
					map[y + r][x + c] = 1;
			}
			cout << endl;
		}
}
void get_mark(int shapeType) {
	scores += mark[shapeType];

}//showblock
void show_block(int x) {
	for (int r = 0; r < Row[x]; r++) {
		for (int c = 0; c < Col[x]; c++) {
			if (Block[x][r][c] == 1)
				cout << "X ";
			else
				cout << "  ";
		}
		cout << endl;
	}
}//checking it is input error or not( overrangecheck/overlapcheck)
void checking_error(int shapeType, int y, int x) {
	if (shapeType == 10) {
		if (0 > y || y >= mapsize || 0 > x || x >= mapsize || 0 > x + 1 || x + 1 >= mapsize || 0 > y - 1 || y - 1 >= mapsize) {
			overrangechecking = false;
		}
	}
	else if (shapeType == 14)
	{
		if (0 > y || y >= mapsize || 0 > y - 1 || y - 1 >= mapsize || 0 > y - 2 || y - 2 >= mapsize) {
			overrangechecking = false;
		}
		if (0 > x || x >= mapsize || 0 > x + 1 || x + 1 >= mapsize || 0 > x + 2 || x + 2 >= mapsize) {
			overrangechecking = false;
		}
	}
	else
		for (int r = 0; r < Row[shapeType]; r++) {
			for (int c = 0; c < Col[shapeType]; c++) {
				if (Block[shapeType][r][c] == 1) {
					if (0 > r + y || r + y >= mapsize || 0 > c + x || c + x >= mapsize) {
						overrangechecking = false;
					}
				}
			}
		}

	if (overrangechecking == true) {
		if (shapeType == 10) {
			if (map[y][x] != 0 || map[y][x + 1] != 0 || map[y - 1][x + 1] != 0) {
				overlapchecking = false;
			}
		}
		else if (shapeType == 14) {
			if (map[y][x] != 0 || map[y][x + 1] != 0 || map[y][x + 2] != 0 || map[y - 1][x + 2] != 0 || map[y - 2][x + 2] != 0) {
				overlapchecking = false;
			}
		}
		else
			for (int r = 0; r < Row[shapeType]; r++) {
				for (int c = 0; c < Col[shapeType]; c++) {
					if (Block[shapeType][r][c] == 1) {
						if (map[y + r][x + c] != 0) { overlapchecking = false; }

					}
				}
			}
	}
}
bool check_input_shape(int shapeType, int y, int x)
{
	overlapchecking = true;
	overrangechecking = true;
	checking_error(shapeType, y, x);


	if (overlapchecking == false || overrangechecking == false) {

		return false;
	}
	return true;
}
void wrong_input()
{
	cout << "wrong input" << endl;
	system("pause");
}
void put_shape_into_board(int shapeType, int y, int x)
{
	put_block(shapeType, y, x);
	get_mark(shapeType);
}
void refresh_board()
{
	clear_board();
	print_board();
}//clear the full line
void clear_full_lines()
{
	refresh_board();
	int x_aixs_clear_mark[10] = { 0 };//To count which line have to be clear 
	int y_aixs_clear_mark[10] = { 0 };
	int count_full_line = 0;
	for (int y = 0; y < mapsize; y++) {
		for (int x = 0; x < mapsize; x++) {
			if (map[y][x] == 0)
				break;
			if (x == mapsize - 1) {
				count_full_line += 1;
				y_aixs_clear_mark[y] = 1;
			}
		}
	}

	for (int x = 0; x < mapsize; x++) {
		for (int y = 0; y < mapsize; y++) {
			if (map[y][x] == 0)
				break;
			if (y == mapsize - 1) {
				count_full_line += 1;
				x_aixs_clear_mark[x] = 1;
			}
		}
	}
	if (count_full_line > 0) {
		clear_board();
		print_board();
		cout << "There are " << count_full_line << " to be clear.";
		system("pause");
		switch (count_full_line)//get the mark by clear line
		{
		case 1:scores += 100; break;
		case 2:scores += 300; break;
		case 3:scores += 600; break;
		case 4:scores += 1000; break;
		default:scores += 1500; break;//full line 5 or above
		}

		for (int x = 0; x < mapsize; x++) {
			if (x_aixs_clear_mark[x] == 1) {
				for (int y = 0; y < mapsize; y++) {
					map[y][x] = 0;
				}
			}
		}
		for (int y = 0; y < mapsize; y++) {
			if (y_aixs_clear_mark[y] == 1) {
				for (int x = 0; x < mapsize; x++) {
					map[y][x] = 0;
				}
			}
		}
		refresh_board();
	}

}
void Locate_Time_Bomb() {
	int Y; int X;
	do {
		Y = rand() % 10;
		X = rand() % 10;
	} while (map[Y][X] != 1);//any board location that has been occupied by a block
	map[Y][X] = Time_Bomb_Initial_vaule + 3;
}
void Time_Bomb()
{
	Time_Bomb_Appear_Count++;

	if (Time_Bomb_Appear_Count == 5)
	{
		Locate_Time_Bomb();
		Time_Bomb_Appear_Count = 0;
	}
}//TimeBomb appear function
void Changing_Bomb_Vaule() {
	for (int y = 0; y < mapsize; y++) {
		for (int x = 0; x < mapsize; x++) {
			if (map[y][x] != 1 && map[y][x] != 0) {
				map[y][x] -= 1;//decreases by 1 on each players move
			}
		}
	}
}//change the time bomb value
void Bomb_gameover_checking() {
	for (int y = 0; y < mapsize; y++) {
		for (int x = 0; x < mapsize; x++) {
			if (map[y][x] != 1 && map[y][x] != 0) {
				int bomb = map[y][x];
				if (bomb == 2)
				{
					cout << "The Bomb was exploded! \n";
					game_over_flag = true;
				}
			}
		}
	}
}
void process_choose0(block &choose0, int y, int x) {
	if (choose0.block_check_input_shape(y, x))
	{
		choose0.block_put_shape_into_board(y, x);
		choose0.resetblock();
		if (gamemode == 1) {
			Time_Bomb();
			Changing_Bomb_Vaule();
		}
	}
}
void process_choose1(block &choose1, int y, int x) {
	if (choose1.block_check_input_shape(y, x))
	{
		choose1.block_put_shape_into_board(y, x);
		choose1.resetblock();
		if (gamemode == 1) {
			Time_Bomb();
			Changing_Bomb_Vaule();
		}
	}
}
void process_choose2(block &choose2, int y, int x) {
	if (choose2.block_check_input_shape(y, x))
	{
		choose2.block_put_shape_into_board(y, x);
		choose2.resetblock();
		if (gamemode == 1) {
			Time_Bomb();
			Changing_Bomb_Vaule();
		}
	}
}
void change_char_to_int(char c_y, int&y) {
	y = 99;
	switch (c_y)
	{
	case 'A':y = 0; break;
	case 'B':y = 1; break;
	case 'C':y = 2; break;
	case 'D':y = 3; break;
	case 'E':y = 4; break;
	case 'F':y = 5; break;
	case 'G':y = 6; break;
	case 'H':y = 7; break;
	case 'I':y = 8; break;
	case 'J':y = 9; break;

	}
}
void check_game_over(block &choose0, block &choose1, block&choose2)
{
	game_over_flag = true;
	// use the for loop to check ,Is there have anycase that block can put into the map 
	for (int y = 0; y < mapsize; y++) {
		for (int x = 0; x < mapsize; x++) {
			int shapeType0 = choose0.shapeType;
			if (check_input_shape(shapeType0, y, x))
				game_over_flag = false;
			int shapeType1 = choose1.shapeType;
			if (check_input_shape(shapeType1, y, x))
				game_over_flag = false;
			int shapeType2 = choose2.shapeType;
			if (check_input_shape(shapeType2, y, x))
				game_over_flag = false;
			if (game_over_flag == false)
				break;
		}
		if (game_over_flag == false) { break; }

	}
	if (game_over_flag == true) {
		cout << "The map is full " << endl;
	}
}
void normal_game_process(block &choose0, block &choose1, block&choose2)
{
	char choosebox = 'Z';
	int x = 99;
	char c_y = 'Z';//the char of y_aixs
	int y;

	cout << "The choose 0 is" << endl;
	choose0.showblock();
	cout << endl << "The choose 1 is" << endl;
	choose1.showblock();
	cout << endl << "The choose 2 is" << endl;
	choose2.showblock();
	cout << "\nHint(You can input \"Quit\" for return to the Game Menu)" << endl;
	cout << "choose one of the box(0-2):";
	cin >> choosebox;
	if (choosebox == 'Q') { game_quit(choose0, choose1, choose2); }
	else if ((int)choosebox != 48 && (int)choosebox != 49 && (int)choosebox != 50)
	{
		wrong_input();
	}
	else {
		cout << "please input the location (eg:A0):";
		cin >> c_y;
		if (c_y == 'Q') { game_quit(choose0, choose1, choose2); }

		else {
			cin >> x;
			cin.clear();
			cin.ignore(10000, '\n');
			change_char_to_int(c_y, y);
			if (x >= 0 && x < 10) {
				if (y != 99) {
					switch ((int)choosebox) {
					case 48:process_choose0(choose0, y, x); break;
					case 49:process_choose1(choose1, y, x); break;
					case 50:process_choose2(choose2, y, x); break;
					}
					clear_full_lines();
					check_game_over(choose0, choose1, choose2);
					Bomb_gameover_checking();
				}
				else {
					wrong_input();
				}
			}
			else {
				wrong_input();
			}

		}
	}

}
void Ai_game_process(block &choose0, block &choose1, block&choose2)
{
	int x;
	int y;
	int choosebox;
	int shapeType;
	//show 3 choose here
	cout << "The choose 0 is" << endl;
	choose0.showblock();
	cout << "The choose 1 is" << endl;
	choose1.showblock();
	cout << "The choose 2 is" << endl;
	choose2.showblock();

	do {
		x = rand() % 10;
		y = rand() % 10;
		choosebox = rand() % 3;
		switch (choosebox)
		{
		case 0:shapeType = choose0.shapeType; break;
		case 1:shapeType = choose1.shapeType; break;
		case 2:shapeType = choose2.shapeType; break;
		}
	} while (!check_input_shape(shapeType, y, x));
	char c_y;
	switch (y)
	{
	case 0:c_y = 'A'; break;
	case 1:c_y = 'B'; break;
	case 2:c_y = 'C'; break;
	case 3:c_y = 'D'; break;
	case 4:c_y = 'E'; break;
	case 5:c_y = 'F'; break;
	case 6:c_y = 'G'; break;
	case 7:c_y = 'H'; break;
	case 8:c_y = 'I'; break;
	case 9:c_y = 'J'; break;
	}

	cout << "choose one of the box(0-2):" << choosebox << endl;
	cout << "please input the location (eg:A0):" << c_y << x << endl;
	system("pause");
	switch (choosebox) {
	case 0:process_choose0(choose0, y, x); break;
	case 1:process_choose1(choose1, y, x); break;
	case 2:process_choose2(choose2, y, x); break;
	}

	clear_full_lines();

	check_game_over(choose0, choose1, choose2);
	if (gamemode == 1)
		Bomb_gameover_checking();

}
void game_quit(block &choose0, block &choose1, block&choose2)
{
	string check;
	cin >> check;
	string ans = "NULL";
	if (check == "uit\0") {
		cout << "\n";
		cout << "Are you sure to leave?" << endl;
		do {
			cout << "If yes, please input 'y'/'Y':" << endl;
			cout << "If no, please input 'n'/'N':" << endl;
			cin >> ans;
			cin.clear();
			cin.ignore(10000, '\n');

			if (ans == "y" || ans == "Y")
			{
				game_over_flag = true;
			}
			else if (ans == "n" || ans == "N")
			{
				//do nothing
			}
			else
			{
				cout << "Wrong input! Please try again:" << endl;
			}
		} while (ans != "y" && ans != "Y" && ans != "n" && ans != "N");

	}
	else wrong_input();
}
bool is_game_over()
{
	return game_over_flag;
}
void play_normal_mode()
{
	game_over_flag = false;
	initialize_board();
	block choose0, choose1, choose2;
	Time_Bomb_Appear_Count = 0;
	while (!is_game_over())
	{
		refresh_board();
		if (Aimode == 1) {
			Ai_game_process(choose0, choose1, choose2);
		}
		else
			normal_game_process(choose0, choose1, choose2);

	}

	cout << "Game over!" << endl;
	cout << "You final marks : " << scores << endl;
}
void Start_Game()
{
	play_normal_mode();
	system("pause");
	if (Aimode == false && scores != 0) {
		if (scores > highest_mark) {
			highest_mark = scores;
			cout << "You are the highest mark ,please input your name : ";//updata the highest mark
			cin >> winner;
		}
		cout << "The highest mark is :" << endl;
		cout << winner << ":" << highest_mark << " mark " << endl;//to show the highest mark of the gmae
		system("pause");
	}
}
