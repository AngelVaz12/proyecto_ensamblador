#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para system("cls") y otras funciones estándar
#include <Windows.h>    // Para Sleep y Beep
#include <conio.h>      // Para getch()

// DEFINICIÓN DEL TAMAÑO DEL LABERINTO
#define REN 16
#define COL 16

// PROTOTIPO DE LA FUNCIÓN EN ENSAMBLADOR
extern int funciones_laberinto(char *mapa, int ren, int col, char tecla);

// PROTOTIPOS DE FUNCIONES
void pantalla_bienvenida();  // MUESTRA MENSAJE INICIAL
int menu();                  // MUESTRA EL MENÚ PRINCIPAL
int display();               // MUESTRA EL JUEGO

int main() {
    int op = 0;
    SetConsoleOutputCP(CP_UTF8); // PERMITE IMPRIMIR CARACTERES UTF-8 EN CONSOLA
    pantalla_bienvenida();       // MUESTRA EL BANNER INICIAL

    // BUCLE PRINCIPAL DEL PROGRAMA
    do {
        if (op != 1) {
            op = menu();        // SI NO VIENE DE UN REINICIO, MUESTRA EL MENÚ
        }

        if (op != 2) {
            op = display();     // MUESTRA EL JUEGO SI NO SE HA SALIDO
        }

    } while (op != 2);          // REPITE MIENTRAS NO SE ELIJA SALIR

    // MENSAJE DE DESPEDIDA
    printf("\n\n\n\n██╗░░██╗░█████╗░░██████╗████████╗░█████╗░      ██╗░░░░░██╗░░░██╗███████╗░██████╗░░█████╗░\n");
    printf("██║░░██║██╔══██╗██╔════╝╚══██╔══╝██╔══██╗      ██║░░░░░██║░░░██║██╔════╝██╔════╝░██╔══██╗\n");
    printf("███████║███████║╚█████╗░░░░██║░░░███████║      ██║░░░░░██║░░░██║█████╗░░██║░░██╗░██║░░██║\n");
    printf("██╔══██║██╔══██║░╚═══██╗░░░██║░░░██╔══██║      ██║░░░░░██║░░░██║██╔══╝░░██║░░╚██╗██║░░██║\n");
    printf("██║░░██║██║░░██║██████╔╝░░░██║░░░██║░░██║      ███████╗╚██████╔╝███████╗╚██████╔╝╚█████╔╝\n");
    printf("╚═╝░░╚═╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚═╝░░╚═╝      ╚══════╝░╚═════╝░╚══════╝░╚═════╝░░╚════╝░\n");

    Sleep(1000);
    system("cls");
    return 0;
}

//----------------------------------------------------------------------------------

void pantalla_bienvenida() {
    // LIMPIA LA PANTALLA Y MUESTRA UN BANNER BONITO
    system("cls");
    printf("██╗░░░░░░█████╗░██████╗░███████╗██████╗░██╗███╗░░██╗████████╗░█████╗░\n");
    printf("██║░░░░░██╔══██╗██╔══██╗██╔════╝██╔══██╗██║████╗░██║╚══██╔══╝██╔══██╗\n");
    printf("██║░░░░░███████║██████╦╝█████╗░░██████╔╝██║██╔██╗██║░░░██║░░░██║░░██║\n");
    printf("██║░░░░░██╔══██║██╔══██╗██╔══╝░░██╔══██╗██║██║╚████║░░░██║░░░██║░░██║\n");
    printf("███████╗██║░░██║██████╦╝███████╗██║░░██║██║██║░╚███║░░░██║░░░╚█████╔╝\n");
    printf("╚══════╝╚═╝░░╚═╝╚═════╝░╚══════╝╚═╝░░╚═╝╚═╝╚═╝░░╚══╝░░░╚═╝░░░░╚════╝░\n\n");
    printf("Presiona ENTER para comenzar...\n");
    getchar();  // ESPERA A QUE EL USUARIO PRESIONE ENTER
}

//----------------------------------------------------------------------------------

int menu() {
    int resp = 0;
    system("cls");  // LIMPIA LA PANTALLA

    // DIBUJA EL MENÚ EN CONSOLA
    printf("╔══════════════════════════════════════╗\n");
    printf("║          JUEGO DEL LABERINTO         ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  1. Empezar                          ║\n");
    printf("║  2. Salir                            ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("Seleccione una opción: ");

    fflush(stdin);   // LIMPIA EL BUFFER DE ENTRADA
    scanf("%d", &resp);  // LEE LA OPCIÓN DEL USUARIO

    Sleep(1000);
    system("cls");
    return resp;     // DEVUELVE LA OPCIÓN
}

//----------------------------------------------------------------------------------

int display() {
    char tecla;

    // MATRIZ DEL LABERINTO
    char mapa[REN][COL] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','P','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','.','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','#','.','#','.','.','.','.','.','.','#','.','#'},
        {'#','#','#','.','#','.','#','#','#','#','#','#','.','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','.','.','#','.','#','.','#'},
        {'#','.','#','#','#','#','#','#','#','#','.','#','.','#','.','#'},
        {'#','.','.','.','.','.','.','.','#','#','.','#','.','#','.','#'},
        {'#','#','#','#','#','#','#','.','#','.','.','#','.','#','.','#'},
        {'#','.','.','.','.','.','#','.','#','#','#','#','.','#','.','#'},
        {'#','.','#','#','#','.','#','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','.','.','.','#','#','#','#','#','#','#','#','.','#'},
        {'#','.','#','.','#','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','.','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','X','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    do {
        // IMPRIME EL LABERINTO EN PANTALLA
        for (int i = 0; i < REN; i++) {
            for (int j = 0; j < COL; j++) {
                printf(" %c", mapa[i][j]);
            }
            printf("\n");
        }

        // INSTRUCCIONES
        printf("\n||| Usa W/A/S/D para moverte |||");
        printf("\n        R para reiniciar");
        printf("\n         E para salir\n\n");

        tecla = getch();  // CAPTURA LA TECLA PRESIONADA

        // SONIDOS AL PRESIONAR TECLAS
        if (tecla == 'w' || tecla == 'a' || tecla == 's' || tecla == 'd') {
            Beep(750, 50);
        } else if (tecla == 'r') {
            Beep(500, 150);
        } else if (tecla == 'e') {
            Beep(1000, 150);
        }

        // SI PRESIONÓ 'r', REINICIA
        if (tecla == 'r') {
            system("cls");
            Sleep(800);
            return 1;
        }

        // LLAMA A LA FUNCIÓN EN ENSAMBLADOR Y VERIFICA SI GANÓ
        int resultado = funciones_laberinto((char *)mapa, REN, COL, tecla);    

        if (resultado == 1) {
            // SI GANÓ, MUESTRA MENSAJE Y SALE
            Sleep(800);
            system("cls");
            printf("░██████╗░░█████╗░███╗░░██╗░█████╗░░██████╗████████╗███████╗\n");
            printf("██╔════╝░██╔══██╗████╗░██║██╔══██╗██╔════╝╚══██╔══╝██╔════╝\n");
            printf("██║░░██╗░███████║██╔██╗██║███████║╚█████╗░░░░██║░░░█████╗░░\n");
            printf("██║░░╚██╗██╔══██║██║╚████║██╔══██║░╚═══██╗░░░██║░░░██╔══╝░░\n");
            printf("╚██████╔╝██║░░██║██║░╚███║██║░░██║██████╔╝░░░██║░░░███████╗\n");
            printf("░╚═════╝░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═════╝░░░░╚═╝░░░╚══════╝\n\n");
            Sleep(1500);
            system("cls");
            return 0;
        }

        system("cls");  // LIMPIA LA PANTALLA

    } while (tecla != 'e');  // REPITE HASTA QUE PRESIONE 'e'

    system("cls");
    Sleep(800);
    return 2;  // SALE DEL PROGRAMA
    // Versión ligera sin cambios visibles
}
