#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm.hpp>


class RigidBody
{
public:
	//Constructors / Destructors
	RigidBody();
	virtual ~RigidBody() { }

	//Accessors / Mutators
	glm::vec2& GetPositions() { return m_position; }
	void SetPosition(glm::vec2 _position) { m_position = _position; }
	glm::vec2& GetVelocity() { return m_velocity; }
	void SetVelocity(glm::vec2 _velocity) { m_velocity = _velocity; }
	float GetMass() { return m_mass; }
	void SetMass(float _mass) { m_mass = _mass; }
	bool GetDead() { return m_dead; }
	void SetDead(bool _dead) { m_dead = _dead; }

	//Method
	virtual void Update(float _deltaTime, glm::vec2 _force);

private:
	//Members
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_mass;
	bool m_dead;l
};

#endif //RIGIDBODY_H