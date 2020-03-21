
// #include "sceneRW.hpp"

// #include <iostream>
// #include <sstream>
// #include <fstream>
// #include <string>
// #include <stack>
// #include <vector>

// #include <glm/ext.hpp>
// #include <glm/gtc/matrix_transform.hpp>


// #include "scene.hpp"


// namespace raytracer {

// bool sceneRW::readvals(std::stringstream &s, const int numvals, float *values)
// {
//     for (int i = 0; i < numvals; i++)
//     {
//         s >> values[i];
//         if (s.fail())
//         {
//             std::cerr << "Failed reading value " << i << " will skip\n";
//             return false;
//         }
//     }
//     return true;
// }


// void sceneRW::read_file(std::string filename, scene *scene){

//     std::ifstream input_stream;

//     input_stream.open(filename.c_str());

//     if(!input_stream.is_open()){
//         std::cerr << "Unable to open input data file: " << filename << "\n";
//         throw 2;
//     }

//     std::string line;

//     getline(input_stream, line);
//     while(input_stream){

//         if ((line.find_first_not_of(" \t\r\n") != std::string::npos) &&
//              (line[0] != '#')){


//             std::string command;
//             std::stringstream ss(line);
//             float values[10];
//             bool validinput;
//             ss >> command;

//             if(command == "size"){

//                 if ( readvals(ss, 2, values)) {

//                     scene->set_width(values[0]);
//                     scene
//                 }

//             }
//         }
//     }



// }

// }