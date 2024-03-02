#include "Spring.hpp"

namespace snus { namespace physics {

Spring::Spring (Particle*   __a,
                Particle*   __b,
                const f32   &__ks,
                const f32   &__d,
                const f32   &__r)
{
  springConstant = __ks;
  damping = __d;
  restLength = __r;
  A = __a;
  B = __b;
  on = true;
}

Spring::~Spring ()
{
  //
}

void
Spring::turn_on ()
{
  on = true;
}

void
Spring::turn_off ()
{
  on = false;
}
bool
Spring::is_on () const
{
  return on;
}
bool
Spring::is_off () const
{
  return !on;
}

f32
Spring::get_current_length () const
{
  return glm::distance (A->position, B->position);
}

f32
Spring::get_rest_length () const
{
  return restLength;
}

f32
Spring::get_strength () const
{
  return springConstant;
}

void
Spring::set_strength (const f32 &__ks)
{
  springConstant = __ks;
}

f32
Spring::get_damping () const
{
  return damping;
}

void
Spring::set_damping (const f32 &__d)
{
  damping = __d;
}

void
Spring::set_rest_length (const f32 &__l)
{
  restLength = __l;
}

void
Spring::apply ()
{
  if (on && (!A->fixed || !B->fixed))
  {
    glm::vec3 a2b = A->position - B->position;
    f32 a2bDistance = glm::length (a2b);
    if (a2bDistance != 0)
    {
      a2b = glm::normalize (a2b);
    }
    f32 springForce = -(a2bDistance - restLength) * springConstant;
    glm::vec3 Va2b = A->velocity - B->velocity;
    f32 dampingForce = -damping * glm::dot(a2b, Va2b);
    f32 r = springForce + dampingForce;
    a2b *= r;
    if (!A->fixed)
    {
      A->force += a2b;
    }
    if (!B->fixed)
    {
      B->force -= a2b;
    }
  }
}

void
Spring::setA (Particle* p)
{
  A = p;
}

void
Spring::setB (Particle* p)
{
  B = p;
}
}} /* namespace snus::physics */
