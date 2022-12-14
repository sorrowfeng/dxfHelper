#ifndef DXFREADER_H
#define DXFREADER_H

#include <QObject>
#include "dxflib/dl_dxf.h"
#include "dxflib/dl_creationadapter.h"

class DxfReader : public QObject, public DL_CreationAdapter
{
    Q_OBJECT
public:
    struct DxfText {
        QString Text;
    };
    explicit DxfReader(const QString &fileName, QObject *parent = nullptr);


    virtual void addText(const DL_TextData& data) override;
    virtual void addLine(const DL_LineData& data) override;
    virtual void addArc(const DL_ArcData& data) override;
    virtual void addCircle(const DL_CircleData& data) override;
    virtual void addEllipse(const DL_EllipseData& data) override;
    virtual void addPolyline(const DL_PolylineData& data) override;
    virtual void addPoint(const DL_PointData& data) override;
    virtual void addSpline(const DL_SplineData& data) override;
    virtual void addBlock(const DL_BlockData& data) override;
    virtual void endBlock() override;

    virtual void addLayer(const DL_LayerData& data) override;
    virtual void addLinetype(const DL_LinetypeData& data) override;
    virtual void addLinetypeDash(double length) override;
    virtual void addXLine(const DL_XLineData& data) override;
    virtual void addRay(const DL_RayData& data) override;
    virtual void addVertex(const DL_VertexData& data) override;
    virtual void addControlPoint(const DL_ControlPointData& data) override;
    virtual void addFitPoint(const DL_FitPointData& data) override;
    virtual void addKnot(const DL_KnotData& data) override;
    virtual void addInsert(const DL_InsertData& data) override;
    virtual void addSolid(const DL_SolidData& data) override;
    virtual void addTrace(const DL_TraceData& data) override;
    virtual void addTextStyle(const DL_StyleData& data) override;
    virtual void addMTextChunk(const std::string& text) override;
    virtual void addMText(const DL_MTextData& data) override;
    virtual void addArcAlignedText(const DL_ArcAlignedTextData& data) override;
    virtual void addAttribute(const DL_AttributeData& data) override;
    virtual void addDimAlign(const DL_DimensionData& data, const DL_DimAlignedData& edata) override;
    virtual void addDimLinear(const DL_DimensionData& data, const DL_DimLinearData& edata) override;
    virtual void addDimRadial(const DL_DimensionData& data, const DL_DimRadialData& edata) override;
    virtual void addDimDiametric(const DL_DimensionData& data, const DL_DimDiametricData& edata) override;
    virtual void addDimAngular(const DL_DimensionData& data, const DL_DimAngularData& edata) override;
    virtual void addDimAngular3P(const DL_DimensionData& data, const DL_DimAngular3PData& edata) override;
    virtual void addDimOrdinate(const DL_DimensionData& data, const DL_DimOrdinateData& edata) override;
    virtual void addLeader(const DL_LeaderData &data) override;
    virtual void addLeaderVertex(const DL_LeaderVertexData &data) override;
    virtual void addHatch(const DL_HatchData& data) override;
    virtual void addHatchLoop(const DL_HatchLoopData& data) override;
    virtual void addHatchEdge(const DL_HatchEdgeData& data) override;
    virtual void addImage(const DL_ImageData &data) override;
    virtual void linkImage(const DL_ImageDefData &data) override;

    virtual void addXRecord(const std::string& handle) override;
    virtual void addXRecordString(int code, const std::string& value) override;
    virtual void addXRecordReal(int code, double value) override;
    virtual void addXRecordInt(int code, int value) override;
    virtual void addXRecordBool(int code, bool value) override;

    virtual void addXDataApp(const std::string& appId) override;
    virtual void addXDataString(int code, const std::string& value) override;
    virtual void addXDataReal(int code, double value) override;
    virtual void addXDataInt(int code, int value) override;

    virtual void addDictionary(const DL_DictionaryData& data) override;
    virtual void addDictionaryEntry(const DL_DictionaryEntryData& data) override;

    virtual void setVariableVector(const std::string& key, double v1, double v2, double v3, int code) override;
    virtual void setVariableString(const std::string& key, const std::string& value, int code) override;
    virtual void setVariableInt(const std::string& key, int value, int code) override;
    virtual void setVariableDouble(const std::string& key, double value, int code) override;

    virtual void add3dFace(const DL_3dFaceData &data) override;
    virtual void addComment(const std::string &comment) override;
    virtual void endSequence() override;


    QList<DL_LineData> dxfLines;
    QList<DL_TextData> dxfText;
    QList<DL_ArcData> dxfArcs;
    QList<DL_CircleData> dxfCircles;
    QList<DL_EllipseData> dxfEllipses;
    QList<DL_PolylineData> dxfPolylines;
    QList<DL_PointData> dxfPoints;
    QList<DL_SplineData> dxfSplines;
    QList<DL_BlockData> dxfBlocks;
    QList<DL_VertexData> dxfVertexs;
    QList<DL_LayerData> dxfLayers;
    QList<DL_LinetypeData> dxfLinetypes;
    QList<DL_XLineData> dxfXLines;
    QList<DL_RayData> dxfRays;
    QList<DL_ControlPointData> dxfControlPoints;
    QList<DL_FitPointData> dxfFitPoints;
    QList<DL_HatchData> dxfHatchs;
    QList<DL_HatchLoopData> dxfHatchLoops;
    QList<DL_HatchEdgeData> dxfHatchEdges;

private:
    QString fileName;

};

#endif // DXFREADER_H
