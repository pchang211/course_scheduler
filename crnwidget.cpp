#include "crnwidget.h"
#include "filedownloader.h"
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <Qstring>

#include <QUrl>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QStringList>
#include <QMessageBox>

const QString url_0 = "https://ssb.middlebury.edu/PNTR/bwckschd.p_disp_listcrse?term_in=201420&subj_in=";
const QString url_1("&crse_in=");
const QString url_2("&crn_in=");


CrnWidget::CrnWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    setLayout(layout);

    text = new QLineEdit();
    layout->addWidget(text);

    QPushButton *button = new QPushButton("Find class");
    connect(button, SIGNAL(pressed()), this, SLOT(requestUrl()));
    layout->addWidget(button);

    QUrl url;

    fd = new FileDownloader(url, this);
    connect(fd, SIGNAL(downloaded()), this, SLOT(loadWebData()));

}

void CrnWidget::requestUrl() {
    if (!text->text().contains(QRegExp("^\\w+\\s\\d+$"))) {
        QMessageBox::information(this, "catch early", "not a valid course");
        return;
    }

    QStringList parts = text->text().split(QRegExp("\\s"));
    qDebug() << parts[0];
    qDebug() << parts[1];

    QString url = url_0 + parts[0] + url_1 + parts[1] + url_2;
    qDebug() << "requested" << url;
    QNetworkRequest request(url);
    fd->Access_Manager.get(request);
}

void CrnWidget::loadWebData() {
    webData = fd->m_DownloadedData;
    if (webData.contains("404 Not Found")) {
        QMessageBox::information(this, "catch early", "invalid entry");
        return;
    }
    else if (webData.contains("No classes were found that meet your search criteria")) {
        QMessageBox::information(this, "catch early", "course not found");
        return;
    }
    parse();
    text->clear();
}

void CrnWidget::parse() {
    qDebug() << "parse()";
    QRegExp time_regex("(\\d{1,2}:\\d{1,2})");
    QRegExp days_regex("(?:\<TD CLASS=\"dddefault\"\>)([MTWRF]{1,5})(?:\</TD\>)");
    time_regex.indexIn(webData);
    days_regex.indexIn(webData);
    QStringList time_parts = time_regex.capturedTexts();
    QStringList days_parts = days_regex.capturedTexts();
    qDebug() << time_parts.at(1);
    qDebug() << days_parts.at(1);

    emit loadCrn(days_parts.at(1) + " " + time_parts.at(1));

}
