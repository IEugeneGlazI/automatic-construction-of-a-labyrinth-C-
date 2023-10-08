#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

#define MAX_FOLDER_NAME 100
#define MAX_FILE_NAME 100


using namespace std;
const int wall = 0, pass = 1;

int finale_function() {
	printf("\n\nНажмите Enter для продолжения...");
	getchar();
	system("cls");
	return 0;
}

void info() {
	system("cls");
	printf("\nВНИМАНИЕ! Перед использованием программы прочитайте правила пользования.\nИначе выбранная вами задача может не вылолниться.\n\n");
	printf("\t\t\t\tО ПРОГРАММЕ:\n\n");
	printf("Передвижение по меню осуществляется стрелками, выбор пункта - клавишей ENTER.\n");
	printf("Пожалуйста, всегда вводите НЕЧЕТНЫЕ РАЗМЕРЫ лабиринта.\n");
	printf("Минимальный размер лабиринта 5 на 5.\n");
	printf("Ширина лабиринта не должна превышать 85.\n");
	printf("При сохранении лабиринта необходимо указывать папку, в которую вы хотите сохранить лабиринт, а также название самого файла.\n");
	printf("Старайтесь не использовать в названии файлов и папок различные символы.");
}

void dev() {
	system("cls");
	printf("\nДанную программу разработал студент гр. 1-42 ИВТФ ИГЭУ Глазков Евгений Владимирович в 2023 году\n");
}

void saveMazeToFile(int** maze, int height, int width, const char* fileName) {
	FILE* file = fopen(fileName, "w");
	if (file != NULL) {
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (maze[i][j] == 0)
					fprintf(file, "0 ");
				else
					fprintf(file, "  ");
			}
			fprintf(file, "\n");
		}
		fclose(file);
		printf("Массив сохранен в файле: %s\n", fileName);
	}
	else {
		printf("Не удалось открыть файл: %s\n", fileName);
	}
	system("pause");
	system("cls");
}

void printMazeFromFile(const char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file != NULL) {
		char buffer[1000];
		printf("Лабиринт из файла:\n\n");

		while (fgets(buffer, 1000, file) != NULL) {
			fputs(buffer, stdout);
		}
		printf("\n");
		fclose(file);
		system("pause");
		system("cls");
	}
	else {
		printf("Не удалось открыть файл: %s\n\n", fileName);
		system("pause");
		system("cls");
	}
}

bool deadend(int x, int y, int** maze, int height, int width) { // Определяем тупики
	int a = 0;

	if (x != 1) { // Лево
		if (maze[y][x - 2] == pass)
			a += 1;
	}
	else a += 1;

	if (y != 1) { // Верх
		if (maze[y - 2][x] == pass)
			a += 1;
	}
	else a += 1;

	if (x != width - 2) { // Право
		if (x < width - 2) {
			if (maze[y][x + 2] == pass)
				a += 1;
		}
	}
	else a += 1;

	if (y != height - 2) { //Низ
		if (y < height - 2) {
			if (maze[y + 2][x] == pass)
				a += 1;
		}
	}
	else a += 1;

	if (a == 4)
		return 1;
	else
		return 0;
}

void mazemake(int** maze, int height, int width) {
	int x, y, c, a;
	bool b;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			maze[i][j] = wall;

	x = 3; y = 3; a = 0;
	while (a < 100000) {
		maze[y][x] = pass; a++;
		while (1) {
			c = rand() % 4;
			switch (c) {
			case 0: if (y != 1)
				if (maze[y - 2][x] == wall) { // Вверх
					maze[y - 1][x] = pass;
					maze[y - 2][x] = pass;
					y -= 2;
				}
			case 1: if (y != height - 2)
				if (y < height - 2) {
					if (maze[y + 2][x] == wall) { // Вниз
						maze[y + 1][x] = pass;
						maze[y + 2][x] = pass;
						y += 2;
					}
				}
			case 2: if (x != 1)
				if (maze[y][x - 2] == wall) { // Налево
					maze[y][x - 1] = pass;
					maze[y][x - 2] = pass;
					x -= 2;
				}
			case 3: if (x != width - 2)
				if (x < width - 2) {
					if (maze[y][x + 2] == wall) { // Направо
						maze[y][x + 1] = pass;
						maze[y][x + 2] = pass;
						x += 2;
					}
				}
			}
			if (deadend(x, y, maze, height, width))
				break;
		}

		if (deadend(x, y, maze, height, width))
			do {
				x = 2 * (rand() % ((width - 1) / 2)) + 1;
				y = 2 * (rand() % ((height - 1) / 2)) + 1;
			} while (maze[y][x] != pass);
	}
}

void visual(int** maze, int height, int width) {
	maze[1][0] = pass;
	maze[height - 2][width - 1] = pass;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			switch (maze[i][j]) {
			case wall:  printf("0 "); break;
			case pass: printf("  "); break;
			}
		printf("\n");
	}
	printf("\n");
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hcon = GetConsoleWindow();

	RECT rect = { 0, 0, 1300, 700 };
	MoveWindow(hcon, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	CONSOLE_FONT_INFO cfi;
	GetCurrentConsoleFont(hConsole, false, &cfi);
	COORD fs = GetConsoleFontSize(hConsole, cfi.nFont);
	PCONSOLE_FONT_INFOEX ccf = new CONSOLE_FONT_INFOEX;
	(*ccf).dwFontSize.X = 9;
	(*ccf).dwFontSize.Y = 20;
	(*ccf).nFont = 11;
	(*ccf).cbSize = sizeof(CONSOLE_FONT_INFOEX);
	ccf->FontWeight = 400;
	lstrcpyW((*ccf).FaceName, L"Lucida Console");
	(*ccf).FontFamily = FF_DONTCARE;
	bool b = SetCurrentConsoleFontEx(hConsole, false, ccf);
	fs = GetConsoleFontSize(hConsole, cfi.nFont);

	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = false;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);


	int n = 5;
	COORD position[5];
	int punkt = 0;
	char names[5][25] = { "Сгенерировать лабиринт", "Открыть лабиринт", "О программе", "Разработчик", "Выход" };
	do
	{

		int xmax, ymax;
		// получение параметров окна 
		PCONSOLE_SCREEN_BUFFER_INFO pwi = new CONSOLE_SCREEN_BUFFER_INFO;
		PWINDOWINFO pgwi = new WINDOWINFO;
		GetConsoleScreenBufferInfo(hConsole, pwi);
		GetWindowInfo(hcon, pgwi);
		xmax = pwi->dwSize.X;
		ymax = pwi->dwSize.Y;

		int y0 = 10;
		for (int i = 0; i < n; i++)
		{
			position[i].X = (xmax - strlen(names[i])) / 2;
			position[i].Y = y0 + i;
		}

		system("color F0");
		char title[] = "ГЕНЕРАЦИЯ ЛАБИРИНТОВ";
		COORD pos;
		pos.X = (xmax - strlen(title)) / 2;
		pos.Y = 5;
		SetConsoleCursorPosition(hConsole, pos);
		puts(title);
		for (int i = 0; i < 5; i++)
		{
			SetConsoleCursorPosition(hConsole, position[i]);
			puts(names[i]);
		}
		system("color F0");
		SetConsoleTextAttribute(hConsole, 117 | FOREGROUND_INTENSITY);
		SetConsoleCursorPosition(hConsole, position[punkt]);	// выделение текущего пункта ярким цветом
		puts(names[punkt]);
		unsigned char ch;
		do
		{
			// обработка перемещения по меню клавишами со стрелками
			ch = _getch();
			if (ch == 224)
			{
				ch = _getch();
				switch (ch)
				{
				case 72:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					system("color F0");
					puts(names[punkt]);
					punkt--;
					if (punkt < 0) punkt = 4;
					SetConsoleTextAttribute(hConsole, 117 | FOREGROUND_INTENSITY);
					SetConsoleCursorPosition(hConsole, position[punkt]);
					puts(names[punkt]); break;
					system("color F0");
				case 80:
					SetConsoleCursorPosition(hConsole, position[punkt]);
					system("color F0");
					puts(names[punkt]);
					punkt++;
					if (punkt > 4) punkt = 0;
					SetConsoleTextAttribute(hConsole, 117 | FOREGROUND_INTENSITY);
					SetConsoleCursorPosition(hConsole, position[punkt]);
					puts(names[punkt]); break;
					system("color F0");
				}
			}
		} while (ch != 13);	// enter
		rewind(stdin);
		switch (punkt)
		{
		case 0:
		{
			system("cls");
			system("color F0");
			srand((unsigned)time(NULL));
			FILE* file;

			int height, width;
			printf("Введите размер лабиринта: ");
			scanf_s("%d %d", &height, &width);
			if (height % 2 == 0 || width % 2 == 0 || width > 85 || width < 5 || height < 5) {
				printf("\nОшибка, внимательнее ознакомьтесь с условиями работы программы.\n\n");
				system("pause");
				system("cls");
				break;
			}
			printf("\n");
			int** maze = new int* [height];
			for (int i = 0; i < height; i++)
				maze[i] = new int[width];

			mazemake(maze, height, width);

			visual(maze, height, width);

			getchar();

			printf("Вы хотите сохранить данный лабиринт в файл? - [д/н]\n- ");
			char Ans_User;
			Ans_User = getchar();
			getchar();
			if (Ans_User == 'д' || Ans_User == 'l' || Ans_User == 'Д' || Ans_User == 'L')
			{
				char folderName[MAX_FOLDER_NAME];
				char fileName[MAX_FILE_NAME];

				printf("Введите название папки: ");
				gets_s(folderName);

				printf("Введите название файла: ");
				gets_s(fileName);

				char a[10] = ".txt";
				strcat_s(fileName, a);

				char command[MAX_FOLDER_NAME + 5]; // Добавляем 5 символов для команды "mkdir "
				strcpy(command, "mkdir ");
				strcat(command, folderName);
				system(command);

				char filePath[MAX_FOLDER_NAME + MAX_FILE_NAME + 2]; // Добавляем 2 символа для разделителя "/"
				strcpy(filePath, folderName);
				strcat(filePath, "/");
				strcat(filePath, fileName);

				saveMazeToFile(maze, height, width, filePath);

				break;
			}

			for (int i = 0; i < height; i++)
				delete[] maze[i];
			delete[] maze;
			finale_function();
			break;
		}
		case 1: {
			system("cls");
			system("color F0");

			char folderName[MAX_FOLDER_NAME];
			char fileName[MAX_FILE_NAME];

			printf("Введите название папки: ");
			gets_s(folderName);

			printf("Введите название файла: ");
			gets_s(fileName);

			char a[10] = ".txt";
			strcat_s(fileName, a);

			char command[MAX_FOLDER_NAME + 5]; // Добавляем 5 символов для команды "mkdir "
			strcpy(command, "mkdir ");
			strcat(command, folderName);
			system(command);

			char filePath[MAX_FOLDER_NAME + MAX_FILE_NAME + 2]; // Добавляем 2 символа для разделителя "/"
			strcpy(filePath, folderName);
			strcat(filePath, "/");
			strcat(filePath, fileName);
			printf("\n");

			printMazeFromFile(filePath);
			break;
		}
		case 2:
			system("color F0");
			info();
			finale_function();
			break;
		case 3:
			system("color F0");
			dev();
			finale_function();
			break;
		}

	} while (punkt != 4);
	return 0;
}