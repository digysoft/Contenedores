/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.

Programa: Contenedores
Autor: Jose Vidal
E-mail: jvidalsm@gmail.com
Fecha: 26/05/2021
Version: 1.0.0

Descripcion:
Entrada: El registro de entrada contiene varios casos de prueba. Cada caso de
prueba consta de una sola línea que contiene de 1 a 1000 letras mayúsculas que
representan el orden de llegada de un conjunto de contenedores.
Por ejemplo, la línea ABAC significa que llegan contenedores consecutivos para
ser cargados en los barcos A, B, A y C, respectivamente. Cuando han llegado todos
loscontenedores, los barcos se cargan en un orden estrictamente creciente:
primero el barco A, luego el barco B y así sucesivamente. Una línea que contiene
la palabra FIN sigue al último caso de prueba.

Salida: Para cada caso de entrada, imprima el número de caso (comenzando con 1)
y el número mínimo de pilas necesarias para almacenar los contenedores antes de
que comience la carga. Su formato de salida debe ser similar al que se muestra aquí.
*******************************************************************************/

//agregar cabeceras
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum{PILAS=30,CONTENEDORES=1000,FIN=3};

int main()
{
    //declarar e inicializar variables.
    int n_caso=0;//indica el total de casos que seran evaluados antes de FIN
    int n_pila=0;//indica el total de pilas para cada caso
    int n_letra=0;//indica la ubicacion de la letra que se evalua para cada caso
    int n_pila_aux = 0;//un contador de pila para recorrer todas las pilas
    int nueva_pila = 0;//indica si se agrega nueva pila (1) o no (0)
    char pilas[PILAS][CONTENEDORES];//matriz de pilas X contenedores
    char contenedores[CONTENEDORES];//buffer para almacenar los contenedores que ingresan para cada caso
    std::string input_contenedores;//recibe los contenedores
    int salir = 0;//si es mayor que 0, sale del programa
    char letra = 0;//se almacena cada letra para evaluacion

    std::cout << "Start:\n";
    std::cout << "=====\n\n";
    while(salir == 0){//permanece en loop mientras salir sea 0

		//inicializar matriz en cero
        for (int i=0; i<PILAS; i++)
        {
            for (int j=0; j<CONTENEDORES; j++)
            {
                pilas[i][j] = 0;
            }
        }

		//inicializar linea de contenedores en cero
        for (int i=0; i<CONTENEDORES; i++)
        {
            contenedores[i] = 0;
        }

        //leer entrada del teclado
        getline (std::cin, input_contenedores);

		//verificar que no sea mayor que el maximo permitido
        if (strlen(input_contenedores.c_str()) > CONTENEDORES) salir = 1;//si no cumple, sale del programa

        if (salir == 0)
        {
			//copiar caracteres recibidos desde el teclado hacia el buffer de contenedores
            strcpy(contenedores, input_contenedores.c_str());

			//verifica que la linea de contenedores sean letras y en mayusculas
            for (int i=0; i<strlen(contenedores); i++)
            {
                if (contenedores[i] < 65 || contenedores[i] > 90)
                {
                    salir = 2;//si no cumple, sale del programa.
                    break;
                }
            }
        }

        if (salir == 0)
        {
			//verificar que sea diferenteque FIN
            if (strlen(contenedores) == FIN && strcmp(contenedores,"FIN") == 0) salir = 3;//si no cumple, sale del programa
        }

        if (salir == 0)
        {
            //reinicia variables
            n_letra = 0;
            n_pila = 0;

			//permanece en el loop mientras exista una letra
            while (contenedores[n_letra] > 0)
            {
                letra = contenedores[n_letra];//asigna a letra para evaluacion

				//en caso sea la primera letra leida
                if (n_letra == 0)
                {
                    pilas[n_pila][0] = letra;//se ubica en primera posicion
                    n_letra++;
                    n_pila++;
                    n_caso++;
                }
                else
                {
                    n_pila_aux = 0;
                    nueva_pila = 1;//se asume que se creara nueva pila

					//permanece en loop hasta que termine de revisar todas las pilas
                    while (n_pila_aux < n_pila)
                    {
                        //obtener ultima posicion de la letra
                        int posicion = strlen(pilas[n_pila_aux]) - 1;

						//compara nueva letra con la que ya se encuentra en el buffer de pilas
                        if (letra <= pilas[n_pila_aux][posicion])
                        {
                            pilas[n_pila_aux][posicion+1] = letra;//ubicar letra encima de todas
                            n_pila_aux = n_pila;//para salir del loop
                            n_letra++;
                            nueva_pila = 0;//no se crea nueva pila
                        }
                        else {
                            n_pila_aux++;
                        }
                    }

					//si existe nueva pila, asignar la letra a la primera ubicacion
                    if (nueva_pila == 1)
                    {
                         pilas[n_pila][0] = letra;//iniciar pila colocando la letra
                         n_letra++;
                         n_pila++;
                         nueva_pila = 0;
                         n_pila_aux = 0;
                    }

                }
            }

			//si existen casos, imprimir el caso actual con la cantidad de pilas
            if (n_caso > 0)
            {
                std::cout << "\tCaso " << n_caso << ": " << n_pila <<"\n";
            }
        }
    }

    //pinta para finalizar
    std::cout << "\n=======\n";

    //evalua la condicion de salida
    switch(salir)
    {
        case 1: std::cout << "*Maximo de contenedores es " << CONTENEDORES << "\n"; break;
        case 2: std::cout << "*Todos los contenedores deben ser letras y en mayusculas\n"; break;
        case 3: std::cout << "*Programa finaliza con entrada 'FIN'\n"; break;
        default: std::cout << "*Error desconocido\n"; break;
    }
}

