#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "snus/snus.hpp"
#include "Particle.hpp"
#include "Spring.hpp"
#include "Attraction.hpp"
#include "Force.hpp"
#include "Integrator.hpp"

namespace snus { namespace physics {
class ParticleSystem
{
  public:
    ParticleSystem ();
    ParticleSystem (f32 g, f32 drag);
    ~ParticleSystem ();

    enum IntegratorType {RUNGE_KUTTA, MODIFIED_EULER, EULER};
    std::vector<Particle*> particles;
    std::vector<Spring*> springs;
    std::vector<Attraction*> attractions;
    std::vector<Force*> forces;
    Integrator* integrator;
    glm::vec3 gravity;
    f32 drag;
    const f32 default_gravity = 0.0000;
    const f32 default_drag = 0.0001;

    Particle* make_particle (f32 __mass, f32 __x, f32 __y, f32 __z);
    Particle* make_particle (f32 __mass, f32 __x, f32 __y);
    Particle* make_particle (f32 __mass, glm::vec2 __point);
    Particle* make_particle ();
    Spring* make_spring (Particle* __a,
                         Particle* __b,
                         float     __ks,
                         float     __d,
                         float     __r);
    Attraction* make_attraction (Particle* __a,
                                 Particle* __b,
                                 float     __k,
                                 float     __distance);
    void set_integrator (Integrator *i);
    void set_integrator (IntegratorType type);
    void set_gravity (f32 x, f32 y, f32 z);
    void set_gravity (f32 g);
    void set_drag (f32 d);
    void tick (f32 t);
    void tick ();
    void clear();
    void add_force (Force* __force);
    void remove_particle (Particle* __p);
    void remove_particle (u32 i);
    void remove_spring (Spring* __s);
    void remove_spring (u32 i);
    void remove_attraction (Attraction* __a);
    void remove_attraction (u32 i);
    void remove_force (Force* __force);
  // protected:
    void apply_forces ();
    void clear_forces ();
};
}} /* namespace snus::physics */