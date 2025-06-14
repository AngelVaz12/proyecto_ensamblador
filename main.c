#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define FILAS 10
#define COLUMNAS 10

extern void mostrarLaberinto(char* lab, int filas, int columnas);
extern int puedeMover(char* lab, int filas, int columnas, int x, int y);

char laberinto[FILAS][COLUMNAS] = {
    "##########",
    "#P     # #",
    "# ### # #M",
    "#   # #  #",
    "### # ####",
    "#     #  #",
    "# ##### ##",
    "#       ##",
    "#######  #",
    "##########"
};

int jugadorX = 1, jugadorY = 1;

void mover(int dx, int dy) {
    int nuevaX = jugadorX + dx;
    int nuevaY = jugadorY + dy;

    if (puedeMover(&laberinto[0][0], FILAS, COLUMNAS, nuevaX, nuevaY)) {
        if (laberinto[nuevaX][nuevaY] == 'M') {
            printf("¡Ganaste!\n");
            exit(0);
        }

        laberinto[jugadorX][jugadorY] = ' ';
        jugadorX = nuevaX;
        jugadorY = nuevaY;
        laberinto[jugadorX][jugadorY] = 'P';
    }
}

int main() {
    char tecla;

    while (1) {
        system("cls");
        mostrarLaberinto(&laberinto[0][0], FILAS, COLUMNAS);
        printf("Mover: W/A/S/D | Salir: Q\n");

        tecla = _getch();

        if (tecla == 'w') mover(-1, 0);
        else if (tecla == 's') mover(1, 0);
        else if (tecla == 'a') mover(0, -1);
        else if (tecla == 'd') mover(0, 1);
        else if (tecla == 'q') break;
    }

    return 0;
}
