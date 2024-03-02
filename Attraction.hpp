// + attracs
// - repels
#pragma once
#include <glm/glm.hpp>
#include "Force.hpp"
#include "Particle.hpp"
#include "snus/snus.hpp"

namespace snus { namespace physics {

class Attraction : public Force
{
  public:
  Attraction (Particle* __a, Particle* __b, f32 __strength, f32 __distance);
  ~Attraction ();

  Particle* A;
  Particle* B;
  f32 strength;
  bool on;
  f32 distance;
  f32 distanceSquared;

  f32 get_distance ();
  void set_distance (f32 __distance);
  f32 get_strength ();
  void set_strength (f32 __strength);
  void turn_on ();
  void turn_off ();
  bool is_on () const;
  bool is_off () const;
  void apply ();
};
}} /* namespace snus::physics */