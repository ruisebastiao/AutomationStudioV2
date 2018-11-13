#include "preprocessingcontours.h"

using namespace cv;
using namespace std;

PreProcessingContours::PreProcessingContours()
{

    m_type=Type::PreProcessingContours;
    m_visualItem="qrc:///PreProcessing/PreProcessingContoursItem.qml";
    m_name="Contours";

}

void PreProcessingContours::apply(Mat& input, Mat& preprocessed)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Canny( input, preprocessed, threshold(), threshold()*2, 3 );
    findContours( preprocessed, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

}
