#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader:public QObject
{
    Q_OBJECT

public:
    explicit FileDownloader(QUrl Url, QObject *parent=0);
    virtual ~FileDownloader();

    QByteArray downloadedData() const;

    void test();
    void changeURL(QString);

    QByteArray m_DownloadedData;
    QNetworkAccessManager Access_Manager;

signals:
    void downloaded();

private slots:
    void fileDownloaded(QNetworkReply* pReply);

private:



};

#endif // FILEDOWNLOADER_H
