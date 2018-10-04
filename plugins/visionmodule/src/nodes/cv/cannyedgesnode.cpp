#include "cannyedgesnode.h"

using namespace cv;
using namespace std;

CannyEdgesNode::CannyEdgesNode()
{

    m_type=Type::CannyEdgesNode;

}

QQmlComponent *CannyEdgesNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/CannyEdgesNodeItem.qml"));
    return qan_FlowNode_delegate.get();
}


void CannyEdgesNode::setInput(QMat *input)
{
    ProcessingNode::setInput(input);
    process();
}

void joinEdges(cv::Mat input){
    int width=input.cols;
    int height=input.rows;
    const int dx[] = {  1, 1, 0, -1, -1, -1, 0, +1, 1 };
    const int dy[] = {  0, 1, 1,  1,  0, -1,-1, -1, 0 };
    const int d2x[] = {  2, 2, 2, 1, 0,-1,-2,-2,-2,-2,-2,-1, 0, 1, 2, 2 };
    const int d2y[] = {  0, 1, 2, 2, 2, 2, 2, 1, 0,-1,-2,-2,-2,-2,-2,-1 };
    const int d3x[] = {  3,3,3,3,2,1,0,-1,-2,-3,-3,-3,-3,-3,-3,-3,-2,-1,0,1,2,3,3,3 };
    const int d3y[] = {  0,1,2,3,3,3,3,3,3,3,2,1,0,-1,-2,-3,-3,-3,-3,-3,-3,-3,-2,-1 };

    for(int i=0;i<input.rows;i++)
        for(int j=0;j<input.cols;j++){

            uchar one_step,two_step,three_step;
            std::vector<int> connection;
            if(input.at<uchar>(i, j)!=0){
                for (int dir = 0; dir < 8; ++dir) {
                    int tmp_x = j + dx[dir];
                    int tmp_y = i + dy[dir];
                    if(tmp_x < 0 || tmp_x >= width || tmp_y < 0 || tmp_y >= height ) one_step=0;//treat outside image as 0
                    else one_step=input.at<uchar>(tmp_y, tmp_x);

                    if(one_step!=0) connection.push_back(dir);
                }

                if(connection.size()<3 && connection.size()!=0) {
                    int direction1=connection.front();
                    int direction2=connection.back();
                    if(direction2-direction1<=1||direction2-direction1==7){
                        int start_direction=(direction2+2)*3;
                        int end_direction=(direction1+6)*3;
                        for(int dir2=start_direction;dir2<end_direction;dir2++){//dir2 is between 6~39
                            int tmp_1x = j + dx [dir2%24/3];
                            int tmp_1y = i + dy [dir2%24/3];
                            int tmp_2x = j + d2x[dir2%24*2/3];
                            int tmp_2y = i + d2y[dir2%24*2/3];
                            int tmp_3x = j + d3x[dir2%24];
                            int tmp_3y = i + d3y[dir2%24];
                            if(tmp_2x < 0 || tmp_2x >= width || tmp_2y < 0 || tmp_2y >= height ) two_step=0;//treat outside image as 0
                            else two_step=input.at<uchar>(tmp_2y, tmp_2x);
                            if(tmp_3x < 0 || tmp_3x >= width || tmp_3y < 0 || tmp_3y >= height ) three_step=0;//treat outside image as 0
                            else three_step=input.at<uchar>(tmp_3y, tmp_3x);
                            if (two_step!=0){
                                input.at<uchar>(tmp_1y, tmp_1x)=255;
                                break;
                            }else if (three_step!=0) {
                                input.at<uchar>(tmp_1y, tmp_1x)=255;
                                input.at<uchar>(tmp_2y, tmp_2x)=255;
                                break;

                            }
                        }
                    }
                }
            }
        }
}



void CannyEdgesNode::doProcess()
{
    if(!m_input){
        return;
    }

    if(m_showOriginal){

        m_input->cvMat()->copyTo(*output()->cvMat());

    }
    else{
        cv::GaussianBlur(*m_input->cvMat(), *m_output->cvMat(), cv::Size(7, 7), 0);
        cv::Canny(*m_output->cvMat(), *m_output->cvMat(),this->thresholdlow(), this->thresholdhigh(),5,true );

//        m_cannyContours.clear();
//        vector<Vec4i> hierarchy;
//        findContours(*m_output->cvMat(), m_cannyContours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0,0) );


    }


    emit outputChanged(m_output);



    ProcessingNode::doProcess();

}

void CannyEdgesNode::DeSerialize(QJsonObject &json)
{


    ProcessingNode::DeSerialize(json);
}
