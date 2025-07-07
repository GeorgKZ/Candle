// This file is a part of "Candle" application.
// This file was originally ported from "GcodeViewParse.java" class
// of "Universal GcodeSender" application written by Will Winder
// (https://github.com/winder/Universal-G-Code-Sender)

// Copyright 2015-2021 Hayrullin Denis Ravilevich

#include <QtCore/QDebug>
#include "gcodeviewparse.h"

GcodeViewParse::GcodeViewParse(QObject *parent) :
    QObject(parent)
{
    absoluteMode = true;
    absoluteIJK = false;
    currentLine = 0;
    debug = true;

    m_min = QVector4D(qQNaN(), qQNaN(), qQNaN(), 1.0);
    m_max = QVector4D(qQNaN(), qQNaN(), qQNaN(), 1.0);

    m_minLength = qQNaN();
}

GcodeViewParse::~GcodeViewParse()
{
    foreach (LineSegment *ls, m_lines) delete ls;
}

QVector4D &GcodeViewParse::getMinimumExtremes()
{
    return m_min;
}

QVector4D &GcodeViewParse::getMaximumExtremes()
{
    return m_max;
}

void GcodeViewParse::testExtremes(QVector4D p3d)
{
    this->testExtremes(p3d.x(), p3d.y(), p3d.z(), p3d.w());
}

void GcodeViewParse::testExtremes(double x, double y, double z, double w)
{
    m_min.setX(Util::nMin(m_min.x(), x));
    m_min.setY(Util::nMin(m_min.y(), y));
    m_min.setZ(Util::nMin(m_min.z(), z));
    m_min.setZ(Util::nMin(m_min.w(), w));

    m_max.setX(Util::nMax(m_max.x(), x));
    m_max.setY(Util::nMax(m_max.y(), y));
    m_max.setZ(Util::nMax(m_max.z(), z));
    m_max.setZ(Util::nMax(m_max.w(), w));
}

void GcodeViewParse::testLength(const QVector4D &start, const QVector4D &end)
{
    double length = (start - end).length();
    if (!qIsNaN(length) && length != 0) m_minLength = qIsNaN(m_minLength) ? length : qMin<double>(m_minLength, length);
}

QList<LineSegment*> GcodeViewParse::toObjRedux(QList<QString> gcode, double arcPrecision, bool arcDegreeMode)
{
    GcodeParser gp;

    foreach (QString s, gcode) {
        gp.addCommand(s);
    }

    return getLinesFromParser(&gp, arcPrecision, arcDegreeMode);
}

QList<LineSegment*> GcodeViewParse::getLineSegmentList()
{
    return m_lines;
}

void GcodeViewParse::reset()
{
    foreach (LineSegment *ls, m_lines) delete ls;
    m_lines.clear();
    m_lineIndexes.clear();
    currentLine = 0;
    m_min = QVector4D(qQNaN(), qQNaN(), qQNaN(), 1.0);
    m_max = QVector4D(qQNaN(), qQNaN(), qQNaN(), 1.0);
    m_minLength = qQNaN();
}

double GcodeViewParse::getMinLength() const
{
    return m_minLength;
}

QSize GcodeViewParse::getResolution() const
{
    return QSize(((m_max.x() - m_min.x()) / m_minLength) + 1, ((m_max.y() - m_min.y()) / m_minLength) + 1);
}

QList<LineSegment*> GcodeViewParse::getLinesFromParser(GcodeParser *gp, double arcPrecision, bool arcDegreeMode)
{
    QList<PointSegment*> psl = gp->getPointSegmentList();
    // For a line segment list ALL arcs must be converted to lines.
    double minArcLength = 0.1;

    QVector4D *start, *end;
    start = nullptr;
    end = nullptr;
    LineSegment *ls;

    // Prepare segments indexes
    m_lineIndexes.resize(psl.count());

    int lineIndex = 0;
    foreach (PointSegment *segment, psl) {
        PointSegment *ps = segment;
        bool isMetric = ps->isMetric();
        ps->convertToMetric();

        end = ps->point();

        // start is null for the first iteration.
        if (start != nullptr) {           
            // Expand arc for graphics.            
            if (ps->isArc()) {
                QList<QVector4D> points =
                    GcodePreprocessorUtils::generatePointsAlongArcBDring(ps->plane(),
                    *start, *end, *ps->center(), ps->isClockwise(), ps->getRadius(), minArcLength, arcPrecision, arcDegreeMode);
                // Create line segments from points.
                if (points.length() > 0) {
                    QVector4D startPoint = *start;
                    foreach (QVector4D nextPoint, points) {
                        if (nextPoint == startPoint) continue;
                        ls = new LineSegment(startPoint, nextPoint, lineIndex);
                        ls->setIsArc(ps->isArc());
                        ls->setIsClockwise(ps->isClockwise());
                        ls->setPlane(ps->plane());
                        ls->setIsFastTraverse(ps->isFastTraverse());
                        ls->setIsZMovement(ps->isZMovement());
                        ls->setIsMetric(isMetric);
                        ls->setIsAbsolute(ps->isAbsolute());
                        ls->setSpeed(ps->getSpeed());
                        ls->setSpindleSpeed(ps->getSpindleSpeed());
                        ls->setDwell(ps->getDwell());
                        this->testExtremes(nextPoint);
                        m_lines.append(ls);
                        m_lineIndexes[ps->getLineNumber()].append(m_lines.count() - 1);
                        startPoint = nextPoint;
                    }
                    lineIndex++;
                }
            // Line
            } else {
                ls = new LineSegment(*start, *end, lineIndex++);
                ls->setIsArc(ps->isArc());
                ls->setIsFastTraverse(ps->isFastTraverse());
                ls->setIsZMovement(ps->isZMovement());
                ls->setIsMetric(isMetric);
                ls->setIsAbsolute(ps->isAbsolute());
                ls->setSpeed(ps->getSpeed());
                ls->setSpindleSpeed(ps->getSpindleSpeed());
                ls->setDwell(ps->getDwell());
                this->testExtremes(*end);
                this->testLength(*start, *end);
                m_lines.append(ls);
                m_lineIndexes[ps->getLineNumber()].append(m_lines.count() - 1);
            }
        }
        start = end;
    }

    return m_lines;
}

QList<LineSegment*> *GcodeViewParse::getLines()
{
    return &m_lines;
}

QVector<QList<int> > &GcodeViewParse::getLinesIndexes()
{
    return m_lineIndexes;
}
