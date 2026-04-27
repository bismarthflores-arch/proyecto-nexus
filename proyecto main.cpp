#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>

using namespace std;

struct Alumno {
    int id;
    string nombre;
    string apellido;
    string celular;
    double nota_final;
};

void limpiarConsola() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

MYSQL* conectarDB() {
    MYSQL* conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "tu_password", "nexus_academy", 3306, NULL, 0)) {
        cout << "Error critico de conexion: " << mysql_error(conn) << endl;
        return NULL;
    }
    return conn;
}

void buscarAlumno(MYSQL* conn) {
    int id;
    cout << "Ingrese CI o ID del alumno: "; cin >> id;
    string query = "SELECT id, nombre, apellido, celular, nota_final FROM alumnos WHERE id = " + to_string(id);

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            cout << "\n===============================" << endl;
            cout << "   FICHA ACADEMICA - NEXUS" << endl;
            cout << "===============================" << endl;
            cout << "Nombre: " << row[1] << " " << row[2] << endl;
            cout << "Celular: " << row[3] << endl;
            cout << "Promedio Actual: " << row[4] << endl;
            cout << "===============================" << endl;
        } else {
            cout << "No se encontro registro con ese ID." << endl;
        }
        mysql_free_result(res);
    }
}

void mostrarRankings(MYSQL* conn, bool honor) {
    string query = honor ? 
        "SELECT nombre, apellido, nota_final FROM alumnos ORDER BY nota_final DESC LIMIT 5" : 
        "SELECT nombre, apellido, nota_final FROM alumnos WHERE nota_final < 4";

    if (mysql_query(conn, query.c_str()) == 0) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row;
        cout << (honor ? "\n--- CUADRO DE HONOR ---" : "\n--- ALUMNOS EN RIESGO ---") << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << "- " << row[0] << " " << row[1] << " | Nota: " << row[2] << endl;
        }
        mysql_free_result(res);
    }
}

void actualizarAlumno(MYSQL* conn) {
    int id, op;
    cout << "ID del alumno a modificar: "; cin >> id;
    cout << "1. Actualizar Nota\n2. Actualizar Celular\nElija: "; cin >> op;

    string query;
    if (op == 1) {
        double nota;
        cout << "Nueva nota final: "; cin >> nota;
        query = "UPDATE alumnos SET nota_final = " + to_string(nota) + " WHERE id = " + to_string(id);
    } else {
        string cel;
        cout << "Nuevo numero de celular: "; cin >> cel;
        query = "UPDATE alumnos SET celular = '" + cel + "' WHERE id = " + to_string(id);
    }

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Base de datos actualizada con exito." << endl;
    } else {
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

int main() {
    MYSQL* conn = conectarDB();
    if (!conn) return 1;

    int opcion;
    do {
        cout << "\n>>> NEXUS ACADEMY v1.0 <<<" << endl;
        cout << "1. Buscar por ID (Ficha)" << endl;
        cout << "2. Ver Cuadro de Honor (Top 5)" << endl;
        cout << "3. Ver Alumnos en Riesgo (< 4)" << endl;
        cout << "4. Modificar Datos (Nota/Celular)" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: "; cin >> opcion;

        switch (opcion) {
            case 1: buscarAlumno(conn); break;
            case 2: mostrarRankings(conn, true); break;
            case 3: mostrarRankings(conn, false); break;
            case 4: actualizarAlumno(conn); break;
        }
    } while (opcion != 5);

    mysql_close(conn);
    return 0;
}
