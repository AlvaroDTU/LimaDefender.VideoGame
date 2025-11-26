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
	bool nivel[] = { false, false, false, false };
	while (true) {
		PlaySound(TEXT("menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
		int seleccion = Menu();
		switch (seleccion) {
		case 1:
			nivel[0] = true;
			PlaySound(NULL, 0, 0);
			if (nivel[0]) {
				PlaySound(TEXT("niveles.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				bool ganaste = true;
				if (ganaste) { PlaySound(TEXT("victorianormal.wav"), NULL, SND_FILENAME | SND_ASYNC); ganastes(); while (_getch() != 13) {} nivel[1] = true; }
				else { PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC); perdiste(); while (_getch() != 13) {} }
			}
			if (nivel[1]) {
				PlaySound(TEXT("niveles.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				bool ganaste = true;
				PlaySound(TEXT("victoria.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (ganaste) { PlaySound(TEXT("victorianormal.wav"), NULL, SND_FILENAME | SND_ASYNC); ganastes(); while (_getch() != 13) {} nivel[2] = true; }
				else { PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC); perdiste(); while (_getch() != 13) {} }
			}
			if (nivel[2]) {
				PlaySound(TEXT("niveles.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				bool ganaste = true;
				PlaySound(TEXT("victorianormal.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (ganaste) { ganastes(); while (_getch() != 13) {} nivel[3] = true; }
				else { PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC); perdiste(); while (_getch() != 13) {} }
			}
			if (nivel[3]) {
				PlaySound(TEXT("final.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
				bool ganaste = Nivel4();
				PlaySound(TEXT("victorianormal.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (ganaste) { ganastes(); while (_getch() != 13) {} PlaySound(TEXT("victoriafinal.wav"), NULL, SND_FILENAME | SND_ASYNC); slod5(); while (_getch() != 13) {} slod6(); while (_getch() != 13) {} ending(); while (_getch() != 13) {} }
				else { PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_ASYNC); perdiste(); while (_getch() != 13) {} }
			}
			break;
		case 2:
			system("color 0F");
			system("cls");
			exit(0);
			break;
		case 3:
			instrucciones();
			while (_getch() != 13) {}
			break;
		case 4:
			creditos();
			while (_getch() != 13) {}
		}
	}
	return 0;
}