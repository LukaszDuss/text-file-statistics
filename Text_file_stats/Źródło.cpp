#include <iostream> // standard input/output stream objects
using namespace std; // deklaracja u�ycia przestrzeni nazw std::

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "pl_PL.utf8"); // pr�ba umo�liwienia programowi wy�wietlania polskich znak�w --FAILED

	
	cout
		<< "*------------------------ - Wczytaj plik" << endl
		<< "| *---------------------- - Wy�wietl statystyki" << endl
		<< "| | *-------------------- - Wy�wietl lini� o danym numerze" << endl
		<< "| | | *------------------ - Zapis pliku w odwrotnej kolejno�ci linii tekstu" << endl
		<< "| | | | *---------------- - Zapis pliku w odwrotnej kolejno�ci znak�w" << endl
		<< "| | | | | *-------------- - Zamian� polskich liter na �aci�skie odpowiedniki" << endl
		<< "| | | | | " << endl;
	
	
	system("pause");
	exit(0);
}