#pragma once

#include "Integrator.hpp"
#include "ParticleSystem.hpp"

namespace snus { namespace physics {
class ModifiedEulerIntegrator : public Integrator
{
  public:
    ModifiedEulerIntegrator (ParticleSystem* __system);
    ~ModifiedEulerIntegrator ();
    ParticleSystem* system;
    void step (const f32 &t);
};
}} /* namespace snus::physics */