#include <opencv2/opencv.hpp>
#include "ImageProcessor.hpp"
#include "MosaicFromSmallCats.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    cout << "Project Root: " << PROJECT_ROOT <<     endl;

    // auto start = chrono::high_resolution_clock::now();
    // // create image processor
    // ImageProcessor processor;
    // processor.processImages();
    // auto end = chrono::high_resolution_clock::now();
    // auto diff = end - start;
    // auto diff_sec = chrono::duration_cast<chrono::milliseconds>(diff);
    // cout << "duration : " << diff_sec.count() << endl;

    // // process the mosaic
    // auto start2 = chrono::high_resolution_clock::now();
    // MosaicFromSmallCats mosaic;
    // mosaic.createMosaic();
    // auto end2 = chrono::high_resolution_clock::now();
    // auto diff2 = end2 - start2;
    // auto diff_sec2 = chrono::duration_cast<chrono::milliseconds>(diff2);
    // cout << "duration : " << diff_sec2.count() << endl;

    // process images color
    

    return 0;
}