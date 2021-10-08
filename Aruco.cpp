#include "opencv2/opencv.hpp"
using namespace cv;
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/aruco.hpp>



int main(int argc, char** argv)
{
    Mat markerImage;
    VideoCapture cap;
   
   

    //cv::Mat CameraMat = (Mat_<float>(3, 3)<< 
    //            645.363462, 0.000000, 328.019093,
    //            0.000000, 648.499768, 243.138670,
    //            0.000000, 0.000000, 1.000000);

    //cv::Mat DistMat = (Mat_<float>(1, 5)<< 
    //            0.067774, -0.112457, -0.010487, 0.012169, 0.000000);
              
   Mat CameraMat = (Mat1f(3, 3) << 645.363462, 0, 328.019093, 0, 648.499768, 243.138670, 0, 0, 1);
   Mat DistMat = (Mat1f(1, 5) << 0.067774, -0.112457, -0.010487, 0.012169, 0.000000);

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(1))
        return 0;
    for(;;)
    {
        Mat frame;
        cap >> frame;
        if( frame.empty() ) break; // end of video stream
            
    
        std::vector<int> markerIds;
        std::vector<std::vector<cv::Point2f>> corners, rejectedCandidates;
        cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
        cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_50);

        cv::aruco::detectMarkers(frame, dictionary, corners, markerIds, parameters, rejectedCandidates);

        cv::aruco::drawDetectedMarkers(frame, corners, markerIds);

        if (markerIds.size() > 0) {
            std::vector<Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, 0.05, CameraMat, DistMat, rvecs, tvecs);
            for(int i=0; i<markerIds.size(); i++){
                cv::aruco::drawAxis(frame, CameraMat, DistMat, rvecs[i], tvecs[i], 0.1);
                std::cout<<"ID :"<<markerIds[i]<<std::endl;
                std::cout<<"Translations :"<<rvecs[i]<<std::endl;
                std::cout <<"Rotations :"<<rvecs[i]<<std::endl;
            }
        }

       

        imshow("Camera", frame);   


          if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}

