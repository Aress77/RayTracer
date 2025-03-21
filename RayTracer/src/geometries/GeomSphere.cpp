#include "GeomSphere.h"

#include <iostream>
#include <utility>

#include "Intersection.h"
#include "Ray.h"

std::vector<Intersection> GeomSphere::intersect(Ray &ray) {
    /**
     * NOTE: Ray is already transformed to the Model coordinate space.
     */
    using namespace glm;

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

    vec3 oc = ray.p0 - center;

    // Quadratic coefficients: a, b, and c for the equation: at^2 + bt + c = 0
    float a = dot(ray.dir, ray.dir); 
    float b = 2.0f * dot(oc, ray.dir);
    float c = dot(oc, oc) - radius * radius;

    // Calculate the discriminant
    float discriminant = b * b - 4 * a * c;

    // No intersection if discriminant is negative
    if (discriminant < 0.0f)
        return intersections;

    // Compute the two rootss
    float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
    float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

    // Only add intersections that are in front of the ray (t > 0)
    if (t1 > 0.0f) {
        vec3 point = ray.p0 + t1 * ray.dir;
        vec3 normal = normalize(point - center);
        intersections.push_back({ t1, point, normal, this, nullptr });
    }
    if (t2 > 0.0f) {
        vec3 point = ray.p0 + t2 * ray.dir;
        vec3 normal = normalize(point - center);
        intersections.push_back({ t2, point, normal, this, nullptr });
    }

    return intersections;
};