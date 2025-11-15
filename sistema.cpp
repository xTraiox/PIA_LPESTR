#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <ctime>
using namespace std;

struct Alumno {
    string nombre;
    int matricula;
    float parciales[3];
    float final;
    string fechaCreacion;
    string fechaModificacion;
};

// ─────────────────────────────────────────────
//           Obtener fecha y hora
// ─────────────────────────────────────────────
string obtenerFechaHora() {
    time_t now = time(0);
    tm *t = localtime(&now);
    char buffer[40];
    strftime(buffer, 40, "%d-%m-%Y_%H:%M:%S", t);
    return string(buffer);
}

// ─────────────────────────────────────────────
//           Cargar archivo alumnos.txt
// ─────────────────────────────────────────────
void cargarDatos(vector<Alumno> &alumnos) {
    ifstream f("alumnos.txt");
    if (!f.is_open()) {
        cout << "No existe alumnos.txt, se creará automáticamente.\n";
        return;
    }

    alumnos.clear();

    Alumno a;
    while (f >> a.nombre >> a.matricula
             >> a.parciales[0] >> a.parciales[1] >> a.parciales[2]
             >> a.fechaCreacion >> a.fechaModificacion) {

        a.final = (a.parciales[0] + a.parciales[1] + a.parciales[2]) / 3.0;
        alumnos.push_back(a);
    }

    cout << "Correctamente " << alumnos.size() << " alumnos cargados.\n";
}

// ─────────────────────────────────────────────
//           Guardar archivo alumnos.txt
// ─────────────────────────────────────────────
void guardarDatos(const vector<Alumno> &alumnos) {
    ofstream f("alumnos.txt");

    for (auto &a : alumnos) {
        f << a.nombre << " " << a.matricula << " "
          << a.parciales[0] << " " << a.parciales[1] << " " << a.parciales[2] << " "
          << a.fechaCreacion << " " << a.fechaModificacion << "\n";
    }

    cout << "Archivo alumnos.txt actualizado.\n";
}

// ─────────────────────────────────────────────
//             Agregar alumno
// ─────────────────────────────────────────────
void agregarAlumno(vector<Alumno> &alumnos) {
    Alumno a;

    cin.ignore();
    cout << "Nombre del alumno: ";
    getline(cin, a.nombre);

    cout << "Matricula: ";
    cin >> a.matricula;

    for (int i = 0; i < 3; i++) {
        cout << "Parcial " << i + 1 << ": ";
        cin >> a.parciales[i];
    }

    a.final = (a.parciales[0] + a.parciales[1] + a.parciales[2]) / 3.0;
    a.fechaCreacion = obtenerFechaHora();
    a.fechaModificacion = a.fechaCreacion;

    alumnos.push_back(a);
    guardarDatos(alumnos);

    cout << "Alumno agregado.\n";
}

// ─────────────────────────────────────────────
//             Leer alumno
// ─────────────────────────────────────────────
void leerAlumno(const vector<Alumno> &alumnos) {
    int mat;
    cout << "Matricula del alumno: ";
    cin >> mat;

    for (auto &a : alumnos) {
        if (a.matricula == mat) {
            cout << "\nNombre: " << a.nombre << "\n";
            cout << "Matricula: " << a.matricula << "\n";
            cout << "Parciales: " << a.parciales[0] << ", "
                 << a.parciales[1] << ", " << a.parciales[2] << "\n";
            cout << "Final: " << a.final << "\n";
            cout << "Creado: " << a.fechaCreacion << "\n";
            cout << "Modificado: " << a.fechaModificacion << "\n";
            return;
        }
    }

    cout << "Alumno no encontrado.\n";
}

// ─────────────────────────────────────────────
//             Modificar alumno
// ─────────────────────────────────────────────
void modificarAlumno(vector<Alumno> &alumnos) {
    int mat;
    cout << "Matricula del alumno a modificar: ";
    cin >> mat;

    for (auto &a : alumnos) {
        if (a.matricula == mat) {

            cin.ignore();
            cout << "Nuevo nombre: ";
            getline(cin, a.nombre);

            for (int i = 0; i < 3; i++) {
                cout << "Nueva calificacion " << i + 1 << ": ";
                cin >> a.parciales[i];
            }

            a.final = (a.parciales[0] + a.parciales[1] + a.parciales[2]) / 3.0;
            a.fechaModificacion = obtenerFechaHora();

            guardarDatos(alumnos);
            cout << "Alumno modificado.\n";
            return;
        }
    }

    cout << "Alumno no encontrado.\n";
}

// ─────────────────────────────────────────────
//             Eliminar alumno
// ─────────────────────────────────────────────
void eliminarAlumno(vector<Alumno> &alumnos) {
    int mat;
    cout << "Matricula: ";
    cin >> mat;

    for (int i = 0; i < alumnos.size(); i++) {
        if (alumnos[i].matricula == mat) {
            alumnos.erase(alumnos.begin() + i);
            guardarDatos(alumnos);
            cout << "Alumno eliminado.\n";
            return;
        }
    }

    cout << "Alumno no encontrado.\n";
}

// ─────────────────────────────────────────────
//           Ordenar alumnos
// ─────────────────────────────────────────────
void ordenarAlumnos(vector<Alumno> &alumnos) {
    int op;
    cout << "\n--- ORDENAR ALUMNOS ---\n";
    cout << "1. Por matrícula\n";
    cout << "2. Por nombre\n";
    cout << "3. Por promedio\n";
    cout << "Opción: ";
    cin >> op;

    switch (op) {
    case 1:
        sort(alumnos.begin(), alumnos.end(),
             [](Alumno a, Alumno b) { return a.matricula < b.matricula; });
        break;

    case 2:
        sort(alumnos.begin(), alumnos.end(),
             [](Alumno a, Alumno b) { return a.nombre < b.nombre; });
        break;

    case 3:
        sort(alumnos.begin(), alumnos.end(),
             [](Alumno a, Alumno b) { return a.final > b.final; });
        break;

    default:
        cout << "Opción inválida.\n";
        return;
    }

    guardarDatos(alumnos);
    cout << "Ordenamiento realizado.\n";
}

// ─────────────────────────────────────────────
//           Exportar Top 3
// ─────────────────────────────────────────────
void exportarTop3(const vector<Alumno> &alumnos) {
    if (alumnos.empty()) {
        cout << "No hay alumnos.\n";
        return;
    }

    vector<Alumno> copia = alumnos;

    sort(copia.begin(), copia.end(),
         [](Alumno a, Alumno b) { return a.final > b.final; });

    ofstream out("top3.txt");
    out << "TOP 3 ALUMNOS\n\n";

    for (int i = 0; i < 3 && i < copia.size(); i++) {
        out << i+1 << ". " << copia[i].nombre
            << " | Matricula: " << copia[i].matricula
            << " | Final: " << copia[i].final << "\n";
    }

    out.close();
    cout << "Archivo top3.txt generado.\n";
}

// ─────────────────────────────────────────────
//                 Menu alumnos
// ──────────────────────────────────────────
void menuAlumnos(vector<Alumno> &alumnos) {
    int op;
    do {
        cout << "\n===== MENU ALUMNOS =====\n";
        cout << "1. Agregar alumno\n";
        cout << "2. Leer alumno\n";
        cout << "3. Modificar alumno\n";
        cout << "4. Eliminar alumno\n";
        cout << "5. Ordenar alumnos\n";
        cout << "0. Volver\n";
        cout << "Opción: ";
        cin >> op;

        switch(op) {
            case 1: agregarAlumno(alumnos); break;
            case 2: leerAlumno(alumnos); break;
            case 3: modificarAlumno(alumnos); break;
            case 4: eliminarAlumno(alumnos); break;
            case 5: ordenarAlumnos(alumnos); break;
        }

    } while (op != 0);
}

// ─────────────────────────────────────────────
//                 Menu reportes
// ───────────────────────────────────────────
void menuReportes(const vector<Alumno> &alumnos) {
    int op;
    do {
        cout << "\n===== MENU REPORTES =====\n";
        cout << "1. Buscar alumno\n";
        cout << "2. Exportar Top 3\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {
            case 1: leerAlumno(alumnos); break;
            case 2: exportarTop3(alumnos); break;
        }

    } while (op != 0);
}

// ────────────────────────────────────
//                    MAIN
// ──────────────────────────────────────────
int main() {
    vector<Alumno> alumnos;
    cargarDatos(alumnos);

    int op;
    do {
        cout << "\nSISTEMA ADMINISTRATIVO\n";
        cout << "1. Menu Alumnos\n";
        cout << "2. Menu Reportes\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        cin >> op;

        switch(op) {
            case 1: menuAlumnos(alumnos); break;
            case 2: menuReportes(alumnos); break;
        }

    } while (op != 0);

    return 0;
}
