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


void ProcessingNode::doProcess()
{


    emit outputChanged(m_output);



    setProcessingDone(true);



}

void ProcessingNode::setInput(QVariant input)
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



