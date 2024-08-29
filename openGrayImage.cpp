#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
#include <thread>
using json = nlohmann::json;
using namespace std;
using namespace cv;


void openGrayImg() {
    Mat img;
    img = imread("/home/paviudes/dev/mosaicgiphycpp/images/moicassou.jpg");
    resize(img, img, Size(50, 50));
    cvtColor(img, img, COLOR_RGB2GRAY);
    imwrite("/home/paviudes/dev/mosaicgiphycpp/test_outputgray.jpg", img);

    Mat img2;
    img2 = imread("/home/paviudes/dev/mosaicgiphycpp/test_outputgray.jpg", IMREAD_GRAYSCALE);
    
    cout << "nb channels img2 : " << img2.channels() << endl;
    cout << "nb channels img : " << img.channels() << endl;
}

int main() {
    openGrayImg();
    return 0;
}