#include "coursewidget.h"
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <QMessageBox>

CourseWidget::CourseWidget(int courseNum, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);

    newRankBox = new QSpinBox(this);
    newRankBox->setMinimum(0);
    newRankBox->setMaximum(10);

    QLabel* label = new QLabel(this);
    label->setText("Course " + QString::number(courseNum) + ": ");

    layout->addWidget(label);
    layout->addWidget(newRankBox);


    for (int i=0; i<5; i++) {
        days[i] = new QLineEdit(this);
        layout->addWidget(days[i]);
    }

}

CourseWidget::CourseWidget(int courseNum, QString values, QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);

    newRankBox = new QSpinBox(this);
    newRankBox->setMinimum(0);
    newRankBox->setMaximum(10);

    QLabel* label = new QLabel(this);
    label->setText("Course " + QString::number(courseNum) + ": ");

    layout->addWidget(label);
    layout->addWidget(newRankBox);

    for (int i=0; i<5; i++) {
        days[i] = new QLineEdit(this);
        layout->addWidget(days[i]);
    }
    days[0]->setText(values);

}

Course CourseWidget::getCourse() {
    std::vector< std::pair<int, int> > timeVector(5);

    QRegExp regex("^[MTWRF]{1,5}\\s\\d{1,2}\\W\\d{1,2}$");

    if (days[0]->text().contains(regex)) {
        qDebug() << "detected";
        for (int i=0; i<5; i++) {
            if (days[i]->text().contains(regex)) {
                qDebug() << "matches";
                QStringList parts = days[i]->text().split(QRegExp("\\s")); //split on whitespace first

                //split all the individual "day" chars i.e. MTW -> [M, T, W]
                QStringList weekdays = parts.at(0).split(QRegExp(""), QString::SkipEmptyParts);

                int time = parseTime(parts.at(1));

                for (int i=0; i<weekdays.size(); i++) {
                    qDebug() << weekdays.at(i);
                    int day;
                    if (weekdays.at(i) == "M") day = 0;
                    else if (weekdays.at(i) == "T") day = 1;
                    else if (weekdays.at(i) == "W") day = 2;
                    else if (weekdays.at(i) == "R") day = 3;
                    else day = 4;

                    std::pair<int, int> pair = std::make_pair(day, time);
                    timeVector[i] = pair;
                    qDebug() << timeVector[i].first << "," << timeVector[i].second;
                }
            }
            else if (days[i]->text()=="") break; //must be empty if it does not match the regex
            else return Course();
        }
    }

    else {
        for (int i=0; i<5; i++) {
            if (days[i]->text().contains(QRegExp("^[0-9]{1,2}\\W\\d{1,2}$"))) {
                std::pair<int, int> pair = std::make_pair(i, parseTime(days[i]->text()));
                timeVector[i] = pair;
                qDebug() << timeVector[i].first << "," << timeVector[i].second;
            }
            //hacky check for errors
            // basically if we know the first entry is not of form: "ABC 12:34", then it cannot have a letter character
            else if (days[i]->text().contains(QRegExp("\\w"))) return Course();
        }
    }
    rank = newRankBox->value();
    return Course(timeVector, rank);
}

int CourseWidget::parseTime(QString input) {
    bool ok;
    QStringList time_parts = input.split(":");
    int time = (time_parts.at(0)+time_parts.at(1)).toInt(&ok, 10);
    qDebug() << time;
    return time;
}
