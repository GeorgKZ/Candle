// This file is a part of "Candle" application.
// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef HEIGHTMAPTABLEMODEL_H
#define HEIGHTMAPTABLEMODEL_H

#include <QtCore/QObject>
#include <QtCore/QAbstractTableModel>

class HeightMapTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HeightMapTableModel(QObject *parent = nullptr);

    void resize(int cols, int rows);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    void clear();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void dataChangedByUserInput();

private:
//    QList<QList<double>> m_data;
    QVector<QVector<double>> m_data;
    QList<QString> m_headers;
};

#endif // HEIGHTMAPTABLEMODEL_H
