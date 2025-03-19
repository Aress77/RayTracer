#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include "GeomTriangle.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Intersection.h"
#include "Ray.h"

GeomTriangle::GeomTriangle(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals) {
    this->vertices[0] = vertices[0];
    this->vertices[1] = vertices[1];
    this->vertices[2] = vertices[2];

    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

std::vector<Intersection> GeomTriangle::intersect(Ray &ray) {
    using namespace glm;
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */

    // vector to store the intersections
    std::vector<Intersection> intersections;

    /**
     * TODO: Implement the Ray intersection with the current geometry
     */

    /**
     * Once you find the intersection, add it to the `intersections` vector.
     *
     * Example:
     * Suppose the ray intersects the current geometry at a point `vec3 point`
     * at a distance `float t`, and the unit normal vector at the intersection
     * point is `vec3 normal`. You would then insert an intersection into the
     * vector as follows:
     *
     * intersections.push_back({t, point, normal, this, nullptr});
     *
     * Note:
     * - Here we pass the Model pointer as `nullptr` because it will be
     *   populated by the Model::intersect() function call.
     * - Only add intersections that are in front of the camera, i.e.,
     *   where t > 0.
     */

    /**
     * TODO: Update `intersections`
     */
    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    
    vec3 A = vertices[0];
    vec3 B = vertices[1];
    vec3 C = vertices[2];

    vec3 edge1 = B - A;
    vec3 edge2 = C - A;

    vec3 h = cross(ray.dir, edge2);
    float a = dot(edge1, h);

    if (fabs(a) < epsilon)
        return intersections;

    float f = 1.0f / a;
    vec3 s = ray.p0 - A;
    float u = f * dot(s, h);

    if (u < 0.0f || u > 1.0f)
        return intersections;

    vec3 q = cross(s, edge1);
    float v = f * dot(ray.dir, q);

    if (v < 0.0f || (u + v) > 1.0f)
        return intersections;

    float t = f * dot(edge2, q);

    if (t > epsilon) {
        vec3 point = ray.p0 + t * ray.dir;

        float w = 1.0f - u - v;
        vec3 interpolatedNormal = normalize(w * normals[0] + u * normals[1] + v * normals[2]);

        intersections.push_back({ t, point, interpolatedNormal, this, nullptr });
    }

    return intersections;
}