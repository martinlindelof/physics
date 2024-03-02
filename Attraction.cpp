#include "Attraction.hpp"

namespace snus { namespace physics {

Attraction::Attraction (Particle* __a, Particle* __b, f32 __strength, f32 __distance)
{
  A = __a;
  B = __b;
  strength = __strength;
  on = true;
  distance = __distance;
  distanceSquared = __distance * __distance;
}

Attraction::~Attraction ()
{
  //
}

f32
Attraction::get_distance ()
{
  return distance;
}

void
Attraction::set_distance (f32 __distance)
{
  distance = __distance;
  distanceSquared = __distance * __distance;
}

f32
Attraction::get_strength ()
{
  return strength;
}

void
Attraction::set_strength (f32 __strength)
{
  strength = __strength;
}

void
Attraction::turn_on ()
{
  on = true;
}

void
Attraction::turn_off ()
{
  on = false;
}

bool
Attraction::is_on () const
{
  return on;
}

bool
Attraction::is_off () const
{
  return !on;
}
void
Attraction::apply ()
{
  if (on && (!A->fixed || !B->fixed))
  {
    glm::vec3 a2b = A->position - B->position;
    // f32 a2bX = A->position.x - B->position.x;
    // f32 a2bY = A->position.y - B->position.y;
    // f32 a2bZ = A->position.z - B->position.z;

    f32 a2bDistanceSquared = glm::dot (a2b, a2b);
    if (a2bDistanceSquared < distanceSquared)
    {
      a2bDistanceSquared = distanceSquared;
    }

    f32 force = strength * A->mass * B->mass / a2bDistanceSquared;
    // f32 length = snus::Q_rsqrt (a2bDistanceSquared);

    // make unit vector
    // a2bX /= length;
    // a2bY /= length;
    // a2bZ /= length;

    // multiply by force
    // a2bX *= force;
    // a2bY *= force;
    // a2bZ *= force;

    a2b *= snus::Q_rsqrt (a2bDistanceSquared) * force;

    // apply
    if (!A->fixed)
    {
      A->force -= a2b;
    }
    if (!B->fixed)
    {
      B->force += a2b;
    }
  }
}
}} /* namespace snus::physics */
