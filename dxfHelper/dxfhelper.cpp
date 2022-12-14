#include "dxfhelper.h"
#include "dxfreader.h"

#include <QImage>
#include <QPainter>

DxfHelper::DxfHelper()
{

}

double norm(double x, double y)
{
    return sqrt(x * x + y * y);
}

QList<QVector3D> DxfHelper::expandPolygon(QList<QVector3D> polygon, float expand)
{
    QList<QVector3D> new_polygon;
    int len = polygon.length();
    if(len<3||qFuzzyIsNull(expand)) return polygon;

    bool repeatFlag = false;
    if(polygon.first()==polygon.back()) {
        repeatFlag = true;
        polygon.removeLast();
        len = polygon.length();
    }

    int convertNum = 0;
    for (int i = 0; i < len; i++)
    {
        QVector3D p = polygon[i];
        QVector3D p1 = polygon[i == 0 ? len - 1 : i - 1];
        QVector3D p2 = polygon[i == len - 1 ? 0 : i + 1];
        float v1x = p1.x() - p.x();
        float v1y = p1.y() - p.y();
        float n1 = norm(v1x, v1y);
        float vv1x = v1x / n1;
        float vv1y = v1y / n1;
        float v2x = p2.x() - p.x();
        float v2y = p2.y() - p.y();
        float n2 = norm(v2x, v2y);
        float vv2x = v2x / n2;
        float vv2y = v2y / n2;
        float vectorLen = -expand / sqrt((1 - (vv1x * vv2x + vv1y * vv2y)) / 2.0f);
        float judge = v1x * v2y - v2x * v1y;
        if (judge < 0) vectorLen *= -1;
        if (judge < 0) convertNum++;
        float vx = vv1x + vv2x;
        float vy = vv1y + vv2y;
        vectorLen = vectorLen / norm(vx, vy);
        vx *= vectorLen;
        vy *= vectorLen;
        new_polygon.append(QVector3D(vx + p.x(), vy + p.y(), 0));
    }
    if(convertNum==len) {
        new_polygon.clear();
        for (int i = 0; i < len; i++)
        {
            QVector3D p = polygon[i];
            QVector3D p1 = polygon[i == 0 ? len - 1 : i - 1];
            QVector3D p2 = polygon[i == len - 1 ? 0 : i + 1];
            float v1x = p1.x() - p.x();
            float v1y = p1.y() - p.y();
            float n1 = norm(v1x, v1y);
            float vv1x = v1x / n1;
            float vv1y = v1y / n1;
            float v2x = p2.x() - p.x();
            float v2y = p2.y() - p.y();
            float n2 = norm(v2x, v2y);
            float vv2x = v2x / n2;
            float vv2y = v2y / n2;
            float vectorLen = -expand / sqrt((1 - (vv1x * vv2x + vv1y * vv2y)) / 2.0f);
            float vx = vv1x + vv2x;
            float vy = vv1y + vv2y;
            vectorLen = vectorLen / norm(vx, vy);
            vx *= vectorLen;
            vy *= vectorLen;
            new_polygon.append(QVector3D(vx + p.x(), vy + p.y(), 0));
        }
    }

    if(repeatFlag) new_polygon.append(new_polygon.first());

    return new_polygon;
}

bool DxfHelper::generateDxf(const QString &fileName)
{
//    currentPos = QPointF(QRandomGenerator::global()->bounded(9999.99), QRandomGenerator::global()->bounded(9999.99));
    currentPos = QPointF(9999.99, 9999.99);
    vertexIndex = 0;
    controlIndex = 0;
    dxfPaths.clear();

    DxfReader dxfReader(fileName);
    for(auto d: dxfReader.dxfText) {
        qDebug() << "text data:" << d.text.c_str() << d.angle << d.style.c_str() << d.height;
    }

    for(auto d: dxfReader.dxfLinetypes) {
        qDebug() << "linetypes data:" << d.name.c_str() << d.flags << d.pattern << d.description.c_str() << d.patternLength << d.numberOfDashes;
    }

    QVector<QPointF> linepath;
    for(auto d: dxfReader.dxfLines) {
        qDebug() << "line data:" << d.x1 << d.y1 << d.z1 << "," << d.x2 << d.y2 << d.z2;
        if(currentPos!=QPointF(d.x1, d.y1)) {
            if(!linepath.isEmpty()) {
                QList<QVector3D> linelist;
                foreach(auto point, linepath) linelist.append(QVector3D(point));
                linepath.clear();
                linelist = expandPolygon(linelist, expandOffset);
                foreach(QVector3D point, linelist) {
                    double x = point.x();
                    double y = point.y();
                    linepath.append(QPointF(x, y));
                    currentPos = QPointF(x, y);
                }
                dxfPaths.append(linepath);
                linepath.clear();
            }
            linepath.append(QPointF(d.x1, d.y1));
            linepath.append(QPointF(d.x2, d.y2));
            currentPos = QPointF(d.x2, d.y2);
        } else {
            linepath.append(QPointF(d.x2, d.y2));
            currentPos = QPointF(d.x2, d.y2);
        }
    }
    if(!linepath.isEmpty()) {
        QList<QVector3D> linelist;
        foreach(auto point, linepath) linelist.append(QVector3D(point));
        linepath.clear();
        linelist = expandPolygon(linelist, expandOffset);
        foreach(QVector3D point, linelist) {
            double x = point.x();
            double y = point.y();
            linepath.append(QPointF(x, y));
            currentPos = QPointF(x, y);
        }
        dxfPaths.append(linepath);
        linepath.clear();
    }


    for(auto d: dxfReader.dxfArcs) {
        qDebug() << "arcs data:" << d.cx << d.cy << d.cz << d.angle1 << d.angle2 << d.radius;


        double cx = d.cx;
        double cy = d.cy;
//        double cz = d.cz;
        double angle1 = d.angle1;
        double angle2 = d.angle2;
        double radius = d.radius;

        radius = radius + expandOffset;


        QPainterPath path;
        double startXPos = cx + cos(abs(angle1)*M_PI/180)*radius;
        double startYPos = cy + sin(abs(angle1)*M_PI/180)*radius;

        path.moveTo(startXPos, startYPos);

        double angleStart ,anglePassed;
        angleStart = angle1;
        if(angleStart>=180) angleStart = angleStart-360;
        anglePassed = angleStart-angle2;
        if(angleStart<180) angleStart = -angleStart;
        if(anglePassed<-360) anglePassed = anglePassed+360;

        QRectF rect(cx-radius, cy-radius, 2*radius, 2*radius);
        path.arcTo(rect, angleStart, anglePassed);

        QVector<QPointF> arcpath;
        for(double i = 0; i <= 1; i += 0.003) {  // TODO: 步长随图片大小调整
            QPointF point = path.pointAtPercent(i);
            double x = point.x();
            double y = point.y();
            arcpath.append(point);
            currentPos=QPointF(x, y);
        }
        dxfPaths.append(arcpath);
//        dxfPathList.append(path);
    }

    for(auto d: dxfReader.dxfCircles) {
        qDebug() << "circle data:" << d.cx << d.cy << d.cz << d.radius;


        double cx = d.cx;
        double cy = d.cy;
//        double cz = d.cz;
        double radius = d.radius;

        radius = radius + expandOffset;


        QPainterPath path;
        path.moveTo(cx+radius, cy);
        path.arcTo(cx-radius, cy-radius, 2*radius, 2*radius, 0, 360);

        QVector<QPointF> circlepath;
        for(double i = 0; i <= 1; i += 0.003) {  // TODO: 步长随图片大小调整
            QPointF point = path.pointAtPercent(i);
            double x = point.x();
            double y = point.y();
            circlepath.append(point);
            currentPos=QPointF(x, y);
        }
        dxfPaths.append(circlepath);
//        dxfPathList.append(path);
    }

    for(auto d: dxfReader.dxfEllipses) {    // 起点角度要×ratio
        qDebug() << "ellipses data:" << d.cx << d.cy << d.cz << d.mx << d.my << d.mz << d.ratio << d.angle1 << d.angle2;

        double cx = d.cx;
        double cy = d.cy;
//        double cz = d.cz;
        double mx = d.mx;
        double my = d.my;
//        double mz = d.mz;
        double ratio = d.ratio;
        double angle1 = d.angle1;
        double angle2 = d.angle2;


        double rab = sqrt((cx- mx)*(cx - mx) +(cy - my)*(cy - my));
        double resy = (expandOffset*(my-cy))/rab + my;
        double resx = (expandOffset*(mx-cx))/rab + mx;

        mx = resx;
        my = resy;


        QPainterPath path;
        double angle_1 = angle1;
        double angle_2 = angle2;
        while(angle_1>=3.14&&angle_2>=6.28) {
            angle_1 -= M_PI;
            angle_2 -= M_PI;
        }
        angle_1 = angle_1*180/M_PI;
        angle_2 = angle_2*180/M_PI;

        double angleStart ,anglePassed;
        angleStart = angle_1;
        if(angleStart>=180) angleStart = angleStart-360;
        anglePassed = angleStart-angle_2;
        if(angleStart<180) angleStart = -angleStart;
        if(anglePassed<-360) anglePassed = anglePassed+360;

        if(abs(anglePassed)<1) anglePassed = 360;

        double c_x = cx;
        double c_y = cy;
        double dl = sqrt(mx*mx+my*my);
        double ds = dl*ratio;

        double rx;
        double ry;
        if(qFuzzyIsNull(mx)) {
            rx = ds; ry = dl;
            angleStart += 90;
        } else {
            rx = dl; ry = ds;
        }

        double angle=angleStart;
        if(angle<0) angle=-angle;
        else if(angle>=0) angle = 360-angle;
        if(!qFuzzyCompare(abs(anglePassed),360)) angle *= ratio;
        double a=qDegreesToRadians(angle);
        double R=rx*ry/sqrt(pow(rx*sin(a),2)+pow(ry*cos(a),2)); //计算对应角度的半径
        double startXPos=c_x+R*cos(a);
        double startYPos=c_y+R*sin(a);
        path.moveTo(startXPos, startYPos);

        qDebug() << c_x << c_y << rx << ry << angleStart << anglePassed << angle;
        path.arcTo(c_x-rx, c_y-ry, 2*rx, 2*ry, angleStart, anglePassed);

        QVector<QPointF> ellipsepath;
        for(double i = 0; i <= 1; i += 0.003) {  // TODO: 步长随图片大小调整
            QPointF point = path.pointAtPercent(i);
            double x = point.x();
            double y = point.y();
            ellipsepath.append(point);
            currentPos=QPointF(x, y);
        }
        dxfPaths.append(ellipsepath);
//        dxfPathList.append(path);
    }

    for(auto d: dxfReader.dxfPolylines) {
        qDebug() << "polylines data:" << d.m << d.n << d.flags << d.number << d.elevation;

        QList<QVector3D> pointlist;
        QVector<QPointF> path;
        for(unsigned int i = 0; i < d.number; i++) {
            double x = dxfReader.dxfVertexs.at(vertexIndex).x;
            double y = dxfReader.dxfVertexs.at(vertexIndex).y;
            double z = dxfReader.dxfVertexs.at(vertexIndex).z;
            pointlist.append(QVector3D(x, y, z));
            vertexIndex++;
        }

        pointlist = expandPolygon(pointlist, expandOffset);
        foreach(QVector3D point, pointlist) {
            double x = point.x();
            double y = point.y();
            path.append(QPointF(x, y));
            currentPos = QPointF(x, y);
        }

        if(d.flags) {
            double x = pointlist.first().x();
            double y = pointlist.first().y();
            path.append(QPointF(x, y));
            currentPos = QPointF(x, y);
        }
        dxfPaths.append(path);
    }

    for(auto d: dxfReader.dxfVertexs) {
        qDebug() << "vertexs data:" << d.x << d.y << d.z << d.bulge;
    }

    for(auto d: dxfReader.dxfPoints) {
        qDebug() << "points data:" << d.x << d.y << d.z;
        QVector<QPointF> path;
        path.append(QPointF(d.x, d.y));
        dxfPaths.append(path);
        currentPos = QPointF(d.x, d.y);
    }

    for(auto d: dxfReader.dxfSplines) {
        qDebug() << "splines data:" << d.nFit << d.flags << d.degree << d.nKnots << d.nControl << d.tangentEndX << d.tangentEndY << d.tangentEndZ << d.tangentStartX << d.tangentStartY << d.tangentStartZ;
        std::vector<QVector2D> pointList;
        for(unsigned int i = 0; i < d.nControl; i++) {
            int x = dxfReader.dxfControlPoints.at(controlIndex).x;
            int y = dxfReader.dxfControlPoints.at(controlIndex).y;
            pointList.push_back(QVector2D(x, y));
            currentPos = QPointF(x, y);
            controlIndex++;
        }

        QList<QVector3D> templist;
        foreach(auto point, pointList) templist.append(point);
        templist = expandPolygon(templist, expandOffset);

        QVector<QVector2D> inputList;
        foreach(auto point, templist) inputList.append(point.toVector2D());
        inputList.push_front(inputList.first());
        inputList.push_back(inputList.back());
        std::vector<QVector2D> finalList(inputList.begin(), inputList.end());

        SplineHelper splineHelper(finalList, TypeCubicBSpline);
        auto splinePath = splineHelper.getSplinePath();

        dxfPaths.append(splinePath);
    }

    for(auto d: dxfReader.dxfControlPoints) {
        qDebug() << "control points data:" << d.w << d.x << d.y << d.z;
    }

    for(auto d: dxfReader.dxfXLines) {
        qDebug() << "XLines data:" << d.bx << d.by << d.bz << d.dx << d.dy << d.dz;
    }

    for(auto d: dxfReader.dxfRays) {
        qDebug() << "rays data:" << d.bx << d.by << d.bz << d.dx << d.dy << d.dz;
    }

    for(auto d: dxfReader.dxfFitPoints) {
        qDebug() << "fit points data:" << d.x << d.y << d.z;
    }

    for(auto d: dxfReader.dxfHatchs) {
        qDebug() << "hatchs data:" << d.angle << d.scale << d.solid << d.originX << d.originY << d.pattern.c_str() << d.numLoops;
    }

    for(auto d: dxfReader.dxfHatchLoops) {
        qDebug() << "hatchLoops data:" << d.numEdges;
    }

    for(auto d: dxfReader.dxfHatchEdges) {
        qDebug() << "hatchEdges data:" << d.cx << d.cy << d.mx << d.my << d.x1 << d.y1 << d.x2 << d.y2 << d.ccw << d.nFit << d.ratio << d.angle1 << d.angle2 << d.degree << d.nKnots << d.radius << d.defined << d.weights << d.nControl << d.periodic << d.rational << d.vertices << d.fitPoints << d.endTangentX << d.endTangentY << d.endTangentY << d.controlPoints << d.startTangentX << d.startTangentY;
    }

    return true;
}

void DxfHelper::matchDXFSize()
{
    double minx =  __DBL_MAX__;
    double maxx =  __DBL_MIN__;
    double miny =  __DBL_MAX__;
    double maxy =  __DBL_MIN__;
    foreach (QVector<QPointF> path, dxfPaths) {
        for(int i = 0; i < path.length(); i++) {
            QPointF point = path.at(i);
            double x = point.x();
            double y = point.y();
            if(x<minx) minx = x;
            if(x>maxx) maxx = x;
            if(y<miny) miny = y;
            if(y>maxy) maxy = y;
        }
    }
    int width = maxx - minx;
    int height = maxy - miny;
    imageSize = QSize(width, height);
    dxfBorderList.clear();
    dxfBorderList.append(minx);
    dxfBorderList.append(miny);
    dxfBorderList.append(maxx);
    dxfBorderList.append(maxy);
}

QImage DxfHelper::generateDXFImage()
{
    matchDXFSize();
    double minx = dxfBorderList.at(0);
    double miny = dxfBorderList.at(1);
    int penwidth = imageSize.width()/400;
    int border = penwidth;
    QImage image((imageSize.width()+2*border), (imageSize.height()+2*border), QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter p(&image);
    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 抗锯齿和使用平滑转换算法
    QPen pen;
    if(penwidth<1) penwidth = 1;
    pen.setWidth(penwidth);
    pen.setColor(Qt::black);
    p.setPen(pen);
    QPainterPath painterpath;
    foreach (QVector<QPointF> path, dxfPaths) {
        for(int i = 0; i < path.length(); i++) {
            double x = path.at(i).x()-minx;
            double y = path.at(i).y()-miny;
            y = imageSize.height()-y;
            x += border;
            y += border;
            QPointF point(x, y);
            if(i == 0)  painterpath.moveTo(point);
            else painterpath.lineTo(point);
        }
//            dxfPathList.append(painterpath);
    }
    qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]\t"<< "dxf path length:" <<dxfPaths.length();
    p.drawPath(painterpath);
    p.end();
    return image;
}

QList<double> DxfHelper::getDxfBorderList() const
{
    return dxfBorderList;
}

QSize DxfHelper::getImageSize() const
{
    return imageSize;
}

QList<QPainterPath> DxfHelper::getDxfPathList() const
{
    return dxfPathList;
}

QVector<QVector<QPointF> > DxfHelper::getDxfPaths() const
{
    return dxfPaths;
}

QList<DXFLine> DxfHelper::getDxfLineList() const
{
    return dxfLineList;
}

QList<DXFRect> DxfHelper::getDxfRectList() const
{
    return dxfRectList;
}

QList<DXFArc> DxfHelper::getDxfArcList() const
{
    return dxfArcList;
}

QList<DXFCircle> DxfHelper::getDxfCircleList() const
{
    return dxfCircleList;
}

QList<DXFEllipse> DxfHelper::getDxfEllipseList() const
{
    return dxfEllipseList;
}

QList<DXFPolyline> DxfHelper::getDxfPolylineList() const
{
    return dxfPolylineList;
}

QList<DXFSpline> DxfHelper::getDxfSplineList() const
{
    return dxfSplineList;
}

void DxfHelper::setExpandOffset(double value)
{
    expandOffset = value;
}
