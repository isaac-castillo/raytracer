#include <iostream>
#include <string>

#include "FreeImage.h"
#include "scene.hpp"
#include "scene_builder.hpp"
#include "tracer.hpp"
#include "util.hpp"
#include <algorithm>
#include <memory>
using namespace raytracer;
void saveScreenshot(std::shared_ptr<Scene> &scene, std::string fname,
                    std::vector<vec3> inputPixels);

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cerr << "Missing file! Retry with a scene file." << std::endl;
    return 0;
  }

  if (argc >= 3) {
    std::cerr << "Too many arguments. Please enter a single scene file. "
              << std::endl;
  }

  scene_builder sb(argv[1]);

  // Expensive operation (recreates the scene)
  std::shared_ptr<Scene> _scene = sb.create_scene();

  _scene->print();
  tracer rt(5, _scene);

  std::vector<vec3> pixels = _scene->render_scene(rt);

  saveScreenshot(_scene, "output.png", pixels);

  return 1;
}

void saveScreenshot(std::shared_ptr<Scene> &scene, std::string fname,
                    std::vector<vec3> inputPixels) {
  int w = scene->get_width();
  int h = scene->get_height();
  int pix = w * h;
  FreeImage_Initialise();

  FIBITMAP *bitmap = FreeImage_Allocate(w, h, 24);
  RGBQUAD color;

  for (size_t i = 0; i < pix; ++i) {
    color.rgbRed = std::min(255.0f, inputPixels[i].x);
    color.rgbGreen = std::min(255.0f, inputPixels[i].y);
    color.rgbBlue = std::min(255.0f, inputPixels[i].z);
    int ii = i / w;
    int jj = i % w;
    FreeImage_SetPixelColor(bitmap, jj, h - ii - 1, &color);
  }

  std::cout << "Saving screenshot: " << fname << "\n";

  FreeImage_Save(FIF_PNG, bitmap, fname.c_str(), 0);
  FreeImage_DeInitialise();
}
