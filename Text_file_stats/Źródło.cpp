#include <iostream> // standard input/output stream objects
using namespace std; // deklaracja u¿ycia przestrzeni nazw std::

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "pl_PL.utf8"); // próba umo¿liwienia programowi wyœwietlania polskich znaków --FAILED

	
	cout
		<< "*------------------------ - Wczytaj plik" << endl
		<< "| *---------------------- - Wyœwietl statystyki" << endl
		<< "| | *-------------------- - Wyœwietl liniê o danym numerze" << endl
		<< "| | | *------------------ - Zapis pliku w odwrotnej kolejnoœci linii tekstu" << endl
		<< "| | | | *---------------- - Zapis pliku w odwrotnej kolejnoœci znaków" << endl
		<< "| | | | | *-------------- - Zamianê polskich liter na ³aciñskie odpowiedniki" << endl
		<< "| | | | | " << endl;
	
	
	system("pause");
	exit(0);
}