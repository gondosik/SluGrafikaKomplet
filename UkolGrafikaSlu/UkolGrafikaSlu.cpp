#include <iostream>
#include <SDL.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>

const int CONSOLE_POSITION_X = 10;
const int CONSOLE_POSITION_Y = 0;
const int CONSOLE_WIDTH = 500;
const int CONSOLE_HEIGHT = 200;
const int WINDOW_POSITION_X = 30;
const int WINDOW_POSITION_Y = 250;
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

void drawCircleUsingBresenhamAlgorithm(double, double, double, SDL_Renderer*);
void drawCirclePoints(double, double, double, double, SDL_Renderer*);

void drawCircleUsingBresenhamAlgorithm(double r, double x0, double y0, SDL_Renderer *renderer) {
	double dvex = 3.0, dvey = ((2.0 * r) - 2.0), p = (1.0 - r);
	double x = 0.0;
	double y = r;

	while (x <= y) {
		drawCirclePoints(x, y, x0, y0, renderer);
		Sleep(10);
		if (p > 0) {
			p -= dvey;
			dvey -= 2;
			y--;
		}
		p += dvex;
		dvex += 2;
		x++;
	}
}

void drawCirclePoints(double x, double y, double x0, double y0, SDL_Renderer *renderer) {
	SDL_RenderDrawPoint(renderer, x+x0, y+y0);
	SDL_RenderDrawPoint(renderer, -x+x0, y+y0);
	SDL_RenderDrawPoint(renderer, x+x0, -y+y0);
	SDL_RenderDrawPoint(renderer, -x+x0, -y+y0);
	SDL_RenderDrawPoint(renderer, y+x0, x+y0);
	SDL_RenderDrawPoint(renderer, -y+x0, x+y0);
	SDL_RenderDrawPoint(renderer, y+x0, -x+y0);
	SDL_RenderDrawPoint(renderer, -y+x0, -x+y0);
	SDL_RenderPresent(renderer);
}

int main(int argc, char** args) {
	HWND consoleWindow = GetConsoleWindow();
	double r = 0.0, x0 = 0.0, y0 = 0.0;
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
 
	SetWindowPos(consoleWindow, 0, CONSOLE_POSITION_X, CONSOLE_POSITION_Y, CONSOLE_WIDTH, CONSOLE_HEIGHT, 0);


	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Chyba pri inicializaci SDL: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "PS-SLU-CircleBresenhamDrawer");
	SDL_SetWindowPosition(window, WINDOW_POSITION_X, WINDOW_POSITION_Y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
	std::cout << "Parametry vykreslovaciho okna jsou:" << std::endl << "Sirka: " << WINDOW_WIDTH << std::endl << "Vyska: " << WINDOW_HEIGHT << std::endl;
	std::cout << "Hodnoty museji mit hodnotu vetsi nez 0!" << std::endl << "Maji datovy typ double." << std::endl;

	do {
		std::cout << "Zadejte hodnotu polomeru r kruznice: " << std::endl;
		std::cin >> r;
	} while (!r);
	do {
		std::cout << "Zadejte hodnotu souradnice stredu S x0: " << std::endl;
		std::cin >> x0;
	} while (!x0);
	do {
		std::cout << "Zadejte hodnotu souradnice stredu S y0: " << std::endl;
		std::cin >> y0;
	} while (!y0);
	std::cout << "Vykresluji kruznici na zaklade polomeru r " << r << " se stredem v bode S[" << x0  << ";" << y0 << "]." << std::endl;
	std::cout << std::endl;
	drawCircleUsingBresenhamAlgorithm(r, x0, y0, renderer);

	if (!window) {
		std::cout << "Chyba pri vytvareni grafickeho okna: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	winSurface = SDL_GetWindowSurface(window);

	if (!winSurface) {
		std::cout << "Chyba pri ziskavani vykreslovaci oblasti: " << SDL_GetError() << std::endl;
		system("pause");
		return 1;
	}

	system("pause");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}