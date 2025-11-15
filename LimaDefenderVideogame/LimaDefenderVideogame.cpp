#include "pch.h"
#include "iostream"
#include "characters.h"
#include "essentials.h"
#include "scenery.h"
#include "conio.h"
#include "cctype"
int main() {
	srand(time(nullptr));
	Console::SetWindowSize(190, 50);
	Console::CursorVisible = false;
	bool inicio = true, juego = false, nivel[] = { 0, 0, 0, 0 };
	while (true) {
		int xopciones = 1, yopciones = 1;
		inicio = true, juego = false;
		imprime_mapa();
		imprime_titulo(55, 3);
		imprime_play(60, 29);
		imprime_credits(90, 39);
		imprime_exit(60, 39);
		imprime_instructions(79, 29);
		system("pause>nul");
		while (inicio) {
			if (_kbhit()) {
				char tecla = getch();
				switch (tolower(tecla)) {
				case 'w':
					if (yopciones == 2) yopciones--;
					break;
				case 'a':
					if (xopciones == 2) xopciones--;
					break;
				case 's':
					if (yopciones == 1) yopciones++;
					break;
				case 'd':
					if (xopciones == 1) xopciones++;
					break;
				case 13:
					if (xopciones == 1 && yopciones == 1) {
						inicio = false;
						juego = true;
						nivel[0] = true;
					}
					if (xopciones == 1 && yopciones == 2) {
						system("color 0F");
						system("cls");
						exit(0);
					}
					if (xopciones == 2 && yopciones == 1) {
						inicio = false;
						juego = false;
						instrucciones();
						while(_getch()!=13){}
					}
					if (xopciones == 2 && yopciones == 2) {
						inicio = false;
						juego = false;
						credits();
						while (_getch() != 13) {}
					}
				}
			}
			if (inicio) {
				if (xopciones == 1 && yopciones == 1) {

					imprime_credits(90, 39);
					imprime_exit(60, 39);
					imprime_instructions(79, 29);
					imprime_selectedplay(60, 29);
				}
				if (xopciones == 2 && yopciones == 1) {
					imprime_play(60, 29);
					imprime_credits(90, 39);
					imprime_exit(60, 39);
					imprime_selectedinstructions(79, 29);
				}
				if (xopciones == 1 && yopciones == 2) {
					imprime_play(60, 29);
					imprime_credits(90, 39);
					imprime_instructions(79, 29);
					imprime_selectedexit(60, 39);
				}
				if (xopciones == 2 && yopciones == 2) {
					imprime_play(60, 29);
					imprime_exit(60, 39);
					imprime_instructions(79, 29);
					imprime_selectedcredits(90, 39);
				}
			}
		}
		//REVISAR SLOTS DE JUEGO (PLAY)

		while (juego) {
			slod0();
			_sleep(250);
			while (_getch() != 13) {}
			slod1();
			_sleep(250);
			while (_getch() != 13) {}
			bool barra_seleccion[3] = { false,false,false };
			nivel_surco();
			barra_nivelSurcoYCallao(barra_seleccion);
			int xprota = 31, yprota = 16;
			int xcasilla = 40, ycasilla = 15;
			const int numLineas = 4;
			const int maxEnemigos = 2; // máximo de enemigos por línea

			int yEnemigos[] = { 16, 25, 34, 43 };
			int lineasActivas[numLineas] = { 0,0,0,0 };
			lineasActivas[rand() % numLineas] = 1; // activa una al azar

			double xEnemigo[numLineas][maxEnemigos];
			int tipoEnemigo[numLineas][maxEnemigos];
			bool enemigoActivo[numLineas][maxEnemigos];
			// Inicializa todo vacío
			for (int i = 0; i < numLineas; i++) {
				for (int j = 0; j < maxEnemigos; j++) {
					enemigoActivo[i][j] = false;
					xEnemigo[i][j] = 0;
					tipoEnemigo[i][j] = 0;
				}
			}
			int enemigosActivos = 1;
			int contadorTiempo = 0;
			int spawnTimer = 0;
			// Crea el primer enemigo
			int lineaInicial = rand() % numLineas;
			enemigoActivo[lineaInicial][0] = true;
			xEnemigo[lineaInicial][0] = 170;
			tipoEnemigo[lineaInicial][0] = 1 + rand() % 3;


			while (nivel[0])
			{
					// Dibujar enemigos
					for (int i = 0; i < numLineas; i++) {
						if (!lineasActivas[i]) continue;

						for (int j = 0; j < maxEnemigos; j++) {
							if (!enemigoActivo[i][j]) continue;

							double& x = xEnemigo[i][j];
							int tipo = tipoEnemigo[i][j];

							switch (tipo) {
							case 1: dibujar_enemigo_poli(x, yEnemigos[i]); break;
							case 2: dibujar_enemigo_chamo(x, yEnemigos[i]); break;
							case 3: dibujar_enemigo_choro(x, yEnemigos[i]); break;
							}

							_sleep(0);
							borrar_enemigo(x, yEnemigos[i]);
							x -= 2;

							if (x <= 50) enemigoActivo[i][j] = false; // desaparece si sale del mapa
						}
					}

					// Activa nuevas líneas poco a poco
					contadorTiempo++;
					if (contadorTiempo > 30 && enemigosActivos < numLineas) {
						int nuevaLinea;
						do {
							nuevaLinea = rand() % numLineas;
						} while (lineasActivas[nuevaLinea] == 1);
						lineasActivas[nuevaLinea] = 1;
						enemigosActivos++;
						contadorTiempo = 0;
					}

					// Crea nuevos enemigos de forma aleatoria en líneas activas
					spawnTimer++;
					if (spawnTimer > 50) {
						int linea = rand() % numLineas;
						if (lineasActivas[linea]) {
							// busca un espacio libre en esa línea
							for (int j = 0; j < maxEnemigos; j++) {
								if (!enemigoActivo[linea][j]) {
									enemigoActivo[linea][j] = true;
									xEnemigo[linea][j] = 165 + rand() % 15;
									tipoEnemigo[linea][j] = 1 + rand() % 3;
									break;
								}
							}
						}
						spawnTimer = 0;
					}
				//dibujar
				dibujar_prota(xprota, yprota);
				casilla(xcasilla, ycasilla);
				//espacio
				_sleep(100);
				//borrar
				borrar_prota(xprota, yprota);
				borrarcasilla(xcasilla, ycasilla);
				//cambiar posicion
				if (kbhit()) {
					char tecla = _getch();
					if (tolower(tecla) == 'w' && yprota > 16) { yprota -= 9; ycasilla -= 9; }
					if (tolower(tecla) == 's' && yprota < 41) { yprota += 9; ycasilla += 9; }
					if (tolower(tecla) == '1') {
						borrar_enemigo(xcasilla + 3, yprota);
						dibujar_vecino1(xcasilla + 3, yprota);
						barra_seleccion[0] = true;
					}
					if (tolower(tecla) == '2') {
						borrar_enemigo(xcasilla + 3, yprota);
						dibujar_vecino2(xcasilla + 3, yprota);
						barra_seleccion[1] = true;
					}
					if (tolower(tecla) == 'a' && xcasilla > 40) {
						xcasilla -= 14;
					}
					if (tolower(tecla) == 'd' && xcasilla < 68) {
						xcasilla += 14;
					}
					barra_nivelSurcoYCallao(barra_seleccion);
					barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;


				}
			}
		}
	}
	return 0;
}
	