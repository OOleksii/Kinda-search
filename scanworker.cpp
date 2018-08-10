#include "scanworker.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <QRegularExpression>
ScanWorker::ScanWorker(QObject *parent, QString url, QString request)
    : QObject(parent), m_url(url), m_searchReques(request)
{
    setAutoDelete(false);
}

ScanWorker::~ScanWorker()
{
    setAutoDelete(true);
    delete m_networkAccesMenager;
    if(nullptr!=m_reply)
    {
        delete m_reply;
    }
}

void ScanWorker::run()
{
    m_networkAccesMenager = new QNetworkAccessManager(this);
    m_reply = m_networkAccesMenager->get(QNetworkRequest(QUrl(m_url)));

    connect(m_reply, &QNetworkReply::finished, this, &ScanWorker::downloadFinished);
}

void ScanWorker::downloadFinished()
{
    QByteArray siteText = m_reply->readAll();
    QString str = QString::fromUtf8(siteText);

    QNetworkReply::NetworkError networkError = m_reply->error();
    foundResult(str.contains(m_searchReques), networkError== QNetworkReply::NetworkError::NoError );

    if (networkError== QNetworkReply::NetworkError::NoError)
    {
        QStringList urlList = scanURL(str);
        if (!urlList.isEmpty())
        {
            emit moreSearchData(urlList);
        }
    }
}

QStringList ScanWorker::scanURL(QString page)
{
    QRegularExpression reg("(https?:\/\/(?:www\.|(?!www))[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|www\.[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|https?:\/\/(?:www\.|(?!www))[a-zA-Z0-9]\.[^\s]{2,}|www\.[a-zA-Z0-9]\.[^\s]{2,})");

    QRegularExpressionMatch match = reg.match(page);
    return  match.capturedTexts();
}
