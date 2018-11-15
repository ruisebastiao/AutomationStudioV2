#include "processingdrawingnode.h"

ProcessingDrawingNode::ProcessingDrawingNode()
{

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
