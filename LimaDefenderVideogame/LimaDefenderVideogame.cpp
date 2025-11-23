#include "pch.h"
#include "iostream"
#include "characters.h"
#include "essentials.h"
#include "scenery.h"
#include "levels.h"

int main() {
	srand(time(nullptr));
    changeWindowSize(190, 50);
    lockNoScroll(190, 50);
	Console::CursorVisible = false;
    bool inicio = true, juego = false, gameOver = false, nivel[] = { 0, 0, 0, 0 };
	while (true) {
		int xopciones = 1, yopciones = 1;
        inicio = true, juego = false, gameOver = false;
		mapa();
		titulo(55, 3);
		imprime_play(60, 29, 0);
		imprime_credits(90, 39, 0);
		imprime_exit(60, 39, 0);
		imprime_instructions(79, 29, 0);
		system("pause>nul");
		while (inicio) {
			if (_kbhit()) {
                char tecla = _getch();
				switch (tecla) {
				case upkey:
					if (yopciones == 2) yopciones--;
					break;
				case leftkey:
					if (xopciones == 2) xopciones--;
					break;
				case downkey:
					if (yopciones == 1) yopciones++;
					break;
				case rightkey:
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
                        nivel[0] = true;
						inicio = false;
						juego = false;
						instrucciones();
						while (_getch() != 13) {}
					}
					if (xopciones == 2 && yopciones == 2) {
						inicio = false;
						juego = false;
						creditos();
						while (_getch() != 13) {}
					}
				}
			}
			if (inicio) {
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
			}
		}
		while (juego) {
            if (nivel[0]) {
                bool ganaste = Nivel1();
                if (ganaste) nivel[1] = true;
                else { perdiste(); while (_getch() != 13) {} break; }
            }
            if (nivel[1]) {
                bool ganaste = Nivel2();
                if (ganaste) nivel[2] = true;
                else { perdiste(); while (_getch() != 13) {} break; }
            }
            if (nivel[2]) {
                bool ganaste = Nivel3();
                if (ganaste) nivel[3] = true;
                else { perdiste(); while (_getch() != 13) {} break; }
            }
            if (nivel[3]) {
                bool ganaste = Nivel4();
                if (ganaste) { slod5(); slod6(); juego = false; }
                else { perdiste(); while (_getch() != 13) {} break; }
            }
		}
	}
    return 0;
}