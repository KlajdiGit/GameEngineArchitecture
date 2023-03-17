#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "StandardIncludes.h"
struct ControllerInfo
{
	//Members
	SDL_JoystickID ID = -1;
	SDL_GameController* Controller = nullptr;
	string Name;
};

class Controller
{
public:
	//Constructors/Destructors
	Controller();
	virtual ~Controller();

	//Accessors
	vector<ControllerInfo>& GetControllers() { return m_controllers; }
	
	//Methods
	void DeleteControllers();
	bool Added(SDL_Event _event);
	bool Removed(SDL_Event _event);

	string ToString();

private:
	//Methods
	void Add(SDL_GameController* _controller, int _controllerID);

	//Members
	vector<ControllerInfo> m_controllers;

};

#endif //CONTROLLER_H

