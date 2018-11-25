#include "processingnode.h"
#include <QtConcurrent>

using namespace cv;

map<ProcessingNode::ProcessingType,string> ProcessingNode::processingTypeTable;

ProcessingNode::ProcessingNode()
{
    m_type=Type::ProcessingNode;


//    setApplyMask(false);
//    setDrawOnSource(false);
}

ProcessingNode::~ProcessingNode()
{

}



void ProcessingNode::setProcess(bool process)
{

    emit processChanged(process);

    //    if(!m_input || m_input->cvMat()->empty())
    //        return;

    if(process){


        if(configsLoaded()==false){
            return;
        }

        QtConcurrent::run([this](){
            QMutexLocker ml(&mMutex);

            this->doProcess();


        });
    }
}

void ProcessingNode::reProcess()
{

    this->doProcess();
}

QString ProcessingNode::name() const
{
    if(m_name==""){
        return QString::fromStdString(processingTypeTable[m_processingType]);
    }

    return FlowNode::name();
}


void ProcessingNode::setOriginalFrame(QMat *originalFrame)
{
    m_originalFrame=originalFrame;
}


void ProcessingNode::doProcess()
{


    emit outputChanged(m_output);



    setProcessingDone(true);



}

void ProcessingNode::setInput(QMat *input)
{

    m_input = input;


    emit inputChanged(m_input);


}

void ProcessingNode::DeSerialize(QJsonObject &json)
{

    FlowNode::DeSerialize(json);




    setApplyMask(m_applyMask);
    setDrawOnSource(m_drawOnSource);



}



