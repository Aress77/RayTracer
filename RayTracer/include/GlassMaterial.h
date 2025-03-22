#ifndef __GLASS_MATERIAL_H__
#define __GLASS_MATERIAL_H__

#include <glm/glm.hpp>
#include "MaterialBase.h"
#include "Ray.h"
#include "Intersection.h"
#include "Scene.h"

class GlassMaterial : public MaterialBase {
   public:
    float ior; 

    GlassMaterial(float ior = 1.5f) : ior(ior) {}

    Ray sample_ray_and_update_radiance(Ray& ray, Intersection& intersection) override;

    glm::vec3 color_of_last_bounce(Ray& ray, Intersection& intersection, Scene const& scene) override;
};

#endif
