#pragma once
#include "Integrator.hpp"
#include "ParticleSystem.hpp"

namespace snus { namespace physics {
class EulerIntegrator : public Integrator
{
  public:
    EulerIntegrator (ParticleSystem* __system);
    ~EulerIntegrator ();
    ParticleSystem* system;
    void step (const f32 &t);
};
}} /* namespace snus::physics */