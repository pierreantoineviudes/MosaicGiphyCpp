#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
using namespace cv;
using namespace std;

int main() {

    Mat img, newimg;

    img = imread("/home/paviudes/dev/mosaicgiphycpp/images/moicassou.jpg", IMREAD_COLOR);
    cvtColor(img, img, COLOR_BGR2GRAY);

    int width, height;
    width = img.size().width;
    height = img.size().height;

    // create new array
    Mat output_arr = Mat::zeros(Size(width, height), CV_8UC1);

    for (int i=0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            uchar &value = img.at<uchar>(j, i);
            uchar &newValue = output_arr.at<uchar>(j, i);
            newValue = value;
        }
    }

    // save big image
    imwrite("./zerosarray.jpg", output_arr);

    return 0;
}