#include "catch.hpp"
#include "../src/camera.hpp"
#include "test_utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
using namespace raytracer;

TEST_CASE("look_at() computes identity matrix", "[camera]") {

    camera cam;

    glm::vec3 lookFrom  = vec3(0,0,0);
    glm::vec3 lookAt    = vec3(0,0,-1);
    glm::vec3 up        = vec3(0,1,0);

    cam.set_look_from(lookFrom).set_look_at(lookAt).set_up(up);
    REQUIRE( cam.look_at_matrix() == mat4(1.0f));

}

TEST_CASE("look_at() computes scaling matrix", "[camera]") {

    camera cam;

    glm::vec3 lookFrom  = vec3(0,0,0);
    glm::vec3 lookAt    = vec3(0,0,1);
    glm::vec3 up        = vec3(0,1,0);

    cam.set_look_from(lookFrom).set_look_at(lookAt).set_up(up);

    glm::mat4 look_at = cam.look_at_matrix();

    REQUIRE( look_at == glm::scale(vec3(-1, 1, -1)) );
    
}

TEST_CASE("look_at() computes translation matrix,", "[camera]"){
    camera cam;

    glm::vec3 lookFrom  = vec3(0,0,8);
    glm::vec3 lookAt    = vec3(0,0,0);
    glm::vec3 up        = vec3(0,1,0);

    cam.set_look_from(lookFrom).set_look_at(lookAt).set_up(up);

    glm::mat4 look_at = cam.look_at_matrix();

    REQUIRE( look_at == glm::translate(vec3(0.0f, 0.0f, -8.0f)) );
}


TEST_CASE("direction() computes direction through center", "[camera"){

    camera cam;

    cam.set_fovy( 90 );

    auto px = 100;
    auto py = 50;
    auto width = 201;
    auto height = 101;

    vec3 direction = cam.direction(px, py, width, height);
    INFO ("cam.direction(..)" << glm::to_string(direction) );
    REQUIRE( direction == vec3(0,0,-1) );

}

TEST_CASE("direction() computes direction through corner", "[camera]"){

    camera cam;


    auto px = 0;
    auto py = 0;
    auto width = 201;
    auto height = 101;

    //round_about way of setting
    cam.set_fovx( 90, width, height );


    vec3 direction = cam.direction(px, py, width, height);
    INFO ("cam.direction(..)" << glm::to_string(direction) );
    REQUIRE( glm::all(glm::lessThan(glm::abs(direction - vec3(-0.66519,0.33259,-0.66851)), vec3(0.01))) );


}



