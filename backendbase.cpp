#include "backendbase.h"
#include <QDebug>
#include <QQmlContext>
#include <QQuickView>

void BackendBase::start()
{
    que.clear();
    moreSearchData(QStringList(m_url));
}

BackendBase::BackendBase(QObject *parent): QObject(parent),
    m_networkAccesMenager(new QNetworkAccessManager(this)),
    threadpol(this)
{
    threadpol.setMaxThreadCount(m_maxThreadCount);
    que.clear();
}

BackendBase::~BackendBase()
{
    threadpol.waitForDone();
}

QString BackendBase::url()
{
    return m_url;
}

void BackendBase::setUrl(QString &newUrl)
{
    m_url = newUrl;
    emit urlChanged();
}

QString BackendBase::maxThreadCount() const
{
    return QString::number(m_maxThreadCount);
}

void BackendBase::setMaxThreadCount(QString value)
{
    m_maxThreadCount = value.toInt();
    threadpol.setMaxThreadCount(m_maxThreadCount);
    emit maxThreadCountChanged();
}

QString BackendBase::searchRequest() const
{
    return m_searchRequest;
}

void BackendBase::setSearchRequest(const QString searchRequest)
{
    m_searchRequest = searchRequest;
    emit searchRequestChanged();
}

void BackendBase::setMaxSearchUrlCount(QString value)
{
    m_maxSearchUrlCount = value.toInt();
    emit maxSearchUrlCountChanged();
}

QString BackendBase::maxSearchUrlCount() const
{
    return QString::number(m_maxSearchUrlCount);
}

void BackendBase::moreSearchData(QStringList newUrls)
{
    QMutexLocker lock(&queMutex);
    que << newUrls;
    if (m_currentlySearched > m_maxSearchUrlCount) // need if for stop
    {
        return;
    }
    for(QString & url : newUrls)
    {
        ScanWorker * newWorker = new ScanWorker(nullptr, url , m_searchRequest);
        connect(newWorker, &ScanWorker::moreSearchData, this, &BackendBase::moreSearchData, Qt::ConnectionType::QueuedConnection );
        newWorker->run();
//        threadpol.start(newWorker);
    }

}
