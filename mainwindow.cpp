#include "mainwindow.h"

#include <QVBoxLayout>
#include <QFormLayout>

#include <QList>

#include <stdlib.h>
#include <set>
#include <vector>
#include <QDebug>

#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QStringBuilder>
#include <QMessageBox>

#include "course.h"
#include "scheduler.h"
#include "coursewidget.h"
#include <crnwidget.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)/*, courseList(10)*/
{

    /*
     * Main Widget
     */
    QWidget *main = new QWidget();
    main->setMinimumSize(600, 0);
    setCentralWidget(main);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    main->setLayout(mainLayout);

    /*
     * Add Course Button
     */
    QPushButton* addCourseButton = new QPushButton(this);
    addCourseButton->setText("Add a course");
    mainLayout->addWidget(addCourseButton, 0, Qt::AlignLeft);

    /*
     * Remove Course Button
     */
    QPushButton* removeCourseButton = new QPushButton(this);
    removeCourseButton->setText("Remove course");
    mainLayout->addWidget(removeCourseButton, 0, Qt::AlignLeft);
    connect(removeCourseButton, SIGNAL(pressed()), this, SLOT(removeCourseField()));

    /*
     * Enter Courses Widget
     */
    numCourses = 0;

    //enterCoursesWidget is a widget with a bunch of courseWidgets in a vboxlayout

    /*QWidget* */enterCoursesWidget = new QWidget();
    enterCoursesLayout = new QVBoxLayout();
    enterCoursesWidget->setLayout(enterCoursesLayout);

//    MainWindow::addCourseField();
    connect(addCourseButton, SIGNAL(pressed()), this, SLOT(addCourseField()));

    mainLayout->addWidget(enterCoursesWidget);

    /*
     * Schedule Widget
     */

    QWidget *scheduleWidget = new QWidget();
    QVBoxLayout *scheduleLayout = new QVBoxLayout();
    scheduleWidget->setLayout(scheduleLayout);
    QPushButton* getScheduleButton = new QPushButton(this);
    getScheduleButton->setText("Generate Schedule");
    scheduleLayout->addWidget(getScheduleButton);
    connect(getScheduleButton, SIGNAL(pressed()), this, SLOT(getSchedule()));

    mainLayout->addWidget(scheduleWidget);

    /*
     * CRN Widget
     */
    CrnWidget *crnwidget = new CrnWidget();
    connect(crnwidget, SIGNAL(loadCrn(QString)), this, SLOT(addCourseField(QString)));
    mainLayout->addWidget(crnwidget);

}

void MainWindow::addCourseField(QString values) {
    qDebug() << "with input" << values;
    if (values.isEmpty()) return;
    CourseWidget* newCourseWidget = new CourseWidget(numCourses, values);
    courseWidgets.push_back(newCourseWidget);
    enterCoursesLayout->addWidget(newCourseWidget);

    numCourses++;
}

void MainWindow::addCourseField() {
    qDebug() << "without input";
    CourseWidget* newCourseWidget = new CourseWidget(numCourses);
    courseWidgets.push_back(newCourseWidget);
    enterCoursesLayout->addWidget(newCourseWidget);

    numCourses++;
}

void MainWindow::removeCourseField() {
    if (!courseWidgets.empty()) {
        CourseWidget* course = courseWidgets.back();
        courseWidgets.pop_back();
        enterCoursesLayout->removeWidget(course);
        numCourses--;
        delete course;
    }
}

void MainWindow::getSchedule() {

    for (int i=0; i<(int)courseWidgets.size(); i++) {
        if (courseWidgets[i]->getCourse().rank == -1) {
            QMessageBox::information(this, "catch early", "enter valid times");
            return;
        }
        courseList.push_back(courseWidgets[i]->getCourse());
        courseList[courseList.size()-1].setId(i);
    }

    Scheduler scheduler (courseList);
    std::vector<Course> result = scheduler.makeSchedule();
    QString schedule_result = "";
    for (int i=0; i<(int)result.size(); i++) {
        qDebug() << "rank: " << result[i].rank;
        schedule_result += QString::number(result[i].id);
        schedule_result += " | ";
    }

    QMessageBox::information(this, "test", schedule_result);
    courseList.erase(courseList.begin(), courseList.end());

}



MainWindow::~MainWindow()
{

}
