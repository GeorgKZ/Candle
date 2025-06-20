// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODETABLEMODEL_H
#define GCODETABLEMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/QString>

struct GCodeItem
{
    enum States { InQueue, Sent, Processed, Skipped };

    QString command;
    char state;
    QString response;
    int line;
    QStringList args;
};

class GCodeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit GCodeTableModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void clear();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    QList<GCodeItem> &data();

signals:

public slots:

private:

    /**
     * Список элементов типа GCodeItem, образующий строки таблицы
     */
    QList<GCodeItem> m_data;

    /**
     * Список строк, образующих заголовок таблицы
     */
    QStringList m_headers;
};

#endif // GCODETABLEMODEL_H
