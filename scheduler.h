#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <map>

class Course;

class Scheduler
{
public:
    // CONSTRUCTOR
    Scheduler(std::vector<Course>);

    // INSTANCE VARIABLES
    std::vector<Course> courseList;
    std::map< std::pair<int, int>, int> timesHash;

    // INSTANCE METHODS
    std::vector<Course> makeSchedule();
    bool canAddToSchedule(Course);

    // int findCourse(Course course)
    // void removeCourse(int index)
};

#endif // SCHEDULER_H
