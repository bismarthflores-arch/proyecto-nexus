#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <iomanip>

using namespace std;


struct Alumno {
    int id;
    string nombre;
    string apellido;
    string celular;
    double nota_final;
};


vector<Alumno> db_alumnos;


void cargarDatosIniciales() {
    db_alumnos = {
        {101, "Marcos", "Luna", "70123456", 9.5}, {102, "Ana", "Ramos", "70234567", 3.5},
        {103, "Luis", "Torres", "70345678", 8.0}, {104, "Carla", "Vaca", "70456789", 2.8},
        {105, "Hugo", "Daza", "70567890", 10.0}, {106, "Elena", "Sosa", "70678901", 4.5},
        {107, "Ivan", "Paz", "70789012", 3.9}, {108, "Sara", "Mendez", "70890123", 7.2},
        {109, "Raul", "Ortiz", "70901234", 5.5}, {110, "Nora", "Copa", "71012345", 2.0},
        {111, "Saul", "Rojas", "71123456", 8.8}, {112, "Luz", "Blanco", "71234567", 6.4},
        {113, "Omar", "Vera", "71345678", 9.1}, {114, "Iris", "Flores", "71456789", 3.0},
        {115, "Joel", "Rios", "71567890", 7.7}
    };
}

void buscarAlumno() {
    int ci;
    cout << "\nIngrese CI o ID del alumno: "; cin >> ci;
    bool encontrado = false;

    for (const auto& a : db_alumnos) {
        if (a.id == ci) {
            cout << "\n--- FICHA DEL ALUMNO (SELECT * FROM alumnos) ---\n";
            cout << "Nombre: " << a.nombre << " " << a.apellido << endl;
            cout << "Celular: " << a.celular << endl;
            cout << "Promedio: " << fixed << setprecision(2) << a.nota_final << endl;
            encontrado = true;
            break;
        }
    }
    if (!encontrado) cout << "Alumno no registrado.\n";
}

void rankingHonor() {
    
    vector<Alumno> copia = db_alumnos;
    sort(copia.begin(), copia.end(), [](Alumno a, Alumno b) {
        return a.nota_final > b.nota_final;
    });

    cout << "\n--- CUADRO DE HONOR (TOP 5) ---\n";
    for (int i = 0; i < 5 && i < copia.size(); i++) {
        cout << i + 1 << ". " << copia[i].nombre << " - Nota: " << copia[i].nota_final << endl;
    }
}

void alumnosEnRiesgo() {
    cout << "\n--- ALUMNOS EN RIESGO (nota < 4) ---\n";
    for (const auto& a : db_alumnos) {
        if (a.nota_final < 4) {
            cout << "- " << a.nombre << " " << a.apellido << " | Nota: " << a.nota_final << endl;
        }
    }
}

void actualizarDatos() {
    int ci, op;
    cout << "\nID del alumno a modificar: "; cin >> ci;
    for (auto& a : db_alumnos) {
        if (a.id == ci) {
            cout << "1. Modificar Nota\n2. Cambiar Celular\nOpcion: "; cin >> op;
            if (op == 1) {
                cout << "Nueva nota: "; cin >> a.nota_final;
            } else {
                cout << "Nuevo celular: "; cin >> a.celular;
            }
            cout << "Datos actualizados exitosamente (Simulated UPDATE).\n";
            return;
        }
    }
    cout << "ID no encontrado.\n";
}

int main() {
    cargarDatosIniciales();
    int opcion;

    do {
        cout << "\n======= NEXUS ACADEMY (ONLINE SIMULATOR) =======";
        cout << "\n1. Consultar Alumno (Buscador)";
        cout << "\n2. Cuadro de Honor (Top 5)";
        cout << "\n3. Alumnos en Riesgo";
        cout << "\n4. Actualizar Datos";
        cout << "\n5. Salir";
        cout << "\nSeleccione una opcion: "; cin >> opcion;

        switch (opcion) {
            case 1: buscarAlumno(); break;
            case 2: rankingHonor(); break;
            case 3: alumnosEnRiesgo(); break;
            case 4: actualizarDatos(); break;
        }
    } while (opcion != 5);

    return 0;
}
