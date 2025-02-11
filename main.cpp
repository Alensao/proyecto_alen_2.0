#include <iostream>
#include "sistema_matricula.h"

void showMainMenu() {
    std::cout << "\n---Menu ---\n";
    std::cout << "=============================================================\n";
    std::cout << "1. Archivo\n";
    std::cout << "=============================================================\n";
    std::cout << "2. Mantenimiento (estudiantes, cursos, horarios)\n";
    std::cout << "=============================================================\n";
    std::cout << "3. Registrar Matricula\n";
    std::cout << "=============================================================\n";
    std::cout << "4. Consultar\n";
    std::cout << "=============================================================\n";
    std::cout << "5. Ver Datos de Matrícula Cargados\n"; // Nueva opción
    std::cout << "Seleccione una opcion: \n";
    std::cout << "=============================================================\n";
}

void showFileMenu() {
    char subOption;
    std::cout << "\n--- Menu ---\n";
    std::cout << "=============================================================\n";
    std::cout << "a. Acerca de \n";
    std::cout << "b. Salir del sistema\n";
    std::cout << "Seleccionar opcion: \n";
    std::cin >> subOption;
    std::cin.ignore();

    std::cout << "=============================================================\n";
    if (subOption == 'a') {
        std::cout << "=============================================================\n";
        std::cout << "\t--- BIENVENIDOS(A) ---\t\n";
        std::cout << "--- Sistema de registro universitario ---\n";
        std::cout << "--- Creado por Est. Alen Cedeno ---\n";
        std::cout << "=============================================================\n";
    }
    else if (subOption == 'b') {
        std::cout << "Saliendo del sistema...\n";
        exit(0);
    }
    else {
        std::cout << "Opcion invalida. Volviendo al menu.\n";
    }
}

void showViewMenu(RegistrationSystem& system) {
    char subOption;
    std::cout << "=============================================================\n";
    std::cout << "\n--- Menu ---\n";
    std::cout << "a. Ver informacion de estudiantes\n";
    std::cout << "b. Ver cursos disponibles\n";
    std::cout << "c. Ver horarios de estudiante y total a cancelar\n";
    std::cout << "Seleccione una opcion:\n";
    std::cin >> subOption;
    std::cin.ignore();
    std::cout << "=============================================================\n";

    if (subOption == 'a') {
        system.viewStudents();
    }
    else if (subOption == 'b') {
        system.showAvailableCourses();
    }
    else if (subOption == 'c') {
        std::string id;
        std::cout << "Ingrese ID de estudiante: ";
        std::cin >> id;
        system.showStudentSchedules(id);
    }
    else {
        std::cout << "Opcion no valida.\n";
    }
}

int main() {
    RegistrationSystem system;
    char menuOption;

    do {
        showMainMenu();
        std::cin >> menuOption;
        std::cin.ignore();

        switch (menuOption) {
        case '1':
            showFileMenu();
            break;
        case '2':
            system.maintenance();
            break;
        case '3': {
            std::string id;
            std::cout << "Ingrese ID de estudiante: ";
            std::cin >> id;
            std::cin.ignore();

            if (system.isRegistered(id)) {
                char wishToEnroll;
                std::cout << "Estudiante encontrado. Desea matricularlo? Digite 's' para si o 'n' para no: ";
                std::cin >> wishToEnroll;
                std::cin.ignore();

                if (wishToEnroll == 's') {
                    system.registerEnrollment();
                }
                else {
                    std::cout << "No se realizo matricula.\n";
                }
            }
            else {
                std::cout << "Estudiante no registrado.\n";
            }
            break;
        }
        case '4':
            showViewMenu(system);
            break;
        case '5': // Nueva opción para ver datos de matrícula
            std::cout << "Cargando registros de matrícula...\n"; // Mensaje informativo
            system.loadEnrollmentData(); // Cargar y mostrar datos
            break;
        default:
            std::cout << "Opcion invalida. Intentelo nuevamente.\n";
            break;
        }
    } while (true);

    return 0;
}