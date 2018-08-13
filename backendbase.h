#ifndef BACKENDBASE_H
#define BACKENDBASE_H

#include <QObject>
#include "scanworker.h"
#include <QStringList>
#include <QMutex>
#include <QMutexLocker>
#include <QThreadPool>
#include "resultsmodel.h"
class BackendBase: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString searchRequest READ searchRequest WRITE setSearchRequest NOTIFY searchRequestChanged)
    Q_PROPERTY(QString maxThreadCount READ maxThreadCount WRITE setMaxThreadCount NOTIFY maxThreadCountChanged)
    Q_PROPERTY(QString maxSearchUrlCount READ maxSearchUrlCount WRITE setMaxSearchUrlCount NOTIFY maxSearchUrlCountChanged)
public slots:
    Q_INVOKABLE void start();
public:
    BackendBase(QObject *parent = nullptr);
    ~BackendBase();
    QString url();
    void setUrl(QString & newUrl);
    QString maxThreadCount() const;
    void setMaxThreadCount(QString value);

    QString searchRequest() const;
    void setSearchRequest(const QString searchRequest);

    void setMaxSearchUrlCount(QString value);

    QString maxSearchUrlCount() const;

private:
    QString m_url {"http://www.example.org"};
    QString m_request{"background-color"};
    QSharedPointer<QNetworkAccessManager> m_networkAccesMenager;
    QStringList que;
    QMutex queMutex;
    QThreadPool threadpol;
    int m_maxThreadCount{4};
    QString m_searchRequest{"Daimler"};
    int m_maxSearchUrlCount {1};
    ResultsModel resultsModel;
signals:
    void urlChanged();
    void maxThreadCountChanged();
    void searchRequestChanged();
    void maxSearchUrlCountChanged();
public slots:
    void moreSearchData(QStringList newUrls);
};

#endif // BACKENDBASE_H
