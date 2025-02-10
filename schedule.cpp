#include"schedule.h"

// Constructor de la clase Schedule
Schedule::Schedule(std::string d, std::string st, std::string et, std::string r, std::string p)
    : day(d), startTime(st), endTime(et), room(r), professor(p) {}

// Método para verificar conflictos
bool Schedule::conflictsWith(const Schedule& other) const {
    return (day == other.day && startTime < other.endTime && endTime > other.startTime);
}
