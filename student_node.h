// student_node.h
#ifndef STUDENT_NODE_H
#define STUDENT_NODE_H

#include "student.h"

struct StudentNode {
    Student* student;
    StudentNode* next;

    StudentNode(Student* s) : student(s), next(nullptr) {}
};

#endif