#include "processingdrawingnode.h"

ProcessingDrawingNode::ProcessingDrawingNode()
{
    m_processingType=ProcessingType::ProcessingDrawingNode;
    ProcessingNode::processingTypeTable[m_processingType]="Drawing";

}

void ProcessingDrawingNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    doProcess();
}

void ProcessingDrawingNode::doProcess()
{
    m_output=m_input;


    ProcessingNode::doProcess();

}
