#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct cell_el {
	bool alive;
	int numLivingNeighbors;
};
typedef struct cell_el cell;

const int width = 150;
const int height = 25;

void clearScreen()
{
	system("cls");
}

void resizeScreen() {
	char buffer[50];
	int n, a = 5, b = 3;
	n = sprintf_s(buffer, "mode %d,%d", 150, 80);
	system(buffer);   //Set mode to ensure window does not exceed buffer size
	//SMALL_RECT WinRect = { 0, 0, width, height };   //New dimensions for window in 8x12 pixel chars
	//SMALL_RECT* WinSize = &WinRect;
	//SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}

cell ** createBoard(int width, int height){

	cell **board;
	board = (cell **)malloc(height * sizeof(cell *));
	for (int i = 0; i < height; i++)
		board[i] = (cell*)malloc(width * sizeof(cell));

	return board;
}

void cleanBoard(cell ** board) {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		board[i][j].alive = false;
}

void deleteBoard(cell ** board) {

	for (int i = 0; i < height; i++)
		free(board[i]);

	free(board);
}

void readBoard(cell ** board) {
	char * fileName = "input.txt";
	char * mode = "r";
	FILE * file;
	fopen_s(&file, fileName, mode);

	int numCells;
	fscanf_s(file, "%d", &numCells);

	for (int i = 0; i < numCells; i++) {
		int x, y;
		fscanf_s(file, "%d", &x);
		fscanf_s(file, "%d", &y);

		board[x][y].alive = true;
	}

	fclose(file);
}

void printBoard(cell ** board) {
	clearScreen();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			printf("%c ", board[i][j].alive ? '1' : ' ');
	}
}

bool isValidCell(int x, int y, int rows, int columns)
{
	return (x >= 0 && x < rows) && (y >= 0 && y < columns);
}

void day(cell ** board) {

	int offset[8][2] = {
		{ -1, -1 },
		{ -1, 0 },
		{ -1, 1 },
		{ 0, -1 },
		{ 0, 1 },
		{ 1, -1 },
		{ 1, 0 },
		{ 1, 1 }
	};

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{

			int count = 0;

			for (int k = 0; k < 8; k++)
			{
				int x = i + offset[k][0];
				int y = j + offset[k][1];
				if (isValidCell(x, y, height, width))
				{
					if (board[x][y].alive)
						count ++;
				}
			}

			board[i][j].numLivingNeighbors = count;
		}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			/* Stays alive */
			if (board[i][j].alive) {
				if (!(board[i][j].numLivingNeighbors == 2 || board[i][j].numLivingNeighbors == 3))
					board[i][j].alive = false;
			}

			/* Born */
			else {
				if (board[i][j].numLivingNeighbors == 3)
					board[i][j].alive = true;
			}
		}
}

/* Main */
int main(int argc, char * argv[]) {

	resizeScreen();

	printf("Hello Army!\n\n");

	/* Create board */
	cell ** board = createBoard(width, height);

	/* Clear board */
	cleanBoard(board);

	/* Read board from file */
	readBoard(board);

	for (int i = 0; i < 1000; i++) {

		/* Print board */
		printBoard(board);

		/* Day */
		day(board);

		/* Wait for enter */
		char c = getchar();
	}
		
	/* Delete board */
	deleteBoard(board);

	/* stop the program from exiting */
	char c = getchar();
}