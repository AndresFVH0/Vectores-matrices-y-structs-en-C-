#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


struct Estudiante {
    string nombre;
    int codigo;
    vector<double> notas;  
};

using Matriz = vector<vector<int>>;

vector<double> leerVector(int n) {
    vector<double> v;
    for (int i = 0; i < n; i++) {
        double x;
        cout << "Elemento " << i + 1 << ": ";
        cin >> x;
        v.push_back(x); 
    }
    return v;
}

void imprimirVector(const vector<double>& v) {
    cout << "[ ";
    for (double x : v) cout << x << " ";
    cout << "]\n";
}

double promedio(const vector<double>& v) {
    if (v.empty()) return 0;
    double suma = 0;
    for (double x : v) suma += x;
    return suma / v.size();
}

double mayor(const vector<double>& v) {
    double m = v[0];
    for (double x : v)
        if (x > m) m = x;
    return m;
}

double menor(const vector<double>& v) {
    double m = v[0];
    for (double x : v)
        if (x < m) m = x;
    return m;
}


Matriz crearMatriz(int filas, int cols) {
    return Matriz(filas, vector<int>(cols, 0));
}

void leerMatriz(Matriz& m, const string& nombre) {
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m[i].size(); j++) {
            cout << nombre << "[" << i << "][" << j << "]: ";
            cin >> m[i][j];
        }
}

void imprimirMatriz(const Matriz& m) {
    for (const auto& fila : m) {
        for (int x : fila) cout << setw(5) << x;
        cout << "\n";
    }
}

Matriz sumar(const Matriz& a, const Matriz& b) {
    Matriz r = crearMatriz(a.size(), a[0].size());
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a[0].size(); j++)
            r[i][j] = a[i][j] + b[i][j];
    return r;
}

Matriz multiplicar(const Matriz& a, const Matriz& b) {
    int n = a.size();
    Matriz r = crearMatriz(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                r[i][j] += a[i][k] * b[k][j];
    return r;
}

Matriz transpuesta(const Matriz& m) {
    Matriz r = crearMatriz(m[0].size(), m.size());
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m[0].size(); j++)
            r[j][i] = m[i][j];
    return r;
}

// ================= FUNCIONES CON REGISTROS (struct) =================
Estudiante leerEstudiante() {
    Estudiante e;
    cout << "Nombre: ";
    getline(cin >> ws, e.nombre);
    cout << "Codigo: ";
    cin >> e.codigo;
    int n;
    do {
        cout << "Cuantas notas tiene? ";
        cin >> n;
    } while (n <= 0);
    e.notas = leerVector(n);
    return e;
}

void mostrarEstudiante(const Estudiante& e) {
    cout << fixed << setprecision(2);
    cout << "Nombre:   " << e.nombre << "\n";
    cout << "Codigo:   " << e.codigo << "\n";
    cout << "Notas:    ";
    imprimirVector(e.notas);
    cout << "Promedio: " << promedio(e.notas) << "\n";
    cout << "----------------------\n";
}


void demoVector() {
    int n;
    do {
        cout << "Cuantos elementos tendra el vector? ";
        cin >> n;
    } while (n <= 0);

    vector<double> v = leerVector(n);
    cout << "\nVector: ";
    imprimirVector(v);
    cout << "Tamano:   " << v.size() << "\n";
    cout << "Promedio: " << promedio(v) << "\n";
    cout << "Mayor:    " << mayor(v) << "\n";
    cout << "Menor:    " << menor(v) << "\n";
}

void demoMatrices() {
    int n;
    do {
        cout << "Tamano de las matrices cuadradas (n x n): ";
        cin >> n;
    } while (n <= 0);

    Matriz a = crearMatriz(n, n), b = crearMatriz(n, n);
    cout << "\n-- Matriz A --\n";
    leerMatriz(a, "A");
    cout << "\n-- Matriz B --\n";
    leerMatriz(b, "B");

    cout << "\nA:\n";            imprimirMatriz(a);
    cout << "\nB:\n";            imprimirMatriz(b);
    cout << "\nA + B:\n";        imprimirMatriz(sumar(a, b));
    cout << "\nA x B:\n";        imprimirMatriz(multiplicar(a, b));
    cout << "\nTranspuesta de A:\n"; imprimirMatriz(transpuesta(a));
}

int main() {
    vector<Estudiante> estudiantes;  
    int opcion;

    do {
        cout << "\n===== MENU =====\n"
             << "1. Vector (promedio, mayor, menor)\n"
             << "2. Matrices (suma, producto, transpuesta)\n"
             << "3. Registrar estudiante (struct)\n"
             << "4. Listar estudiantes\n"
             << "0. Salir\n"
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: demoVector(); break;
            case 2: demoMatrices(); break;
            case 3: estudiantes.push_back(leerEstudiante()); break;
            case 4:
                if (estudiantes.empty()) cout << "No hay estudiantes registrados.\n";
                for (const auto& e : estudiantes) mostrarEstudiante(e);
                break;
            case 0: cout << "Hasta luego!\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
