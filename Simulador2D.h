#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream>
#include <iomanip>

template <typename T>
class Simulador2D
{
private:
    // Matriz de la cuadricula (Dinamica y Generica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinamico y Generico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estatico)
    float _constantes[3]; // [0] = Coeficiente de Difusion, [1] = DeltaX, [2] = DeltaT

    // Metodos privados auxiliares
    void _liberarGrid();
    void _asignarGrid();
    void _copiarDatos(T **origen, T **destino, int filasMin, int columnasMin);

public:
    // Constructor
    Simulador2D(int f, int c) : _filas(f), _columnas(c), _numFuentes(0), _capacidadFuentes(2)
    {
        // Inicializar constantes por defecto
        _constantes[0] = 0.25f; // Coeficiente de Difusion
        _constantes[1] = 1.0f;  // DeltaX
        _constantes[2] = 1.0f;  // DeltaT

        // Asignar memoria para el grid
        _asignarGrid();

        // Inicializar grid con ceros
        inicializarGrid();

        // Asignar memoria inicial para fuentes
        _fuentes = new T[_capacidadFuentes];
    }

    // Destructor
    ~Simulador2D()
    {
        _liberarGrid();
        delete[] _fuentes;
    }

    // Constructor de copia
    Simulador2D(const Simulador2D<T> &otro)
        : _filas(otro._filas), _columnas(otro._columnas),
          _numFuentes(otro._numFuentes), _capacidadFuentes(otro._capacidadFuentes)
    {

        // Copiar constantes
        for (int i = 0; i < 3; i++)
        {
            _constantes[i] = otro._constantes[i];
        }

        // Asignar y copiar grid
        _asignarGrid();
        _copiarDatos(otro._grid, _grid, _filas, _columnas);

        // Asignar y copiar fuentes
        _fuentes = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; i++)
        {
            _fuentes[i] = otro._fuentes[i];
        }
    }

    // Operador de asignacion
    Simulador2D<T> &operator=(const Simulador2D<T> &otro)
    {
        if (this != &otro)
        {
            // Liberar memoria actual
            _liberarGrid();
            delete[] _fuentes;

            // Copiar datos basicos
            _filas = otro._filas;
            _columnas = otro._columnas;
            _numFuentes = otro._numFuentes;
            _capacidadFuentes = otro._capacidadFuentes;

            // Copiar constantes
            for (int i = 0; i < 3; i++)
            {
                _constantes[i] = otro._constantes[i];
            }

            // Asignar y copiar grid
            _asignarGrid();
            _copiarDatos(otro._grid, _grid, _filas, _columnas);

            // Asignar y copiar fuentes
            _fuentes = new T[_capacidadFuentes];
            for (int i = 0; i < _numFuentes; i++)
            {
                _fuentes[i] = otro._fuentes[i];
            }
        }
        return *this;
    }

    // Redimensionar Grid
    void redimensionarGrid(int nuevaF, int nuevaC)
    {
        // Crear nuevo grid temporal
        T **nuevoGrid = new T *[nuevaF];
        for (int i = 0; i < nuevaF; i++)
        {
            nuevoGrid[i] = new T[nuevaC];
            // Inicializar con ceros
            for (int j = 0; j < nuevaC; j++)
            {
                nuevoGrid[i][j] = T(0);
            }
        }

        // Copiar datos existentes
        int filasMin = (_filas < nuevaF) ? _filas : nuevaF;
        int columnasMin = (_columnas < nuevaC) ? _columnas : nuevaC;
        _copiarDatos(_grid, nuevoGrid, filasMin, columnasMin);

        // Liberar grid anterior
        _liberarGrid();

        // Asignar nuevo grid
        _grid = nuevoGrid;
        _filas = nuevaF;
        _columnas = nuevaC;
    }

    // Agregar Fuente (con expansion automatica)
    void agregarFuente(T valor)
    {
        // Verificar si necesita expansion
        if (_numFuentes >= _capacidadFuentes)
        {
            // Duplicar capacidad
            int nuevaCapacidad = _capacidadFuentes * 2;
            T *nuevasFuentes = new T[nuevaCapacidad];

            // Copiar fuentes existentes
            for (int i = 0; i < _numFuentes; i++)
            {
                nuevasFuentes[i] = _fuentes[i];
            }

            // Liberar memoria anterior
            delete[] _fuentes;

            // Asignar nuevo vector
            _fuentes = nuevasFuentes;
            _capacidadFuentes = nuevaCapacidad;
        }

        // Agregar nueva fuente
        _fuentes[_numFuentes] = valor;
        _numFuentes++;
    }

    // Simular Paso (Algoritmo de Difusion)
    void simularPaso()
    {
        // Crear matriz temporal
        T **temp = new T *[_filas];
        for (int i = 0; i < _filas; i++)
        {
            temp[i] = new T[_columnas];
        }

        // Copiar valores actuales a temporal
        _copiarDatos(_grid, temp, _filas, _columnas);

        // Aplicar algoritmo de difusion (solo celdas internas)
        for (int i = 1; i < _filas - 1; i++)
        {
            for (int j = 1; j < _columnas - 1; j++)
            {
                // Promedio de los cuatro vecinos
                T suma = temp[i - 1][j] + temp[i + 1][j] + temp[i][j - 1] + temp[i][j + 1];
                _grid[i][j] = suma / T(4);
            }
        }

        // Liberar matriz temporal
        for (int i = 0; i < _filas; i++)
        {
            delete[] temp[i];
        }
        delete[] temp;
    }

    // Metodos de configuracion
    void inicializarGrid(T valorInicial = T(0))
    {
        for (int i = 0; i < _filas; i++)
        {
            for (int j = 0; j < _columnas; j++)
            {
                _grid[i][j] = valorInicial;
            }
        }
    }

    void establecerConstantes(float coefDifusion, float deltaX, float deltaT)
    {
        _constantes[0] = coefDifusion;
        _constantes[1] = deltaX;
        _constantes[2] = deltaT;
    }

    void aplicarFuenteEnGrid(int fila, int columna, int indiceFuente)
    {
        if (fila >= 0 && fila < _filas && columna >= 0 && columna < _columnas &&
            indiceFuente >= 0 && indiceFuente < _numFuentes)
        {
            _grid[fila][columna] = _fuentes[indiceFuente];
        }
    }

    // Metodos de acceso
    T obtenerValor(int fila, int columna) const
    {
        if (fila >= 0 && fila < _filas && columna >= 0 && columna < _columnas)
        {
            return _grid[fila][columna];
        }
        return T(0);
    }

    void establecerValor(int fila, int columna, T valor)
    {
        if (fila >= 0 && fila < _filas && columna >= 0 && columna < _columnas)
        {
            _grid[fila][columna] = valor;
        }
    }

    int obtenerFilas() const
    {
        return _filas;
    }

    int obtenerColumnas() const
    {
        return _columnas;
    }

    int obtenerNumFuentes() const
    {
        return _numFuentes;
    }

    T obtenerFuente(int indice) const
    {
        if (indice >= 0 && indice < _numFuentes)
        {
            return _fuentes[indice];
        }
        return T(0);
    }

    // Metodos de visualizacion
    void mostrarGrid() const
    {
        for (int i = 0; i < _filas; i++)
        {
            std::cout << "| ";
            for (int j = 0; j < _columnas; j++)
            {
                std::cout << std::setw(6) << std::setprecision(1) << std::fixed << _grid[i][j] << " | ";
            }
            std::cout << std::endl;
        }
    }

    void mostrarFuentes() const
    {
        std::cout << "Fuentes registradas (" << _numFuentes << "/" << _capacidadFuentes << "):" << std::endl;
        for (int i = 0; i < _numFuentes; i++)
        {
            std::cout << "Fuente " << (i + 1) << ": " << _fuentes[i] << std::endl;
        }
    }

    void mostrarConstantes() const
    {
        std::cout << "Constantes de Simulacion:" << std::endl;
        std::cout << "Coeficiente de Difusion: " << _constantes[0] << std::endl;
        std::cout << "Delta X: " << _constantes[1] << std::endl;
        std::cout << "Delta T: " << _constantes[2] << std::endl;
    }
};

// Definiciones de metodos privados auxiliares 
template <typename T>
void Simulador2D<T>::_liberarGrid()
{
    if (_grid != nullptr)
    {
        for (int i = 0; i < _filas; i++)
        {
            delete[] _grid[i];
        }
        delete[] _grid;
        _grid = nullptr;
    }
}

template <typename T>
void Simulador2D<T>::_asignarGrid()
{
    _grid = new T *[_filas];
    for (int i = 0; i < _filas; i++)
    {
        _grid[i] = new T[_columnas];
    }
}

template <typename T>
void Simulador2D<T>::_copiarDatos(T **origen, T **destino, int filasMin, int columnasMin)
{
    for (int i = 0; i < filasMin; i++)
    {
        for (int j = 0; j < columnasMin; j++)
        {
            destino[i][j] = origen[i][j];
        }
    }
}

#endif
