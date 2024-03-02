#include "EulerIntegrator.hpp"
#include "ParticleSystem.hpp"
#include "Particle.hpp"
#include "snus/snus.hpp"

namespace snus { namespace physics {
EulerIntegrator::EulerIntegrator (ParticleSystem* __system)
{
  system = __system;
}

EulerIntegrator::~EulerIntegrator ()
{
  //
}

void
EulerIntegrator::step (const f32 &t)
{
  system->clear_forces();
  system->apply_forces();

  for (Particle* p : system->particles)
  {
    if (!p->fixed)
    {
      p->velocity += p->force / (p->mass*t);
      p->position += p->velocity / t;
    }
  }
}

}} /* namespace snus::physics */
