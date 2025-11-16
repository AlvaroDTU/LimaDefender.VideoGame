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
				char tecla = tolower(_getch());
				switch (tecla) {
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
						while (_getch() != 13) {}
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
		while (juego) {
			slod0();
			_sleep(250);
			while (_getch() != 13) {}
			slod1();
			_sleep(250);
			while (_getch() != 13) {}
			bool barra_seleccion[3] = { false,false,false };
			nivel_surco();
			int xprota = 31, yprota = 16;
			int xcasilla = 40, ycasilla = 15;
			const int numLineas = 4;
			const int maxEnemigos = 2;
			int enemigosGenerados = 0;
			int enemigosEliminados = 0;
			int maxEnemigosNivel = 14;
			int yLineas[numLineas] = { 16, 25, 34, 43 };

			bool activoBala[numLineas][3];
			int balaX[numLineas][3];
			int balaY[numLineas][3];

			// Inicializar balas
			for (int linea = 0; linea < numLineas; linea++) {
				for (int b = 0; b < 3; b++) {
					activoBala[linea][b] = false;
				}
			}
			bool enemigoActivo[numLineas][maxEnemigos];
			double enemigoX[numLineas][maxEnemigos];
			int enemigoTipo[numLineas][maxEnemigos];
			int spawnCooldown = 100;
			
			// Inicialización
			for (int linea = 0; linea < numLineas; linea++) {
				for (int slot = 0; slot < maxEnemigos; slot++) {
					enemigoActivo[linea][slot] = false;
				}
			}
			//INICIO ANIMACIONES NIVEL 1
			while (nivel[0])
			{
				barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;
				if (enemigosGenerados < maxEnemigosNivel) {
					if (spawnCooldown < 0) {
						for (int slot = 0; slot < maxEnemigos; slot++) {
							int lineaRandom = rand() % 4;
							if (enemigoActivo[lineaRandom][slot] == false) {
								enemigoActivo[lineaRandom][slot] = true;
								enemigoX[lineaRandom][slot] = 181;
								enemigoTipo[lineaRandom][slot] = 1 + rand() % 3;
								spawnCooldown = 100;
								enemigosGenerados++;
								break;
							}
						}
					}
				}
					for (int linea = 0; linea < numLineas; linea++) {
						for (int slot = 0; slot < maxEnemigos; slot++) {
							if (!enemigoActivo[linea][slot]) continue;
							borrar_enemigo((int)enemigoX[linea][slot], yLineas[linea]);
							enemigoX[linea][slot] -= 0.2;
							if (enemigoX[linea][slot] <= 50) {
								enemigoActivo[linea][slot] = false;
								enemigosEliminados++;
								continue;
							}
							switch (enemigoTipo[linea][slot]) {
							case 1: dibujar_enemigo_poli((int)enemigoX[linea][slot], yLineas[linea]); break;
							case 2: dibujar_enemigo_chamo((int)enemigoX[linea][slot], yLineas[linea]); break;
							case 3: dibujar_enemigo_choro((int)enemigoX[linea][slot], yLineas[linea]); break;
							}
						}
					}
					spawnCooldown--;
				
				// ----------------------------------------------------
				// 3. BORRAR PROTAGONISTA DEL FRAME ANTERIOR
				// ----------------------------------------------------
				borrar_prota(xprota, yprota);
				borrarcasilla(xcasilla, ycasilla);
				// ----------------------------------------------------
				// 4. PROCESAR INPUT DEL JUGADOR
				// ----------------------------------------------------
				if (_kbhit()) {
					char tecla = tolower(_getch());

					if (tecla == 'w' && yprota > 16) { yprota -= 9;  ycasilla -= 9; }
					if (tecla == 's' && yprota < 41) { yprota += 9;  ycasilla += 9; }
					if (tecla == 'a' && xcasilla > 40) { xcasilla -= 14; }
					if (tecla == 'd' && xcasilla < 68) { xcasilla += 14; }

					if (tecla == '1' || tecla == '2') {

						// DIBUJAR EL VECINO
						borrar_enemigo(xcasilla + 3, yprota);

						if (tecla == '1') dibujar_vecino1(xcasilla + 3, yprota);
						if (tecla == '2') dibujar_vecino2(xcasilla + 3, yprota);

						// MARCAR BARRA
						barra_seleccion[(tecla == '1' ? 0 : 1)] = true;

						// ---- DISPARO AUTOMÁTICO ----

						int lineaActual = (yprota - 16) / 9;

						for (int b = 0; b < 3; b++) {
							if (!activoBala[lineaActual][b]) {

								activoBala[lineaActual][b] = true;
								balaX[lineaActual][b] = xcasilla + 8;
								balaY[lineaActual][b] = yprota;

								break;
							}
						}
					}
				}
				// =======================================
//   MOVIMIENTO DE BALAS + COLISIONES
// =======================================
				for (int linea = 0; linea < numLineas; linea++) {
					for (int b = 0; b < 3; b++) {

						if (!activoBala[linea][b]) continue;

						// BORRAR FRAME ANTERIOR
						borrar_bala(balaX[linea][b], balaY[linea][b]);

						// AVANZAR
						balaX[linea][b] += 1;

						// SI SALE DEL MAPA
						if (balaX[linea][b] > 185) {
							activoBala[linea][b] = false;
							continue;
						}

						// COLISION CON ENEMIGOS
						for (int slot = 0; slot < maxEnemigos; slot++) {

							if (!enemigoActivo[linea][slot]) continue;

							int ex = (int)enemigoX[linea][slot];
							int ey = yLineas[linea];

							// DETECCIÓN SIMPLE (AABB)
							if (balaX[linea][b] >= ex - 2 && balaX[linea][b] <= ex + 4) {

								borrar_enemigo(ex, ey);
								enemigoActivo[linea][slot] = false;

								// matar bala
								activoBala[linea][b] = false;

								break;
							}
						}

						if (activoBala[linea][b]) {
							dibujar_bala(balaX[linea][b], balaY[linea][b]);
						}
					}
				}


				// ----------------------------------------------------
				// 5. DIBUJAR PROTAGONISTA Y CASILLA
				// ----------------------------------------------------
				dibujar_prota(xprota, yprota);
				casilla(xcasilla, ycasilla);


				// ----------------------------------------------------
				// 6. BARRA / HUD
				// ----------------------------------------------------
				barra_nivelSurcoYCallao(barra_seleccion);


				// ----------------------------------------------------
				// 7. PAUSA (FPS)
				// ----------------------------------------------------
				_sleep(30);
			}
		}
	}
	return 0;
}
	