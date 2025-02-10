#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include "schedule.h" 
#include <string>
// Asegúrate de que este archivo esté correctamente incluido

const int MAX_GROUPS = 2; // Máximo de grupos por curso
const int MAX_SCHEDULES_PER_GROUP = 1; // Máximo de horarios por grupo

class Course {
public:
    std::string name;
    std::string code;
    int credits;
    std::string professor; // Asegúrate de que este campo esté definido
    std::string groupCodes[MAX_GROUPS]; // Códigos de grupo
    std::string prerequisiteCourses[MAX_GROUPS]; // Cursos de requisito
    int availableSlots[MAX_GROUPS]; // Cupos disponibles para cada grupo
    Schedule schedules[MAX_GROUPS][MAX_SCHEDULES_PER_GROUP]; // Horarios para cada grupo
    std::string career;

    Course(std::string name, std::string code, int credits, std::string professor, std::string group1, std::string group2, std::string prereq1, std::string prereq2, std::string career);
};

#endif
