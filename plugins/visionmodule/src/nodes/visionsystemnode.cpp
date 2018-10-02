#include "roinode.h"
#include "visionsystemnode.h"

VisionSystemNode::VisionSystemNode()
{


    m_type=Type::VisionSystemNode;




}

VisionSystemNode::~VisionSystemNode()
{

    for (int var = 0; var < m_ROINodes.length(); ++var) {
        ROINode* roinode= qobject_cast<ROINode*>(m_ROINodes.at(var));

        roinode->deleteLater();
    }


}

QQmlComponent *VisionSystemNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:/components/nodes/VisionSystemNode.qml"));
    return delegate.get();
}


void VisionSystemNode::readNode(QJsonObject roiobject){

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


    }

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

    m_frameSourcePort= new FlowNodePort(this,qan::PortItem::Type::In,"frameSource");
    m_processFramePort= new FlowNodePort(this,qan::PortItem::Type::In,"processFrame");


    m_frameProcessedPort= new FlowNodePort(this,qan::PortItem::Type::Out,"frameProcessed");

    FlowNode::DeSerialize(json);

    QJsonArray roisArray = json["rois"].toArray();

    for (int i = 0; i < roisArray.count(); ++i) {
        QJsonObject roiObject=roisArray[i].toObject();
        if(roiObject["type"]=="ROINode"){
            readNode(roiObject);
        }
    }



}
