// This file is a part of "Candle" application.
// This file was originally ported from "GcodePreprocessorUtils.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#ifndef GCODEPREPROCESSORUTILS_H
#define GCODEPREPROCESSORUTILS_H

#include <QtCore/QObject>
#include <QtGui/QMatrix4x4>
#include <cmath>
#include "pointsegment.h"

class GcodePreprocessorUtils : public QObject
{
    Q_OBJECT
public:
    static QString overrideSpeed(QString command, double speed, double *original = NULL);
    static QString removeComment(QString command);
    static QString parseComment(QString command);
    static QString truncateDecimals(int length, QString command);
    static QString removeAllWhitespace(QString command);
    static QList<float> parseCodes(const QStringList &args, char code);
    static QList<int> parseGCodes(QString command);
    static QList<int> parseMCodes(QString command);
    static QStringList splitCommand(const QString &command);
    static double parseCoord(QStringList argList, char c);
    static QVector4D updatePointWithCommand(const QVector4D &initial, double x, double y, double z, bool absoluteMode);
    static QVector4D updatePointWithCommand(const QStringList &commandArgs, const QVector4D &initial, bool absoluteMode);
    static QVector4D updatePointWithCommand(const QString &command, const QVector4D &initial, bool absoluteMode);
    static QVector4D convertRToCenter(QVector4D start, QVector4D end, double radius, bool absoluteIJK, bool clockwise);
    static QVector4D updateCenterWithCommand(QStringList commandArgs, QVector4D initial, QVector4D nextPoint, bool absoluteIJKMode, bool clockwise);
    static QString generateG1FromPoints(QVector4D start, QVector4D end, bool absoluteMode, int precision);
    static double getAngle(QVector4D start, QVector4D end);
    static double calculateSweep(double startAngle, double endAngle, bool isCw);
    static QList<QVector4D> generatePointsAlongArcBDring(PointSegment::planes plane, QVector4D start, QVector4D end, QVector4D center, bool clockwise, double R, double minArcLength, double arcPrecision, bool arcDegreeMode);
    static QList<QVector4D> generatePointsAlongArcBDring(PointSegment::planes plane, QVector4D p1, QVector4D p2, QVector4D center, bool isCw, double radius, double startAngle, double sweep, int numPoints);
    static inline bool isDigit(char c);
    static inline bool isLetter(char c);
    static inline char toUpper(char c);
signals:

public slots:

private:

};

#endif // GCODEPREPROCESSORUTILS_H
