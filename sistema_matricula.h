#ifndef SISTEMA_MATRICULA_H
#define SISTEMA_MATRICULA_H

#include <iostream>
#include <string>

#include <fstream>

#include "student.h"
#include "course.h"
#include "schedule.h"
#include "student_node.h"

const int MAX_STUDENTS = 100;

const int MAX_SCHEDULES = 10;
const int CREDIT_PRICE = 12000;

class RegistrationSystem {
private:
    StudentNode* headStudent; // Cabeza de la lista enlazada de estudiantes
    Student* students[MAX_STUDENTS];
    Course* courses[MAX_COURSES];
    Schedule* schedules[MAX_SCHEDULES];

    int numStudents = 0;
    int numCourses = 0;
    int numSchedules = 0;

public:
    RegistrationSystem();
    ~RegistrationSystem();

    void about();
    void maintenance();
    void registerEnrollment();
    void viewStudents();
    void showStudentSchedules(const std::string& id);
    void showAvailableSchedules();
    void addStudent(std::string name, std::string id, std::string career, int level);
    void addCourse(std::string name, std::string code, int credits, std::string professor, std::string group1, std::string group2, std::string prereq1, std::string prereq2, std::string career);
    void addSchedule(std::string day, std::string startTime, std::string endTime, std::string room);
    bool isRegistered(const std::string& id);
    void showAvailableCourses();
    bool checkScheduleConflict(const Schedule& newSchedule, const std::string& courseName);
    bool hasApprovedCourses(const std::string& id, const std::string& prereq1, const std::string& prereq2);
    void saveEnrollmentData(const std::string& id, const std::string& courseName, const std::string& group);
    void loadEnrollmentData();
};

#endif
