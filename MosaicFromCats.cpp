#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>
using json = nlohmann::json;
using namespace std;
using namespace cv;

void classifyImages()
{

    // std::ifstream f("./images_bdd_data.json");
    // json data = json::parse(f);
    // string s = data.dump();
    // ofstream out("./output.json");
    // out << s ;
    // out.close();
    // cout << "finished save" << endl;
    // cout << "jsondata : " << data << endl;
    // cout << "hello world" << endl;

    vector<cv::String> fn;
    glob("/home/paviudes/dev/mosaicgiphycpp/data/CAT_00/*.jpg", fn, false);

    // classify all images
    size_t count = fn.size(); // number of png files in images folder
    Mat img;
    for (size_t i = 0; i < count; i++)
    {
        cout << i << "/" << count << endl;
        img = imread(fn[i]);
        cvtColor(img, img, COLOR_RGB2GRAY);
        cout << "img.size : " << img.size() << endl;
        cout << "img.channels : " << img.channels() << endl;
        cout << "n_rows : " << img.size().height << endl;
        cout << "n_col : " << img.size().width << endl;
        Scalar mean = cv::mean(img);
        cout << "mean of img : " << mean << endl;
        cout << "mean of img : " << mean[0] << endl;
        break;
    }

    cout << "number of jpg files : " << count << endl;

    // build json dict
    json dict_of_images;
    for (int i = 0; i < 255; i++)
    {
        vector<string> v;
        dict_of_images[i] = v;
    }

    // open an image
    for (size_t i = 0; i < count; i++)
    {
        cout << i << "/" << count << endl;
        img = imread(fn[i]);
        cvtColor(img, img, COLOR_RGB2GRAY);
        Scalar mean = cv::mean(img);
        dict_of_images[mean[0]].push_back(fn[i]);
    }

    // save json object to file
    string s = dict_of_images.dump();
    ofstream out("./output.json");
    out << s;
    out.close();
    cout << "finished save" << endl;
}

void createMosaic()
{

    int TAILLE_DALLE = 50;
    int ALPHA = 10;

    // open the big image
    Mat bigImg = imread("/home/paviudes/dev/mosaicgiphycpp/images/sophia.jpg");
    int width = bigImg.size().width;
    int height = bigImg.size().height;
    int newWidth = width / ALPHA;
    int newHeight = height / ALPHA;

    // resze t new height and width
    resize(bigImg, bigImg, Size(newWidth, newHeight));
    cvtColor(bigImg, bigImg, COLOR_RGB2GRAY);

    // create empty array
    Mat output_arr = Mat::zeros(newHeight * TAILLE_DALLE, newWidth * TAILLE_DALLE, CV_8UC1);

    // open dict of images path
    std::ifstream f("/home/paviudes/dev/mosaicgiphycpp/output.json");
    json data = json::parse(f);

    // Iterate through image
    for (int i = 0; i < newHeight; i++)
    {
        cout << i << "/" << newHeight << endl;
        for (int j = 0; j < newWidth; j++)
        {
            int value = (int)(bigImg.at<uchar>(j, i));

            // Check if value exists in dictionary
            if (data[value].size() > 0)
            {
                // Load the first image corresponding to the value
                string fileName = data[value][0];
                Mat smallImage = imread(fileName);

                if (!smallImage.empty())
                {
                    resize(smallImage, smallImage, Size(TAILLE_DALLE, TAILLE_DALLE));
                    // go to gray
                    cvtColor(smallImage, smallImage, COLOR_RGB2GRAY);

                    // Replace the corresponding pixels in the output array
                    for (int k = 0; k < TAILLE_DALLE; k++)
                    {
                        for (int l = 0; l < TAILLE_DALLE; l++)
                        {
                            uchar &value = smallImage.at<uchar>(l, k);
                            uchar &newValue = output_arr.at<uchar>(
                                j * TAILLE_DALLE + l,
                                i * TAILLE_DALLE + k);
                            newValue = value;
                        }
                    }
                }
                else
                {
                    cerr << "Failed to read small image: " << fileName << endl;
                }
            }
            else
            {
                // cout << "error json" << endl;
            }
        }
    }

    // save big image
    imwrite("./outputsophia.jpg", output_arr);
    cout << "succeded to save image !! " << endl;
}

int main()
{
    // classifyImages();
    createMosaic();
    return 0;
}



/*
    IDEAS TO MAKE THINGS BETTER
    TODO: multithread, investiguer la grande erreur, bdd avec chats plus petits
*/