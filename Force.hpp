#pragma once

namespace snus { namespace physics {
class Force
{
  public:
  virtual void turn_on () = 0;
  virtual void turn_off () = 0;
  virtual bool is_on () const = 0;
  virtual bool is_off () const = 0;
  virtual void apply () = 0;
};
}} /* namespace snus::physics */