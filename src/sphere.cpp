#include "sphere.hpp"
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include "ray.hpp"
#include "util.hpp"
namespace raytracer
{

    Sphere::Sphere(float radius, vec3 center, mat4 transformation) : Shape(vec3(), transformation), _radius(radius), _center(center)
    {
        float pi = glm::pi<float>();
        std::vector<vec4> sphereVertices;

        int stacks = 20;
        int slices = 20;
        float fstacks = (float) stacks;
        float fslices = (float) slices;
        for (int i = 0; i < slices; i++)
        {
            for (int j = 0; j < stacks; j++)
            {
                // Top left
                sphereVertices.push_back(vec4(
                    radius * -cos(2.0f * pi * i / fstacks) * sin(pi * (j + 1.0f) / fslices),
                    radius * -cos(pi * (j + 1.0f) / fslices),
                    radius * sin(2.0f * pi * i / fstacks) * sin(pi * (j + 1.0f) / fslices),
                    1.0f));

                // Top right
                sphereVertices.push_back(vec4(
                    radius * -cos(2.0f * pi * (i + 1.0) / fstacks) * sin(pi * (j + 1.0) / fslices),
                    radius * -cos(pi * (j + 1.0) / fslices),
                    radius * sin(2.0f * pi * (i + 1.0) / fstacks) * sin(pi * (j + 1.0) / fslices),
                    1.0f));

                sphereVertices.push_back(vec4(
                    radius * -cos(2.0f * pi * (i + 1.0) / fstacks) * sin(pi * j / fslices),
                    radius * -cos(pi * j / fslices),
                    radius * sin(2.0f * pi * (i + 1.0) / fstacks) * sin(pi * j / fslices),
                    1.0f));

                // Need to repeat 2 of the vertices since we can only draw triangles. Eliminates the confusion
                // of array indices.
                // Top left
                sphereVertices.push_back(vec4(
                    radius * -cos(2.0f * pi * i / fstacks) * sin(pi * (j + 1.0f) / fslices),
                    radius * -cos(pi * (j + 1.0f) / fslices),
                    radius * sin(2.0f * pi * i / fstacks) * sin(pi * (j + 1.0f) / fslices),
                    1.0f));

                sphereVertices.push_back(vec4(
                    radius * -cos(2.0f * pi * (i + 1.0) / fstacks) * sin(pi * j / fslices),
                    radius * -cos(pi * j / fslices),
                    radius * sin(2.0f * pi * (i + 1.0) / fstacks) * sin(pi * j / fslices),
                    1.0f));

                sphereVertices.push_back(vec4(
                    radius * -cos(2.0f * pi * i / fstacks) * sin(pi * j / fslices),
                    radius * -cos(pi * j / fslices),
                    radius * sin(2.0f * pi * i / fstacks) * sin(pi * j / fslices),
                    1.0f));
            }
        }
    }

    std::optional<IntersectResult> Sphere::inside(const Ray & _ray) {
        auto inverse_ray = util::inverse_ray(_transform, _ray);



        const auto [ray_position, ray_direction] = inverse_ray;

        //fake "normal", has direction, but not normalized
        const auto p_normal = ray_position - _center;

        float a = glm::dot(ray_direction, ray_direction); 
        float b = 2 * glm::dot(ray_direction, p_normal);
        float c = glm::dot(p_normal, p_normal ) - (_radius * _radius);
        float discriminant =  b*b - 4*a*c;

        std::optional<IntersectResult> return_result;
        if(discriminant < 0){
            return std::nullopt;
        }
        
        IntersectResult result;

        result.shape_ptr = std::make_shared<Sphere>(*this);

        if(discriminant == 0){
            result.distance = -b/(2*a);
        }

        float pos_root = (-b + glm::sqrt(discriminant)) / (2 * a);
        float neg_root = (-b - glm::sqrt(discriminant)) / (2 * a);
        if(pos_root > 0 && neg_root  > 0){
            result.distance = glm::min(pos_root, neg_root);
        }
        else if(pos_root > 0 && neg_root < 0){
            result.distance = pos_root;;
        }
        else if (pos_root < 0 and neg_root < 0){
            return std::nullopt;
        } 
        auto world_coord  = util::transform_to_world(_transform, ray_position + ray_direction * result.distance);
        result.point = util::dehomogenize(world_coord);

        return_result = result;
        return return_result;

    }
    void Sphere::print() {

    }

    vec3 Sphere::normal(const vec3 & vec) const {

        vec4 object_point = glm::inverse(_transform) * vec4(vec, 1);
        vec4 fake_normal = object_point - vec4(_center, 0);
        vec4 normal = glm::mat4(glm::transpose(glm::inverse(_transform))) * fake_normal;
        normal.w = 0;

        return glm::normalize(vec3(normal));
    }

    vec3 Sphere::get_center(){
        return _center;
    }
    float Sphere::get_radius(){
        return _radius;
    }


}