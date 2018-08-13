#ifndef RESULTSMODEL_H
#define RESULTSMODEL_H
#include <QAbstractListModel>
#include <QList>

class Result: public QObject
{
    Q_OBJECT

public:
//    Result (QObject *parent = nullptr, QString Url = "");
//    ~Result();
    QString getUrl() const;
    QString getStatus() const;
private:
    QString m_URL{""};
    bool m_found{false};
    int m_error;
    bool m_pending {true};
public slots:
    void results(bool found, int error);
};

class ResultsModel: public QAbstractTableModel
{
    enum Role
    {
        none,
        Url,
        Status
    };
public:
    ResultsModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    void insertRow(QString Url);
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
public slots:
    void dataChanged();
private:
    QList<Result> m_data;
};

#endif // RESULTSMODEL_H
