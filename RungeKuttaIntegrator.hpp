#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Integrator.hpp"
#include "ParticleSystem.hpp"

namespace snus { namespace physics {
class RungeKuttaIntegrator : public Integrator
{
  public:
    RungeKuttaIntegrator (ParticleSystem* __system);
    ~RungeKuttaIntegrator ();

    std::vector<glm::vec3> originalPositions;
    std::vector<glm::vec3> originalVelocities;
    std::vector<glm::vec3> k1Forces;
    std::vector<glm::vec3> k1Velocities;
    std::vector<glm::vec3> k2Forces;
    std::vector<glm::vec3> k2Velocities;
    std::vector<glm::vec3> k3Forces;
    std::vector<glm::vec3> k3Velocities;
    std::vector<glm::vec3> k4Forces;
    std::vector<glm::vec3> k4Velocities;
    ParticleSystem* system;

    void allocateParticles ();
    void step (const f32 &deltaT);
};

}} /* namespace snus::physics */