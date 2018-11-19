#include "processinggeometricnode.h"

using namespace cv;
using namespace std;


ProcessingGeometricNode::ProcessingGeometricNode()
{
    m_processingType=ProcessingType::ProcessingGeometricNode;
}


QQmlComponent *ProcessingGeometricNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingGeometricNode.qml"));
    return delegate.get();

}



void ProcessingGeometricNode::setInput(QMat *input)
{

}

void ProcessingGeometricNode::doProcess()
{

    qDebug() << "typeName for first :" << m_input1.typeName();

    vector<RotatedRect> rotatedrect_obj = m_input1.value<vector<RotatedRect>>();

    vector<Rect> rect_obj = m_input1.value<vector<Rect>>();

    //
    if(rect_obj.size()>0){

    }

}

void ProcessingGeometricNode::DeSerialize(QJsonObject &json)
{

    m_input1Port= new FlowNodePort(this,qan::PortItem::Type::In,"input1");
    m_input2Port= new FlowNodePort(this,qan::PortItem::Type::In,"input2");

    m_inPorts.append(m_input1Port);
    m_inPorts.append(m_input2Port);


    ProcessingNode::DeSerialize(json);

    m_inputPort->setHidden(true);


    m_outputPort->setHidden(true);

    if(m_processPort->portLabel()==""){
        m_processPort->setPortLabel("process");
    }

    if(m_input1Port->portLabel()==""){
        m_input1Port->setPortLabel("Input 1");
    }
    if(m_input2Port->portLabel()==""){
        m_input2Port->setPortLabel("Input 2");
    }

//    if(m_input1Port->portLabel()==""){
//        m_input1Port->setPortLabel("Logical Output");
//    }

}
