#ifndef CRNWIDGET_H
#define CRNWIDGET_H

#include <QWidget>
#include "filedownloader.h"
#include <QLineEdit>

class FileDownloader;
class QByteArray;
class QTextEdit;
class QString;
class QComboBox;

class CrnWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CrnWidget(QWidget *parent = 0);
    FileDownloader* fd;
    QLineEdit* text;
    void parse();


signals:
    void loadCrn(QString);

public slots:
    void loadWebData();
    void requestUrl();

private:
    QString webData;
};

#endif // CRNWIDGET_H
