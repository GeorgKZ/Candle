// This file is a part of "Candle" application.
// This file was originally ported from "LineSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <QtGui/QVector4D>
#include "pointsegment.h"

class LineSegment
{
public:
    LineSegment();
    LineSegment(QVector4D a, QVector4D b, int num);
    LineSegment(LineSegment *initial);
    ~LineSegment();

    int getLineNumber();
    QList<QVector4D> getPointArray();
    QList<double> getPoints();

    QVector4D &getStart();
    void setStart(QVector4D vector);

    QVector4D &getEnd();
    void setEnd(QVector4D vector);

    void setToolHead(int head);
    int getToolhead();
    void setSpeed(double s);
    double getSpeed();
    void setIsZMovement(bool isZ);
    bool isZMovement();
    void setIsArc(bool isA);
    bool isArc();
    void setIsFastTraverse(bool isF);
    bool isFastTraverse();

    bool contains(const QVector4D &point);

    bool drawn() const;
    void setDrawn(bool drawn);

    bool isMetric() const;
    void setIsMetric(bool isMetric);

    bool isAbsolute() const;
    void setIsAbsolute(bool isAbsolute);

    bool isHightlight() const;
    void setIsHightlight(bool isHightlight);

    int vertexIndex() const;
    void setVertexIndex(int vertexIndex);

    double getSpindleSpeed() const;
    void setSpindleSpeed(double spindleSpeed);

    double getDwell() const;
    void setDwell(double dwell);

    bool isClockwise() const;
    void setIsClockwise(bool isClockwise);

    PointSegment::planes plane() const;
    void setPlane(const PointSegment::planes &plane);

private:
    int m_toolhead;
    double m_speed;
    double m_spindleSpeed;
    double m_dwell;
    QVector4D m_first, m_second;

    // Line properties
    bool m_isZMovement;
    bool m_isArc;
    bool m_isClockwise;
    bool m_isFastTraverse;
    int m_lineNumber;
    bool m_drawn;
    bool m_isMetric;
    bool m_isAbsolute;
    bool m_isHightlight;
    int m_vertexIndex;

    PointSegment::planes m_plane;
};

#endif // LINESEGMENT_H
