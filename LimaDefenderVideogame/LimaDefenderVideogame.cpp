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
		
			_sleep(250);
			while (_getch() != 13) {}
			bool barra_seleccion[3] = { false,false,false };
			nivel_surco();
			int xprota = 31, yprota = 16;
			int xcasilla = 40, ycasilla = 15;
			const int numLineas = 4;
			const int maxEnemigos = 2;
            const int numColumnas = 3;
			int enemigosGenerados = 0;
			int enemigosEliminados = 0;
			int maxEnemigosNivel = 14;
			int yLineas[numLineas] = { 16, 25, 34, 43 };
            bool vecinoActivo[numLineas][numColumnas];
            const int MAX_BALAS = 20;
            bool balaActiva[MAX_BALAS];
            double balaX[MAX_BALAS];
            int balaY[MAX_BALAS];
            int balaLinea[MAX_BALAS];
            int cooldownDisparo[numLineas][numColumnas] = { 0 };
            const int TIEMPO_ENTRE_DISPAROS = 50;
            bool enemigoActivo[numLineas][maxEnemigos] = { false };
			double enemigoX[numLineas][maxEnemigos];
			int enemigoTipo[numLineas][maxEnemigos];
			int spawnCooldown = 100;
            for (int linea = 0; linea < numLineas; linea++) {
                for (int slot = 0; slot < numColumnas; slot++) {
                    vecinoActivo[linea][slot] = false;
                }
            }
            for (int i = 0; i < MAX_BALAS; i++)
                balaActiva[i] = false;
			//INICIO ANIMACIONES NIVEL 1

            while (nivel[0])
            {
                barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;

                // ================================================================
                // 1. SPAWN DE ENEMIGOS (hasta maxEnemigosNivel)
                // ================================================================
                if (enemigosGenerados < maxEnemigosNivel)
                {
                    if (spawnCooldown <= 0)
                    {
                        int lineaRandom = rand() % numLineas;

                        for (int slot = 0; slot < maxEnemigos; slot++)
                        {
                            if (!enemigoActivo[lineaRandom][slot])
                            {
                                enemigoActivo[lineaRandom][slot] = true;
                                enemigoX[lineaRandom][slot] = 181;
                                enemigoTipo[lineaRandom][slot] = 1 + rand() % 3;

                                enemigosGenerados++;
                                spawnCooldown = 80 + rand() % 40;
                                break;
                            }
                        }
                    }
                    else spawnCooldown--;
                }


                // ================================================================
                // 2. MOVER + DIBUJAR ENEMIGOS
                // ================================================================
                for (int linea = 0; linea < numLineas; linea++)
                {
                    for (int slot = 0; slot < maxEnemigos; slot++)
                    {
                        if (!enemigoActivo[linea][slot]) continue;

                        borrar_enemigo((int)enemigoX[linea][slot], yLineas[linea]);

                        enemigoX[linea][slot] -= 0.2;

                        if (enemigoX[linea][slot] <= 50)
                        {
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


                // ================================================================
                // 3. DETECTAR ENEMIGOS POR LÍNEA
                // ================================================================
                bool enemigoEnLinea[numLineas] = { false,false,false,false };

                for (int linea = 0; linea < numLineas; linea++)
                {
                    for (int slot = 0; slot < maxEnemigos; slot++)
                    {
                        if (enemigoActivo[linea][slot])
                        {
                            enemigoEnLinea[linea] = true;
                            break;
                        }
                    }
                }


                // ================================================================
                // 4. BORRAR PROTAGONISTA Y CASILLA ANTERIOR
                // ================================================================
                borrar_prota(xprota, yprota);
                borrarcasilla(xcasilla, ycasilla);


                // ================================================================
                // 5. INPUT DEL JUGADOR (MOVIMIENTO + COLOCAR VECINOS)
                // ================================================================
                if (_kbhit()) {
                    char tecla = tolower(_getch());

                    if (tecla == 'w' && yprota > 16) { yprota -= 9;  ycasilla -= 9; }
                    if (tecla == 's' && yprota < 41) { yprota += 9;  ycasilla += 9; }
                    if (tecla == 'a' && xcasilla > 40) { xcasilla -= 14; }
                    if (tecla == 'd' && xcasilla < 68) { xcasilla += 14; }

                    if (tecla == '1' || tecla == '2')
                    {
                        borrar_enemigo(xcasilla + 3, yprota);

                        if (tecla == '1') dibujar_vecino1(xcasilla + 3, yprota);
                        if (tecla == '2') dibujar_vecino2(xcasilla + 3, yprota);

                        barra_seleccion[(tecla == '1' ? 0 : 1)] = true;

                        int lineaActual = (yprota - 16) / 9;
                        int columnaActual = (xcasilla - 40) / 14;

                        vecinoActivo[lineaActual][columnaActual] = true;
                    }
                }


                // ================================================================
                // 6. DISPARO CONTINUO TIPO LANZAGUISANTES
                // ================================================================
                for (int linea = 0; linea < numLineas; linea++)
                {
                    for (int col = 0; col < numColumnas; col++)
                    {
                        if (!vecinoActivo[linea][col]) continue;

                        // NO hay enemigos, resetear cooldown y no disparar
                        if (!enemigoEnLinea[linea])
                        {
                            cooldownDisparo[linea][col] = 0;
                            continue;
                        }

                        // Hay enemigos,  bajar cooldown
                        if (cooldownDisparo[linea][col] > 0)
                        {
                            cooldownDisparo[linea][col]--;
                            continue;
                        }

                        // Disparar (crear una nueva bala)
                        for (int i = 0; i < MAX_BALAS; i++) {
                            if (!balaActiva[i]) {
                                balaActiva[i] = true;

                                balaX[i] = 41 + col * 14 + 8;
                                balaY[i] = yLineas[linea] + 2;
                                balaLinea[i] = linea;
                                break;
                            }
                        }

                        // Reiniciar cooldown
                        cooldownDisparo[linea][col] = TIEMPO_ENTRE_DISPAROS;
                    }
                }


                // ================================================================
                // 7. MOVER + DIBUJAR BALAS + COLISIONES
                // ================================================================
                for (int i = 0; i < MAX_BALAS; i++)
                {
                    if (!balaActiva[i]) continue;

                    borrar_bala((int)balaX[i], balaY[i]);

                    balaX[i] += 1.4;

                    int linea = balaLinea[i];

                    if (balaX[i] > 185)
                    {
                        balaActiva[i] = false;
                        continue;
                    }

                    for (int slot = 0; slot < maxEnemigos; slot++)
                    {
                        if (!enemigoActivo[linea][slot]) continue;

                        int ex = (int)enemigoX[linea][slot];

                        if (balaX[i] >= ex - 2 && balaX[i] <= ex + 6)
                        {
                            borrar_enemigo(ex, yLineas[linea]);
                            enemigoActivo[linea][slot] = false;
                            enemigosEliminados++;

                            balaActiva[i] = false;
                            break;
                        }
                    }

                    if (balaActiva[i])
                        dibujar_bala((int)balaX[i], balaY[i]);
                }


                // ================================================================
                // 8. DIBUJAR PROTA + CASILLA
                // ================================================================
                dibujar_prota(xprota, yprota);
                casilla(xcasilla, ycasilla);


                // ================================================================
                // 9. HUD
                // ================================================================
                barra_nivelSurcoYCallao(barra_seleccion);


                // ================================================================
                // 10. FIN DEL NIVEL
                // ================================================================
                if (enemigosGenerados == maxEnemigosNivel &&
                    enemigosEliminados == maxEnemigosNivel)
                {
                    nivel[0] = false;
                    break;
                }
                // ================================================================
                // 11. FPS
                // ================================================================
                _sleep(30);
            }
		}
	}
    return 0;
}
	