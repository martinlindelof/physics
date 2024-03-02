#pragma once
#include "snus/snus.hpp"

namespace snus { namespace physics {
class Integrator
{
  public:
  virtual void step (const f32 &t) = 0;
};
}} /* namespace snus::physics */