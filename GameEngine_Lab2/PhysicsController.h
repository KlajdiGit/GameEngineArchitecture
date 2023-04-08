#ifndef PHYSICS_CONTROLLER_H
#define PHYSICS_CONTROLLER_H

#include "StandardIncludes.h"
#include "Particle.h"

class PhysicsController : public Singleton<PhysicsController>
{
public:
	//Constructor / Destructor
	PhysicsController();
	virtual ~PhysicsController();

	//Accessors
	float GetGravity() { return  m_gravity; }
	void SetGravity(float _gravity) { m_gravity = _gravity; }
	vector<Particle*>& GetParticles() { return m_particles; }

	//Methods
	void Update(float _deltaTime);
	Particle* AddParticle(glm::vec2 _position, float _lifeTIme);
	string ToString();

private:
	//Members
	float m_gravity;
	glm::vec2 m_force;
	vector<Particle*> m_particles;
};

#endif // PHYSICS_CONTROLLER_H
