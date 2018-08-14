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
    Q_PROPERTY(ResultsModel * resultsModel READ resultsModel NOTIFY resultsModelChanged)
public slots:
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
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
    ResultsModel *resultsModel();
private:
    QString m_url {"http://www.example.org"};
    QSharedPointer<QNetworkAccessManager> m_networkAccesMenager;
    QStringList que;
    QMutex queMutex;
    QThreadPool threadpol;
    int m_maxThreadCount{4};
    QString m_searchRequest{"home"};
    int m_maxSearchUrlCount {10};
    ResultsModel m_resultsModel;
    bool m_stopSearch{false};
signals:
    void urlChanged();
    void maxThreadCountChanged();
    void searchRequestChanged();
    void maxSearchUrlCountChanged();
    void resultsModelChanged();
public slots:
    void moreSearchData(QStringList newUrls);
};

#endif // BACKENDBASE_H
