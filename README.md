A Proyecto: Sistema de Gestión Académica "Nexus Academy"

Este es un sistema desarrollado en *C++* que interactúa con una base de datos *MySQL/MariaDB*. Permite gestionar alumnos, sus calificaciones y generar reportes de rendimiento académico directamente desde la consola.

B Requerimientos Técnicos
* Lenguaje: C++
* Base de Datos: MySQL Server 8.0
* Conector: MySQL Connector/C++ o mysql.h
* IDE sugerido: Visual Studio 

C Instalación y Configuración
1. Importar el archivo database.sql en MySQL Workbench para crear la base de datos y la tabla de alumnos.
2. Configurar las credenciales de conexión (Host, User, Password) en el archivo main.cpp.
3. Compilar el proyecto vinculando las librerías de MySQL (libmysql.lib).

D Funcionalidades
- Buscador: Consulta individual por ID de alumno.
- Cuadro de Honor: Ranking de los 5 mejores promedios.
- Alumnos en Riesgo: Filtro automático de alumnos con nota menor a 4.
- Actualización: Modificación de notas y teléfonos en tiempo real.
E
Desarrollado por: Bismarth Yair Flores Paco - Rudy Angel Luque Quispe
Carrera: Ingeniería Mecatrónica - UCB
