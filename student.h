#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

const int MAX_COURSES = 10; // Máximo de cursos por estudiante
const int MAX_APPROVED_COURSES = 2; // Máximo de cursos aprobados

class Student {
public:
    std::string name;
    std::string id;
    std::string career;
    int level;
    std::string courses[MAX_COURSES];
    std::string days[MAX_COURSES];
    std::string startTimes[MAX_COURSES];
    std::string endTimes[MAX_COURSES];
    std::string rooms[MAX_COURSES];
    std::string approvedCourses[MAX_APPROVED_COURSES]; // Cursos aprobados
    int numCourses = 0;

    Student(std::string name, std::string id, std::string career, int level);
};

#endif