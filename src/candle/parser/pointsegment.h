// This file is a part of "Candle" application.
// This file was originally ported from "PointSegment.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef POINTSEGMENT_H
#define POINTSEGMENT_H

#include <QtGui/QVector4D>

#include "arcproperties.h"

class PointSegment
{
public:
    enum planes {
        XY,
        ZX,
        YZ
    };

    PointSegment();
    PointSegment(PointSegment *ps);
    PointSegment(const QVector4D *b, int num);
    PointSegment(QVector4D *point, int num, QVector4D *center, double radius, bool clockwise);
    ~PointSegment();
    void setPoint(QVector4D m_point);
    QVector4D* point();

    QVector<double> points();
    void setToolHead(int head);
    int getToolhead();
    void setLineNumber(int num);
    int getLineNumber();
    void setSpeed(double s);
    double getSpeed();
    void setIsZMovement(bool isZ);
    bool isZMovement();
    void setIsMetric(bool m_isMetric);
    bool isMetric();
    void setIsArc(bool isA);
    bool isArc();
    void setIsFastTraverse(bool isF);
    bool isFastTraverse();
    void setArcCenter(QVector4D *center);
    QVector<double> centerPoints();
    QVector4D *center();
    void setIsClockwise(bool clockwise);
    bool isClockwise();
    void setRadius(double rad);
    double getRadius();
    void convertToMetric();

    bool isAbsolute() const;
    void setIsAbsolute(bool isAbsolute);

    planes plane() const;
    void setPlane(const planes &plane);

    double getSpindleSpeed() const;
    void setSpindleSpeed(double spindleSpeed);

    double getDwell() const;
    void setDwell(double dwell);

private:
    ArcProperties *m_arcProperties;
    int m_toolhead;
    double m_speed;
    double m_spindleSpeed;
    double m_dwell;
    QVector4D *m_point;
    bool m_isMetric;
    bool m_isZMovement;
    bool m_isArc;
    bool m_isFastTraverse;
    bool m_isAbsolute;
    int m_lineNumber;
    planes m_plane;
};

#endif // POINTSEGMENT_H
