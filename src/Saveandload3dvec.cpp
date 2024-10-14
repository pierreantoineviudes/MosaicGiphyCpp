#include "Saveandload3dvec.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

Saveandload3dvec::Saveandload3dvec()
{
    cout << "initializer" << endl;

    int n_color = 3;

    // create 3D vec
    json myJson;
    std::vector<std::vector<std::vector<std::string>>> vec3D(n_color, std::vector<std::vector<std::string>>(n_color, std::vector<std::string>(n_color, "")));
    myJson = vec3D;

    this->myVec3D = vec3D;
    this->myJson = myJson;
}

void Saveandload3dvec::save3dvec()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {   
                myVec3D[i][j][k] = "value";
            }
        }
    }

    // update json
    myJson = myVec3D;

    // save json object to file
    string s = myJson.dump();
    ofstream out("/mnt/d/fichiers_pa/dev_ubuntu/MosaicGiphyCpp/testjson.json");
    out << s;
    out.close();
}
