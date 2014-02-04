#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl Url, QObject *parent) :
    QObject(parent)
{
    connect(&Access_Manager, SIGNAL(finished(QNetworkReply*)),
                SLOT(fileDownloaded(QNetworkReply*)));

//    QNetworkRequest request(Url);
//    Access_Manager.get(request);
}

FileDownloader::~FileDownloader()
{

}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    qDebug() << "file downloaded";
    //emit a signal
    pReply->deleteLater();
    emit downloaded();
}

void FileDownloader::changeURL(QString url) {
    QNetworkRequest request(url);
    Access_Manager.get(request);
    qDebug() << "URL changed";
}

void FileDownloader::test() {
    qDebug() << "FileDownloader";
}

QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
