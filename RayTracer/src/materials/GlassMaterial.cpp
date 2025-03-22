#define GLM_ENABLE_EXPERIMENTAL

#include "GlassMaterial.h"
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>

using namespace glm;

Ray GlassMaterial::sample_ray_and_update_radiance(Ray& ray, Intersection& intersection) {
    ray.n_bounces++;

    if (ray.n_bounces > 20) {
        ray.isWip = false;
        return ray;
    }

    vec3 normal = intersection.normal;
    vec3 incident = normalize(ray.dir);

    float cosi = clamp(dot(incident, normal), -1.0f, 1.0f);
    float etai = 1.0f, etat = ior;

    if (cosi < 0.0f) {
        cosi = -cosi;
    } else {
        std::swap(etai, etat);
        normal = -normal;
    }

    float eta = etai / etat;
    float k = 1.0f - eta * eta * (1.0f - cosi * cosi);

    vec3 new_dir;
    if (k < 0.0f) {
        new_dir = reflect(incident, normal);
    } else {
        new_dir = normalize(eta * incident + (eta * cosi - sqrt(k)) * normal);
    }

    ray.p0 = intersection.point + 0.001f * new_dir;
    ray.dir = new_dir;

    return ray;
}

glm::vec3 GlassMaterial::color_of_last_bounce(Ray& ray, Intersection& intersection, Scene const& scene) {
    return glm::vec3(0.0f); 
}

