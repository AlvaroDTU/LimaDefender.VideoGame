#include "pch.h"
#include "iostream"
#include "characters.h"
#include "essentials.h"
#include "scenery.h"
#include "conio.h"
#include "cctype"
int main() {
	//pingaza
	//gabotevoyAMETERELPENE
	//alvaro FULL PEDO A KITI PATITAS, Ese dia dijiste q era tu tipo
	//gabotevoyAMETERELPENE
	//ALVAROPONTENE4PAMTERTEPINGAOCNGABO
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
			_sleep(500);
			while(_getch() != 13){}
			slod1();
			_sleep(500);
			while (_getch() != 13) {}
			bool barra_seleccion[3] = { false,false,false };
			nivel_surco();
			barra_nivelSurcoYCallao(barra_seleccion);
			int xprota = 31, yprota = 16;
			int xcasilla = 40, ycasilla = 15;
			bool aparece_casilla = false;
			while (nivel[0])
			{
				//dibujar
				dibujar_prota(xprota, yprota);
				casilla(xcasilla, ycasilla);
				//espacio
				_sleep(0);
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
