#include "scheduler.h"
#include <vector>
#include "course.h"
#include <stdlib.h>
#include <algorithm>
#include <QDebug>
#include <map>

Scheduler::Scheduler(std::vector<Course> courseList)
{
    this->courseList = courseList;
}

std::vector<Course> Scheduler::makeSchedule() {

    // All you have to do is sort by rankings, then find the first four unique times
    int maxClasses = 4;
    int addedCourses = 0;
    std::vector<Course> result;
    timesHash.clear(); //reset everytime we want to make a new schedule

    /*
     * Custom comparator for courses based on rank
     */
    struct {
        bool operator()(Course a, Course b) {
            return a.rank > b.rank;
        }
    } compareCourse;

    // SORT BY RANK
    std::sort(courseList.begin(), courseList.end(), compareCourse);

    //THIS IS WHERE THE ACTUAL SCHEDULING IS
    for (int i=0; i<(int)courseList.size(); i++) {
        Course currentCourse = courseList[i];
        if (addedCourses<maxClasses && canAddToSchedule(currentCourse)) {
            result.push_back(currentCourse);
            for (int j=0; j<(int)currentCourse.times.size(); j++) {
                timesHash[currentCourse.times[j]] = 1;
            }
            addedCourses++;
        }
    }

    return result;

}

bool Scheduler::canAddToSchedule(Course course) {
    std::vector< std::pair<int, int> > times = course.times;
    for (int i=0; i<(int)times.size(); i++) {
        if (times[i].second!=0 && timesHash.count(times[i]) > 0) {
            qDebug() << "failure with " << times[i].first << ", " << times[i].second;
            return false;
        }
    }
    return true;
}
