#include "sistema_matricula.h"

Student::Student(std::string name, std::string id, std::string career, int level)
    : name(name), id(id), career(career), level(level), numCourses(0) {}

Course::Course(std::string name, std::string code, int credits, std::string professor, std::string group1, std::string group2, std::string prereq1, std::string prereq2, std::string career)
    : name(name), code(code), credits(credits), professor(professor), career(career) {
    groupCodes[0] = group1;
    groupCodes[1] = group2;
    prerequisiteCourses[0] = prereq1;
    prerequisiteCourses[1] = prereq2;

    // Inicializar los cupos disponibles
    availableSlots[0] = 30; // 30 cupos para el grupo 1
    availableSlots[1] = 30; // 30 cupos para el grupo 2

    for (int i = 0; i < MAX_GROUPS; i++) {
        for (int j = 0; j < MAX_SCHEDULES_PER_GROUP; j++) {
            schedules[i][j] = Schedule("", "", "", "", ""); // Inicializar con valores vacíos
        }
    }
}

RegistrationSystem::RegistrationSystem() : headStudent(nullptr) {
    // Inicialización de cursos y horarios
}

RegistrationSystem::~RegistrationSystem() {
    // Liberar memoria de la lista de estudiantes
    StudentNode* current = headStudent;
    while (current != nullptr) {
        StudentNode* toDelete = current;
        current = current->next;
        delete toDelete->student; // Liberar el estudiante
        delete toDelete; // Liberar el nodo
    }
    for (int i = 0; i < numStudents; ++i) {
        delete students[i];
    }
    for (int i = 0; i < numCourses; ++i) {
        delete courses[i];
    }
    for (int i = 0; i < numSchedules; ++i) {
        delete schedules[i];
    }

}
void RegistrationSystem::about() {
    std::cout << "Sistema de registro\n";
    std::cout << "Creado por Est. Alen Cedeno\n";
}

void RegistrationSystem::maintenance() {
    char subOption;
    std::cout << "\nSeleccione una opcion: a: Para agregar estudiantes | b: Para agregar curso | c: Para agregar horario: ";
    std::cin >> subOption;
    std::cin.ignore();

    if (subOption == 'a') {
        std::string name, id, career;
        int level;

        std::cout << "Ingrese el nombre del estudiante: ";
        std::getline(std::cin, name);
        std::cout << "Ingrese la cedula del estudiante completa: ";
        std::getline(std::cin, id);

        bool validID = false;
        while (!validID) {
            validID = true;
            if (id.length() < 1 || id.length() > 9) {
                std::cout << "La cedula debe estar completa. Intente nuevamente: ";
                std::getline(std::cin, id);
                validID = false;
            }
            else {
                for (size_t i = 0; i < id.length(); ++i) {
                    if (id[i] < '0' || id[i] > '9') {
                        validID = false;
                        std::cout << "La cedula debe contener solo digitos. Intente nuevamente: ";
                        std::getline(std::cin, id);
                        break;
                    }
                }
            }
        }

        std::cout << "Ingrese la carrera del estudiante: ";
        std::getline(std::cin, career);
        std::cout << "Ingrese el nivel del estudiante en numeros: ";
        while (true) {
            std::cin >> level;
            if (std::cin.fail() || level < 1 || level > 10) {
                std::cout << "Por favor ingrese un nivel valido entre 1 y 10: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else {
                break;
            }
        }
        std::cin.ignore();

        addStudent(name, id, career, level);
    }
    else if (subOption == 'b') {
        std::string name, code, professor, career;
        int credits;
        std::cout << "Ingrese el nombre del curso: ";
        std::getline(std::cin, name);
        std::cout << "Ingrese el nombre del curso: ";
        std::getline(std::cin, career);
        std::cout << "Ingrese el codigo del curso: ";
        std::getline(std::cin, code);
        std::cout << "Ingrese los creditos del curso: ";

        while (true) {
            std::cin >> credits;
            if (std::cin.fail() || credits <= 0) {
                std::cout << "Por favor ingrese un numero de creditos valido: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else {
                break;
            }
        }
        std::cin.ignore();
        std::cout << "Ingrese el nombre del profesor: ";
        std::getline(std::cin, professor);

        std::string group1, group2, prereq1, prereq2;
        std::cout << "Ingrese el codigo del grupo 1: ";
        std::getline(std::cin, group1);
        std::cout << "Ingrese el codigo del grupo 2: ";
        std::getline(std::cin, group2);
        std::cout << "Ingrese el codigo del curso de requisito 1: ";
        std::getline(std::cin, prereq1);
        std::cout << "Ingrese el codigo del curso de requisito 2: ";
        std::getline(std::cin, prereq2);

        addCourse(name, code, credits, professor, group1, group2, prereq1, prereq2, career);
    }
    else if (subOption == 'c') {
        std::string day, startTime, endTime, room;
        std::cout << "Ingrese el dia del horario: ";
        std::getline(std::cin, day);
        std::cout << "Ingrese la hora de inicio: ";
        std::getline(std::cin, startTime);
        std::cout << "Ingrese la hora de finalizacion: ";
        std::getline(std::cin, endTime);
        std::cout << "Ingrese el aula: ";
        std::getline(std::cin, room);
        addSchedule(day, startTime, endTime, room);
    }
}

void RegistrationSystem::addStudent(std::string name, std::string id, std::string career, int level) {
    if (numStudents < MAX_STUDENTS) {
        students[numStudents] = new Student(name, id, career, level);
        // Solicitar cursos aprobados
        for (int i = 0; i < MAX_APPROVED_COURSES; i++) {
            std::cout << "Ingrese el codigo del curso aprobado " << (i + 1) << ": ";
            std::getline(std::cin, students[numStudents]->approvedCourses[i]);
        }

        StudentNode* newNode = new StudentNode(students[numStudents]);
        if (headStudent == nullptr) {
            headStudent = newNode; // Si la lista está vacía, el nuevo nodo es la cabeza
        }
        else {
            StudentNode* current = headStudent;
            while (current->next != nullptr) {
                current = current->next; // Ir al final de la lista
            }
            current->next = newNode; // Agregar el nuevo nodo al final
        }

        numStudents++;
        std::cout << "Estudiante agregado con éxito.\n";
    }
    else {
        std::cout << "Se alcanzó el número máximo de estudiantes.\n";
    }
}


void RegistrationSystem::addCourse(std::string name, std::string code, int credits, std::string professor, std::string group1, std::string group2, std::string prereq1, std::string prereq2, std::string career) {
    if (numCourses < MAX_COURSES) {
        courses[numCourses] = new Course(name, code, credits, professor, group1, group2, prereq1, prereq2, career);

        // Solicitar horarios para cada grupo
        for (int i = 0; i < MAX_GROUPS; i++) {
            std::string day, startTime, endTime, room;
            std::cout << "Ingrese el horario para el grupo " << courses[numCourses]->groupCodes[i] << " (Día, Hora de inicio, Hora de fin, Aula): ";
            std::cin >> day >> startTime >> endTime >> room;
            courses[numCourses]->schedules[i][0] = Schedule(day, startTime, endTime, room, professor);
        }

        numCourses++;
        std::cout << "Curso agregado con exito.\n";
    }
    else {
        std::cout << "Se alcanzo el numero maximo de cursos.\n";
    }
}

bool RegistrationSystem::isRegistered(const std::string& id) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->id == id) {
            return true;
        }
    }
    return false;
}

void RegistrationSystem::addSchedule(std::string day, std::string startTime, std::string endTime, std::string room) {
    if (numSchedules < MAX_SCHEDULES) {
        schedules[numSchedules] = new Schedule(day, startTime, endTime, room, ""); // Puedes pasar el profesor si es necesario
        numSchedules++;
    }
    else {
        std::cout << "Se alcanzo el numero maximo de horarios.\n";
    }
}

bool RegistrationSystem::hasApprovedCourses(const std::string& id, const std::string& prereq1, const std::string& prereq2) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->id == id) {
            bool hasPrereq1 = false;
            bool hasPrereq2 = false;

            for (int j = 0; j < MAX_APPROVED_COURSES; j++) {
                if (students[i]->approvedCourses[j] == prereq1) {
                    hasPrereq1 = true;
                }
                if (students[i]->approvedCourses[j] == prereq2) {
                    hasPrereq2 = true;
                }
            }
            return hasPrereq1 && hasPrereq2; // Retorna verdadero solo si ambos requisitos están cumplidos
        }
    }
    return false; // Si el estudiante no fue encontrado
}

void RegistrationSystem::registerEnrollment() {
    std::string id;
    std::cout << "Ingrese la cedula del estudiante: ";
    std::cin >> id;
    std::cin.ignore();

    if (isRegistered(id)) {
        std::cout << "Estudiante encontrado.\n";
        showAvailableCourses();

        std::string courseCode;
        std::cout << "Ingrese el codigo del curso al que desea inscribirse: ";
        std::cin >> courseCode;

        bool courseFound = false;
        for (int i = 0; i < numCourses; i++) {
            if (courses[i]->code == courseCode) {
                courseFound = true;
                std::cout << "Curso encontrado: " << courses[i]->name << "\n";

                for (int j = 0; j < MAX_APPROVED_COURSES; j++) {
                    if (students[i]->approvedCourses[j] == courseCode) {



                        std::cout << "Error: Este curso ya fue aprobado por el estudiante.\n";
                        return; // Regresar al menú
                    }
                }
                // Validar requisitos
                if (!hasApprovedCourses(id, courses[i]->prerequisiteCourses[0], courses[i]->prerequisiteCourses[1])) {
                    std::cout << "No cumple con los requisitos para inscribirse en este curso.\n";
                    return; // Regresar al menú
                }
                for (int j = 0; j < numStudents; j++) {
                    if (students[j]->id == id) {
                        if (students[j]->career != courses[i]->career) {
                            std::cout << "Error: Este curso no es de tu carrera.\n";
                            return; // Regresar al menú
                        }
                        break;
                    }
                }

                std::string selectedGroup;
                std::cout << "Seleccione el grupo al que desea inscribirse: ";
                std::cin >> selectedGroup;

                // Verificar si el grupo seleccionado tiene cupos disponibles
                int groupIndex = -1;
                for (int j = 0; j < MAX_GROUPS; j++) {
                    if (courses[i]->groupCodes[j] == selectedGroup) {
                        groupIndex = j;
                        break;
                    }
                }

                if (groupIndex != -1 && courses[i]->availableSlots[groupIndex] > 0) {
                    // Inscribir al estudiante en el grupo
                    for (int j = 0; j < numStudents; j++) {
                        if (students[j]->id == id) {
                            students[j]->courses[students[j]->numCourses] = courses[i]->name;
                            students[j]->days[students[j]->numCourses] = courses[i]->schedules[groupIndex][0].day;
                            students[j]->startTimes[students[j]->numCourses] = courses[i]->schedules[groupIndex][0].startTime;
                            students[j]->endTimes[students[j]->numCourses] = courses[i]->schedules[groupIndex][0].endTime;
                            students[j]->rooms[students[j]->numCourses] = courses[i]->schedules[groupIndex][0].room;
                            students[j]->numCourses++;
                            courses[i]->availableSlots[groupIndex]--; // Disminuir el cupo disponible
                            std::cout << "Inscripcion exitosa en el curso: " << courses[i]->name << " en el grupo " << selectedGroup << "\n";
                            break;
                        }
                    }
                }
                else {
                    std::cout << "El grupo seleccionado no tiene cupos disponibles.\n";
                }
                break;
            }
        }
        if (!courseFound) {
            std::cout << "Curso no encontrado.\n";
        }
    }
    else {
        std::cout << "Estudiante no registrado.\n";
    }
}

void RegistrationSystem::viewStudents() {
    std::cout << "Lista de estudiantes:\n";
    std::cout << "Nombre\t\t\tCedula\t\t\tCarrera\t\t\tNivel\t\tCursos\t\t\n";

    // Usar la lista enlazada para mostrar estudiantes
    StudentNode* current = headStudent;
    while (current != nullptr) {
        std::cout << current->student->name << "\t\t" << current->student->id << "\t\t"
            << current->student->career << "\t\t" << current->student->level << "\t";
        for (int j = 0; j < current->student->numCourses; j++) {
            std::cout << current->student->courses[j] << " ";
        }
        std::cout << "\n";
        current = current->next; // Ir al siguiente nodo
    }
}

void RegistrationSystem::showStudentSchedules(const std::string& id) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->id == id) {
            std::cout << "Horarios de " << students[i]->name << " (Carrera: " << students[i]->career
                << ", Nivel: " << students[i]->level << "):\n";
            int totalCredits = 0;

            for (int j = 0; j < students[i]->numCourses; j++) {
                std::cout << "Curso: " << students[i]->courses[j] << ", "
                    << "Dia: " << students[i]->days[j] << ", "
                    << "Hora: " << students[i]->startTimes[j] << "-" << students[i]->endTimes[j] << ", "
                    << "Aula: " << students[i]->rooms[j] << "\n";

                for (int k = 0; k < numCourses; k++) {
                    if (students[i]->courses[j] == courses[k]->name) {
                        totalCredits += courses[k]->credits;
                        break;
                    }
                }
            }

            int amountToPay = totalCredits * CREDIT_PRICE;
            std::cout << "Monto a pagar: " << amountToPay << " colones\n";
            break;
        }
    }
}

void RegistrationSystem::showAvailableCourses() {
    std::cout << "Cursos disponibles:\n";
    for (int i = 0; i < numCourses; i++) {
        std::cout << "Nombre: " << courses[i]->name << ", Codigo: " << courses[i]->code
            << ", Creditos: " << courses[i]->credits << ", Profesor: " << courses[i]->professor << "\n";
        std::cout << "Códigos NCR: " << courses[i]->groupCodes[0] << ", " << courses[i]->groupCodes[1] << "\n";
        std::cout << "Códigos de requisito: " << courses[i]->prerequisiteCourses[0] << ", " << courses[i]->prerequisiteCourses[1] << "\n";
    }
}

void RegistrationSystem::showAvailableSchedules() {
    std::cout << "Horarios disponibles:\n";
    for (int i = 0; i < numSchedules; i++) {
        std::cout << "Dia: " << schedules[i]->day << ", Hora: " << schedules[i]->startTime << " - " << schedules[i]->endTime << ", Aula: " << schedules[i]->room << "\n";
    }
}

bool RegistrationSystem::checkScheduleConflict(const Schedule& newSchedule, const std::string& courseName) {
    for (int i = 0; i < numStudents; i++) {
        for (int j = 0; j < students[i]->numCourses; j++) {
            if (students[i]->courses[j] != courseName &&
                students[i]->days[j] == newSchedule.day &&
                students[i]->startTimes[j] == newSchedule.startTime &&
                students[i]->endTimes[j] == newSchedule.endTime &&
                students[i]->rooms[j] == newSchedule.room) {
                return true;
            }
        }
    }
    return false;
}

