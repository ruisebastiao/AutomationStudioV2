#include "processingdrawingnode.h"

ProcessingDrawingNode::ProcessingDrawingNode()
{
    m_processingType=ProcessingType::ProcessingDrawingNode;


}

void ProcessingDrawingNode::setInput(QVariant input)
{
    ProcessingNode::setInput(input);
    doProcess();
}

void ProcessingDrawingNode::doProcess()
{
    m_output=m_input;


    ProcessingNode::doProcess();

}
