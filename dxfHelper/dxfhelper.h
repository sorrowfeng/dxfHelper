#ifndef DXFHELPER_H
#define DXFHELPER_H

#include <QPointF>
//#include <QRandomGenerator>
#include <QDebug>
#include <QPainterPath>
#include <QtMath>
#include <QVector2D>
#include <QVector3D>
#include <spline_library/splinehelper.h>


struct DXFLine {
    double x1;
    double y1;
    double z1;
    double x2;
    double y2;
    double z2;
};

struct DXFRect {
    QList<QVector3D> list;
};


struct DXFArc {
    double cx;
    double cy;
    double cz;
    double angle1;
    double angle2;
    double radius;
};

struct DXFCircle {
    double cx;
    double cy;
    double cz;
    double radius;
};

struct DXFEllipse {
    double cx;
    double cy;
    double cz;
    double mx;
    double my;
    double mz;
    double angle1;
    double angle2;
    double ratio;
};

struct DXFPolyline {
    double flags;
    double number;
    QList<QVector3D> list;
};

struct DXFSpline {
    double nControl;
    QList<QVector3D> controlPoints;
};


class DxfHelper
{
public:
    DxfHelper();
    QList<QVector3D> expandPolygon(QList<QVector3D> polygon, float expand);
    bool generateDxf(const QString &fileName);
    QVector<QVector<QPointF>> getDxfPaths() const;

    QList<DXFLine> getDxfLineList() const;
    QList<DXFRect> getDxfRectList() const;
    QList<DXFArc> getDxfArcList() const;
    QList<DXFCircle> getDxfCircleList() const;
    QList<DXFEllipse> getDxfEllipseList() const;
    QList<DXFPolyline> getDxfPolylineList() const;
    QList<DXFSpline> getDxfSplineList() const;

    void setExpandOffset(double value);

    void matchDXFSize();
    QImage generateDXFImage();
    QList<QPainterPath> getDxfPathList() const;
    QSize getImageSize() const;
    QList<double> getDxfBorderList() const;
private:
    QPointF currentPos;
    unsigned int vertexIndex = 0;
    unsigned int controlIndex = 0;
    QVector<QVector<QPointF>> dxfPaths;
    QList<QPainterPath> dxfPathList;

    double expandOffset = 0;

    QList<DXFLine> dxfLineList;
    QList<DXFRect> dxfRectList;
    QList<DXFArc> dxfArcList;
    QList<DXFCircle> dxfCircleList;
    QList<DXFEllipse> dxfEllipseList;
    QList<DXFPolyline> dxfPolylineList;
    QList<DXFSpline> dxfSplineList;
    QList<double> dxfBorderList;
    QSize imageSize;
};

#endif // DXFHELPER_H
