#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat frame;
    VideoCapture cap;
    int deviceID = 0;
    int apiID = CAP_ANY;
    cap.open(deviceID, apiID);

    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open WebCam\n";
        return -1;
    }

    for (;;)
    {
        int largest_area = 0;
        int largest_contour_index = 0;
        Rect bounding_rect;

        //cap.read(frame);
        cap >> frame;
        Mat dst(frame.rows, frame.cols, CV_8UC1, Scalar::all(0));

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        threshold(gray, gray, 125, 255, THRESH_BINARY);
        //Mat gBlur;
        //GaussianBlur(gray, gBlur, Size(5,5), 1.8);

        //Mat cann;
        //Canny(gBlur, cann, 45, 90);


        //dilate(edges, edges, getStructuringElement(MORPH_RECT, Size(3,3)));
        //erode(edges, edges, getStructuringElement(MORPH_RECT, Size(5,5)));

        //morphologyEx(cann, cann, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(3,3)));
        //morphologyEx(cann, cann, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(3,3)));
        //morphologyEx(cann, cann, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(3,3)));

        //threshold(edges, edges, 200, 255, THRESH_BINARY);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(gray, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++)
        {
            Point2f center;
            float radius;

            double a = contourArea(contours[i], false);
            //double l = arcLength(contours[i], false);
            //minEnclosingCircle(contours[i], center, radius);

            char buffer[64] = {0};
            //putText(frame, buffer, Point(center.x, center.y + 20), FONT_HERSHEY_SIMPLEX, .6, Scalar::all(0), 1);

            if (a > largest_area)
            {
                largest_area = a;
                largest_contour_index = i;
                bounding_rect = boundingRect(contours[i]);
            }
        }
        drawContours(frame, contours, largest_contour_index, Scalar(0,255,0), 2);

        //rectangle(frame, bounding_rect, Scalar(0, 255, 0), 1, 8, 0);

        imshow("", frame);
        //imshow("1", frame);

        if (frame.empty())
        {
            cerr << "ERROR! Blank frame grabbed\n";
            break;
        }

        if (waitKey(5) >= 0)
            break;
    }

    return 0;


    /*
    imshow("Source", Image);
    waitKey();

    Mat gray;
    cvtColor(Image, gray, COLOR_BGR2GRAY);
    imshow("Gray", gray);
    waitKey();


    //GaussianBlur(gray, gray, Size(5,5), 0);
    //imshow("GBlur", gray);
    //waitKey();

    //Mat edge;
    //Canny(gray, edge, 35, 125);
    //imshow("Cann", edge);
    //waitKey();

    Mat thresh;
    threshold(gray, thresh, 120, 255, THRESH_BINARY);
    imshow("Thresh", thresh);
    waitKey();

    vector<vector<Point>> contours;
    findContours(thresh, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    imshow("Find Contours", contours);
    waitKey();


    //int big;
    //max(edge, contourArea(contours[big], true));
    //imshow("Max", edge);
    //waitKey();




    for (size_t i = 0; i < contours.size(); i++)
    {
        arcLength(contours[i], true);
        contourArea(contours[i]);
        drawContours(Image, contours[i], -1, Scalar::all(255), 3, LINE_AA);
    }

    imshow("", Image);
    waitKey();
    return 0;
    */
}

