#include "Simulador2D.h"
#include <iostream>
#include <iomanip>

void mostrarMenu()
{
    std::cout << "\n=== SIMULADOR GENERICO DE FLUIDOS 2D ===" << std::endl;
    std::cout << "1. Simular 1 paso" << std::endl;
    std::cout << "2. Simular multiples pasos" << std::endl;
    std::cout << "3. Mostrar grid actual" << std::endl;
    std::cout << "4. Mostrar fuentes" << std::endl;
    std::cout << "5. Agregar nueva fuente" << std::endl;
    std::cout << "6. Aplicar fuente en posicion" << std::endl;
    std::cout << "7. Redimensionar grid" << std::endl;
    std::cout << "8. Reinicializar grid" << std::endl;
    std::cout << "9. Cambiar a simulador de enteros" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Opcion: ";
}

template <typename T>
void ejecutarSimuladorFloat()
{
    std::cout << "\n--- Simulador Generico de Fluidos (Difusion) ---" << std::endl;
    std::cout << "\n>> Inicializando Sistema (Tipo FLOAT) <<" << std::endl;

    // Crear simulador de 5x5
    Simulador2D<T> simulador(5, 5);
    std::cout << "Creando Grid (FLOAT) de 5x5..." << std::endl;

    // Agregar fuentes
    std::cout << "\n>> Agregando Fuentes de Concentracion <<" << std::endl;
    simulador.agregarFuente(T(100.0));
    std::cout << "Agregar Fuente 1 (Valor 100.0): Exito." << std::endl;

    simulador.agregarFuente(T(50.0));
    std::cout << "Agregar Fuente 2 (Valor 50.0): Exito." << std::endl;

    // Aplicar valores iniciales
    std::cout << "\n>> Aplicando Valores Iniciales <<" << std::endl;
    simulador.aplicarFuenteEnGrid(2, 2, 0); // Fuente 1 en centro
    simulador.aplicarFuenteEnGrid(4, 0, 1); // Fuente 2 en esquina
    std::cout << "Grid[2,2] = 100.0 (Fuente 1)" << std::endl;
    std::cout << "Grid[4,0] = 50.0 (Fuente 2)" << std::endl;

    // Mostrar grid inicial
    std::cout << "\n--- Grid Inicial (Paso 0) ---" << std::endl;
    simulador.mostrarGrid();

    int opcion;
    int pasos = 0;

    do
    {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            pasos++;
            std::cout << "\nSimulando Propagacion..." << std::endl;
            simulador.simularPaso();
            std::cout << "\n--- Grid Despues del Paso " << pasos << " ---" << std::endl;
            simulador.mostrarGrid();
            break;
        }
        case 2:
        {
            int numPasos;
            std::cout << "Numero de pasos a simular: ";
            std::cin >> numPasos;
            for (int i = 0; i < numPasos; i++)
            {
                simulador.simularPaso();
                pasos++;
            }
            std::cout << "\n--- Grid Despues de " << numPasos << " pasos adicionales (Paso total: " << pasos << ") ---" << std::endl;
            simulador.mostrarGrid();
            break;
        }
        case 3:
        {
            std::cout << "\n--- Grid Actual (Paso " << pasos << ") ---" << std::endl;
            simulador.mostrarGrid();
            break;
        }
        case 4:
        {
            std::cout << "\n--- Fuentes Registradas ---" << std::endl;
            simulador.mostrarFuentes();
            break;
        }
        case 5:
        {
            T valor;
            std::cout << "Valor de la nueva fuente: ";
            std::cin >> valor;
            simulador.agregarFuente(valor);
            std::cout << "Fuente agregada exitosamente." << std::endl;
            break;
        }
        case 6:
        {
            int fila, columna, indiceFuente;
            std::cout << "Fila: ";
            std::cin >> fila;
            std::cout << "Columna: ";
            std::cin >> columna;
            std::cout << "Indice de fuente (0-" << (simulador.obtenerNumFuentes() - 1) << "): ";
            std::cin >> indiceFuente;
            simulador.aplicarFuenteEnGrid(fila, columna, indiceFuente);
            std::cout << "Fuente aplicada en posicion [" << fila << "," << columna << "]" << std::endl;
            break;
        }
        case 7:
        {
            int nuevaF, nuevaC;
            std::cout << "Nuevas dimensiones - Filas: ";
            std::cin >> nuevaF;
            std::cout << "Columnas: ";
            std::cin >> nuevaC;
            simulador.redimensionarGrid(nuevaF, nuevaC);
            std::cout << "Redimensionando Grid a " << nuevaF << "x" << nuevaC << ". Datos copiados." << std::endl;
            break;
        }
        case 8:
        {
            T valorInicial;
            std::cout << "Valor inicial para reinicializar: ";
            std::cin >> valorInicial;
            simulador.inicializarGrid(valorInicial);
            pasos = 0;
            std::cout << "Grid reinicializado." << std::endl;
            break;
        }
        case 9:
        {
            std::cout << "Cambiando a simulador de enteros..." << std::endl;
            return; // Salir de esta funcion para cambiar de tipo
        }
        case 0:
        {
            std::cout << "Liberando memoria del Grid y Fuentes... Sistema cerrado." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Opcion no valida." << std::endl;
            break;
        }
        }
    } while (opcion != 0 && opcion != 9);
}

void ejecutarSimuladorInt()
{
    std::cout << "\n--- Simulador Generico de Fluidos (Difusion) ---" << std::endl;
    std::cout << "\n>> Inicializando Sistema (Tipo INT) <<" << std::endl;

    // Crear simulador de 4x4 con enteros
    Simulador2D<int> simulador(4, 4);
    std::cout << "Creando Grid (INT) de 4x4..." << std::endl;

    // Agregar fuentes enteras
    std::cout << "\n>> Agregando Fuentes de Concentracion (Enteros) <<" << std::endl;
    simulador.agregarFuente(80);
    std::cout << "Agregar Fuente 1 (Valor 80): Exito." << std::endl;

    simulador.agregarFuente(40);
    std::cout << "Agregar Fuente 2 (Valor 40): Exito." << std::endl;

    // Aplicar valores iniciales
    std::cout << "\n>> Aplicando Valores Iniciales <<" << std::endl;
    simulador.aplicarFuenteEnGrid(1, 1, 0); // Fuente 1
    simulador.aplicarFuenteEnGrid(2, 2, 1); // Fuente 2
    std::cout << "Grid[1,1] = 80 (Fuente 1)" << std::endl;
    std::cout << "Grid[2,2] = 40 (Fuente 2)" << std::endl;

    // Mostrar grid inicial
    std::cout << "\n--- Grid Inicial (Paso 0) ---" << std::endl;
    simulador.mostrarGrid();

    int opcion;
    int pasos = 0;

    do
    {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            pasos++;
            std::cout << "\nSimulando Propagacion..." << std::endl;
            simulador.simularPaso();
            std::cout << "\n--- Grid Despues del Paso " << pasos << " ---" << std::endl;
            simulador.mostrarGrid();
            break;
        }
        case 2:
        {
            int numPasos;
            std::cout << "Numero de pasos a simular: ";
            std::cin >> numPasos;
            for (int i = 0; i < numPasos; i++)
            {
                simulador.simularPaso();
                pasos++;
            }
            std::cout << "\n--- Grid Despues de " << numPasos << " pasos adicionales (Paso total: " << pasos << ") ---" << std::endl;
            simulador.mostrarGrid();
            break;
        }
        case 3:
        {
            std::cout << "\n--- Grid Actual (Paso " << pasos << ") ---" << std::endl;
            simulador.mostrarGrid();
            break;
        }
        case 4:
        {
            std::cout << "\n--- Fuentes Registradas ---" << std::endl;
            simulador.mostrarFuentes();
            break;
        }
        case 5:
        {
            int valor;
            std::cout << "Valor de la nueva fuente: ";
            std::cin >> valor;
            simulador.agregarFuente(valor);
            std::cout << "Fuente agregada exitosamente." << std::endl;
            break;
        }
        case 6:
        {
            int fila, columna, indiceFuente;
            std::cout << "Fila: ";
            std::cin >> fila;
            std::cout << "Columna: ";
            std::cin >> columna;
            std::cout << "Indice de fuente (0-" << (simulador.obtenerNumFuentes() - 1) << "): ";
            std::cin >> indiceFuente;
            simulador.aplicarFuenteEnGrid(fila, columna, indiceFuente);
            std::cout << "Fuente aplicada en posicion [" << fila << "," << columna << "]" << std::endl;
            break;
        }
        case 7:
        {
            int nuevaF, nuevaC;
            std::cout << "Nuevas dimensiones - Filas: ";
            std::cin >> nuevaF;
            std::cout << "Columnas: ";
            std::cin >> nuevaC;
            simulador.redimensionarGrid(nuevaF, nuevaC);
            std::cout << "Redimensionando Grid a " << nuevaF << "x" << nuevaC << ". Datos copiados." << std::endl;
            break;
        }
        case 8:
        {
            int valorInicial;
            std::cout << "Valor inicial para reinicializar: ";
            std::cin >> valorInicial;
            simulador.inicializarGrid(valorInicial);
            pasos = 0;
            std::cout << "Grid reinicializado." << std::endl;
            break;
        }
        case 9:
        {
            std::cout << "Cambiando a simulador de flotantes..." << std::endl;
            return; // Salir de esta función para cambiar de tipo
        }
        case 0:
        {
            std::cout << "Liberando memoria del Grid y Fuentes... Sistema cerrado." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Opcion no valida." << std::endl;
            break;
        }
        }
    } while (opcion != 0 && opcion != 9);
}

int main()
{
    std::cout << std::fixed << std::setprecision(1);

    int tipoSimulador;

    do
    {
        std::cout << "\n=== SELECCION DE TIPO DE SIMULADOR ===" << std::endl;
        std::cout << "1. Simulador de flotantes (float)" << std::endl;
        std::cout << "2. Simulador de enteros (int)" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione el tipo: ";
        std::cin >> tipoSimulador;

        switch (tipoSimulador)
        {
        case 1:
            ejecutarSimuladorFloat<float>();
            break;
        case 2:
            ejecutarSimuladorInt();
            break;
        case 0:
            std::cout << "Gracias por usar el Simulador 2D!" << std::endl;
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
            break;
        }
    } while (tipoSimulador != 0);

    return 0;
}
