#include "resultsmodel.h"
#include <QDebug>

Result::Result(QString Url, QObject *parent ):QObject (parent),m_URL(Url)
{

}

Result::~Result()
{

}
ResultsModel::ResultsModel(QObject *parent):QAbstractTableModel(parent)
{
    m_data.clear();
}

int ResultsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

int ResultsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
    qDebug () <<index<< role <<index.row();
    switch(role)
    {
        case Url:
            return m_data[index.row()]->getUrl();
        case status:
            return  m_data[index.row()]->getStatus();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> ResultsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "URL";
    roles[1] = "status";
    return roles;

}

void ResultsModel::insert(Result * res)
{
   QMutexLocker lock(&dataLock);
   beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
   m_data<<res;
   connect(res, &Result::newData, this, &ResultsModel::resultsModelChanged);
   endInsertRows();
   emit resultsModelChanged();
}

Result *ResultsModel::getLast()
{
    return nullptr;
}


void Result::results(bool found, int error)
{
    m_pending = false;
    m_found = found;
    m_error = error;
    emit newData();
}




QString Result::getUrl() const
{
    return m_URL;
}

QString Result::getStatus() const
{
    if (m_pending)
    {
        return "Is downloading";
    } else
    if (m_error != 0)
    {
        return "Error " + QString::number(m_error);
    } else
    {
        return m_found? "Yes":"No";
    }
}
