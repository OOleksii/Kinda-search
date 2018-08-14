#include "backendbase.h"
#include <QDebug>
#include <QQmlContext>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include "resultsmodel.h"
void BackendBase::start()
{
    que.clear();
    m_stopSearch = false;
    m_resultsModel.clear();
    moreSearchData(QStringList(m_url));
}

void BackendBase::stop()
{
    m_stopSearch = true;
}

BackendBase::BackendBase(QObject *parent): QObject(parent),
    m_networkAccesMenager(new QNetworkAccessManager(this)),
    threadpol(this)
{
    threadpol.setMaxThreadCount(m_maxThreadCount);
    que.clear();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("resultsModel", &m_resultsModel);

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

ResultsModel* BackendBase::resultsModel()
{
    return & m_resultsModel;
}

void BackendBase::moreSearchData(QStringList newUrls)
{
    QMutexLocker lock(&queMutex);
    if ((m_resultsModel.rowCount() >= m_maxSearchUrlCount) || m_stopSearch) // need if for stop
    {
        return;
    }
    for(QString & url : newUrls)
    {
        ScanWorker * newWorker = new ScanWorker(nullptr, url , m_searchRequest);
        connect(newWorker, &ScanWorker::moreSearchData, this, &BackendBase::moreSearchData, Qt::ConnectionType::QueuedConnection );

        Result* newResult = new Result(url);

        connect(newWorker, &ScanWorker::foundResult, newResult, &Result::results, Qt::ConnectionType::QueuedConnection );

        m_resultsModel.insert(newResult);

        threadpol.start(newWorker);
    }
}
