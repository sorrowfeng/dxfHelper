#include "dxfreader.h"
#include <QDebug>

DxfReader::DxfReader(const QString &fileName, QObject *parent)
    : QObject(parent)
    , fileName(fileName)
{    
    // 读取 dxf 文件
    DL_Dxf *dxf = new DL_Dxf;
    if (!dxf->in(fileName.toStdString().c_str(), this)) { // if file open failed
        std::cerr << fileName.toStdString() << " could not be opened.\n";
        return;
    }
    delete dxf;
    dxf = nullptr;
}

void DxfReader::addText(const DL_TextData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfText << data;
}

void DxfReader::addLine(const DL_LineData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfLines << data;
}

void DxfReader::addArc(const DL_ArcData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfArcs << data;
}

void DxfReader::addCircle(const DL_CircleData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfCircles << data;
}

void DxfReader::addEllipse(const DL_EllipseData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfEllipses << data;
}

void DxfReader::addPolyline(const DL_PolylineData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfPolylines << data;
}

void DxfReader::addPoint(const DL_PointData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfPoints << data;
}

void DxfReader::addSpline(const DL_SplineData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfSplines << data;
}

void DxfReader::addBlock(const DL_BlockData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfBlocks << data;
}

void DxfReader::endBlock()
{

}

void DxfReader::addLayer(const DL_LayerData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfLayers << data;
}

void DxfReader::addLinetype(const DL_LinetypeData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfLinetypes << data;
}

void DxfReader::addLinetypeDash(double length)
{

}

void DxfReader::addXLine(const DL_XLineData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfXLines << data;
}

void DxfReader::addRay(const DL_RayData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfRays << data;
}

void DxfReader::addVertex(const DL_VertexData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfVertexs << data;
}

void DxfReader::addControlPoint(const DL_ControlPointData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfControlPoints << data;
}

void DxfReader::addFitPoint(const DL_FitPointData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfFitPoints << data;
}

void DxfReader::addKnot(const DL_KnotData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addInsert(const DL_InsertData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addSolid(const DL_SolidData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addTrace(const DL_TraceData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addTextStyle(const DL_StyleData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addMTextChunk(const std::string &text)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addMText(const DL_MTextData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addArcAlignedText(const DL_ArcAlignedTextData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addAttribute(const DL_AttributeData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimAlign(const DL_DimensionData &data, const DL_DimAlignedData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimLinear(const DL_DimensionData &data, const DL_DimLinearData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimRadial(const DL_DimensionData &data, const DL_DimRadialData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimDiametric(const DL_DimensionData &data, const DL_DimDiametricData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimAngular(const DL_DimensionData &data, const DL_DimAngularData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimAngular3P(const DL_DimensionData &data, const DL_DimAngular3PData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDimOrdinate(const DL_DimensionData &data, const DL_DimOrdinateData &edata)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addLeader(const DL_LeaderData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addLeaderVertex(const DL_LeaderVertexData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addHatch(const DL_HatchData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfHatchs << data;
}

void DxfReader::addHatchLoop(const DL_HatchLoopData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfHatchLoops << data;
}

void DxfReader::addHatchEdge(const DL_HatchEdgeData &data)
{
    qDebug() << Q_FUNC_INFO;
    dxfHatchEdges << data;
}

void DxfReader::addImage(const DL_ImageData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::linkImage(const DL_ImageDefData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addXRecord(const std::string &handle)
{

}

void DxfReader::addXRecordString(int code, const std::string &value)
{

}

void DxfReader::addXRecordReal(int code, double value)
{

}

void DxfReader::addXRecordInt(int code, int value)
{

}

void DxfReader::addXRecordBool(int code, bool value)
{

}

void DxfReader::addXDataApp(const std::string &appId)
{

}

void DxfReader::addXDataString(int code, const std::string &value)
{

}

void DxfReader::addXDataReal(int code, double value)
{

}

void DxfReader::addXDataInt(int code, int value)
{

}

void DxfReader::addDictionary(const DL_DictionaryData &data)
{
//    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addDictionaryEntry(const DL_DictionaryEntryData &data)
{
//    qDebug() << Q_FUNC_INFO;
}

void DxfReader::setVariableVector(const std::string &key, double v1, double v2, double v3, int code)
{

}

void DxfReader::setVariableString(const std::string &key, const std::string &value, int code)
{

}

void DxfReader::setVariableInt(const std::string &key, int value, int code)
{

}

void DxfReader::setVariableDouble(const std::string &key, double value, int code)
{

}

void DxfReader::add3dFace(const DL_3dFaceData &data)
{
    qDebug() << Q_FUNC_INFO;
}

void DxfReader::addComment(const std::string &comment)
{

}

void DxfReader::endSequence()
{
    qDebug() << Q_FUNC_INFO;
}
