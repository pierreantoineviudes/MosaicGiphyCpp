#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ImageProcessor
{
public:
    ImageProcessor();
    json config;
    void processImageArr(int deb_inclu, int fin_exclue);
    void processImages();
    int taille_dalle;
    int max_num_threads;
    json dict_of_images;
};