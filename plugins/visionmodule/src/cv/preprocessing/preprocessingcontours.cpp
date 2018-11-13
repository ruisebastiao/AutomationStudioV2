#include "preprocessingcontours.h"

using namespace cv;
using namespace std;

PreProcessingContours::PreProcessingContours()
{

    m_type=Type::PreProcessingContours;
    m_visualItem="qrc:///PreProcessing/PreProcessingContoursItem.qml";
    m_name="Contours";

}

void PreProcessingContours::apply(Mat& input, Mat& preprocessed, Mat &original)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    m_filteredContours.clear();

    Mat drawing;

    cvtColor(original,drawing,CV_GRAY2BGR);





    //    Canny( input, preprocessed, threshold(), threshold()*2, 3 );
    findContours( input, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );



    //   drawContours(drawing, contours, -1, cv::Scalar(0,255,0), 1);

    setTotalContours(contours.size());

    for(int i = 0; i < contours.size(); i++)
    {

        vector<Point> contour=contours[i];
        //        vector<Point> approx;

        //        approxPolyDP(countour,approx,arcLength(Mat(countour), true)*0.02,true);

        double contourlength=arcLength(contour,true);
        Rect contour_rect=boundingRect(contour);

        bool length_condition=contourlength>minCountourLength() && contourlength<maxCountourLength();

        if(length_condition==false){
            continue;
        }

        bool width_condition=contour_rect.width>minCountourWidth() && contour_rect.width<maxCountourWidth();
        bool height_condition=contour_rect.height>minCountourHeight() && contour_rect.height<maxCountourHeight();

        if(length_condition && width_condition && height_condition){
            m_filteredContours.push_back(contour);
        }

    }
    setTotalFilteredContours(m_filteredContours.size());

    drawContours(drawing, m_filteredContours, -1, cv::Scalar(0,255,0), 1);

    drawing.copyTo(preprocessed);

    emit filteredContoursChanged(m_filteredContours);


}
