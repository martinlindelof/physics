#pragma once
#include <glm/glm.hpp>
#include "Particle.hpp"
#include "Force.hpp"

namespace snus { namespace physics {
class Spring : public Force
{
  public:
    Spring (Particle*   __a,
            Particle*   __b,
            const f32   &__ks,
            const f32   &__d,
            const f32   &__r);
    ~Spring ();

    Particle* A;
    Particle* B;
    f32 springConstant;
    f32 damping;
    f32 restLength;
    bool on;

    void turn_on ();
    void turn_off ();
    bool is_on () const;
    bool is_off () const;
    f32 get_current_length () const;
    f32 get_rest_length () const;
    f32 get_strength () const;
    void set_strength (const f32 &__ks);
    f32 get_damping () const;
    void set_damping (const f32 &__d);
    void set_rest_length (const f32 &__l);
    void apply ();

  protected:
    void setA (Particle* p);
    void setB (Particle* p);
};
}} /* namespace snus::physics */