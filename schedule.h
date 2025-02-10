#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>

class Schedule {
public:
    std::string day; // Día de la semana
    std::string startTime; // Hora de inicio
    std::string endTime; // Hora de fin
    std::string room; // Aula asignada
    std::string professor; // Nombre del profesor

    Schedule() : day(""), startTime(""), endTime(""), room(""), professor("") {}
    Schedule(std::string d, std::string st, std::string et, std::string r, std::string p);
    bool conflictsWith(const Schedule& other) const; // Método para verificar conflictos
};

#endif
