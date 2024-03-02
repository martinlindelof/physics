#include "ModifiedEulerIntegrator.hpp"

namespace snus { namespace physics {

ModifiedEulerIntegrator::ModifiedEulerIntegrator (ParticleSystem* __system)
{
  system = __system;
}
ModifiedEulerIntegrator::~ModifiedEulerIntegrator ()
{
  //
}

void
ModifiedEulerIntegrator::step (const f32 &t)
{
  system->clear_forces ();
  system->apply_forces ();

  f32 halftt = 0.5f*t*t;

  for (Particle* p : system->particles)
  {
    if (!p->fixed)
    {
      glm::vec3 a = (p->force / p->mass);
      p->position += p->velocity/t;
      p->position += a * halftt;
      p->velocity += a / t;
    }
  }
}

}} /* namespace snus::physics */
