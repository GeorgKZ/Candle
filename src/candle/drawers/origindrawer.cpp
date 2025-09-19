#include "origindrawer.h"

OriginDrawer::OriginDrawer()
{
}

OriginDrawer::~OriginDrawer()
{
}

bool OriginDrawer::updateData()
{
    m_lines = QVector<VertexData>()
        // X-axis
        << VertexData(QVector4D( 0.0,  0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 9.0,  0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(10.0,  0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 8.0,  0.5, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 8.0,  0.5, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 8.0, -0.5, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 8.0, -0.5, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(10.0,  0.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))

        // Y-axis
        << VertexData(QVector4D( 0.0,  0.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.0,  9.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.0, 10.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.5,  8.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.5,  8.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-0.5,  8.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-0.5,  8.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.0, 10.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))

        // Z-axis
        << VertexData(QVector4D( 0.0, 0.0,  0.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.0, 0.0,  9.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.0, 0.0, 10.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.5, 0.0,  8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.5, 0.0,  8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-0.5, 0.0,  8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-0.5, 0.0,  8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 0.0, 0.0, 10.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))

        // 2x2 rect
        << VertexData(QVector4D( 1.0,  1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-1.0,  1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-1.0,  1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-1.0, -1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(-1.0, -1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 1.0, -1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 1.0, -1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 1.0,  1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))

        // X-label
        << VertexData(QVector4D( 8.5,  3.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(  10,  1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 8.5,  1.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(  10,  3.0, 0.0, 1.0), QVector3D(1.0, 0.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))

        // Y-label
        << VertexData(QVector4D( 1.0,   10, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(1.75,  9.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(1.75,  9.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 2.5,   10, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(1.75,  9.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D(1.75,  8.0, 0.0, 1.0), QVector3D(0.0, 1.0, 0.0), QVector4D(sNan, sNan, sNan, 1.0))

        // Z-label
        << VertexData(QVector4D( 1.0,  0.0, 8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 2.5,  0.0, 8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 1.0,  0.0, 8.0, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 2.5,  0.0,  10, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 1.0,  0.0,  10, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0))
        << VertexData(QVector4D( 2.5,  0.0,  10, 1.0), QVector3D(0.0, 0.0, 1.0), QVector4D(sNan, sNan, sNan, 1.0));

    return true;
}
