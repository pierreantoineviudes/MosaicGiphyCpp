#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
 
    Mat image, grayImg;
    image = imread( argv[1], IMREAD_COLOR );
 
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    // access a few data
    if (image.data)
    {
        // convert image to grayscale
        cvtColor(image, grayImg, COLOR_BGR2GRAY);
        uint8_t* pixelPtr = (uint8_t*)grayImg.data;
        int cn = grayImg.channels();
        Scalar_<uint8_t> bgrPixel;

        for(int i = 0; i < grayImg.rows; i++)
        {
            for(int j = 0; j < grayImg.cols; j++)
            {
                bgrPixel.val[0] = pixelPtr[i*grayImg.cols*cn + j*cn + 0]; // B
                bgrPixel.val[1] = pixelPtr[i*grayImg.cols*cn + j*cn + 1]; // G
                bgrPixel.val[2] = pixelPtr[i*grayImg.cols*cn + j*cn + 2]; // R
                
                // do something with BGR values...
                cout << "bgrPixel : " << bgrPixel << endl;
            }
        }
        
    }
 
    waitKey(0);
 
    return 0;
}