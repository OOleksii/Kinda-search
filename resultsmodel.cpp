#include "resultsmodel.h"

//Result::Result(QObject *parent, QString Url):QObject (parent)
//{
//    m_URL =Url;
//}

//Result::~Result()
//{

//}
ResultsModel::ResultsModel()
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
    switch(index.column())
    {
        case 0:
            return m_data[index.row()].getUrl();
        case 1:
            return  m_data[index.row()].getStatus();
        default:
            return QVariant();
    }
}

void ResultsModel::insertRow(QString Url)
{
//    m_data <<Result(Url);
}

QHash<int, QByteArray> ResultsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "Url";
    roles[1] = "status";
    return roles;

}

void ResultsModel::dataChanged()
{

}

void Result::results(bool found, int error)
{
    m_pending = false;
    m_found = found;
    m_error = error;
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
