#include "processingnode.h"
#include <QtConcurrent>

using namespace cv;

ProcessingNode::ProcessingNode()
{
    m_type=Type::ProcessingNode;


    //    setApplyMask(false);
    //    setDrawOnSource(false);
}

ProcessingNode::~ProcessingNode()
{

}



void ProcessingNode::setProcess(QVariant process)
{

    emit processChanged(process);

    //    if(!m_input || m_input->cvMat()->empty())
    //        return;

    if(process.value<bool>()){


        if(configsLoaded()==false){
            return;
        }


        this->doProcess();


    }
}

void ProcessingNode::reProcess()
{

    this->doProcess();
}

QString ProcessingNode::name() const
{


    QVariantList proctypes=getProcessingTypes();

    QVariantList::const_iterator procType = std::find_if(proctypes.begin(),proctypes.end(),
                                                         [&](const QVariant&x) {

        QVariantMap value=x.value<QVariantMap>();
        QString val1=value.keys().at(0);
        QString val2=QVariant::fromValue(m_processingType).value<QString>();

        return val1==val2;
    });

    if(procType ==proctypes.end()){
        // finded
        return "?";
    }

    QVariantMap map=(*procType).value<QVariantMap>();
    QString retval=map.value(QVariant::fromValue(m_processingType ).value<QString>()).toString();
    return retval;

    //    return FlowNode::name();
}

void ProcessingNode::initializeNode(int id)
{
    FlowNode::initializeNode(id);

    FlowNodePort* port=getPortFromKey("maskInput");
    if(port){
        port->setHidden(true);
    }

    port=getPortFromKey("drawSource");
    if(port){
        port->setHidden(true);
    }
}

void ProcessingNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);
}


void ProcessingNode::doProcess()
{


    emit outputChanged(m_output);



    setProcessingDone(true);



}

void ProcessingNode::setInput(QVariant input)
{


    if(disabled().value<bool>()){
        return;
    }

    m_input = input;


    emit inputChanged(m_input);


}

void ProcessingNode::DeSerialize(QJsonObject &json)
{
    m_deserealizing=true;
    FlowNode::DeSerialize(json);





    setApplyMask(m_applyMask);
    setDrawOnSource(m_drawOnSource);
    setDrawOnSourcePortVisible(m_drawOnSourcePortVisible);
    FlowNodePort* port=getPortFromKey("drawSource");

    QObject::connect(port->getPortItem(), &qan::PortItem::inEdgeAdded, this, [this](qan::EdgeItem& inEdgeItem){

        if(!m_drawOnSourcePortVisible){
            SelectableEdge* selectededge= dynamic_cast<SelectableEdge*>(inEdgeItem.getEdge());
            selectededge->setIsHidden(true);
        }

    });


    m_deserealizing=false;

}



