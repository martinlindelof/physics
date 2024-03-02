#include "RungeKuttaIntegrator.hpp"

namespace snus { namespace physics {

RungeKuttaIntegrator::RungeKuttaIntegrator (ParticleSystem* __system)
{
  system = __system;
}

RungeKuttaIntegrator::~RungeKuttaIntegrator ()
{
  //
}

void
RungeKuttaIntegrator::allocateParticles ()
{
  while (system->particles.size() > originalPositions.size())
  {
    originalPositions.push_back (glm::vec3());
    originalVelocities.push_back (glm::vec3());
    k1Forces.push_back (glm::vec3());
    k1Velocities.push_back (glm::vec3());
    k2Forces.push_back (glm::vec3());
    k2Velocities.push_back (glm::vec3());
    k3Forces.push_back (glm::vec3());
    k3Velocities.push_back (glm::vec3());
    k4Forces.push_back (glm::vec3());
    k4Velocities.push_back (glm::vec3());
  }
}

void
RungeKuttaIntegrator::step (const f32 &deltaT)
{
  allocateParticles ();
  // save original position and velocity
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      originalPositions[i] = (p->position);
      originalVelocities[i] = (p->velocity);
    }
    // and clear the forces
    p->force = glm::vec3(0, 0, 0);
  }
  // get all the k1 values
  system->apply_forces ();
  // save the intermediate forces
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      k1Forces[i] = (p->force);
      k1Velocities[i] = (p->velocity);
    }
    p->force = glm::vec3 (0, 0, 0); // and clear the forces
  }
  // get k2 values
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      glm::vec3 originalPosition = originalPositions[i];
      glm::vec3 k1Velocity = k1Velocities[i];
      p->position = originalPosition + (k1Velocity * (0.5f * deltaT));
      glm::vec3 originalVelocity = originalVelocities[i];
      glm::vec3 k1Force = k1Forces[i];
      p->velocity = originalVelocity + k1Force * 0.5f * deltaT / p->mass;
    }
  }
  system->apply_forces ();
  // save the intermediate forces
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      k2Forces[i] = (p->force);
      k2Velocities[i] = (p->velocity);
    }
    p->force = glm::vec3 (0, 0, 0); // and clear the forces
  }
  // get k3 values
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      glm::vec3 originalPosition = originalPositions[i];
      glm::vec3 k2Velocity = k2Velocities[i];
      p->position = (originalPosition + k2Velocity * 0.5f * deltaT);
      glm::vec3 originalVelocity = originalVelocities[i];
      glm::vec3 k2Force = k2Forces[i];
      p->velocity = (originalVelocity + k2Force * 0.5f * deltaT / p->mass);
    }
  }
  system->apply_forces ();
  // save the intermediate forces
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      k3Forces[i] = (p->force);
      k3Velocities[i] = (p->velocity);
    }
    p->force = glm::vec3 (0, 0, 0); // and clear the forces
  }
  // get k4 values
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      glm::vec3 originalPosition = originalPositions[i];
      glm::vec3 k3Velocity = k3Velocities[i];
      p->position = (originalPosition + k3Velocity + deltaT);
      glm::vec3 orignalVelocity = originalVelocities[i];
      glm::vec3 k3Force = k3Forces[i];
      p->position = (orignalVelocity + k3Force * deltaT / p->mass);
    }
  }
  system->apply_forces ();
  // save the intermediate forces
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    if (!p->fixed)
    {
      k4Forces[i] = (p->force);
      k4Velocities[i] = (p->velocity);
    }
  }
  // put them all together and what do you get?
  for (size_t i = 0; i < system->particles.size(); i++)
  {
    Particle* p = system->particles[i];
    p->age += deltaT;
    if (!p->fixed)
    {
      // update positions
      glm::vec3 originalPosition = originalPositions[i];
      glm::vec3 k1Velocity = k1Velocities[i];
      glm::vec3 k2Velocity = k2Velocities[i];
      glm::vec3 k3Velocity = k3Velocities[i];
      glm::vec3 k4Velocity = k4Velocities[i];
      p->position = (originalPosition + deltaT / 6.0f * (k1Velocity + 2.0f*k2Velocity + 2.0f*k3Velocity + k4Velocity));
      // update velocity
      glm::vec3 originalVelocity = originalVelocities[i];
      glm::vec3 k1Force = k1Forces[i];
      glm::vec3 k2Force = k2Forces[i];
      glm::vec3 k3Force = k3Forces[i];
      glm::vec3 k4Force = k4Forces[i];
      p->velocity= (originalVelocity + deltaT / (6.0f * p->mass) * (k1Force + 2.0f*k2Force + 2.0f*k3Force + k4Force));
    }
  }
}

}} /* namespace snus::physics */
