#include "roinode.h"
#include "visionsystemnode.h"

VisionSystemNode::VisionSystemNode()
{


    m_type=Type::VisionSystemNode;




}

VisionSystemNode::~VisionSystemNode()
{



}

QQmlComponent *VisionSystemNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/VisionSystemNodeItem.qml"));
    return delegate.get();
}


void VisionSystemNode::readROINode(QJsonObject roiobject){

    if(!m_visionGraphView){
        return;
    }
    auto newnode=m_visionGraphView->getGraph()->insertNode<ROINode>(nullptr);

    ROINode* node=dynamic_cast<ROINode*>(newnode);
    if(node){
        //node->setParent(this);
        node->DeSerialize(roiobject);
        m_ROINodes.append(node);

        //node->bindSourceProperty(this,"sourceFrame","input");
        QObject::connect(node,&ROINode::roiProcessingDoneChanged,this,[this](){
            this->setFrameProcessed(true);
        }
        );

        connect(node,&FlowNode::removeNode,[&](FlowNode* nodetoremove){
            int nodepos=m_ROINodes.indexOf( static_cast<ROINode*>(nodetoremove));
            if(nodepos>0){
                ROINode* noderemoved=m_ROINodes.at(nodepos);
                if(noderemoved){
                    m_ROINodes.removeAll(noderemoved);
                    this->m_visionGraphView->getGraph()->removeNode(noderemoved);

                }

            }
        });


    }

}

void VisionSystemNode::initializePorts()
{
    m_frameSourcePort= new FlowNodePort(this,qan::PortItem::Type::In,"frameSource");
    m_processFramePort= new FlowNodePort(this,qan::PortItem::Type::In,"processFrame");
    m_inPorts.append(m_frameSourcePort);
    m_inPorts.append(m_processFramePort);

    m_frameProcessedPort= new FlowNodePort(this,qan::PortItem::Type::Out,"frameProcessed");
    m_outPorts.append(m_frameProcessedPort);
    FlowNode::initializePorts();

}

void VisionSystemNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);


    QJsonArray nodesArrayList;

    foreach (FlowNode* node, m_ROINodes) {
        QJsonObject nodeobject;
        node->Serialize(nodeobject);
        nodesArrayList.append(nodeobject);


    }

    json["rois"]=nodesArrayList;

}

void VisionSystemNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);

    QJsonArray roisArray = json["rois"].toArray();

    for (int i = 0; i < roisArray.count(); ++i) {
        QJsonObject roiObject=roisArray[i].toObject();
        if(roiObject["type"]=="ROINode"){
            readROINode(roiObject);
        }
    }



}
