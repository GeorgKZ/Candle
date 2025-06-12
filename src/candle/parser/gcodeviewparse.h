// This file is a part of "Candle" application.
// This file was originally ported from "GcodeViewParse.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODEVIEWPARSE_H
#define GCODEVIEWPARSE_H

#include <QtCore/QObject>
#include <QtGui/QVector4D>
#include <QtGui/QVector2D>
#include "linesegment.h"
#include "gcodeparser.h"
#include "utils/util.h"

class GcodeViewParse : public QObject
{
    Q_OBJECT
public:
    explicit GcodeViewParse(QObject *parent = nullptr);
    ~GcodeViewParse();

    QVector4D &getMinimumExtremes();
    QVector4D &getMaximumExtremes();
    double getMinLength() const;
    QSize getResolution() const;
    QList<LineSegment*> toObjRedux(QList<QString> gcode, double arcPrecision, bool arcDegreeMode);
    QList<LineSegment*> getLineSegmentList();
    QList<LineSegment*> getLinesFromParser(GcodeParser *gp, double arcPrecision, bool arcDegreeMode);

    QList<LineSegment*> *getLines();
    QVector<QList<int>> &getLinesIndexes();

    void reset();

signals:

public slots:

private:
    bool absoluteMode;
    bool absoluteIJK;

    // Parsed object
    QVector4D m_min, m_max;
    double m_minLength;
    QList<LineSegment*> m_lines;
    QVector<QList<int>> m_lineIndexes;    

    // Parsing state.
    QVector4D lastPoint;
    int currentLine; // for assigning line numbers to segments.

    // Debug
    bool debug;
    void testExtremes(QVector4D p3d);
    void testExtremes(double x, double y, double z, double w);
    void testLength(const QVector4D &start, const QVector4D &end);
};

#endif // GCODEVIEWPARSE_H
