#include "Particle.hpp"

namespace snus { namespace physics {
Particle::Particle ()
{
  mass = 1.0;
  age = 0.0;
  fixed = false;
  locked = false;
  position = glm::vec3 (0, 0, 0);
  velocity = glm::vec3 (0, 0, 0);
  force = glm::vec3 (0, 0, 0);
}

Particle::Particle (const f32 &m)
{
  mass = m;
  age = 0.0;
  fixed = false;
  locked = false;
  position = glm::vec3 (0, 0, 0);
  velocity = glm::vec3 (0, 0, 0);
  force = glm::vec3 (0, 0, 0);
}

Particle::~Particle ()
{
  //
}

void
Particle::set_locked (bool b)
{
  locked = b;
}

void
Particle::set_fixed (bool b)
{
  if (!locked)
  {
    fixed = b;
  }
}

void
Particle::make_fixed ()
{
  // makes particle fixed
  fixed = true;
}

void
Particle::reset ()
{
  mass = 1.0;
  age = 0.0;
  fixed = false;
  locked = false;
  position = glm::vec3 (0, 0, 0);
  velocity = glm::vec3 (0, 0, 0);
  force = glm::vec3 (0, 0, 0);
}
}} /* namespace snus::physics */
