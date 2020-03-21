#ifndef SCENERW_HPP
#define SCENERW_HPP

#include "scene.hpp"

#include <string>

namespace raytracer {
class sceneRW
{
private:
     bool readvals(std::stringstream &s, const int numvals, float *values);

public:


    void read_file(std::string filename,  scene * scene);
    void write_file(std::string filename);
    void write_file();
};

}
#endif