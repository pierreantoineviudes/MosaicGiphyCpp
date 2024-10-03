#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

using json = nlohmann::json;
using namespace cv;

class MosaicFromSmallCats
{
public:
    MosaicFromSmallCats();
    json config;
    int taille_dalle;
    int max_num_threads;
    int alpha;
    Mat bigImg;
    json json_data;
    int width;
    int height;
    int newWidth;
    int newHeight;
    Mat outputArr;

    void createMosaicUneTranche(int deb_inclu, int fin_exclue);
    void createMosaic();
};