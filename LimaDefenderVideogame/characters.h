#pragma once
#include "essentials.h"
using namespace std;
using namespace System;

struct Jefe {
int x;
int y;
bool activo;
bool ataque;
int vida;
int cooldownataque;
int cooldown_mov;
int linea[2];
};
struct Enemigo {
	bool activo;
	double x;
	int y;
	int tipo;
	double vel;
	double velLenta;
	int vida;
	bool atacando;
	int cooldownataque;
	int tiempoEfecto;
};
struct Vecino {
	bool activo;
	int x;
	int y;
	int cooldown;
	int vida;
	int tipo;
};
struct Bala {
	bool activa;
	double x;
	int y;
	int linea;
	int tipo;
};
void borrar_prota(int x, int y) {
	int borrar[6][8] = {
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0}
	};
	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (borrar[f][c] == 0) { Console::BackgroundColor = ConsoleColor::Gray; cout << " "; }
		}
	}
}
void borrar_enemigo(int x, int y) {
	int borrar[6][8] = {
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0},
	   {0,0,0,0,0,0,0,0}
	};
	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (borrar[f][c] == 0) { Console::BackgroundColor = ConsoleColor::Black; cout << " "; }
		}
	}
}
//aliados
void dibujar_prota(int x, int y) {

	int prota[6][8] = {
	   {0,6,6,6,6,6,6,0},
	   {0,5,2,8,2,8,5,0},
	   {0,3,3,1,1,1,1,0},
	   {1,1,3,2,2,3,1,1},
	   {5,1,1,1,1,3,3,5},
	   {0,7,7,0,0,7,7,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (prota[f][c] == 1) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (prota[f][c] == 2) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (prota[f][c] == 3) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (prota[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkCyan; cout << (char)219; }
			if (prota[f][c] == 5) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (prota[f][c] == 6) { setTextColorRGB(135, 65, 0); cout << (char)219; }
			if (prota[f][c] == 7) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (prota[f][c] == 8) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
		}
	}
}




void dibujar_aliado_robotin(int x, int y) {
	int robotin[6][8] = {
	   {2,2,2,2,2,2,2,2},
	   {1,6,6,1,1,6,6,1},
	   {0,1,1,5,5,1,1,0},
	   {1,6,4,6,6,4,6,1},
	   {2,1,1,1,1,1,1,2},
	   {0,2,2,0,0,2,2,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (robotin[f][c] == 1) { Console::ForegroundColor = ConsoleColor::Gray; cout << (char)219; }
			if (robotin[f][c] == 2) { Console::ForegroundColor = ConsoleColor::DarkGray; cout << (char)219; }
			if (robotin[f][c] == 3) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (robotin[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (robotin[f][c] == 5) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (robotin[f][c] == 6) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
		}
	}

}

void dibujar_aliado_uchu(int x, int y) {
	int uchu[6][8] = {
	   {5,5,5,5,5,5,5,5},
	   {5,4,6,2,6,2,4,5},
	   {5,4,4,4,4,4,4,5},
	   {3,3,3,3,3,3,3,3},
	   {4,3,3,3,3,3,3,4},
	   {0,1,1,0,0,1,1,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (uchu[f][c] == 1) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (uchu[f][c] == 2) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (uchu[f][c] == 3) { Console::ForegroundColor = ConsoleColor::DarkGreen; cout << (char)219; }
			if (uchu[f][c] == 4) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (uchu[f][c] == 5) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (uchu[f][c] == 6) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
		}
	}

}

void dibujar_vecino1(int x, int y) {
	int vecino1[6][8] = {
	{0,1,1,1,1,1,1,0},
	{0,2,5,2,2,5,2,0},
	{0,2,2,2,2,2,2,0},
	{3,3,3,3,3,3,3,3},
	{2,3,3,3,3,3,3,2},
	{0,4,4,0,0,4,4,0},
	};
	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (vecino1[f][c] == 1) { setTextColorRGB(135, 65, 0); cout << (char)219; cout << (char)219; }
			if (vecino1[f][c] == 2) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (vecino1[f][c] == 3) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (vecino1[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkGray; cout << (char)219; }
			if (vecino1[f][c] == 5) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
		}
	}

}
void dibujar_vecino2(int x, int y) {
	int vecino2[6][8] = {
	{1,1,1,1,1,1,1,1},
	{1,2,5,2,2,5,2,1},
	{1,2,2,2,2,2,2,1},
	{2,3,3,2,2,3,3,2},
	{2,3,3,3,3,3,3,2},
	{0,4,4,0,0,4,4,0}
	};
	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (vecino2[f][c] == 1) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (vecino2[f][c] == 2) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (vecino2[f][c] == 3) { Console::ForegroundColor = ConsoleColor::Red; cout << (char)219; }
			if (vecino2[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (vecino2[f][c] == 5) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
		}
	}
}
//enemigos
void dibujar_enemigo1(int x, int y) {
	int poli[6][8] = {
	   {0,4,4,4,4,4,4,0},
	   {4,6,5,8,8,6,5,4},
	   {0,8,8,8,8,8,8,0},
	   {2,2,2,2,3,3,2,2},
	   {8,2,2,2,2,2,2,8},
	   {0,1,1,0,0,1,1,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (poli[f][c] == 1) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (poli[f][c] == 2) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (poli[f][c] == 3) { Console::ForegroundColor = ConsoleColor::DarkYellow; cout << (char)219; }
			if (poli[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkGray; cout << (char)219; }
			if (poli[f][c] == 5) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (poli[f][c] == 6) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (poli[f][c] == 8) { setTextColorRGB(255, 211, 186); cout << (char)219; }
		}
	}
}
void dibujar_enemigo2(int x, int y) {
	int chamo[6][8] = {
	  { 7,7,7,3,3,4,4,0},
	  { 0,2,1,5,2,1,5,7},
	  { 0,5,5,5,5,5,5,5},
	  { 5,4,4,4,4,4,4,5},
	  { 5,3,3,3,3,3,3,0},
	  { 0,7,7,0,0,7,7,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (chamo[f][c] == 1) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (chamo[f][c] == 2) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (chamo[f][c] == 3) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (chamo[f][c] == 4) { Console::ForegroundColor = ConsoleColor::Yellow; cout << (char)219; }
			if (chamo[f][c] == 7) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (chamo[f][c] == 5) { setTextColorRGB(186, 91, 0); cout << (char)219; }
			if (chamo[f][c] == 6) { Console::ForegroundColor = ConsoleColor::Gray; cout << (char)219; }
		}
	}
}
void dibujar_enemigo3(int x, int y) {
	int choro[6][8] = {
	  { 0,4,4,4,4,4,4,0},
	  { 4,1,2,1,1,2,1,4},
	  { 0,4,4,4,4,4,4,0},
	  { 3,3,3,3,3,3,3,3},
	  { 4,3,3,3,3,3,3,4},
	  { 0,2,2,0,0,2,2,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (choro[f][c] == 1) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (choro[f][c] == 2) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (choro[f][c] == 3) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (choro[f][c] == 4) { setTextColorRGB(255, 211, 186); cout << (char)219; }
		}
	}
}

//enemios pegando
void dibujar_enemigo2_pegando(int x, int y) {
	int chamo[6][8] = {
	  {1,1,1,3,3,4,4,0},
	  {0,5,6,2,5,6,2,1},
	  {0,2,2,2,2,2,2,0},
	  {2,4,4,4,2,2,2,2},
	  {0,3,3,3,3,3,3,0},
	  {0,1,1,0,0,1,1,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (chamo[f][c] == 5) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (chamo[f][c] == 6) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (chamo[f][c] == 3) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (chamo[f][c] == 4) { Console::ForegroundColor = ConsoleColor::Yellow; cout << (char)219; }
			if (chamo[f][c] == 1) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (chamo[f][c] == 2) { setTextColorRGB(186, 91, 0); cout << (char)219; }
		}
	}
}

void dibujar_enemigo1_pegando(int x, int y) {
	int poli[6][8] = {
	   {0,4,4,4,4,4,4,0},
	   {4,5,6,3,5,6,3,4},
	   {0,3,3,3,3,3,3,0},
	   {3,2,2,3,2,2,2,2},
	   {0,2,2,2,2,2,2,0},
	   {0,1,1,0,0,1,1,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (poli[f][c] == 1) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (poli[f][c] == 2) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (poli[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkGray; cout << (char)219; }
			if (poli[f][c] == 6) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (poli[f][c] == 5) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (poli[f][c] == 3) { setTextColorRGB(255, 211, 186); cout << (char)219; }
		}
	}
}

void dibujar_enemigo3_pegando(int x, int y) {
	int choro[6][8] = {
	 {0,3,3,3,3,3,3,0},
	 {3,5,6,5,5,6,5,3},
	 {0,3,3,3,3,3,3,0},
	 {3,1,1,3,1,1,1,1},
	 {0,1,1,1,1,1,1,0},
	 {0,6,6,0,0,6,6,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (choro[f][c] == 5) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (choro[f][c] == 6) { Console::ForegroundColor = ConsoleColor::White; cout << (char)219; }
			if (choro[f][c] == 1) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (choro[f][c] == 3) { setTextColorRGB(255, 211, 186); cout << (char)219; }
		}
	}
}

//JEFE
void dibujar_cuervo(int x, int y) {

	int cuervo[17][16] = {
	{0,0,0,0,0,1,1,1,2,2,5,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,2,2,2,2,5,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,2,2,2,2,5,5},
	{0,0,0,0,0,1,1,1,3,1,1,1,2,5,0,0},
	{0,0,1,1,1,1,1,4,3,1,1,1,2,5,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{1,0,0,0,0,0,0,1,1,1,1,2,0,0,0,0},
	{0,0,0,0,1,1,3,1,1,1,1,3,2,2,0,0},
	{0,0,0,1,1,1,3,1,1,1,1,3,1,2,2,0},
	{0,0,0,1,1,1,1,3,1,1,3,1,1,1,2,0},
	{0,0,0,1,1,1,1,1,3,3,1,1,1,1,2,0},
	{0,0,0,1,1,1,1,1,1,3,1,1,1,1,2,0},
	{0,0,1,1,1,1,1,1,1,1,3,1,1,1,2,2},
	{0,0,0,1,1,0,1,1,1,1,1,1,0,1,2,0},
	{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
	};
	for (int f = 0; f < 17; f++) {
		for (int c = 0; c < 16; c++) {
			gotoxy(x + c, y + f);
			if (cuervo[f][c] == 1) { setTextColorRGB(28, 28, 28); cout << (char)219; }
			if (cuervo[f][c] == 2) { setTextColorRGB(56, 56, 56); cout << (char)219; }
			if (cuervo[f][c] == 3) { setTextColorRGB(255, 144, 0); cout << (char)219; }
			if (cuervo[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (cuervo[f][c] == 5) { setTextColorRGB(110, 110, 110); cout << (char)219; }
		}
	}
}
void borrar_cuervo(int x, int y) {

	int cuervo[17][16] = {
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0},
	{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
	};
	for (int f = 0; f < 17; f++) {
		for (int c = 0; c < 16; c++) {
			gotoxy(x + c, y + f);
			if (cuervo[f][c] == 1) { Console::BackgroundColor = ConsoleColor::Black; cout << " "; }
			if (cuervo[f][c] == 9) { Console::BackgroundColor = ConsoleColor::White; cout << " "; }
		}
	}
}
void dibujar_cuervo_apuntando(int x, int y) {

	int cuervo[17][19] = {
	{0,0,0,0,0,0,0,0,1,1,1,2,2,5,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,5,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,5,5},
	{0,0,0,0,0,0,0,0,1,1,1,3,1,1,1,2,5,0,0},
	{0,0,0,0,0,1,1,1,1,1,4,3,1,1,1,2,5,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,1,1,1,1,2,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,3,1,1,1,1,3,2,2,0,0},
	{1,1,1,1,1,1,1,1,1,3,1,1,1,1,3,1,2,2,0},
	{0,1,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,2,0},
	{0,0,0,0,0,0,0,0,1,1,1,3,3,1,1,1,1,2,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,3,1,1,1,1,2,0},
	{0,0,0,0,0,0,0,0,1,1,1,1,1,3,1,1,1,2,2},
	{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,2,0},
	{0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
	};
	for (int f = 0; f < 17; f++) {
		for (int c = 0; c < 19; c++) {
			gotoxy(x + c, y + f);
			if (cuervo[f][c] == 1) { setTextColorRGB(28, 28, 28); cout << (char)219; }
			if (cuervo[f][c] == 2) { setTextColorRGB(56, 56, 56); cout << (char)219; }
			if (cuervo[f][c] == 3) { setTextColorRGB(255, 144, 0); cout << (char)219; }
			if (cuervo[f][c] == 4) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (cuervo[f][c] == 5) { setTextColorRGB(110, 110, 110); cout << (char)219; }
		}
	}
}

void borrar_cuervo_apuntando(int x, int y) {
	int cuervo[17][19] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	for (int f = 0; f < 17; f++) {
		for (int c = 0; c < 19; c++) {
			gotoxy(x + c, y + f);
			if (cuervo[f][c] == 0) cout << " ";
		}
	}
}
void dibujar_policorrupto() {
	int poli_c[15][35] = {
{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
{4,0,0,0,0,0,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,0,0,0,0,0,4},
{4,0,0,0,0,0,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,0,0,0,0,0,4},
{4,0,0,0,0,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,4},
{4,0,0,0,0,1,1,1,6,1,6,6,1,1,6,6,6,6,6,6,6,1,1,6,6,1,6,1,1,1,0,0,0,0,4},
{4,0,0,0,0,0,1,1,1,6,6,6,6,6,6,7,7,7,7,7,6,6,6,6,6,7,1,1,1,0,0,0,0,0,4},
{4,0,0,0,0,0,1,1,1,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,1,1,1,0,0,0,0,0,4},
{4,0,0,0,0,0,0,1,1,1,6,6,6,7,7,7,7,7,7,7,7,7,6,6,6,1,1,1,0,0,0,0,0,0,4},
{4,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,1,1,1,0,0,0,0,0,0,4},
{4,0,0,0,0,0,1,1,1,1,1,7,6,6,6,6,6,6,6,6,6,6,6,7,1,1,1,1,1,0,0,0,0,0,4},
{4,0,0,0,1,1,1,1,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,1,7,1,1,1,1,1,1,0,0,0,4},
{4,0,0,1,1,1,1,5,1,1,1,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,1,5,1,1,1,1,0,0,4},
{4,0,1,1,2,1,1,1,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,4},
{4,1,2,2,1,1,5,1,2,1,1,2,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,4},
{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
	};

	for (int f = 0; f < 15; f++) {
		for (int c = 0; c < 35; c++) {
			gotoxy(c + 155, f);
			if (poli_c[f][c] == 0)Console::ForegroundColor = ConsoleColor::White;
			if (poli_c[f][c] == 1 || poli_c[f][c] == 2)Console::ForegroundColor = ConsoleColor::Black;
			if (poli_c[f][c] == 3)Console::ForegroundColor = ConsoleColor::Green;
			if (poli_c[f][c] == 4)Console::ForegroundColor = ConsoleColor::Gray;
			if (poli_c[f][c] == 5)Console::ForegroundColor = ConsoleColor::DarkGray;
			if (poli_c[f][c] == 6)setTextColorRGB(255, 211, 186);
			if (poli_c[f][c] == 7)Console::ForegroundColor = ConsoleColor::DarkYellow;
			cout << (char)219;
		}
	}
}
void dibujar_chupetin() {
	int chupetin[15][35] = {
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	{7,0,0,0,0,4,4,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,4,4,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,4,4,4,4,4,0,0,0,0,7},
	{7,0,0,0,0,4,4,4,2,2,6,6,6,2,2,2,2,2,6,6,6,6,2,2,2,4,4,4,4,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,4,4,0,0,0,7},
	{7,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,1,2,2,2,2,2,2,3,3,3,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,1,2,2,2,2,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,3,3,2,2,2,2,2,1,1,0,0,0,0,0,0,0,7},
	{7,0,0,0,0,0,0,0,1,2,2,2,3,3,3,3,3,3,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,7},
	{7,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,5,1,1,1,1,0,0,0,0,7},
	{7,0,0,0,1,1,4,4,4,6,1,1,2,2,2,2,2,2,2,2,2,1,1,5,5,5,5,5,5,5,1,0,0,0,7},
	{7,0,0,1,4,4,4,6,6,5,5,5,1,2,2,2,2,2,2,2,1,6,6,6,5,5,4,4,4,4,4,1,0,0,7},
	{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},
	};
	for (int f = 0; f < 15; f++) {
		for (int c = 0; c < 35; c++) {
			gotoxy(c + 155, f);
			if (chupetin[f][c] == 0) Console::ForegroundColor = ConsoleColor::White;
			if (chupetin[f][c] == 1) Console::ForegroundColor = ConsoleColor::Black;
			if (chupetin[f][c] == 2) setTextColorRGB(255, 211, 186);
			if (chupetin[f][c] == 3) Console::ForegroundColor = ConsoleColor::Red;
			if (chupetin[f][c] == 4) setTextColorRGB(255, 170, 0);
			if (chupetin[f][c] == 5) Console::ForegroundColor = ConsoleColor::Blue;
			if (chupetin[f][c] == 6) Console::ForegroundColor = ConsoleColor::DarkBlue;
			if (chupetin[f][c] == 7) Console::ForegroundColor = ConsoleColor::Black;
			cout << char(219);
		}
	}
}


void barra(int x, int y) {
	int barra[6][37] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0},
	};

	for (int f = 0; f < 6; f++) {
		for (int c = 0; c < 37; c++) {
			gotoxy(x + c, y + f);
			if (barra[f][c] == 0) { Console::BackgroundColor = ConsoleColor::Black; cout << " "; }
			if (barra[f][c] == 1) { Console::BackgroundColor = ConsoleColor::White; cout << " "; }
		}
	}

}

void barra_vacia(int x, int y) {
	int barra[4][8] = {
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1},
	};

	for (int f = 0; f < 4; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (barra[f][c] == 1) Console::BackgroundColor = ConsoleColor::DarkGray; cout << " ";
		}
	}

}

void barra_vecino1(int x, int y, bool seleccion_barra) {
	int barra[4][8] = {
	{1,1,2,2,2,2,1,1},
	{1,1,3,3,3,3,1,1},
	{1,4,4,4,4,4,4,1},
	{1,1,5,1,1,5,1,1},
	};

	for (int f = 0; f < 4; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (barra[f][c] == 1) {
				if (seleccion_barra == true) setBackgroundColor(171, 255, 186);
				else Console::BackgroundColor = ConsoleColor::White;
				cout << " ";
			}
			if (barra[f][c] == 2) { setTextColorRGB(135, 65, 0); cout << (char)219; }
			if (barra[f][c] == 3) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (barra[f][c] == 4) { Console::ForegroundColor = ConsoleColor::Blue; cout << (char)219; }
			if (barra[f][c] == 5) { Console::ForegroundColor = ConsoleColor::DarkGray; cout << (char)219; }

		}
	}

}

void barra_vecino2(int x, int y, bool seleccion_barra) {
	int barra[4][8] = {
	{1,6,6,6,6,6,6,1},
	{1,6,3,3,3,3,6,1},
	{1,3,7,7,7,7,3,1},
	{1,1,8,1,1,8,1,1},
	};
	for (int f = 0; f < 4; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (barra[f][c] == 1) {
				if (seleccion_barra == true) setBackgroundColor(171, 255, 186);
				else Console::BackgroundColor = ConsoleColor::White;
				cout << " ";
			}
			if (barra[f][c] == 3) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (barra[f][c] == 6) { Console::ForegroundColor = ConsoleColor::DarkRed; cout << (char)219; }
			if (barra[f][c] == 7) { Console::ForegroundColor = ConsoleColor::Red; cout << (char)219; }
			if (barra[f][c] == 8) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
		}
	}
}

void aliado_robotin(int x, int y, bool seleccion_barra) {
	int barra[4][8] = {
	{1,1,5,5,5,5,1,1},
	{1,1,9,9,9,9,1,1},
	{1,5,8,0,0,8,5,1},
	{1,1,5,1,1,5,1,1},
	};
	for (int f = 0; f < 4; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (barra[f][c] == 0) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (barra[f][c] == 1) {
				if (seleccion_barra == true) setBackgroundColor(171, 255, 186);
				else Console::BackgroundColor = ConsoleColor::White;
				cout << " ";
			}
			if (barra[f][c] == 5) { Console::ForegroundColor = ConsoleColor::DarkGray; cout << (char)219; }
			if (barra[f][c] == 8) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (barra[f][c] == 9) { Console::ForegroundColor = ConsoleColor::Gray; cout << (char)219; }
		}
	}
}

void aliado_uchulu(int x, int y, bool seleccion_barra) {
	int barra[4][8] = {
	{1,6,6,6,6,6,6,1},
	{1,6,3,3,3,3,6,1},
	{1,3,7,7,7,7,3,1},
	{1,1,8,1,1,8,1,1},
	};
	for (int f = 0; f < 4; f++) {
		for (int c = 0; c < 8; c++) {
			gotoxy(x + c, y + f);
			if (barra[f][c] == 0) { Console::ForegroundColor = ConsoleColor::Black; cout << (char)219; }
			if (barra[f][c] == 1) {
				if (seleccion_barra == true) setBackgroundColor(171, 255, 186);
				else Console::BackgroundColor = ConsoleColor::White;
				cout << " ";
			}
			if (barra[f][c] == 8) { Console::ForegroundColor = ConsoleColor::DarkBlue; cout << (char)219; }
			if (barra[f][c] == 3) { setTextColorRGB(255, 211, 186); cout << (char)219; }
			if (barra[f][c] == 6) { Console::ForegroundColor = ConsoleColor::Red; cout << (char)219; }
			if (barra[f][c] == 7) { Console::ForegroundColor = ConsoleColor::Green; cout << (char)219; }
		}
	}
}

void barra_nivel1(bool seleccion_barra[]) {
	barra(46, 0);
	gotoxy(50, 5); cout << "1";
	gotoxy(59, 5); cout << "2";
	gotoxy(68, 5); cout << "3";
	gotoxy(77, 5); cout << "4";
	gotoxy(48, 0); cout << "25 PV";
	gotoxy(57, 0); cout << "25 PV";
	barra_vecino1(47, 1, seleccion_barra[0]);
	barra_vecino2(56, 1, seleccion_barra[1]);
	barra_vacia(65, 1);
	barra_vacia(74, 1);
}

void barra_nivel2(bool seleccion_barra[]) {
	barra(46, 0);
	gotoxy(50, 5); cout << "1";
	gotoxy(59, 5); cout << "2";
	gotoxy(68, 5); cout << "3";
	gotoxy(77, 5); cout << "4";
	gotoxy(48, 0); cout << "25 PV";
	gotoxy(57, 0); cout << "25 PV";
	gotoxy(66, 0); cout << "50 PV";
	barra_vecino1(47, 1, seleccion_barra[0]);
	barra_vecino2(56, 1, seleccion_barra[1]);
	aliado_uchulu(65, 1, seleccion_barra[2]);
	barra_vacia(74, 1);
}

void barra_nivel3(bool seleccion_barra[]) {
	barra(46, 0);
	gotoxy(50, 5); cout << "1";
	gotoxy(59, 5); cout << "2";
	gotoxy(68, 5); cout << "3";
	gotoxy(77, 5); cout << "4";
	gotoxy(48, 0); cout << "25 PV";
	gotoxy(57, 0); cout << "25 PV";
	gotoxy(66, 0); cout << "50 PV";
	gotoxy(75, 0); cout << "50 PV";
	barra_vecino1(47, 1, seleccion_barra[0]);
	barra_vecino2(56, 1, seleccion_barra[1]);
	aliado_uchulu(65, 1, seleccion_barra[2]);
	aliado_robotin(74, 1, seleccion_barra[3]);
}

void barra_nivel4(bool seleccion_barra[]) {
	barra(46, 0);
	gotoxy(50, 5); cout << "1";
	gotoxy(59, 5); cout << "2";
	gotoxy(68, 5); cout << "3";
	gotoxy(77, 5); cout << "4";
	gotoxy(48, 0); cout << "25 PV";
	gotoxy(57, 0); cout << "25 PV";
	gotoxy(66, 0); cout << "50 PV";
	gotoxy(75, 0); cout << "50 PV";
	barra_vecino1(47, 1, seleccion_barra[0]);
	barra_vecino2(56, 1, seleccion_barra[1]);
	aliado_uchulu(65, 1, seleccion_barra[2]);
	aliado_robotin(74, 1, seleccion_barra[3]);
}

void dibujar_bala(int x, int y, int tipo) {
	switch (tipo) {
	case 1: Console::ForegroundColor = ConsoleColor::Gray; break;
	case 2: setTextColorRGB(239, 228, 176); break;
	case 3: setTextColorRGB(237, 28, 36); break;
	case 4: setTextColorRGB(63, 72, 204); break;
	case 5: setTextColorRGB(255, 128, 0); break;
	}
	gotoxy(x, y);
	cout << (char)254;
}

void borrar_bala(int x, int y) {
	Console::BackgroundColor = ConsoleColor::Black; // o el color del piso
	gotoxy(x, y);
	cout << " ";
}

void barraVida_policorrupto(int estado) {
	int barravida[3][43] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	//7: estado lleno, 0: estado vacio
	for (int e = 6; e >= estado; e--) {
		for (int i = 0; i <= 4; i++) {
			barravida[1][1 + 6 * e + i] = 2;
		}
	}
	for (int f = 0; f < 3; f++) {
		for (int c = 0; c < 43; c++) {
			gotoxy(110 + c, 11 + f);
			if (barravida[f][c] == 0) setTextColorRGB(22, 22, 22);
			if (barravida[f][c] == 1) setTextColorRGB(255, 0, 0);
			if (barravida[f][c] == 2) setTextColorRGB(255, 255, 255);
			cout << char(219);
		}
	}
	gotoxy(123, 11); setTextColorRGB(255, 255, 255); setBackgroundColor(22, 22, 22); cout << "POLICIA CORRUPTO";
}
void barraVida_chupetin(int estado) {
	int barravida[3][55] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	//9: estado lleno, 0: estado vacio
	for (int e = 8; e >= estado; e--) {
		for (int i = 0; i <= 4; i++) {
			barravida[1][1 + 6 * e + i] = 2;
		}
	}
	for (int f = 0; f < 3; f++) {
		for (int c = 0; c < 55; c++) {
			gotoxy(98 + c, 11 + f);
			if (barravida[f][c] == 0) setTextColorRGB(22, 22, 22);
			if (barravida[f][c] == 1) setTextColorRGB(255, 0, 0);
			if (barravida[f][c] == 2) setTextColorRGB(255, 255, 255);
			cout << char(219);
		}
	}
	gotoxy(145, 11); setTextColorRGB(255, 255, 255); setBackgroundColor(22, 22, 22); cout << "CHUPETIN";
}
