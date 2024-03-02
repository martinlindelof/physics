#include "ParticleSystem.hpp"
#include "ModifiedEulerIntegrator.hpp"
#include "EulerIntegrator.hpp"
#include "RungeKuttaIntegrator.hpp"

namespace snus { namespace physics {

ParticleSystem::ParticleSystem ()
{
  integrator = new ModifiedEulerIntegrator (this);
  gravity = glm::vec3 (0, default_gravity, 0);
  drag = default_drag;
}

ParticleSystem::ParticleSystem (f32 __gravity, f32 __drag)
{
  integrator = new ModifiedEulerIntegrator (this);
  gravity = glm::vec3 (0, __gravity, 0);
  drag = __drag;
}

ParticleSystem::~ParticleSystem ()
{
  //
}

Particle*
ParticleSystem::make_particle (f32 __mass, f32 __x, f32 __y, f32 __z)
{
  Particle* particle = new Particle (__mass);
  particle->position = glm::vec3 (__x, __y, __z);
  particles.push_back (particle);
  return particle;
}

Particle*
ParticleSystem::make_particle (f32 __mass, glm::vec2 __point)
{
  return make_particle (__mass, __point.x, __point.y, 0.0);
}

Particle*
ParticleSystem::make_particle (f32 __mass, f32 __x, f32 __y)
{
  return make_particle (__mass, __x, __y, 0.0);
}

Particle*
ParticleSystem::make_particle ()
{
  return make_particle (1.0, 0.0, 0.0, 0.0);
}

Spring*
ParticleSystem::make_spring (Particle* __a,
                             Particle* __b,
                             float     __ks,
                             float     __d,
                             float     __r)
{
  Spring* spring = new Spring (__a, __b, __ks, __d, __r);
  springs.push_back (spring);
  return spring;
}

Attraction*
ParticleSystem::make_attraction (Particle* __a,
                                 Particle* __b,
                                 float     __k,
                                 float     __distance)
{
  Attraction* force = new Attraction (__a, __b, __k, __distance);
  attractions.push_back (force);
  return force;
}

void
ParticleSystem::set_integrator (Integrator *i)
{
  delete integrator;
  integrator = i;
}

void
ParticleSystem::set_integrator (IntegratorType type)
{
  delete integrator;
  switch (type)
  {
    default:
    case IntegratorType::RUNGE_KUTTA:
      integrator = new RungeKuttaIntegrator (this);
      break;
    case IntegratorType::MODIFIED_EULER:
      integrator = new ModifiedEulerIntegrator (this);
      break;
    case IntegratorType::EULER:
      integrator = new EulerIntegrator (this);
      break;
  }
}

void
ParticleSystem::set_gravity (f32 x, f32 y, f32 z)
{
  gravity = glm::vec3 (x, y, z);
}

void
ParticleSystem::set_gravity (f32 g)
{
  gravity = glm::vec3 (0, g, 0);
}

void
ParticleSystem::set_drag (f32 d)
{
  drag = d;
}

void
ParticleSystem::tick (f32 t)
{
  integrator->step (t);
}

void
ParticleSystem::tick ()
{
  tick (1);
}

void
ParticleSystem::clear()
{
  for (Particle* p : particles)
  {
    delete p;
  }
  for (Spring* s : springs)
  {
    delete s;
  }
  for (Attraction* a : attractions)
  {
    delete a;
  }
  for (Force* f : forces)
  {
    delete f;
  }
  particles.clear();
  springs.clear();
  attractions.clear();
  forces.clear();
}

void
ParticleSystem::add_force (Force* __force)
{
  forces.push_back (__force);
}

void
ParticleSystem::remove_particle (Particle* __p)
{
  particles.erase (std::ranges::find(particles.begin(), particles.end(), __p));
  delete __p;
}

void
ParticleSystem::remove_particle (u32 i)
{
  Particle* erased = particles[i];
  particles.erase (particles.begin() + i);
  delete erased;
}

void
ParticleSystem::remove_spring (Spring* __s)
{
  springs.erase (std::ranges::find(springs.begin(), springs.end(), __s));
  delete __s;
}

void
ParticleSystem::remove_spring (u32 i)
{
  Spring* erased = springs[i];
  springs.erase (springs.begin() + i);
  delete erased;
}

void
ParticleSystem::remove_attraction (Attraction* __a)
{
  attractions.erase (std::ranges::find(attractions.begin(), attractions.end(), __a));
  delete __a;
}

void
ParticleSystem::remove_attraction (u32 i)
{
  Attraction* erased = attractions[i];
  attractions.erase (attractions.begin() + i);
  delete erased;
}

void
ParticleSystem::remove_force (Force* __force)
{
  forces.erase (std::ranges::find(forces.begin(), forces.end(), __force));
  delete __force;
}

void
ParticleSystem::apply_forces ()
{
  if (glm::length (gravity) > 0.0f)
  {
    for (Particle* particle : particles)
    {
      particle->force += gravity;
    }
  }
  for (Particle* particle : particles)
  {
    particle->force -= particle->velocity * drag;
  }
  for (Spring* spring : springs)
  {
    spring->apply();
  }
  for (Attraction* attr : attractions)
  {
    attr->apply();
  }
  for (Force* force: forces)
  {
    force->apply();
  }
}

void
ParticleSystem::clear_forces ()
{
  for (Particle* particle : particles)
  {
    particle->force = glm::vec3(0, 0, 0);
  }
}

}} /* namespace snus::physics */
