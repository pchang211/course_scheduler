#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

class Course;
//class QFormLayout;
class QVBoxLayout;
class CourseWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QWidget *enterCoursesWidget;
    QVBoxLayout *enterCoursesLayout;

    int numCourses;
    std::vector<Course> courseList;
    std::vector<CourseWidget*> courseWidgets;
    ~MainWindow();


private slots:
    void addCourseField();
    void addCourseField(QString values);
    void removeCourseField();
    void getSchedule();

private:

};

#endif // MAINWINDOW_H
