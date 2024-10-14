
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Saveandload3dvec
{
public:
    json myJson;
    std::vector<std::vector<std::vector<std::string>>> myVec3D;
    Saveandload3dvec();
    void save3dvec();
};