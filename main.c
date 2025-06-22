#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define FILAS 10
#define COLUMNAS 10

// FUNCIONES DEFINIDAS EN ENSAMBLADOR (.asm)
extern void _mostrarLaberinto(char* lab, int filas, int columnas);
extern int _puedeMover(char* lab, int filas, int columnas, int x, int y);

// MATRIZ DEL LABERINTO (10x10)
char laberinto[FILAS][COLUMNAS] = {
    "##########",
    "#P     # #",
    "# ### #  #",
    "#   # ## #",
    "### #    #",
    "#   #####X",
    "# #      #",
    "# ###### #",
    "#        #",
    "##########"
};

int jugadorX = 1, jugadorY = 1;

// FUNCION PARA MOVER AL JUGADOR
void mover(int dx, int dy) {
    int nuevaX = jugadorX + dx;
    int nuevaY = jugadorY + dy;

    if (_puedeMover(&laberinto[0][0], FILAS, COLUMNAS, nuevaX, nuevaY)) {
        if (laberinto[nuevaX][nuevaY] == 'X') {
            system("cls");
            laberinto[jugadorX][jugadorY] = ' ';
            jugadorX = nuevaX;
            jugadorY = nuevaY;
            laberinto[jugadorX][jugadorY] = 'P';
            _mostrarLaberinto(&laberinto[0][0], FILAS, COLUMNAS);
            printf("¡Felicidades! Has llegado a la salida.\n");
            exit(0);
        }

        laberinto[jugadorX][jugadorY] = ' ';
        jugadorX = nuevaX;
        jugadorY = nuevaY;
        laberinto[jugadorX][jugadorY] = 'P';
    }
}

// FUNCION PRINCIPAL
int main() {
    char tecla;

    while (1) {
        system("cls");
        _mostrarLaberinto(&laberinto[0][0], FILAS, COLUMNAS);
        printf("Usa W/A/S/D para moverte. Presiona 'q' para salir.\n");

        tecla = _getch();

        if (tecla == 'w') mover(-1, 0);
        else if (tecla == 's') mover(1, 0);
        else if (tecla == 'a') mover(0, -1);
        else if (tecla == 'd') mover(0, 1);
        else if (tecla == 'q') break;
    }

    return 0;
}
