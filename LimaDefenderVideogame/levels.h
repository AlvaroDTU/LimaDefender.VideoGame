#pragma once
#include "iostream"
#include "essentials.h"
#include "characters.h"
#include "scenery.h"
#define upkey 72
#define downkey 80
#define rightkey 77
#define leftkey 75
int Menu() {
	PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	mapa();
	titulo(55, 3);
	imprime_play(60, 29, 0);
	imprime_credits(90, 39, 0);
	imprime_exit(60, 39, 0);
	imprime_instructions(79, 29, 0);
	system("pause>nul");
	int xopciones = 1, yopciones = 1;
	while (true) {
		if (xopciones == 1 && yopciones == 1) {
			imprime_play(60, 29, 1);
			imprime_credits(90, 39, 0);
			imprime_exit(60, 39, 0);
			imprime_instructions(79, 29, 0);

		}
		if (xopciones == 2 && yopciones == 1) {
			imprime_play(60, 29, 0);
			imprime_credits(90, 39, 0);
			imprime_exit(60, 39, 0);
			imprime_instructions(79, 29, 1);
		}
		if (xopciones == 1 && yopciones == 2) {
			imprime_play(60, 29, 0);
			imprime_credits(90, 39, 0);
			imprime_exit(60, 39, 1);
			imprime_instructions(79, 29, 0);
		}
		if (xopciones == 2 && yopciones == 2) {
			imprime_play(60, 29, 0);
			imprime_credits(90, 39, 1);
			imprime_exit(60, 39, 0);
			imprime_instructions(79, 29, 0);
		}
		if (_kbhit()) {
			int tecla = _getch();
			if (tecla == 224) {
				int flecha = _getch();
				switch (flecha) {
				case upkey: if (yopciones == 2) yopciones--; break;
				case leftkey: if (xopciones == 2) xopciones--; break;
				case downkey: if (yopciones == 1) yopciones++; break;
				case rightkey: if (xopciones == 1) xopciones++; break;
				}
			}
			if (tecla == 13) {
				if (xopciones == 1 && yopciones == 1) return 1;
				if (xopciones == 1 && yopciones == 2) return 2;
				if (xopciones == 2 && yopciones == 1) return 3;
				if (xopciones == 2 && yopciones == 2) return 4;
				break;
			}
		}
	}
}
bool Nivel1() {
	slod0();
	while (_getch() != 13) {} //Se pausa hasta que pulsemos enter
	slod1();
	while (_getch() != 13) {}
	bool barra_seleccion[3] = { false };
	nivel_surco();
	puntosVecinales();
	int xprota = 31, yprota = 16;
	int xcasilla = 40, ycasilla = 15;
	//Constantes por nivel
	const int numLineas = 4;
	const int numColumnas = 3;
	const int maxEnemigosLinea = 3;
	const int MAX_BALAS = 48; //max balas en pantalla dentro del nivel
	int yLineas[numLineas] = { 16, 25, 34, 43 };

	int enemigosGenerados = 0;
	int enemigosEliminados = 0;
	int maxEnemigosNivel = 5;

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
			enemigos[l][s].vel = 0;
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
			vecinos[l][c].tipo = 0;
			vecinos[l][c].vida = 5;

		}

	//Inicializar balas
	for (int i = 0; i < MAX_BALAS; i++) {
		balas[i].activa = false;
		balas[i].x = 0;
		balas[i].y = 0;
		balas[i].linea = 0;
	}
	//INICIO NIVEL 1
	while (true)
	{
		barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;
		// SISTEMA DE PUNTOS VECINALES
		gotoxy(6, 1);
		Console::BackgroundColor = ConsoleColor::White;
		Console::ForegroundColor = ConsoleColor::Black;
		cout << puntosV << " ";
		//SPAWN DE ENEMIGOS
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
						switch (enemigos[lineaRandom][s].tipo) {
						case 1: enemigos[lineaRandom][s].vida = 6; enemigos[lineaRandom][s].vel = 0.3; break;
						case 2: enemigos[lineaRandom][s].vida = 3; enemigos[lineaRandom][s].vel = 1.5; break;
						case 3: enemigos[lineaRandom][s].vida = 4; enemigos[lineaRandom][s].vel = 0.75; break;
						}
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
		// 2. MOVER + DIBUJAR ENEMIGOS
		for (int l = 0; l < numLineas; l++)
		{
			for (int s = 0; s < maxEnemigosLinea; s++)
			{
				if (!enemigos[l][s].activo) continue;

				borrar_enemigo((int)enemigos[l][s].x, enemigos[l][s].y);
				bool colisionVecino = false;
				for (int c = 0; c < numColumnas; c++) {
					if (vecinos[l][c].activo) {
						if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
							colisionVecino = true;
							enemigos[l][s].atacando = true;
							break;
						}
					}
				}
				if (colisionVecino) {
					if (enemigos[l][s].cooldownataque > 0)
						enemigos[l][s].cooldownataque--;
					else {
						for (int c = 0; c < numColumnas; c++) {
							if (vecinos[l][c].activo) {
								if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
									vecinos[l][c].vida--;
									if (vecinos[l][c].vida <= 0) {
										borrar_enemigo(vecinos[l][c].x, vecinos[l][c].y);
										vecinos[l][c].activo = false;
										enemigos[l][s].atacando = false;
									}
									break;
								}
							}
						}

						enemigos[l][s].cooldownataque = 20;
					}
					switch (enemigos[l][s].tipo)
					{

					case 1: dibujar_enemigo1_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 2: dibujar_enemigo2_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 3: dibujar_enemigo3_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					}
					continue;
				}
				enemigos[l][s].atacando = false;
				enemigos[l][s].x -= enemigos[l][s].vel;
				if (enemigos[l][s].x <= 42) {
					enemigos[l][s].activo = false;
					return false;
				}

				switch (enemigos[l][s].tipo) {
				case 1: dibujar_enemigo1((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 2: dibujar_enemigo2((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 3: dibujar_enemigo3((int)enemigos[l][s].x, enemigos[l][s].y); break;
				}
			}
		}
		// 3. DETECTAR ENEMIGOS EN CADA LÍNEA
		bool enemigoEnLinea[numLineas] = { false,false,false,false };

		for (int l = 0; l < numLineas; l++) {
			for (int s = 0; s < maxEnemigosLinea; s++) {
				if (enemigos[l][s].activo) enemigoEnLinea[l] = true;
			}
		}

		// 6. CREACION DE BALA
		for (int l = 0; l < numLineas; l++)
		{
			for (int c = 0; c < numColumnas; c++)
			{
				if (!vecinos[l][c].activo) continue;
				if (vecinos[l][c].tipo == 3) continue;
				if (!enemigoEnLinea[l]) {
					vecinos[l][c].cooldown = 0;
					continue;
				}
				if (vecinos[l][c].cooldown > 0) {
					vecinos[l][c].cooldown--;
					continue;
				}
				for (int i = 0; i < MAX_BALAS; i++) {
					if (!balas[i].activa) {
						balas[i].activa = true;
						balas[i].x = vecinos[l][c].x + 8;
						balas[i].y = vecinos[l][c].y + 2;
						balas[i].tipo = 1;
						balas[i].linea = l;
						break;
					}
				}
				vecinos[l][c].cooldown = TIEMPO_ENTRE_DISPAROS;
			}
		}
		// 7. MOVER BALAS 
		for (int i = 0; i < MAX_BALAS; i++)
		{
			if (!balas[i].activa) continue;

			borrar_bala((int)balas[i].x, balas[i].y);
			balas[i].x += 1.5;
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
				dibujar_bala((int)balas[i].x, balas[i].y, balas[i].tipo);
		}
		// 4. BORRAR PROTAGONISTA Y CASILLA ANTERIOR
		borrar_prota(xprota, yprota);
		borrarcasilla(xcasilla, ycasilla);
		// 5. INPUT DEL JUGADOR (MOV + PLANTAR VECINO)
		if (_kbhit()) {
			int tecla = _getch();
			if (tecla == 224) {
				int flecha = _getch();
				if (flecha == upkey && yprota > 16) { yprota -= 9; ycasilla -= 9; }
				if (flecha == downkey && yprota < 41) { yprota += 9; ycasilla += 9; }
				if (flecha == leftkey && xcasilla > 40) { xcasilla -= 14; }
				if (flecha == rightkey && xcasilla < 68) { xcasilla += 14; }
			}
			if (tecla == '1' || tecla == '2' || tecla == 13) {
				int lineaActual = (yprota - 16) / 9;
				int columnaActual = (xcasilla - 40) / 14;
				if (!vecinos[lineaActual][columnaActual].activo) {
					if (tecla == '1') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 1;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '2') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 2;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
				}
				if (tecla == 13) {
					borrar_enemigo(xcasilla + 3, yprota);
					vecinos[lineaActual][columnaActual].activo = false;
					vecinos[lineaActual][columnaActual].vida = 5;
					vecinos[lineaActual][columnaActual].tipo = 0;
				}
			}
		}
		// 8. REDIBUJAR VECINOS + PROTA + CASILLA
		for (int l = 0; l < numLineas; l++) {
			for (int c = 0; c < numColumnas; c++) {
				if (vecinos[l][c].activo) {
					switch (vecinos[l][c].tipo) {
					case 1: dibujar_vecino1(vecinos[l][c].x, vecinos[l][c].y); break;
					case 2: dibujar_vecino2(vecinos[l][c].x, vecinos[l][c].y); break;
					}
				}
			}
		}
		dibujar_prota(xprota, yprota);
		casilla(xcasilla, ycasilla);
		// 9. HUD
		barra_nivel1(barra_seleccion);
		// 10. FIN DEL NIVEL
		if (enemigosGenerados == maxEnemigosNivel && enemigosEliminados == maxEnemigosNivel) {
			return true;
		}
		_sleep(30);
	}
}
bool Nivel2() {
	slod2();
	while (_getch() != 13) {} //Se pausa hasta que pulsemos enter
	bool barra_seleccion[3] = { false };
	nivel_ves();
	puntosVecinales();
	int xprota = 31, yprota = 16;
	int xcasilla = 40, ycasilla = 15;
	//Constantes por nivel
	const int numLineas = 4;
	const int numColumnas = 3;
	const int maxEnemigosLinea = 3;
	const int MAX_BALAS = 48; //max balas en pantalla dentro del nivel
	int yLineas[numLineas] = { 16, 25, 34, 43 };

	int enemigosGenerados = 0;
	int enemigosEliminados = 0;
	int maxEnemigosNivel = 9;// modifique de 5 a 8

	int spawnCooldown = 80;// modifique de 100 a 80
	const int TIEMPO_ENTRE_DISPAROS = 50;
	int puntosV = 100;// modifique de 100 a 90

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
			enemigos[l][s].vel = 0;
			enemigos[l][s].velLenta = 0;
			enemigos[l][s].tiempoEfecto = 0;
			enemigos[l][s].vida = 0;
		}
	}
	//Inicializar vecinos
	for (int l = 0; l < numLineas; l++)
		for (int c = 0; c < numColumnas; c++) {
			vecinos[l][c].activo = false;
			vecinos[l][c].cooldown = 0;
			vecinos[l][c].x = 0;
			vecinos[l][c].y = 0;
			vecinos[l][c].tipo = 0;
			vecinos[l][c].vida = 5;
		}

	//Inicializar balas
	for (int i = 0; i < MAX_BALAS; i++) {
		balas[i].activa = false;
		balas[i].x = 0;
		balas[i].y = 0;
		balas[i].linea = 0;
	}
	//INICIO ANIMACIONES NIVEL 2
	while (true)
	{
		barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;
		// SISTEMA DE PUNTOS VECINALES
		gotoxy(6, 1);
		Console::BackgroundColor = ConsoleColor::White;
		Console::ForegroundColor = ConsoleColor::Black;
		cout << puntosV << " ";
		// 1. SPAWN DE ENEMIGOS
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
						switch (enemigos[lineaRandom][s].tipo) {
						case 1: enemigos[lineaRandom][s].vida = 6; enemigos[lineaRandom][s].vel = 0.3; enemigos[lineaRandom][s].velLenta = 0.5 * 0.3; break; //-50% cuando se ralentizan
						case 2: enemigos[lineaRandom][s].vida = 3; enemigos[lineaRandom][s].vel = 1.5; enemigos[lineaRandom][s].velLenta = 0.5 * 1.5; break; //-50% cuando se ralentizan
						case 3: enemigos[lineaRandom][s].vida = 4; enemigos[lineaRandom][s].vel = 0.75; enemigos[lineaRandom][s].velLenta = 0.5 * 0.75; break; //-50% cuando se ralentizan
						}
						enemigos[lineaRandom][s].atacando = false;
						enemigos[lineaRandom][s].cooldownataque = 0;
						enemigos[lineaRandom][s].tiempoEfecto = 0;
						enemigosGenerados++;
						spawnCooldown = 80;
						// modifique de 100 a 80
						break;
					}
				}
			}
			else spawnCooldown--;
		}
		// 2. MOVER + DIBUJAR ENEMIGOS
		for (int l = 0; l < numLineas; l++)
		{
			for (int s = 0; s < maxEnemigosLinea; s++)
			{
				if (!enemigos[l][s].activo) continue;

				borrar_enemigo((int)enemigos[l][s].x, enemigos[l][s].y);
				bool colisionVecino = false;
				for (int c = 0; c < numColumnas; c++) {
					if (vecinos[l][c].activo) {
						if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
							colisionVecino = true;
							enemigos[l][s].atacando = true;
							break;
						}
					}
				}
				if (colisionVecino) {
					if (enemigos[l][s].cooldownataque > 0)
						enemigos[l][s].cooldownataque--;
					else {
						for (int c = 0; c < numColumnas; c++) {
							if (vecinos[l][c].activo) {
								if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
									vecinos[l][c].vida--;
									if (vecinos[l][c].vida <= 0) {
										borrar_enemigo(vecinos[l][c].x, vecinos[l][c].y);
										vecinos[l][c].activo = false;
										enemigos[l][s].atacando = false;
									}
									break;
								}
							}
						}

						enemigos[l][s].cooldownataque = 20;
					}
					switch (enemigos[l][s].tipo)
					{
					case 1: dibujar_enemigo1_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 2: dibujar_enemigo2_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 3: dibujar_enemigo3_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					}
					continue;
				}
				enemigos[l][s].atacando = false;
				if (enemigos[l][s].tiempoEfecto > 0) { enemigos[l][s].tiempoEfecto--; enemigos[l][s].x -= enemigos[l][s].velLenta; }
				else enemigos[l][s].x-= enemigos[l][s].vel;
				if (enemigos[l][s].x <= 42) {
					enemigos[l][s].activo = false;
					return false;
				}

				switch (enemigos[l][s].tipo) {
				case 1: dibujar_enemigo1((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 2: dibujar_enemigo2((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 3: dibujar_enemigo3((int)enemigos[l][s].x, enemigos[l][s].y); break;
				}
			}
		}
		// 3. DETECTAR ENEMIGOS EN CADA LÍNEA
		bool enemigoEnLinea[numLineas] = { false,false,false,false };
		for (int l = 0; l < numLineas; l++) {
			for (int s = 0; s < maxEnemigosLinea; s++) {
				if (enemigos[l][s].activo) enemigoEnLinea[l] = true;
			}
		}
		// 6. DISPARO AUTOMÁTICO
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
						switch (vecinos[l][c].tipo) {
						case 1: balas[i].tipo = 1; break;
						case 2: balas[i].tipo = 1; break;
						case 3: balas[i].tipo = 2 + rand() % 4; break; //puede ser de 2 a 5
						}
						balas[i].linea = l;
						break;
					}
				}
				vecinos[l][c].cooldown = TIEMPO_ENTRE_DISPAROS;
			}
		}
		// 7. MOVER BALAS 
		for (int i = 0; i < MAX_BALAS; i++)
		{
			if (!balas[i].activa) continue;

			borrar_bala((int)balas[i].x, balas[i].y);
			balas[i].x += 1.5;
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
					if (balas[i].tipo >= 2) enemigos[balas[i].linea][s].tiempoEfecto = 100;
					if (enemigos[balas[i].linea][s].vida == 0) {
						borrar_enemigo((int)enemigos[balas[i].linea][s].x, enemigos[balas[i].linea][s].y);
						enemigos[balas[i].linea][s].activo = false;
						puntosV += 20;
						enemigosEliminados++;
						enemigos[balas[i].linea][s].vida = 3;
						enemigos[balas[i].linea][s].tiempoEfecto = 0;
					}
					break;
				}
			}

			if (balas[i].activa)
				dibujar_bala((int)balas[i].x, balas[i].y, balas[i].tipo);
		}
		// 4. BORRAR PROTAGONISTA Y CASILLA ANTERIOR
		borrar_prota(xprota, yprota);
		borrarcasilla(xcasilla, ycasilla);
		// 5. INPUT DEL JUGADOR (MOV + PLANTAR VECINO)
		if (_kbhit()) {
			int tecla = _getch();
			if (tecla == 224) {
				int flecha = _getch();
				if (flecha == upkey && yprota > 16) { yprota -= 9; ycasilla -= 9; }
				if (flecha == downkey && yprota < 41) { yprota += 9; ycasilla += 9; }
				if (flecha == leftkey && xcasilla > 40) { xcasilla -= 14; }
				if (flecha == rightkey && xcasilla < 68) { xcasilla += 14; }
			}
			if (tecla == '1' || tecla == '2' || tecla == 13) {
				int lineaActual = (yprota - 16) / 9;
				int columnaActual = (xcasilla - 40) / 14;
				if (!vecinos[lineaActual][columnaActual].activo) {
					if (tecla == '1') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 1;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '2') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 2;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '3') {
						if (puntosV >= 50) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 3;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 50;
							barra_seleccion[0] = true;
						}
					}
				}
				if (tecla == 13) {
					borrar_enemigo(xcasilla + 3, yprota);
					vecinos[lineaActual][columnaActual].activo = false;
					vecinos[lineaActual][columnaActual].vida = 5;
					vecinos[lineaActual][columnaActual].tipo = 0;
				}
			}
		}
		// 8. REDIBUJAR VECINOS + PROTA + CASILLA
		for (int l = 0; l < numLineas; l++) {
			for (int c = 0; c < numColumnas; c++) {
				if (vecinos[l][c].activo) {
					switch (vecinos[l][c].tipo) {
					case 1: dibujar_vecino1(vecinos[l][c].x, vecinos[l][c].y); break;
					case 2: dibujar_vecino2(vecinos[l][c].x, vecinos[l][c].y); break;
					case 3: dibujar_aliado_uchu(vecinos[l][c].x, vecinos[l][c].y); break;
					}
				}
			}
		}
		dibujar_prota(xprota, yprota);
		casilla(xcasilla, ycasilla);
		// 9. HUD
		barra_nivel2(barra_seleccion);
		// 10. APARICION BOSS
		if (enemigosEliminados >= 2) {
			dibujar_policorrupto();
			barraVida_policorrupto(maxEnemigosNivel-enemigosEliminados);
		}
		// 11. FIN DEL NIVEL
		if (enemigosGenerados == maxEnemigosNivel && enemigosEliminados == maxEnemigosNivel) {
			return true;
		}
		_sleep(30);
	}
}
bool Nivel3() {
	slod3();
	while (_getch() != 13) {} //Se pausa hasta que pulsemos enter
	bool barra_seleccion[3] = { false,false,false };
	nivel_callao();
	puntosVecinales();
	int xprota = 31, yprota = 16;
	int xcasilla = 40, ycasilla = 15;
	//Constantes por nivel
	const int numLineas = 4;
	const int numColumnas = 3;
	const int maxEnemigosLinea = 4;// modifique de 3 a 4
	const int MAX_BALAS = 48; //max balas en pantalla dentro del nivel
	int yLineas[numLineas] = { 16, 25, 34, 43 };

	int enemigosGenerados = 0;
	int enemigosEliminados = 0;
	int maxEnemigosNivel = 12;// modifique de 5 a 12

	int spawnCooldown = 70;// modifique de 100 a 70
	const int TIEMPO_ENTRE_DISPAROS = 50;
	int puntosV = 125;

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
			enemigos[l][s].vel = 0;
			enemigos[l][s].velLenta = 0;
			enemigos[l][s].vida = 3;
		}
	}
	//Inicializar vecinos
	for (int l = 0; l < numLineas; l++) {
		for (int c = 0; c < numColumnas; c++) {
			vecinos[l][c].activo = false;
			vecinos[l][c].cooldown = 0;
			vecinos[l][c].x = 0;
			vecinos[l][c].y = 0;
			vecinos[l][c].tipo = 0;
			vecinos[l][c].vida = 5;
		}
	}
	//Inicializar balas
	for (int i = 0; i < MAX_BALAS; i++) {
		balas[i].activa = false;
		balas[i].x = 0;
		balas[i].y = 0;
		balas[i].tipo = 0;
		balas[i].linea = 0;
	}
	//INICIO ANIMACIONES NIVEL 3
	while (true)
	{
		barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;
		// SISTEMA DE PUNTOS VECINALES
		gotoxy(6, 1);
		Console::BackgroundColor = ConsoleColor::White;
		Console::ForegroundColor = ConsoleColor::Black;
		cout << puntosV << " ";
		// 1. SPAWN DE ENEMIGOS
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
						switch (enemigos[lineaRandom][s].tipo) {
						case 1: enemigos[lineaRandom][s].vida = 6; enemigos[lineaRandom][s].vel = 0.3; enemigos[lineaRandom][s].velLenta = 0.5 * 0.3; break; //-50% cuando se ralentizan
						case 2: enemigos[lineaRandom][s].vida = 3; enemigos[lineaRandom][s].vel = 1.5; enemigos[lineaRandom][s].velLenta = 0.5 * 1.5; break; //-50% cuando se ralentizan
						case 3: enemigos[lineaRandom][s].vida = 4; enemigos[lineaRandom][s].vel = 0.75; enemigos[lineaRandom][s].velLenta = 0.5 * 0.75; break; //-50% cuando se ralentizan
						}
						enemigos[lineaRandom][s].atacando = false;
						enemigos[lineaRandom][s].cooldownataque = 0;
						enemigos[lineaRandom][s].tiempoEfecto = 0;
						enemigosGenerados++;
						spawnCooldown = 70;
						// modifique de 100 a 70
						break;
					}
				}
			}
			else spawnCooldown--;
		}
		// 2. MOVER + DIBUJAR ENEMIGOS
		for (int l = 0; l < numLineas; l++)
		{
			for (int s = 0; s < maxEnemigosLinea; s++)
			{
				if (!enemigos[l][s].activo) continue;

				borrar_enemigo((int)enemigos[l][s].x, enemigos[l][s].y);
				bool colisionVecino = false;
				for (int c = 0; c < numColumnas; c++) {
					if (vecinos[l][c].activo) {
						if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
							colisionVecino = true;
							enemigos[l][s].atacando = true;
							break;
						}
					}
				}
				if (colisionVecino) {
					if (enemigos[l][s].cooldownataque > 0)
						enemigos[l][s].cooldownataque--;
					else {
						for (int c = 0; c < numColumnas; c++) {
							if (vecinos[l][c].activo) {
								if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
									vecinos[l][c].vida--;
									if (vecinos[l][c].vida <= 0) {
										borrar_enemigo(vecinos[l][c].x, vecinos[l][c].y);
										vecinos[l][c].activo = false;
										enemigos[l][s].atacando = false;
									}
									break;
								}
							}
						}

						enemigos[l][s].cooldownataque = 20;
					}
					switch (enemigos[l][s].tipo)
					{
					case 1: dibujar_enemigo1_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 2: dibujar_enemigo2_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 3: dibujar_enemigo3_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					}
					continue;
				}
				enemigos[l][s].atacando = false;
				if (enemigos[l][s].tiempoEfecto > 0) { enemigos[l][s].tiempoEfecto--; enemigos[l][s].x -= enemigos[l][s].velLenta; }
				else enemigos[l][s].x -= enemigos[l][s].vel;

				if (enemigos[l][s].x <= 40) {
					enemigos[l][s].activo = false;
					return false;
				}

				switch (enemigos[l][s].tipo) {
				case 1: dibujar_enemigo1((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 2: dibujar_enemigo2((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 3: dibujar_enemigo3((int)enemigos[l][s].x, enemigos[l][s].y); break;
				}
			}
		}
		// 3. DETECTAR ENEMIGOS EN CADA LÍNEA
		bool enemigoEnLinea[numLineas] = { false,false,false,false };
		for (int l = 0; l < numLineas; l++) {
			for (int s = 0; s < maxEnemigosLinea; s++) {
				if (enemigos[l][s].activo) enemigoEnLinea[l] = true;
			}
		}
		// 6. CREACION DE BALAS
		for (int l = 0; l < numLineas; l++)
		{
			for (int c = 0; c < numColumnas; c++)
			{
				if (!vecinos[l][c].activo) continue;
				if (vecinos[l][c].tipo == 4) continue;
				if (!enemigoEnLinea[l]) {
					vecinos[l][c].cooldown = 0;
					continue;
				}
				if (vecinos[l][c].cooldown > 0) {
					vecinos[l][c].cooldown--;
					continue;
				}
				for (int i = 0; i < MAX_BALAS; i++) {
					if (!balas[i].activa) {
						balas[i].activa = true;
						balas[i].x = vecinos[l][c].x + 8;
						balas[i].y = vecinos[l][c].y + 2;
						switch (vecinos[l][c].tipo) {
						case 1: balas[i].tipo = 1; break;
						case 2: balas[i].tipo = 1; break;
						case 3: balas[i].tipo = 2 + rand() % 4; break; //puede ser de 2 a 5
						}
						balas[i].linea = l;
						break;
					}
				}
				vecinos[l][c].cooldown = TIEMPO_ENTRE_DISPAROS;
			}
		}
		// 7. MOVER BALAS 
		for (int i = 0; i < MAX_BALAS; i++)
		{
			if (!balas[i].activa) continue;

			borrar_bala((int)balas[i].x, balas[i].y);
			balas[i].x += 1.5;
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
					if (balas[i].tipo >= 2) enemigos[balas[i].linea][s].tiempoEfecto = 100;
					if (enemigos[balas[i].linea][s].vida == 0) {
						borrar_enemigo((int)enemigos[balas[i].linea][s].x, enemigos[balas[i].linea][s].y);
						enemigos[balas[i].linea][s].activo = false;
						puntosV += 20;
						enemigosEliminados++;
						enemigos[balas[i].linea][s].vida = 3;
						enemigos[balas[i].linea][s].tiempoEfecto = 0;
					}
					break;
				}
			}
			if (balas[i].activa)
				dibujar_bala((int)balas[i].x, balas[i].y, balas[i].tipo);
		}
		// 4. BORRAR PROTAGONISTA Y CASILLA ANTERIOR
		borrar_prota(xprota, yprota);
		borrarcasilla(xcasilla, ycasilla);
		// 5. INPUT DEL JUGADOR (MOV + PLANTAR VECINO)
		if (_kbhit()) {
			int tecla = _getch();
			if (tecla == 224) {
				int flecha = _getch();
				if (flecha == upkey && yprota > 16) { yprota -= 9; ycasilla -= 9; }
				if (flecha == downkey && yprota < 41) { yprota += 9; ycasilla += 9; }
				if (flecha == leftkey && xcasilla > 40) { xcasilla -= 14; }
				if (flecha == rightkey && xcasilla < 68) { xcasilla += 14; }
			}
			if (tecla == '1' || tecla == '2' || tecla == 13) {
				int lineaActual = (yprota - 16) / 9;
				int columnaActual = (xcasilla - 40) / 14;
				if (!vecinos[lineaActual][columnaActual].activo) {
					if (tecla == '1') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 1;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '2') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 2;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '3') {
						if (puntosV >= 50) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 3;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 50;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '4') {
						if (puntosV >= 50) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 4;
							vecinos[lineaActual][columnaActual].vida = 15;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 50;
							barra_seleccion[0] = true;
						}
					}
				}
				if (tecla == 13) {
					borrar_enemigo(xcasilla + 3, yprota);
					vecinos[lineaActual][columnaActual].activo = false;
					vecinos[lineaActual][columnaActual].vida = 5;
					vecinos[lineaActual][columnaActual].tipo = 0;
				}
			}
		}
		// 8. REDIBUJAR VECINOS + PROTA + CASILLA
		for (int l = 0; l < numLineas; l++) {
			for (int c = 0; c < numColumnas; c++) {
				if (vecinos[l][c].activo) {
					switch (vecinos[l][c].tipo) {
					case 1: dibujar_vecino1(vecinos[l][c].x, vecinos[l][c].y); break;
					case 2: dibujar_vecino2(vecinos[l][c].x, vecinos[l][c].y); break;
					case 3: dibujar_aliado_uchu(vecinos[l][c].x, vecinos[l][c].y); break;
					case 4: dibujar_aliado_robotin(vecinos[l][c].x, vecinos[l][c].y); break;
					}
				}
			}
		}
		dibujar_prota(xprota, yprota);
		casilla(xcasilla, ycasilla);
		barra_nivel3(barra_seleccion);
		if (enemigosEliminados >= 3) {
			dibujar_chupetin();
			barraVida_chupetin(maxEnemigosNivel - enemigosEliminados);
		}
		//FIN DE NIVEL
		if (enemigosGenerados == maxEnemigosNivel && enemigosEliminados == maxEnemigosNivel) {
			return true;
		}
		_sleep(30);
	}
}
bool Nivel4() {
	slod4();
	while (_getch() != 13) {} //Se pausa hasta que pulsemos enter
	bool barra_seleccion[3] = { false,false,false };
	nivel_centro();
	puntosVecinales();
	int xprota = 31, yprota = 16;
	int xcasilla = 40, ycasilla = 15;
	//Constantes por nivel
	const int numLineas = 4;
	const int numColumnas = 3;
	const int maxEnemigosLinea = 4;// modifique de 3 a 4
	const int MAX_BALAS = 48; //max balas en pantalla dentro del nivel
	int yLineas[numLineas] = { 16, 25, 34, 43 };

	int enemigosGenerados = 0;
	int enemigosEliminados = 0;
	int maxEnemigosNivel = 18;// modifique de 5 a 18

	int spawnCooldown = 60;// modifique de 100 a 60
	const int TIEMPO_ENTRE_DISPAROS = 50;
	int puntosV = 150;// modifique de 100 a 80
	
	Enemigo enemigos[numLineas][maxEnemigosLinea];
	Vecino vecinos[numLineas][numColumnas];
	Bala balas[MAX_BALAS];
	Jefe cuervo;
	cuervo.cooldown_mov=60+rand()%100-60+1;
	cuervo.x=0;
	cuervo.y=0;
	//Inicializar enemigos
	for (int l = 0; l < numLineas; l++) {
		for (int s = 0; s < maxEnemigosLinea; s++) {
			enemigos[l][s].activo = false;
			enemigos[l][s].x = 0;
			enemigos[l][s].y = 0;
			enemigos[l][s].tipo = 0;
			enemigos[l][s].vel = 0;
			enemigos[l][s].tiempoEfecto = 0;
			enemigos[l][s].vida = 3;
		}
	}
	//Inicializar vecinos
	for (int l = 0; l < numLineas; l++) {
		for (int c = 0; c < numColumnas; c++) {
			vecinos[l][c].activo = false;
			vecinos[l][c].cooldown = 0;
			vecinos[l][c].x = 0;
			vecinos[l][c].y = 0;
			vecinos[l][c].tipo = 0;
			vecinos[l][c].vida = 5;
		}
	}
	//Inicializar balas
	for (int i = 0; i < MAX_BALAS; i++) {
		balas[i].activa = false;
		balas[i].x = 0;
		balas[i].y = 0;
		balas[i].linea = 0;
	}
	//INICIO ANIMACIONES NIVEL 4
	while (true) {
		barra_seleccion[0] = barra_seleccion[1] = barra_seleccion[2] = false;
		// SISTEMA DE PUNTOS VECINALES
		gotoxy(6, 1);
		Console::BackgroundColor = ConsoleColor::White;
		Console::ForegroundColor = ConsoleColor::Black;
		cout << puntosV << " ";
		// 1. SPAWN DE ENEMIGOS
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
						switch (enemigos[lineaRandom][s].tipo) {
						case 1: enemigos[lineaRandom][s].vida = 6; enemigos[lineaRandom][s].vel = 0.3; enemigos[lineaRandom][s].velLenta = 0.5 * 0.3; break; //-50% cuando se ralentizan
						case 2: enemigos[lineaRandom][s].vida = 3; enemigos[lineaRandom][s].vel = 1.5; enemigos[lineaRandom][s].velLenta = 0.5 * 1.5; break; //-50% cuando se ralentizan
						case 3: enemigos[lineaRandom][s].vida = 4; enemigos[lineaRandom][s].vel = 0.75; enemigos[lineaRandom][s].velLenta = 0.5 * 0.75; break; //-50% cuando se ralentizan
						}
						enemigos[lineaRandom][s].atacando = false;
						enemigos[lineaRandom][s].cooldownataque = 0;
						enemigos[lineaRandom][s].tiempoEfecto = 0;
						enemigosGenerados++;
						spawnCooldown = 60; // modifique de 100 a 70
						break;
					}
				}
			}
			else spawnCooldown--;
		}
		// 2. MOVER + DIBUJAR ENEMIGOS
		for (int l = 0; l < numLineas; l++)
		{
			for (int s = 0; s < maxEnemigosLinea; s++)
			{
				if (!enemigos[l][s].activo) continue;

				borrar_enemigo((int)enemigos[l][s].x, enemigos[l][s].y);
				bool colisionVecino = false;
				for (int c = 0; c < numColumnas; c++) {
					if (vecinos[l][c].activo) {
						if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
							colisionVecino = true;
							enemigos[l][s].atacando = true;
							break;
						}
					}
				}
				if (colisionVecino) {
					if (enemigos[l][s].cooldownataque > 0)
						enemigos[l][s].cooldownataque--;
					else {
						for (int c = 0; c < numColumnas; c++) {
							if (vecinos[l][c].activo) {
								if (enemigos[l][s].x >= vecinos[l][c].x && enemigos[l][s].x <= vecinos[l][c].x + 8) {
									vecinos[l][c].vida--;
									if (vecinos[l][c].vida <= 0) {
										borrar_enemigo(vecinos[l][c].x, vecinos[l][c].y);
										vecinos[l][c].activo = false;
										enemigos[l][s].atacando = false;
									}
									break;
								}
							}
						}

						enemigos[l][s].cooldownataque = 20;
					}
					switch (enemigos[l][s].tipo) {
					case 1: dibujar_enemigo1_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 2: dibujar_enemigo2_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					case 3: dibujar_enemigo3_pegando((int)enemigos[l][s].x, enemigos[l][s].y); break;
					}
					continue;
				}
				enemigos[l][s].atacando = false;
				if (enemigos[l][s].tiempoEfecto > 0) { enemigos[l][s].tiempoEfecto--; enemigos[l][s].x -= enemigos[l][s].velLenta; }
				else enemigos[l][s].x -= enemigos[l][s].vel;
				if (enemigos[l][s].x <= 42) {
					enemigos[l][s].activo = false;
					return false;
				}

				switch (enemigos[l][s].tipo) {
				case 1: dibujar_enemigo1((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 2: dibujar_enemigo2((int)enemigos[l][s].x, enemigos[l][s].y); break;
				case 3: dibujar_enemigo3((int)enemigos[l][s].x, enemigos[l][s].y); break;
				}
			}
		}
		// 3. DETECTAR ENEMIGOS EN CADA LÍNEA
		bool enemigoEnLinea[numLineas] = { false,false,false,false };

		for (int l = 0; l < numLineas; l++) {
			for (int s = 0; s < maxEnemigosLinea; s++) {
				if (enemigos[l][s].activo) enemigoEnLinea[l] = true;
			}
		}
		// 6. DISPARO AUTOMÁTICO
		for (int l = 0; l < numLineas; l++)
		{
			for (int c = 0; c < numColumnas; c++)
			{
				if (!vecinos[l][c].activo) continue;
				if (vecinos[l][c].tipo == 4) continue;
				if (!enemigoEnLinea[l]) {
					vecinos[l][c].cooldown = 0;
					continue;
				}
				if (vecinos[l][c].cooldown > 0) {
					vecinos[l][c].cooldown--;
					continue;
				}

				for (int i = 0; i < MAX_BALAS; i++) {
					if (!balas[i].activa) {
						balas[i].activa = true;
						balas[i].x = vecinos[l][c].x + 8;
						balas[i].y = vecinos[l][c].y + 2;
						switch (vecinos[l][c].tipo) {
						case 1: balas[i].tipo = 1; break;
						case 2: balas[i].tipo = 1; break;
						case 3: balas[i].tipo = 2 + rand() % 4; break; //puede ser de 2 a 5
						}
						balas[i].linea = l;
						break;
					}
				}
				vecinos[l][c].cooldown = TIEMPO_ENTRE_DISPAROS;
			}
		}
		// 7. MOVER BALAS 
		for (int i = 0; i < MAX_BALAS; i++)
		{
			if (!balas[i].activa) continue;

			borrar_bala((int)balas[i].x, balas[i].y);
			balas[i].x += 1.5;
			//COLISION MAPA
			if (balas[i].x > 188) {
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
					if (balas[i].tipo >= 2) enemigos[balas[i].linea][s].tiempoEfecto = 100;
					if (enemigos[balas[i].linea][s].vida == 0) {
						borrar_enemigo((int)enemigos[balas[i].linea][s].x, enemigos[balas[i].linea][s].y);
						enemigos[balas[i].linea][s].activo = false;
						puntosV += 20;
						enemigosEliminados++;
						enemigos[balas[i].linea][s].vida = 3;
						enemigos[balas[i].linea][s].tiempoEfecto = 0;
					}
					break;
				}
			}

			if (balas[i].activa)
				dibujar_bala((int)balas[i].x, balas[i].y, balas[i].tipo);
		}
		// 4. BORRAR PROTAGONISTA Y CASILLA ANTERIOR
		borrar_prota(xprota, yprota);
		borrarcasilla(xcasilla, ycasilla);
		// 5. DETECTAR TECLAS
		if (_kbhit()) {
			int tecla = _getch();
			if (tecla == 224) {
				int flecha = _getch();
				if (flecha == upkey && yprota > 16) { yprota -= 9; ycasilla -= 9; }
				if (flecha == downkey && yprota < 41) { yprota += 9; ycasilla += 9; }
				if (flecha == leftkey && xcasilla > 40) { xcasilla -= 14; }
				if (flecha == rightkey && xcasilla < 68) { xcasilla += 14; }
			}
			if (tecla == '1' || tecla == '2' || tecla == 13) {
				int lineaActual = (yprota - 16) / 9;
				int columnaActual = (xcasilla - 40) / 14;
				if (!vecinos[lineaActual][columnaActual].activo) {
					if (tecla == '1') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 1;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '2') {
						if (puntosV >= 25) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 2;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 25;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '3') {
						if (puntosV >= 50) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 3;
							vecinos[lineaActual][columnaActual].vida = 5;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 50;
							barra_seleccion[0] = true;
						}
					}
					if (tecla == '4') {
						if (puntosV >= 50) {
							vecinos[lineaActual][columnaActual].x = 43 + columnaActual * 14;
							vecinos[lineaActual][columnaActual].y = yLineas[lineaActual];
							vecinos[lineaActual][columnaActual].cooldown = 0;
							vecinos[lineaActual][columnaActual].tipo = 4;
							vecinos[lineaActual][columnaActual].vida = 15;
							vecinos[lineaActual][columnaActual].activo = true;
							puntosV -= 50;
							barra_seleccion[0] = true;
						}
					}
				}
				if (tecla == 13) {
					borrar_enemigo(xcasilla + 3, yprota);
					vecinos[lineaActual][columnaActual].activo = false;
					vecinos[lineaActual][columnaActual].vida = 5;
					vecinos[lineaActual][columnaActual].tipo = 0;
				}
			}
		}
		// 8. REDIBUJAR VECINOS + PROTA + CASILLA
		for (int l = 0; l < numLineas; l++) {
			for (int c = 0; c < numColumnas; c++) {
				if (vecinos[l][c].activo) {
					switch (vecinos[l][c].tipo) {
					case 1: dibujar_vecino1(vecinos[l][c].x, vecinos[l][c].y); break;
					case 2: dibujar_vecino2(vecinos[l][c].x, vecinos[l][c].y); break;
					case 3: dibujar_aliado_uchu(vecinos[l][c].x, vecinos[l][c].y); break;
					case 4: dibujar_aliado_robotin(vecinos[l][c].x, vecinos[l][c].y); break;
					}
				}
			}
		}
		dibujar_prota(xprota, yprota);
		casilla(xcasilla, ycasilla);
		// 9. HUD
		barra_nivel4(barra_seleccion);
		// 10. FIN DEL NIVEL
		if (enemigosGenerados == maxEnemigosNivel && enemigosEliminados == maxEnemigosNivel) {
			return true;
		}
		if (enemigosGenerados == 2) {
			cuervo.activo=true;
		}
		_sleep(30);
	}
}