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

void VisionSystemNode::setFrameBufferSource(QVariant frameBufferSource)
{

    m_frameBufferSource = frameBufferSource;
    emit frameBufferSourceChanged(m_frameBufferSource);

}


//void VisionSystemNode::readROINode(QJsonObject roiobject){

//    if(!m_visionGraphView){
//        return;
//    }
//    auto newnode=m_visionGraphView->getGraph()->insertNode<ROINode>(nullptr);

//    ROINode* node=dynamic_cast<ROINode*>(newnode);
//    if(node){
//        //node->setParent(this);
//        node->DeSerialize(roiobject);
//        m_ROINodes.append(node);

//        QObject::connect(node,&ROINode::roiProcessingDoneChanged,this,[this](){
//            this->setFrameProcessed(true);
//        }
//        );

////        connect(node,&FlowNode::removeNode,[&](FlowNode* nodetoremove){
////            int nodepos=m_ROINodes.indexOf( static_cast<ROINode*>(nodetoremove));
////            if(nodepos>0){
////                ROINode* noderemoved=m_ROINodes.at(nodepos);
////                if(noderemoved){
////                    m_ROINodes.removeAll(noderemoved);
////                    this->m_visionGraphView->getGraph()->removeNode(noderemoved);

////                }

////            }
////        });


//    }

//}


void VisionSystemNode::Serialize(QJsonObject &json)
{
    FlowNode::Serialize(json);


}

void VisionSystemNode::DeSerialize(QJsonObject &json)
{


    FlowNode::DeSerialize(json);

}
