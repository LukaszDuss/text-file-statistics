
#include "pch.h" // precompiled header
#include <iostream> // standard input/output stream objects
#include <stdlib.h> // C++ standard library
#include <math.h> // common mathematical operations and transformations
#include <regex> // regular expression library
#include <fstream> // Stream class to both read and write from/to files.
#include<windows.h>
#include <stdio.h>

#define KEY_UP 0x26
#define KEY_DOWN 0x28
#define KEY_X 0x58

#define ERROR "\x1B[31m"
#define SUCCESS "\x1B[32m"
#define	WARNING "\x1B[33m"
#define DARK_BLUE "\033[3;44;93m"
#define	LIGHT_BLUE "\033[3;104;93m"
#define DARK_GREY "\033[3;100;30m"
#define	LIGHT_GREY "\033[3;100;93m"
#define RESET "\033[0m"

using namespace std; // deklaracja użycia przestrzeni nazw std::

string *filePath;
string *newFilePath;

struct textFileStats {
	int lowerCount;       //Alpha characters in lowercase only: a-z.
	int upperCount;       //Alpha characters in uppercase only: A-Z.
	int spaceCount;       //Whitespace characters: ' `, \n, \t, \v, \r, \l.
	int enterCount;		  //Enters
	int digitCount;		  //Digits
	int diactCount;		  //Diacritis characters
	int punctCount;       //Other characters
	int count;			  //All characters
};

struct fileCharsCache {
	int charNumber;
	char character;
};
fileCharsCache* charsCache;

struct fileLinesCache {
	int lineNumber;
	string line;
};
fileLinesCache* linesCache;

string NumDigits(int x)
{
	x = abs(x);
	return (x < 10 ? "     " :
		(x < 100 ? "    " :
		(x < 1000 ? "   " :
			(x < 10000 ? "  " :
				" "))));
}
void getFilePath() {
	system("CLS");
	cout << DARK_BLUE
		<< ".________________________________________________________________________." << endl
		<< "|                                                                        |" << endl
		<< "|                   PODAJ ŚCIEŻKĘ DO PLIKU TESKTOWEGO:                   |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET
		<< WARNING
		<< "\t\tNa przyklad: 'C:\\Dokumenty\\pliktekstowy.txt"
		<< RESET << endl;
	cin >> *filePath;
	if (filePath != NULL) {
		cout << endl << "Podano: " << endl << *filePath << endl << endl;
	}
	else
	{
		cout << ERROR << endl << "Nie podano ścieżki lub ścieżka jest niepoprawna" << endl << *filePath << endl;
		getFilePath();
	}
}

void getNewFilePath() {
	system("CLS");
	cout << DARK_BLUE
		<< ".________________________________________________________________________." << endl
		<< "|                                                                        |" << endl
		<< "|             PODAJ ŚCIEŻKĘ DLA NOWEGO PLIKU TESKTOWEGO:                 |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET
		<< WARNING
		<< "\t\tNa przyklad: 'C:\\Dokumenty\\pliktekstowy.txt"
		<< RESET << endl;
	cin >> *newFilePath;
	if (newFilePath != NULL) {
		cout << endl << "Podano: " << endl << *newFilePath << endl << endl;
	}
	else
	{
		cout << ERROR << endl << "Nie podano ścieżki lub ścieżka jest niepoprawna" << endl << *newFilePath << endl;
		getNewFilePath();
	}
}

int getCharsCount() {
	int charCount = 0;
	string path = *filePath;
	fstream file;
	file.open(path.c_str(), ios::in);

	if (!file)
	{
		cout << ERROR << endl << "Couldn't open " << path << endl;
	}
	else
	{
		for (char c = file.get(); c != EOF; c = file.get())
		{
			charCount++;
		}
	}
	file.close();
	return charCount;
}

int getLinesCount() {
	int lineCount = 0;
	string tmp;
	string path = *filePath;
	fstream file;
	file.open(path.c_str(), ios::in);
	if (!file)
	{
		cout << ERROR << endl << "Couldn't open " << path << endl;
	}
	else
	{
		while (!file.eof()) {
			getline(file, tmp);
			lineCount++;
		}
	}
	file.close();

	return lineCount;
}


void displayCachedLines() {
	int linesCount = getLinesCount();
	char userInput = 'i';
	int line = 0;
	while (userInput != 'x')
	{
		int lineLength = linesCache[line].line.length();
		string tmp = "";
		string tmp2 = "";
		for (int i = 1; i < 64 - lineLength; i++)
		{
			tmp += " ";
		}

		(line+1 < 10 ? tmp2 = "   " :
			(line+1 < 100 ? tmp2 = "  " : ""));

		system("CLS");
		cout << DARK_BLUE
			<< ".________________________________________________________________________." << endl
			<< "|                                                                        |" << endl
			<< "|                       WYŚWIETLANIE LINI " << line + 1 << NumDigits(line)<< tmp2 << "                       |" << endl
			<< "|                                                                        |" << endl
			<< "|    Strzalka do góry poprzednia linia          (-)                      |" << endl
			<< "|    Strzalka na dól następna linia             (+)                      |" << endl
			<< "|    Wciśnij x aby powrócić do glównego menu     x                       |" << endl
			<< "|________________________________________________________________________|" << endl
			<< RESET << LIGHT_BLUE
			<< "|                                                                        |" << endl
			<< RESET << LIGHT_GREY
			<< "|  " << line + 1 << ": " << linesCache[line].line << tmp << tmp2 << " |" << endl
			<< RESET << LIGHT_BLUE
			<< "|                                                                        |" << endl
			<< "|________________________________________________________________________|" << endl
			<< RESET;
		cout << linesCache[line].line.length();
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD NumInputs = 0;
		DWORD InputsRead = 0;
		bool running = true;

		INPUT_RECORD irInput;

		GetNumberOfConsoleInputEvents(hInput, &NumInputs);

		ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

		switch (irInput.Event.KeyEvent.wVirtualKeyCode) {
		case KEY_UP:
			if (line > 0) {
				line--;
			}
			system("pause");
			break;
		case KEY_DOWN:
			if (line < linesCount - 1)
			{
				line++;
			}
			system("pause");
			break;
		case KEY_X:
			system("CLS");
			cout << DARK_BLUE
				<< ".________________________________________________________________________." << endl
				<< "|                                                                        |" << endl
				<< "|                       POWRÓT DO GLOWNEGO MENU                          |" << endl
				<< "|                                                                        |" << endl
				<< "|________________________________________________________________________|" << endl
				<< RESET;
			userInput = 'x';
			system("pause");
			break;
		default:
			break;
		}
	}
}

void reverseLinesOrder() {
	getNewFilePath();

}

void reverseCharsOrder() {
	getNewFilePath();

}

void deletePolishChars() {
	getNewFilePath();

}


void getFileToCache() {
	try
	{
		int charCount = getCharsCount();
		int lineCount = getLinesCount();

		charsCache = new fileCharsCache[charCount];
		linesCache = new fileLinesCache[lineCount];

		string path = *filePath;
		fstream file;
		file.open(path.c_str(), ios::in);

		if (!file)
		{
			cout << ERROR << endl << "Couldn't open " << path << endl;
		}
		else
		{
			int i = 0;
			for (char c = file.get(); c != EOF; c = file.get())
			{
				charsCache[i].character = c;
				i++;
				charsCache[i].charNumber = i;
			}
		}
		file.close();

		file.open(path.c_str(), ios::in);
		if (!file)
		{
			cout << ERROR << endl << "Couldn't open " << path << endl;
		}
		else
		{
			int i = 0;
			while (!file.eof()) {

				getline(file, linesCache[i].line);
				i++;
				linesCache[i].lineNumber = i;
			}
		}
		file.close();

		system("pause");
		system("CLS");
	}
	catch (...)
	{
		// this executes if f() throws  string or int or any other unrelated type
		//all errors should be displayed BLOODY RED
	}
}


void displayStatistics(textFileStats fileStats, int lineCount)
{
	string tmp;
	(lineCount < 10 ? tmp = "                          " :
		(lineCount < 100 ? tmp = "                        " :
		(lineCount < 1000 ? tmp = "                       " :
			(lineCount < 10000 ? tmp = "                      " :
				tmp = "                     "))));

	system("CLS");
	cout << LIGHT_GREY
		<< ".________________________________________________________________________." << endl
		<< "|                                                                        |" << endl
		<< "|              STATYSTYKA PLIKU PODANEGO PRZEZ UŻYTKOWNIKA               |" << endl
		<< "|                                                                        |" << endl
		<< RESET
		<< DARK_BLUE
		<< ".________________________________________________________________________." << endl
		<< "|                                                                        |" << endl
		<< "|    +--------------------------------------------- Wszystkie znaki      |" << endl
		<< "|    |     +--------------------------------------- Wielkie litery       |" << endl
		<< "|    |     |     +--------------------------------- Male litery          |" << endl
		<< "|    |     |     |     +--------------------------- Spacje               |" << endl
		<< "|    |     |     |     |     +--------------------- Polskie znaki        |" << endl
		<< "|    |     |     |     |     |     +--------------- Cyfry                |" << endl
		<< "|    |     |     |     |     |     |     +--------- Inne znaki           |" << endl
		<< "|    |     |     |     |     |     |     |     +--- Ilość linii/zdań     |" << endl
		<< "|____|_____|_____|_____|_____|_____|_____|_____|_________________________|" << endl
		<< RESET
		<< LIGHT_BLUE
		<< "|"
		<< NumDigits(fileStats.count)
		<< fileStats.count
		<< NumDigits(fileStats.upperCount)
		<< fileStats.upperCount
		<< NumDigits(fileStats.lowerCount)
		<< fileStats.lowerCount
		<< NumDigits(fileStats.spaceCount)
		<< fileStats.spaceCount
		<< NumDigits(fileStats.diactCount)
		<< fileStats.diactCount
		<< NumDigits(fileStats.digitCount)
		<< fileStats.digitCount
		<< NumDigits(fileStats.punctCount)
		<< fileStats.punctCount
		<< NumDigits(fileStats.punctCount)
		<< lineCount
		<< tmp << "|" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET;

	system("pause");
	system("CLS");
}

void getStats()
{
	try
	{
		int linesCount = getLinesCount();
		string path = *filePath;
		fstream file;
		file.open(path.c_str(), ios::in);

		if (!file)
		{
			cout << ERROR << "NIE MOŻNA OTWORZYĆ PLIKU: " << path << endl;
		}
		else
		{
			textFileStats fileStats;
			fileStats.lowerCount = 0;
			fileStats.upperCount = 0;
			fileStats.spaceCount = 0;
			fileStats.enterCount = 0;
			fileStats.punctCount = 0;
			fileStats.digitCount = 0;
			fileStats.diactCount = 0;
			fileStats.count = 0;

			for (char c = file.get(); c != EOF; c = file.get())
			{
				//cout << c << " - ";
				//cout << int(c) << endl;
				fileStats.count++;
				if ((int(c) >= 97) && (int(c) <= 122)) {
					fileStats.lowerCount++;
				}
				else if ((int(c) >= 65) && (int(c) <= 90)) {
					fileStats.upperCount++;
				}
				else if (int(c) == 32) {
					fileStats.spaceCount++;
				}
				else if (int(c) == 10)
				{
					fileStats.enterCount++;
				}
				else if ((int(c) >= 48) && (int(c) <= 57)) {
					fileStats.digitCount++;
				}
				else if ((int(c) >= -116) && (int(c) <= -1)) {

					fileStats.diactCount++;
				}
				else {
					fileStats.punctCount++;
				}
			}
			displayStatistics(fileStats, linesCount);
		}
		file.close();
	}
	catch (...)
	{
		// this executes if f() throws  string or int or any other unrelated type
		//all errors should be displayed BLOODY RED
	}
}
void subMenuSelector(char userSubChoice) {
	switch (userSubChoice) {
	case 'z':
	case 'Z':
		reverseCharsOrder();
		break;
	case'l':
	case 'L':
		reverseLinesOrder();
		break;
	case 'b':
	case 'B':
		cout << DARK_GREY
			<< ".________________________________________________________________________." << endl
			<< "|                                                                        |" << endl
			<< "|                       POWRÓT DO GLOWNEGO MENU                          |" << endl
			<< "|                                                                        |" << endl
			<< "|________________________________________________________________________|" << endl
			<< RESET;
		system("pause");
		break;
	default:
		cout << ERROR << endl << "NIEPOPRAWNY WYBÓR" << endl;
		system("pause");
		break;
	}
}

void displaySubMenu() {
	char userSubChoice;
	system("CLS");
	cout << DARK_BLUE
		<< ".________________________________________________________________________." << endl
		<< "|                                                                        |" << endl
		<< "|                   ZAPIS PLIKU W ODWROTNEJ KOLEJNOŚCI                   |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET
		<< LIGHT_BLUE
		<< "|                                                                        |" << endl
		<< "|     Z - ZAPISZ W ODWROTNEJ KOLEJNOŚCI ZNAKAMI                          |" << endl
		<< "|                                                                        |" << endl
		<< "|     L - ZAPISZ W ODWROTNEJ KOLEJNOŚCI LINIAMI                          |" << endl
		<< "|                                                                        |" << endl
		<< "|     B - POWRÓT DO GLOWNEGO MENU                                        |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET;
	cin >> userSubChoice;
	system("CLS");
	subMenuSelector(userSubChoice);
}

void menuSelector(char userChoice) {
	switch (userChoice) {
	case 'p':
	case 'P':
		getFilePath();
		break;
	case 's':
	case 'S':
		getStats();
		break;
	case 'l':
	case 'L':
		displayCachedLines();
		break;
	case 'o':
	case 'O':
		displaySubMenu();
		break;
	case 'u':
	case 'U':
		deletePolishChars();
		break;
	case 'q':
	case 'Q':
		cout << ERROR
			<< "PROGRAM ZAKOŃCZY SWOJE DZIALANIE!" << endl
			<< RESET;
		system("pause");
		exit(0);
		break;
	default:
		cout << ERROR << endl << "NIEPOPRAWNY WYBÓR" << endl;
		system("pause");
		break;
	}
}

void displayMenu() {
	char userChoice;
	system("CLS");
	cout << DARK_BLUE
		<< ".________________________________________________________________________." << endl
		<< "|                                                                        |" << endl
		<< "|             MENU PROGRAMU - STATYSTYKA PLIKU TEKSTOWEGO                |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET
		<< LIGHT_BLUE
		<< "|                                                                        |" << endl
		<< "|     P - WYBIERZ ŚCIEŻKĘ PLIKU                                          |" << endl
		<< "|     S - WYŚWIETL STATYSTYKI PLIKU                                      |" << endl
		<< "|     L - WYŚWIETL PLIK LINIA PO LINII                                   |" << endl
		<< "|     O - ZAPIS PLIKU W ODWROTNEJ KOLEJNOŚCI                             |" << endl
		<< "|     U - USUNIĘCIE POLSKICH ZNAKÓW                                      |" << endl
		<< "|     Q - WYJŚCIE Z PROGRAMU                                             |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET;
	cin >> userChoice;
	system("CLS");
	menuSelector(userChoice);
}


int main(int argc, char *argv[]) // main( ilość argumentów, tablica pointerów argumentów)
{
	setlocale(LC_ALL, "Polish"); // umożliwienia programowi wyświetlania polskich znaków
	filePath = new string;
	newFilePath = new string;
	system("CLS"); // wyczyść konsole

	if ((argc > 0) && (argc < 4))
	{
		if ((argc = 1) || (argc = 2))
		{
			if (argc = 1)
			{
				cout << "Program w trybie single shot" << endl;
				getFilePath();
			}
			else
			{
				cout << "Program w trybie burst shot" << endl;
			}
			getFileToCache();
			while (true) {
				displayMenu();
			}
		}
		else {
			if (argc = 3)
			{
				cout << "Program w trybie full auto" << endl;

				//file and operation defined by user - full auto mode
			}
		}
	}
	else
	{
		cout << "Nieprawidlowa ilość argumentów!" << endl;
	}
}
