#ifndef SCANWORKER_H
#define SCANWORKER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSharedPointer>
#include <QRunnable>
class ScanWorker: public QObject, public QRunnable
{
    Q_OBJECT
public:
    ScanWorker(QObject *parent, QString url, QString request);
    ~ScanWorker() override;
    void run() override;
public slots:
    void downloadFinished();
signals:
    void finishedDownload();
    void finishedParsing();
    void moreSearchData(QStringList newUrls);
    void foundResult(bool result, int error);
private:
    QString m_url;
    QNetworkAccessManager * m_networkAccesMenager;
    QNetworkReply* m_reply;
    QString m_searchReques;
    QStringList scanURL(QString page);
};

#endif // SCANWORKER_H
