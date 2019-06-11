#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

struct file_stats
{
	int lower_count;       //Alpha characters in lowercase only: a-z.
	int upper_count;       //Alpha characters in uppercase only: A-Z.
	int alpha_count;       //Alpha characters : a - z, A - Z(upper - or lowercase).
	int space_count;       //Whitespace characters: ' `, \n, \t, \v, \r, \l.
	int punct_count;       //Control characters: ASCII 0-31 and 127.
	int diacr_count;       //Locale characters,
	int lines_count;       //How many '\n' is in the file
	string stored_lines[]; //
};

void get_stats()
{
	try
	{

		for (char c = file.get(); c != EOF; c = file.get())
		{
			cout << "-- File contents --" << endl;
			cout << c << endl;
			cout << "-- End --" << endl;
			cout << c << endl;

			if (islower(c))
			{
				lower_count++;
			}
			if (isupper(c))
			{
				upper_count++;
			}
			if (isalpha(c))
			{
				alpha_count++;
			}
			if (ispunct(c))
			{
				punct_count++;
			}
			if (isspace(c))
			{
				space_count++;
			}
		}
	}
	catch (const overflow_error& e)
	{
		// this executes if f() throws  overflow_error (same type rule)
		//all errors should be displayed BLOODY RED
	}
	catch (const runtime_error& e)
	{
		// this executes if f() throws  underflow_error (base class rule)
		//all errors should be displayed BLOODY RED
	}
	catch (const exception& e)
	{
		// this executes if f() throws  logic_error (base class rule)
		//all errors should be displayed BLOODY RED
	}
	catch (...)
	{
		// this executes if f() throws  string or int or any other unrelated type
		//all errors should be displayed BLOODY RED
	}
}

void read_file()
{
	fstream file;
	string filename;
	file.open(filename.c_str(), ios::in);

	if (!file)
	{
		cout << "Couldn't open " << filename << endl;
	}
	else
	{
		get_stats(file);
	}
	file.close();
}

void update_file()
{
}

void reverse_lines_order()
{
	//reverse lines order
	//the file will be overwriten
}

void reverse_chars_order()
{
	//reverse chars order
	//the file will be overriten
}

int main(int argc, char** argv)
{
	if (argc >= 1 && argc <= 3)
	{

		if (argc = 1)
		{
			//-h for help-display syntax and availabe arguments.
			//else run in single shot mode (text user interface)
			for (;;) // pozwala na wyświetlanie "menu" programu pomimo czyszcznia konsoli
			{
				system("cls");

				//remember last choice and invert colors
				//display requested stat
				cout << "******************\n";
				cout << "wyświetlenie linii nr # podanej przez użytkownika" <<
					<< "- nawigowanie pomiędzy kolejnymi liniami tekstu z pliku(za pomocą klawiszy strzałek)" << //if arr count++ and display arr[count] w podmenu
					<< "- zapis pliku w odwrotnej kolejności linii tekstu" <<
					<< "- zapis pliku w odwrotnej kolejności znaków" << 
					<< "- zamianę polskich liter na łacińskie odpowiedniki " << 
					<< "- ilość znaków" <<
					<< "- ilość liter(w tym małych i dużych oraz polskich)" <<
					<< "- ilość zdań" <<
					<< "- ilość wyrazów(spójniki nie są wyrazami)" <<
					<< "- ilość linii tekstu w pliku(za linię uznajemy ciąg znaków zakończony \"enterem\")" <<
					system("pause");
				cout << "******************\n";
				exit(0);
			}
		}
		if (argc = 2)
		{
			// run full auto mode
			// just print ALL the results
		}
		if (argc = 3)
		{
			// run semi auto mode
			// user wants to see only specyfic info
		}
	}
	else
	{
		//bloody red SMT WENT WRONG
	}
}
