#include "processingcontoursnode.h"

using namespace cv;

using namespace std;

ProcessingContoursNode::ProcessingContoursNode()
{
    m_processingType=ProcessingType::ProcessingContoursNode;



}

QQmlComponent *ProcessingContoursNode::delegate(QQmlEngine &engine) noexcept
{
    static UniqueQQmlComponentPtr   delegate;
    if ( !delegate )
        delegate = UniqueQQmlComponentPtr(new QQmlComponent(&engine, "qrc:///Nodes/Cv/ProcessingContoursNodeItem.qml"));
    return delegate.get();

}

void ProcessingContoursNode::setInput(QVariant input)
{
//    if(m_input){
//        m_input->cvMat()->copyTo(*m_originalInput->cvMat());
//    }

    ProcessingNode::setInput(input);
}

void ProcessingContoursNode::doProcess()
{

    // TODO
    // value colde be read once at variant change
    QMat* in=m_input.value<QMat*>();



    if(!in || in->cvMat()->empty()){
        return;
    }

    std::vector<std::vector<cv::Point>> fileredcontours=m_filteredContours.value<std::vector<std::vector<cv::Point>>>();

    vector<vector<Point> > contours;

    //    vector<vector<Point> > contours_box;

    vector<Vec4i> hierarchy;

    m_filteredContours.clear();


    QMat* v_output=m_output.value<QMat*>();

    // TODO during real time processing this should be removed, only needed if in config mode
    m_originalInput->cvMat()->copyTo(*v_output->cvMat());




    //    Canny( input, preprocessed, threshold(), threshold()*2, 3 );
    findContours( *in->cvMat(), contours, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0, 0) );



    vector<vector<Vec4i>> defects;
    vector<vector<Point>> hullsP;

    //   drawContours(drawing, contours, -1, cv::Scalar(0,255,0), 1);

    setTotalContours(contours.size());

    for(int i = 0; i < contours.size(); i++)
    {

        vector<Point> contour=contours[i];
        vector<Point> approx_contour;
        vector<Point >hullP;
        vector<int> hullI;
        vector<Vec4i> defect;



        double contourlength=arcLength(contour,true);


        bool length_condition=(minCountourLength()==0 && maxCountourLength()==0) || contourlength>minCountourLength() && contourlength<maxCountourLength();

        if(length_condition==false){
            continue;
        }

        double contourarea=contourArea(contour);

        bool area_condition=(minCountourArea()==0 && maxCountourArea()==0) ||  (contourarea>minCountourArea() && contourarea<maxCountourArea());

        if(area_condition==false){
            continue;
        }


        //        approxPolyDP(contour,contour,contourlength*0.02,true);
        approxPolyDP(contour,approx_contour,3,true);
        //        Rect contour_rect=boundingRect(contour);
        RotatedRect minrect=minAreaRect(approx_contour);


        bool width_condition= (minCountourWidth()==0 && maxCountourWidth()==0) || (minrect.size.width>minCountourWidth() && minrect.size.width<maxCountourWidth());
        bool height_condition= (minCountourHeight()==0 && maxCountourHeight()==0) || (minrect.size.height>minCountourHeight() && minrect.size.height<maxCountourHeight());

        //        convexHull(Mat(contour, hull[i], False);




        if(length_condition && width_condition && height_condition){
            //            cv::Point2f vertices[4];
            //             minrect.points(vertices);
            //             for(int i = 0; i < 4; ++i)
            //               cv::line(drawing, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 0, 255), 1, CV_AA);


            fileredcontours.push_back(contour);
        }

    }
    setTotalFilteredContours(fileredcontours.size());


    drawContours(*m_drawSource->cvMat(), fileredcontours, -1, cv::Scalar(0,255,0), 1);

    drawContours(*v_output->cvMat(), fileredcontours, -1, cv::Scalar(0,255,0), 1);

    m_output=QVariant::fromValue(v_output);

    LOG_INFO()<<"Total contours:"<<m_totalContours;
    LOG_INFO()<<"Fildtered contours:"<<fileredcontours.size();

    emit filteredContoursChanged(QVariant::fromValue<std::vector<std::vector<cv::Point>>>(fileredcontours));

//    m_output=QVariant::fromValue(m_drawSource);

    ProcessingNode::doProcess();
}

void ProcessingContoursNode::DeSerialize(QJsonObject &json)
{

    ProcessingNode::DeSerialize(json);


    FlowNodePort* port=getPortFromKey("output");
    if(port){
        port->setHidden(true);
    }
}

