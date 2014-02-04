#include "course.h"

Course::Course() {
    //for error checking
    this->rank = -1;
}

Course::Course(std::vector< std::pair<int, int> > time_array)
{
    times = time_array;
    rank = 0;
}

Course::Course(std::vector< std::pair<int, int> > time_array, int rank) {
    times = time_array;
    this->rank = rank;
}

Course::Course(std::vector< std::pair<int, int> > time_array, int rank, QString name) {
    times = time_array;
    this->rank = rank;
    this->name = name;
}

void Course::setRank(int rank) {
    this->rank = rank;
}

void Course::setTimes(std::vector< std::pair<int, int> > times) {
    this->times = times;
}

void Course::setName(QString name) {
    this->name = name;
}

void Course::setId(int id) {
    this->id = id;
}
