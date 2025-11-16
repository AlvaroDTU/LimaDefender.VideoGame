#include "pch.h"
#include "iostream"
#include "characters.h"
#include "essentials.h"
#include "scenery.h"
#include "conio.h"
#include "cctype"
struct Enemigo {
    bool activo;
    double x;
    int y;
    int tipo;
    int vida;
    bool atacando;
    int cooldownataque;
};
struct Vecino {
    bool activo;
    int x;
    int y;
    int cooldown;
    int vida;
};
struct Bala {
    bool activa;
    double x;
    int y;
    int linea;
};
int main() {
	srand(time(nullptr));
	Console::SetWindowSize(190, 50);
	Console::CursorVisible = false;
    bool inicio = true, juego = false, gameOver = false, nivel[] = { 0, 0, 0, 0 };
	while (true) {
		int xopciones = 1, yopciones = 1;
        inicio = true, juego = false, gameOver = false;
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
			while (_getch() != 13) {}
            slod1();
            while (_getch() != 13) {}
			bool barra_seleccion[3] = { false,false,false };
			nivel_surco();
            puntosVecinales();
			int xprota = 31, yprota = 16;
			int xcasilla = 40, ycasilla = 15;
            //Constantes por nivel
			const int numLineas = 4;
            const int numColumnas = 3;
			const int maxEnemigosLinea = 2;
            const int MAX_BALAS = 20;
            int yLineas[numLineas] = { 16, 25, 34, 43 };
            
			int enemigosGenerados = 0;
			int enemigosEliminados = 0;
			int maxEnemigosNivel = 14;

			int spawnCooldown = 100;
            const int TIEMPO_ENTRE_DISPAROS = 50;
            int puntosV = 100;

            Enemigo enemigos[numLineas][maxEnemigosLinea];
            Vecino vecinos[numLineas][numColumnas];
            Bala balas[MAX_BALAS];
            //Inicializar enemigos
            for (int l = 0; l < numLineas; l++) {
                for (int s = 0; s < maxEnemigosLinea; s++) {
                    enemigos[l][s].activo = false;
                    enemigos[l][s].x = 0;
                    enemigos[l][s].y = 0;
                    enemigos[l][s].tipo = 0;
                    enemigos[l][s].vida = 3;
                }
            }
            //Inicializar vecinos
            for (int l = 0; l < numLineas; l++)
                for (int c = 0; c < numColumnas; c++) {
                    vecinos[l][c].activo = false;
                    vecinos[l][c].cooldown = 0;
                    vecinos[l][c].x = 0;
                    vecinos[l][c].y = 0;
                    vecinos[l][c].vida = 5;
                }

            //Inicializar balas
            for (int i = 0; i < MAX_BALAS; i++) {
                balas[i].activa = false;
                balas[i].x = 0;
                balas[i].y = 0;
                balas[i].linea = 0;
            }
			//INICIO ANIMACIONES NIVEL 1
            while (nivel[0])
            {
                // SISTEMA DE PUNTOS VECINALES
                gotoxy(6, 1);
                Console::BackgroundColor = ConsoleColor::White;
                Console::ForegroundColor = ConsoleColor::Black;
                cout << puntosV<<" ";

                barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;


                //----------------------------------------------------------
                // 1. SPAWN DE ENEMIGOS
                //----------------------------------------------------------
                if (enemigosGenerados < maxEnemigosNivel)
                {
                    if (spawnCooldown <= 0)
                    {
                        int lineaRandom = rand() % numLineas;

                        for (int s = 0; s < maxEnemigosLinea; s++)
                        {
                            if (!enemigos[lineaRandom][s].activo)
                            {
                                enemigos[lineaRandom][s].activo = true;
                                enemigos[lineaRandom][s].x = 181;
                                enemigos[lineaRandom][s].y = yLineas[lineaRandom];
                                enemigos[lineaRandom][s].tipo = 1 + rand() % 3;
                                enemigos[lineaRandom][s].vida = 3;
                                enemigos[lineaRandom][s].atacando = false;
                                enemigos[lineaRandom][s].cooldownataque = 0;
                                enemigosGenerados++;
                                spawnCooldown = 100;
                                break;
                            }
                        }
                    }
                    else spawnCooldown--;
                }


                //----------------------------------------------------------
                // 2. MOVER + DIBUJAR ENEMIGOS
                //----------------------------------------------------------
                for (int l = 0; l < numLineas; l++)
                {
                    for (int s = 0; s < maxEnemigosLinea; s++)
                    {
                        if (!enemigos[l][s].activo) continue;

                        borrar_enemigo((int)enemigos[l][s].x, enemigos[l][s].y);

                        switch (enemigos[l][s].tipo) {
                            case 1: enemigos[l][s].x -= 0.2; break;
                            case 2: enemigos[l][s].x -= 1.0; break;
                            case 3: enemigos[l][s].x -= 0.5; break;
                        }

                        if (enemigos[l][s].x <= 42) {
                            enemigos[l][s].activo = false;
                            gameOver = true;
                            break;
                        }

                        switch (enemigos[l][s].tipo) {
                        case 1: dibujar_enemigo_poli((int)enemigos[l][s].x, enemigos[l][s].y); break;
                        case 2: dibujar_enemigo_chamo((int)enemigos[l][s].x, enemigos[l][s].y); break;
                        case 3: dibujar_enemigo_choro((int)enemigos[l][s].x, enemigos[l][s].y); break;
                        }
                    }
                }
                if (gameOver) break;
                //----------------------------------------------------------
                // 3. DETECTAR ENEMIGOS EN CADA LÍNEA
                //----------------------------------------------------------
                bool enemigoEnLinea[numLineas] = { false,false,false,false };

                for (int l = 0; l < numLineas; l++)
                    for (int s = 0; s < maxEnemigosLinea; s++)
                        if (enemigos[l][s].activo) enemigoEnLinea[l] = true;


                //----------------------------------------------------------
                // 4. BORRAR PROTAGONISTA Y CASILLA ANTERIOR
                //----------------------------------------------------------
                borrar_prota(xprota, yprota);
                borrarcasilla(xcasilla, ycasilla);


                //----------------------------------------------------------
                // 5. INPUT DEL JUGADOR (MOV + PLANTAR VECINO)
                //----------------------------------------------------------
                if (_kbhit()) {
                    char tecla = tolower(_getch());

                    if (tecla == 'w' && yprota > 16) { yprota -= 9; ycasilla -= 9; }
                    if (tecla == 's' && yprota < 41) { yprota += 9; ycasilla += 9; }
                    if (tecla == 'a' && xcasilla > 40) { xcasilla -= 14; }
                    if (tecla == 'd' && xcasilla < 68) { xcasilla += 14; }

                    if (tecla == '1')
                    {
                        if (puntosV >= 25) {
                            int lineaActual = (yprota - 16) / 9;
                            int columnaActual = (xcasilla - 40) / 14;

                            vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
                            vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
                            vecinos[lineaActual][columnaActual].cooldown = 0;
                            vecinos[lineaActual][columnaActual].activo = true;
                            puntosV -= 25;
                            barra_seleccion[0] = true;
                        }
                        
                    }
                }


                //----------------------------------------------------------
                // 6. DISPARO AUTOMÁTICO
                //----------------------------------------------------------
                for (int l = 0; l < numLineas; l++)
                {
                    for (int c = 0; c < numColumnas; c++)
                    {
                        if (!vecinos[l][c].activo) continue;
                        if (!enemigoEnLinea[l]) {
                            vecinos[l][c].cooldown = 0;
                            continue;
                        }
                        if (vecinos[l][c].cooldown > 0) {
                            vecinos[l][c].cooldown--;
                            continue;
                        }
                        // Crear bala
                        for (int i = 0; i < MAX_BALAS; i++) {
                            if (!balas[i].activa) {
                                balas[i].activa = true;
                                balas[i].x = vecinos[l][c].x + 8;
                                balas[i].y = vecinos[l][c].y + 2;
                                balas[i].linea = l;
                                break;
                            }
                        }
                        vecinos[l][c].cooldown = TIEMPO_ENTRE_DISPAROS;
                    }
                }


                //----------------------------------------------------------
                // 7. MOVER BALAS 
                //----------------------------------------------------------
                for (int i = 0; i < MAX_BALAS; i++)
                {
                    if (!balas[i].activa) continue;

                    borrar_bala((int)balas[i].x, balas[i].y);
                    balas[i].x += 1.0;
                    //COLISION MAPA
                    if (balas[i].x > 185) {
                        balas[i].activa = false;
                        continue;
                    }

                    //COLISION CON EL ENEMIGO
                    for (int s = 0; s < maxEnemigosLinea; s++)
                    {
                        if (!enemigos[balas[i].linea][s].activo) continue;

                        if (balas[i].x >= enemigos[balas[i].linea][s].x && balas[i].x <= enemigos[balas[i].linea][s].x + 8)
                        {
                            balas[i].activa = false;
                            enemigos[balas[i].linea][s].vida--;
                            if (enemigos[balas[i].linea][s].vida == 0) {
                                borrar_enemigo((int)enemigos[balas[i].linea][s].x, enemigos[balas[i].linea][s].y);
                                enemigos[balas[i].linea][s].activo = false;
                                puntosV += 20;
                                enemigosEliminados++;
                                enemigos[balas[i].linea][s].vida = 3;
                            }
                            break;
                        }
                    }

                    if (balas[i].activa)
                        dibujar_bala((int)balas[i].x, balas[i].y);
                }


                //----------------------------------------------------------
                // 8. REDIBUJAR VECINOS + PROTA + CASILLA
                //----------------------------------------------------------
                for (int l = 0; l < numLineas; l++)
                    for (int c = 0; c < numColumnas; c++)
                        if (vecinos[l][c].activo)
                            dibujar_vecino1(vecinos[l][c].x, vecinos[l][c].y);

                dibujar_prota(xprota, yprota);
                casilla(xcasilla, ycasilla);
                //----------------------------------------------------------
                // 9. HUD
                //----------------------------------------------------------
                barra_nivelSurcoYCallao(barra_seleccion);


                //----------------------------------------------------------
                // 10. FIN DEL NIVEL
                //----------------------------------------------------------
                if (enemigosGenerados == maxEnemigosNivel &&
                    enemigosEliminados == maxEnemigosNivel)
                {
                    nivel[0] = false;
                    nivel[1] = true;
                    gameOver = false;
                    break;
                }

                //----------------------------------------------------------
                // 11. FPS
                //----------------------------------------------------------
                _sleep(30);
            }
            if (gameOver) {
                juego = false;
                Perdiste();
                while (_getch() == 13) {}
                break;
            }
		}
	}
    return 0;
}
	