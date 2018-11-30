#ifndef PROCESSINGENCLOSINGNODE_H
#define PROCESSINGENCLOSINGNODE_H

#include "processingnode.h"



class ProcessingEnclosingNode : public ProcessingNode
{
    Q_OBJECT

    Q_PROPERTY(QVariant contours READ contours WRITE setContours NOTIFY contoursChanged REVISION 30)

    Q_PROPERTY(QVariant enclosingShapes READ enclosingShapes WRITE setEnclosingShapes NOTIFY enclosingShapesChanged REVISION 31)

    Q_PROPERTY(EnclosingType enclosingType READ enclosingType WRITE setEnclosingType NOTIFY enclosingTypeChanged USER("serialize"))



public:

    enum EnclosingType {
        RotatedRectEnclosing=0,
        BoundingRectEnclosing
    };
    Q_ENUM(EnclosingType )

    ProcessingEnclosingNode();

    // ProcessingNode interface
    static QQmlComponent *delegate(QQmlEngine &engine) noexcept;
public slots:
    void setInput(QVariant input) override;

    void setContours(QVariant contours)
    {

        m_contours = contours;
        emit contoursChanged(m_contours);
    }


    void setEnclosingShapes(QVariant enclosingShapes)
    {


        m_enclosingShapes = enclosingShapes;
        emit enclosingShapesChanged(m_enclosingShapes);
    }


    void setEnclosingType(EnclosingType enclosingType)
    {
        if (m_enclosingType == enclosingType)
            return;

        m_enclosingType = enclosingType;
        emit enclosingTypeChanged(m_enclosingType);
        if(configsLoaded() ){
            setProcess(true);
        }
    }

protected:
    void doProcess() override;

    // JsonSerializable interface
public:
    void DeSerialize(QJsonObject &json) override;



    QVariant enclosingShapes() const
    {
        return m_enclosingShapes;
    }


    QVariant contours() const
    {
        return m_contours;
    }

    EnclosingType enclosingType() const
    {
        return m_enclosingType;
    }

signals:
    void contoursChanged(QVariant contours);

    void enclosingShapesChanged(QVariant enclosingShapes);

    void enclosingTypeChanged(EnclosingType enclosingType);

private:

    QVariant m_contours=QVariant::fromValue(std::vector<std::vector<cv::Point>>());
    QVariant m_enclosingShapes=QVariant();
    EnclosingType m_enclosingType=RotatedRectEnclosing;

    // FlowNode interface
public:

};

#endif // PROCESSINGENCLOSINGNODE_H
