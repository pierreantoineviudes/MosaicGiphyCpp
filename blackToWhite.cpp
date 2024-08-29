#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
#include <chrono>
using json = nlohmann::json;
using namespace std;
using namespace cv;
using namespace chrono;

int main() {

    Mat bigImg = imread("/home/paviudes/dev/mosaicgiphycpp/images/jeanne.jpg");
    cvtColor(bigImg, bigImg, COLOR_BGR2GRAY);

    // replace all values in black
    uchar &value = bigImg.at<uchar>(0);
    value = 0;
    cout << "value : " << (int)value << endl;


    for (int i = 0; i < bigImg.size().height; i++)
    {
        for (int j = 0; j < bigImg.size().width; j++)
        {
            // replace pixels
            uchar &value = bigImg.at<uchar>(i, j);
            value = 0;
            
        }
        
    }
    imwrite("./outputblackToWhite.jpg", bigImg);
    return 0;

}