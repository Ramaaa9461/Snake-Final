#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

//Accedo a la conosla para utilizar sus valores
const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void initializeConsoleColors(); //Seteo los colores para luego poder utilizarlos 

void setCurrentColor(int color); //Seteo el color actual con el se renderizara la pantalla

void goToCoordinates(int x, int y); //Me posiciono en una coordenada especifica

void hideCursor(); //Escondo el cursor

int getScreenWidth(); //Calculo el ancho de la consola

int getScreenHeight();//Calculo el largo de la consola





