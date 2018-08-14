#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H
#include <QAbstractListModel>
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QList>
#include <QMutex>
#include <QMutexLocker>
class Result :public QObject
{
    Q_OBJECT

public:
    Result ( QString Url, QObject *parent = nullptr);
    ~Result();
    QString getUrl() const;
    QString getStatus() const;
private:
    QString m_URL{""};
    bool m_found{false};
    int m_error;
    bool m_pending {true};
    QString m_errorCode;
public slots:
    void results(bool found, int error, QString errorCode);
signals:
    void newData();
};

class ResultsModel: public QAbstractTableModel
{
    Q_OBJECT

    enum Role
    {
        Url = 0,
        status =1
    };
public:
    ResultsModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
    void insert(Result * res);
    Result * getLast();
    QMutex dataLock;
    void clear();
private:
    QList<Result*> m_data;
signals:
    void resultsModelChanged();
public slots:
    void contentChanged();
};

#endif // RESULTSMODEL_H
