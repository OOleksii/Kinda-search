#include "scanworker.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <QRegularExpression>
#include <QEventLoop>
ScanWorker::ScanWorker(QObject *parent, QString url, QString request)
    : QObject(parent), m_url(url), m_searchReques(request)
{
    setAutoDelete(true);
}

ScanWorker::~ScanWorker()
{
}

void ScanWorker::run()
{
    QNetworkAccessManager network;

    QEventLoop loop;
    m_reply = network.get(QNetworkRequest(QUrl(m_url)));
    connect(m_reply, &QNetworkReply::finished, this, &ScanWorker::downloadFinished);
    connect(this, &ScanWorker::finished,& loop,&QEventLoop::exit);
    loop.exec();
}

void ScanWorker::downloadFinished()
{
    QByteArray siteText = m_reply->readAll();
    QString str = QString::fromUtf8(siteText);

    QNetworkReply::NetworkError networkError = m_reply->error();
    foundResult(str.contains(m_searchReques), networkError!= QNetworkReply::NetworkError::NoError, m_reply->errorString() );
    if (networkError== QNetworkReply::NetworkError::NoError)
    {
        QStringList urlList = scanURL(str);
        if (!urlList.isEmpty())
        {
            emit moreSearchData(urlList);
        }
    }
    m_reply->deleteLater();
    emit finished();
}

QStringList ScanWorker::scanURL(QString page)
{
    QString http("http");
    int start = 0, end = 0;
    QStringList result;

    while (page.contains(http)||page.contains(http))
    {
        start = page.indexOf(http);
        end = start +1;
        while ( (end < page.size()) && (!forbidenCharacters.contains(page[end])))
        {
            ++end;
        }
        result << page.mid(start, end-start);
        page.remove(start,end-start);
    }
    return  result;
}
