/*
Instituto Tecnologico de Costa Rica

Integrantes:	Owel Jafet Gutiérrez Ortiz,		2026800869
				Miranda Jiménez Alvarado,		2026008616
				Keishiro Gabriel Cubero Abe,	2026091245
				Eduardo Alfonso Moreno Pérez,	2025080891

Profesor : Mauricio Aviles Cisneros

Semana 13 : Proyecto 0 - Juegos de Solitario

Fecha de entrega : 26 / 10 / 2026

*/

/*
Programa principal (main):
	Punto de entrada del sistema de solitarios. Muestra el menu para elegir
	entre Golf y Spider, o salir. Crea el juego elegido como un objeto de
	tipo Game (polimorfismo), y repite sus rondas (init, play y end) mientras
	el jugador quiera continuar. Valida la opcion del menu y captura las
	excepciones que puedan lanzar las clases del juego.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../src/golf/GolfGame.h"
#include "../src/spider/SpiderGame.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::exception;
using std::srand;
using std::time;

void clearLine() {
	cin.ignore(1000, '\n');
}

int main()
{
	srand(time(nullptr));  // una sola vez

	try {
		int option = 0;
		while (option != 3) {
			cout << "┌───────────────────┐" << endl;
			cout << "│     SOLITARIO     │" << endl;
			cout << "├───────────────────┤" << endl;
			cout << "│ 1. Golf           │" << endl;
			cout << "│ 2. Spider         │" << endl;
			cout << "│ 3. Salir          │" << endl;
			cout << "├───────────────────┤" << endl;
			cout << "│ Opcion:           │\r│ Opcion: ";
			cin >> option;
			cout << "\033[F" << "│ Opcion: " << option << "         │" << endl;
			cout << "└───────────────────┘" << endl;

			if (cin.eof()) {  // se cerro la entrada: salir
				break;
			}
			if (cin.fail()) {  // escribieron letras en vez de un numero
				cin.clear();
				option = 0;
			}

			if (option == 3) {
				cout << "Cerrando juego..." << endl;
				cout << "¡Hasta pronto!" << endl;
				break;
			}
			clearLine();
			if (option != 1 && option != 2) {
				cout << "Error, opción incorrecta (1, 2 o 3)." << endl;
				continue;
			}

			Game* game;
			if (option == 1) {
				game = new GolfGame();
			}
			else {
				game = new SpiderGame();
			}

			char again;
			do {
				game->init();
				game->play();
				game->end();

				cout << "¿Jugar de nuevo? (s/n): "; 
				cin >> again;
				clearLine();
			} while (again == 's' || again == 'S');
			delete game;
		}
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}