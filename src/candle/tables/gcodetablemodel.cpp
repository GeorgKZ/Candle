// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QtWidgets/QApplication>
#include "gcodetablemodel.h"

GCodeTableModel::GCodeTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

QVariant GCodeTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_data.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column())
        {
        case 0: return index.row() == this->rowCount() - 1 ? QString() : QString::number(index.row() + 1);
        case 1: return m_data.at(index.row()).command;
        case 2:
            if (index.row() == this->rowCount() - 1) return QString();
            switch (m_data.at(index.row()).state) {
            case GCodeItem::InQueue: return tr("In queue");
            case GCodeItem::Sent: return tr("Sent");
            case GCodeItem::Processed: return tr("Processed");
            case GCodeItem::Skipped: return tr("Skipped");
            }
            return tr("Unknown");
        case 3: return m_data.at(index.row()).response;
        case 4: return m_data.at(index.row()).line;
        case 5: return QVariant(m_data.at(index.row()).args);
        }
    }

    if (role == Qt::TextAlignmentRole) {
        switch (index.column()) {
        case 0: return Qt::AlignCenter;
        default: return Qt::AlignVCenter;
        }
    }

    return QVariant();
}

bool GCodeTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        switch (index.column())
        {
        case 0: return false;
        case 1: m_data[index.row()].command = value.toString(); break;
        case 2: m_data[index.row()].state = value.toInt(); break;
        case 3: m_data[index.row()].response = value.toString(); break;
        case 4: m_data[index.row()].line = value.toInt(); break;
        case 5: m_data[index.row()].args = value.toStringList(); break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool GCodeTableModel::insertRow(int row, const QModelIndex &parent)
{
    if (row > rowCount()) return false;

    beginInsertRows(parent, row, row);
    m_data.insert(row, GCodeItem());
    endInsertRows();
    return true;
}

bool GCodeTableModel::removeRow(int row, const QModelIndex &parent)
{
    //if (!index(row, 0).isValid()) return false;

    beginRemoveRows(parent, row, row);
    m_data.removeAt(row);
    endRemoveRows();
    return true;
}

bool GCodeTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_data.erase(m_data.begin() + row, m_data.begin() + row + count);
    endRemoveRows();
    return true;
}

void GCodeTableModel::clear()
{
    beginResetModel();

//    foreach (GCodeItem* item, m_data) delete item;

    m_data.clear();
    endResetModel();
}

int GCodeTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_data.size();
}

int GCodeTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_headers.size();
}

QVariant GCodeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((section < 0)
        || ((orientation == Qt::Horizontal) && (section >= columnCount()))
        || ((orientation == Qt::Vertical) && (section >= rowCount()))) {
        return QVariant();
    }

    switch(role)
    {
        case Qt::DisplayRole:
            if (orientation == Qt::Horizontal) {
                return m_headers.at(section);
            }
            else if (orientation == Qt::Vertical) {
                return QString::number(section + 1);
            }
            break;
        default:
            break;
    }
    return QVariant();
}

Qt::ItemFlags GCodeTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index) |
        (index.column() == 1 ? Qt::ItemIsEditable : Qt::NoItemFlags);
}

QList<GCodeItem> &GCodeTableModel::data()
{
    return m_data;
}

bool GCodeTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
  QAbstractTableModel::setHeaderData(section,orientation,value,role);

  if (role != Qt::DisplayRole || orientation != Qt::Horizontal || section < 0) return false;

  if (section == m_headers.size()) m_headers.push_back(value.toString());
  else if (section > m_headers.size()) {
      for (int i = m_headers.size(); i < section; ++i) {
        m_headers.push_back("");
      }
      m_headers.push_back(value.toString());
  }
  else {
      m_headers[section] = value.toString();
  }

  emit headerDataChanged(orientation, section, section);

  return true;
}
