#include "postprocessingcontours.h"
#include "Logger.h"

using namespace cv;
using namespace std;

PostProcessingContours::PostProcessingContours()
{

    m_type=Type::PostProcessingContours;
    m_visualItem="qrc:///Processing/PostProcessing/PostProcessingContoursItem.qml";
    m_name="Contours";

}

void PostProcessingContours::apply(Mat& input, Mat& preprocessed, Mat &original)
{
    vector<vector<Point> > contours;

//    vector<vector<Point> > contours_box;

    vector<Vec4i> hierarchy;

    m_filteredContours.clear();

    Mat drawing;

    cvtColor(original,drawing,CV_GRAY2BGR);





    //    Canny( input, preprocessed, threshold(), threshold()*2, 3 );
    findContours( input, contours, RETR_LIST, CHAIN_APPROX_SIMPLE, Point(0, 0) );



    vector<vector<Vec4i>> defects;
    vector<vector<Point>> hullsP;

    //   drawContours(drawing, contours, -1, cv::Scalar(0,255,0), 1);

    setTotalContours(contours.size());

    for(int i = 0; i < contours.size(); i++)
    {

        vector<Point> contour=contours[i];
        vector<Point >hullP;
        vector<int> hullI;
        vector<Vec4i> defect;



        double contourlength=arcLength(contour,true);


        bool length_condition=contourlength>minCountourLength() && contourlength<maxCountourLength();

        if(length_condition==false){
            continue;
        }

        double contourarea=contourArea(contour);

        bool area_condition=contourarea>minCountourArea() && contourarea<maxCountourArea();

        if(area_condition==false){
            continue;
        }


//        approxPolyDP(contour,contour,contourlength*0.02,true);
        approxPolyDP(contour,contour,3,true);
        //        Rect contour_rect=boundingRect(contour);
        RotatedRect minrect=minAreaRect(contour);


        bool width_condition=minrect.size.width>minCountourWidth() && minrect.size.width<maxCountourWidth();
        bool height_condition=minrect.size.height>minCountourHeight() && minrect.size.height<maxCountourHeight();

        //        convexHull(Mat(contour, hull[i], False);




        if(length_condition && width_condition && height_condition){
            cv::Point2f vertices[4];
             minrect.points(vertices);
             for(int i = 0; i < 4; ++i)
               cv::line(drawing, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 0, 255), 1, CV_AA);


            m_filteredContours.push_back(contour);
        }

    }
    setTotalFilteredContours(m_filteredContours.size());

    drawContours(drawing, m_filteredContours, -1, cv::Scalar(0,255,0), 1);


    drawing.copyTo(preprocessed);

    emit filteredContoursChanged(m_filteredContours);


}


//            convexHull(contour, hullP, false);
//            convexHull(contour, hullI, false);
//            if(hullI.size() > 3 )
//            {

//                convexityDefects(contour, hullI, defect);

//                LOG_INFO()<<"Defects:"<<defect.size();

//                defects.push_back(defect);
//            }
//            hullsP.push_back(hullP);

//            drawContours( drawing, hullsP, hullsP.size()-1, cv::Scalar(0,0,255), 1, 8, vector<Vec4i>(), 0, Point() );
