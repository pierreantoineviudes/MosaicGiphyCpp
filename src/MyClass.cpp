#include "MyClass.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

void MyClass::Myclass()
{

}

void MyClass::greeting()
{
    cout << "Hello world from myclass" << endl;
}

Mat MyClass::readImg()
{
    Mat img;
    img = imread("../data/input", IMREAD_COLOR);
    return img;
}