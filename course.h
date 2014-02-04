#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <QString>

class Course
{
public:
    // INSTANCE VARIABLES
    std::vector< std::pair<int, int> > times;
    int rank;
    int id;
    QString name;

    // CONSTRUCTORS
    Course();
    Course(std::vector< std::pair<int, int> >);
    Course(std::vector< std::pair<int, int> >, int);
    Course(std::vector< std::pair<int, int> >, int, QString);

    // INSTANCE VARIABLES
    void setRank(int);
    void setTimes(std::vector< std::pair<int, int> >);
    void setName(QString);
    void setId(int);
};

#endif // COURSE_H
