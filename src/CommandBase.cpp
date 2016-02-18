#include "CommandBase.h"
#include "Subsystems/Shooter.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
Shooter* shooter = NULL;
Shoot* shoot = NULL;


CommandBase::CommandBase(const std::string &name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	shooter = new Shooter();
	oi = new OI();
}
