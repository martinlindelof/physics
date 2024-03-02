#pragma once
#include <glm/glm.hpp>
#include "snus/snus.hpp"

namespace snus { namespace physics {
class Particle
{
  public:
    Particle ();
    Particle (const f32 &mass);
    ~Particle ();

    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 force;
    f32 mass;
    f32 age;
    bool fixed;
    bool locked;

    void set_locked (bool b);
    void set_fixed (bool b);
    void make_fixed ();
    void reset();
};
}} /* namespace snus::physics */
