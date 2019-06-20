#include <vector>
#include "pch.h" // precompiled header
#include <iostream> // standard input/output stream objects
//#include <stdlib.h> // C++ standard library
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
		<< "|                   PODAJ ŚCIEŻKĘ DO PLIKU TEKSTOWEGO:                   |" << endl
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET
		<< WARNING
		<< "\t\tNa przyklad: 'C:\\Dokumenty\\pliktekstowy.txt"
		<< RESET << endl;
	cin >> *filePath;
	if (filePath == NULL) {
		getFilePath();
	}
}



int getCharsCount() {
	int charCount = 0;
	string path = *filePath;
	fstream file;
	file.open(path.c_str(), ios::in);

	if (!file)
	{
		char repeat;
		cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
			<< RESET << path << ERROR
			<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
			<< RESET << endl
			<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;
		cin >> repeat;
		if ((repeat == 'T') || (repeat == 't'))
		{
			getFilePath();
		}
		else
		{
			exit(0);
		}
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
		cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
			<< RESET << path << ERROR
			<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
			<< RESET << endl
			<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

		char repeat;
		cin >> repeat;
		if ((repeat == 'T') || (repeat == 't'))
		{
			getFilePath();
		}
		else
		{
			exit(0);
		}
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

		(line + 1 < 10 ? tmp2 = "   " :
			(line + 1 < 100 ? tmp2 = "  " : ""));

		system("CLS");
		cout << DARK_BLUE
			<< ".________________________________________________________________________." << endl
			<< "|                                                                        |" << endl
			<< "|                       WYŚWIETLANIE LINI " << line + 1 << NumDigits(line) << tmp2 << "                       |" << endl
			<< "|                                                                        |" << endl
			<< "|    Strzalka w górę poprzednia linia           (-)                      |" << endl
			<< "|    Strzalka w dól następna linia              (+)                      |" << endl
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
		//cout << linesCache[line].line.length();
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
			break;
		default:
			break;
		}
	}
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
			cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
				<< RESET << path << ERROR
				<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
				<< RESET << endl
				<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

			char repeat;
			cin >> repeat;
			if ((repeat == 'T') || (repeat == 't'))
			{
				getFilePath();
				getFileToCache();
			}
			else
			{
				exit(0);
			}
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

		//do rozdzielenia na osobne funkcje

		file.open(path.c_str(), ios::in);
		if (!file)
		{
			cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
				<< RESET << path << ERROR
				<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
				<< RESET << RESET << endl
				<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

			char repeat;
			cin >> repeat;
			if ((repeat == 'T') || (repeat == 't'))
			{
				getFilePath();
				getFileToCache();
			}
			else
			{
				exit(0);
			}
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
		cout << "Niespodziewany bląd, program zostanie zamknięty" << endl;
		exit(0);
	}
}

void reverseLinesOrder() {
	int linesCount = getLinesCount();
	string path = *filePath;
	fstream file;
	file.open(path.c_str(), ios::in);
	vector <string> cache;
	cache.reserve(linesCount);
	if (!file)
	{
		cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
			<< RESET << path << ERROR
			<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
			<< RESET << endl
			<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

		char repeat;
		cin >> repeat;
		if ((repeat == 'T') || (repeat == 't'))
		{
			getFilePath();
			getFileToCache();
			reverseLinesOrder();
		}
		else
		{
			exit(0);
		}
	}
	else
	{
			while (!file.eof()) {
				string tmp;
				getline(file, tmp);
				cache.push_back(tmp);
			}
		file.close();

		//system("CLS");
		cout << DARK_BLUE
			<< ".________________________________________________________________________." << endl
			<< "|                                                                        |" << endl
			<< "|      LINIE ZOSTANĄ ODWRÓCONE ORAZ ZAPISANE W PLIKU TEKSTOWYM           |" << endl
			<< "|      ORYGINALNY PLIK ZOSTANIE ZMODYFIKOWANY NA STALĘ...                |" << endl
			<< "|      CZY NA PEWNO CHCESZ ZAPISAC ZMIANY DO PLIKU? (T/n)                |" << endl
			<< "|________________________________________________________________________|" << endl
			<< RESET;
		char choice;
		cin >> choice;
		if ((choice == 'T') || (choice == 't') || (choice == 'Y') || (choice == 'y'))
		{
			file.open(path.c_str(), ios::out);
			for (int i = linesCount - 1; i >= 0; i--) {
				file << cache.at(i) << "\n";
			}
			file.close();
		}


		system("pause");
	}
}




void reverseCharsOrder() {
	int charsCount = getCharsCount();
	string path = *filePath;
	fstream file;
	file.open(path.c_str(), ios::in);
	vector <char> cache;
	cache.reserve(charsCount);
	if (!file)
	{
		cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
			<< RESET << path << ERROR
			<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
			<< RESET << endl
			<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

		char repeat;
		cin >> repeat;
		if ((repeat == 'T') || (repeat == 't'))
		{
			getFilePath();
			getFileToCache();
			reverseCharsOrder();
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		for (char c = file.get(); c != EOF; c = file.get())
		{
				cache.push_back(c);
		}
		file.close();

		//system("CLS");
		cout << DARK_BLUE
			<< ".________________________________________________________________________." << endl
			<< "|                                                                        |" << endl
			<< "|      ZNAKI ZOSTANĄ ODWRÓCONE ORAZ ZAPISANE W PLIKU TEKSTOWYM           |" << endl
			<< "|      ORYGINALNY PLIK ZOSTANIE ZMODYFIKOWANY NA STALĘ...                |" << endl
			<< "|      CZY NA PEWNO CHCESZ ZAPISAC ZMIANY DO PLIKU? (T/n)                |" << endl
			<< "|________________________________________________________________________|" << endl
			<< RESET;
		char choice;
		cin >> choice;
		if ((choice == 'T') || (choice == 't') || (choice == 'Y') || (choice == 'y'))
		{
			file.open(path.c_str(), ios::out);
			for (int i = charsCount-1; i >= 0; i--) {
				file << cache.at(i);
			}
			file.close();
		}


		system("pause");
	}
}





void deletePolishChars() {

	int charsCount = getCharsCount();
	string path = *filePath;
	fstream file;
	file.open(path.c_str(), ios::in | ios::out);
	vector <char> cache;
	cache.reserve(charsCount);
	if (!file)
	{
		cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
			<< RESET << path << ERROR
			<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
			<< RESET << endl
			<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

		char repeat;
		cin >> repeat;
		if ((repeat == 'T') || (repeat == 't'))
		{
			getFilePath();
			getFileToCache();
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		for (char c = file.get(); c != EOF; c = file.get())
		{
			switch (c) {
			case 'ą':
				cache.push_back('a');
				break;
			case 'ć':
				cache.push_back('c');
				break;
			case 'ę':
				cache.push_back('e');
				break;
			case 'ł':
				cache.push_back('l');
				break;
			case 'ń':
				cache.push_back('n');
				break;
			case 'ó':
				cache.push_back('o');
				break;
			case 'ś':
				cache.push_back('s');
				break;
			case 'ż':
			case 'ź':
				cache.push_back('z');
				break;
			case 'Ą':
				cache.push_back('A');
				break;
			case 'Ć':
				cache.push_back('C');
				break;
			case 'Ę':
				cache.push_back('E');
				break;
			case 'Ł':
				cache.push_back('L');
				break;
			case 'Ń':
				cache.push_back('N');
				break;
			case 'Ó':
				cache.push_back('O');
				break;
			case 'Ś':
				cache.push_back('S');
				break;
			case 'Ż':
			case 'Ź':
				cache.push_back('Z');
				break;
			default:
				cache.push_back(c);
				break;
			}
		}
		file.close();

		//system("CLS");
		cout << DARK_BLUE
			<< ".________________________________________________________________________." << endl
			<< "|                                                                        |" << endl
			<< "|      POLSKIE ZNAKI ZOSTALY USUNIĘTE Z KOPII W PAMIĘCI PODRĘCZNEJ       |" << endl
			<< "|      ORYGINALNY PLIK ZOSTANIE ZMODYFIKOWAN NA STALĘ...                 |" << endl
			<< "|      CZY NA PEWNO CHCESZ ZAPISAC ZMIANY DO PLIKU? (T/n)                |" << endl
			<< "|________________________________________________________________________|" << endl
			<< RESET;
		char choice;
		cin >> choice;
		if ((choice == 'T') || (choice == 't') || (choice == 'Y') || (choice == 'y'))
		{
			file.open(path.c_str(), ios::out);
			//save cached chars to file
			for (int i = 0; i < charsCount; i++) {
				file << cache[i];
			}
			file.close();
		}


		system("pause");
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
		<< "|                                                                        |" << endl
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
		file.open(path.c_str(), ios::in );

		if (!file)
		{
			cout << ERROR << "WYSTĄPIL BLAD PODCZAS OTWIERANIA PLIKU!!" << endl
				<< RESET << path << ERROR
				<< " -NIE JEST POPRAWNĄ ŚCIEŻKĄ DO PLIKU" << endl
				<< RESET << endl
				<< "Czy chces podać ścieżkę pliku ponownie? (T/N)" << endl;

			char repeat;
			cin >> repeat;
			if ((repeat == 'T') || (repeat == 't'))
			{
				getFilePath();
				getStats();
			}
			else
			{
				exit(0);
			}
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
		<< "|                                                                        |" << endl
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
		<< "|                                                                        |" << endl
		<< "|________________________________________________________________________|" << endl
		<< RESET;
	cin >> userChoice;
	system("CLS");
	menuSelector(userChoice);
}

void simplyfiedMenu() {
	cout << "nope" << endl;

}


int main(int argc, char *argv[]) // main( ilość argumentów, tablica pointerów argumentów)
{
	setlocale(LC_ALL, "Polish"); // umożliwienia programowi wyświetlania polskich znaków
	filePath = new string;
	newFilePath = new string;
	system("CLS"); // wyczyść konsole

	switch (argc) {
	case 1:
	{
		getFilePath();
		getFileToCache();
		while (true) {
			displayMenu();
		}
	}
	break;
	case 2:
	{
		if ((*argv[1] == 'H') || (*argv[1] == 'h') || (*argv[1] == '?') || (*argv[1] == 'help') || (*argv[1] == 'm') || (*argv[1] == 'man') || (*argv[1] == 'i') || (*argv[1] == 'info'))
		{
			cout << DARK_BLUE
				<< ".________________________________________________________________________." << endl
				<< "|                                                                        |" << endl
				<< "|         INSTRUKCJA PROGRAMU \"STATYSTYKA PLIKU TEKSTOWEGO\"              |" << endl
				<< "|                                                                        |" << endl
				<< "|________________________________________________________________________|" << endl
				<< RESET
				<< LIGHT_BLUE
				<< "|                                                                        |" << endl
				<< "|   ABY WLACZYĆ PROGAM W TRYBIE AUTOMATYCZNYM LUB PÓL AUTOMATYCZNYM      |" << endl
				<< "|   UŻYTKOWNIK MUSI PODAC DODATKOWE ARGUMENTY PRZY WLĄCZANIU PROGRAMU    |" << endl
				<< "|   OBSLUGIWANE POLECENIA(ARGUMENTY):                                    |" << endl
				<< "|                                                                        |" << endl
				<< "|     STAT   - WYŚWIETL STATYSTYKI PLIKU                                 |" << endl
				<< "|     LINE   - WYŚWIETL PLIK LINIA PO LINII                              |" << endl
				<< "|     SRL    - ZAPIS PLIKU W ODWROTNEJ KOLEJNOŚCI LINII                  |" << endl
				<< "|     SRCH   - ZAPIS PLIKU W ODWROTNEJ KOLEJNOŚCI ZNAKÓW                 |" << endl
				<< "|     DEL    - USUNIĘCIE POLSKICH ZNAKÓW                                 |" << endl
				<< "|                                                                        |" << endl
				<< "|                                                                        |" << endl
				<< "|   PROGRAM WYMAGA WPROWADZENIA PELNEJ SCIEŻKI DO PLIKU.                 |" << endl
				<< "|   PRZYKLADOWO:                                                         |" << endl
				<< "|   C:\\MOJE DOKUMENTY\\PLIKI TEKSTOWE\\PLIK TEKSTOWY.TXT                   |" << endl
				<< "|                                                                        |" << endl
				<< "|   SKLADNIA:                                                            |" << endl
				<< "|   {NAZWA_EXE}* {ŚCIEŻKA_PLIKU}* {ARGUMENT}                             |" << endl
				<< "|   * - WYMAGANE                                                         |" << endl
				<< "|                                                                        |" << endl
				<< "|   PRZYKLADOWO:                                                         |" << endl
				<< "|                                                                        |" << endl
				<< "|   TEXT-STATS.EXE  C:\\PLIK.TXT  STAT                                    |" << endl
				<< "|   PODANIE POWYŻSZEJ KOMENDY W WIERSZU POLECEŃ WYŚWIETLI STATYSTYKI     |" << endl
				<< "|   DLA PLIKU \"PLIK.TXT\" ZNAJDUJĄCEGO SIĘ NA DYSKU C                     |" << endl
				<< "|                                                                        |" << endl
				<< "|   TEXT-STATS.EXE C:\\PLIK.TXT                                           |" << endl
				<< "|   PODANIE POWYŻSZEJ KOMENDY W WIERSZU POLECEŃ WYŚWIETLI PELEN MENU     |" << endl
				<< "|   PROGRAMU Z ZALADOWANYM PLIKIEM TEKSOWYM \"PLIK.TXT\"                   |" << endl
				<< "|   ZNAJDUJĄCYM SIĘ NA DYSKU C                                           |" << endl
				<< "|                                                                        |" << endl
				<< "|                                                                        |" << endl
				<< "|________________________________________________________________________|" << endl
				<< RESET;
			exit(0);
		}
		else
		{
			*filePath = argv[1];
		}

		getFileToCache();
		while (true) {
			displayMenu();
		}
	}
	break;
	case 3:
	{
		*filePath = argv[1];
		char choice = *argv[2];
		cout << "Program w trybie full auto" << endl;
		system("pause");
	}
	break;
	default:
	{
		cout << "Nieprawidlowa ilość argumentów!" << endl;
		exit(0);
	}
	break;
	}

}




