#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H

#include <QWidget>
#include "course.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QStringList>

class CourseWidget : public QWidget
{
    Q_OBJECT
public:

    //CONSTRUCTOR
    explicit CourseWidget(int, QWidget *parent = 0);
    CourseWidget(int, QString, QWidget *parent = 0);

    //INSTANCE VARIABLES
    QLineEdit* days[5];
    QSpinBox* newRankBox;
    int rank;
    int parseTime(QString);

    //INSTANCE METHODS
    Course getCourse();

signals:

public slots:

};

#endif // COURSEWIDGET_H
