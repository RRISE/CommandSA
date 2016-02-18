#ifndef SHOOTER_H
#define SHOOTER_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem
{
private:
	Preferences* prefs;
	CANTalon* pCollectorMotor;
	CANTalon* pShooterMotorLeft;
	CANTalon* pShooterMotorRight;
	Timer* pTimer;
	DigitalInput* limitSwitch;
	Counter* counter;
	AnalogInput* frontUltra;

public:
	Shooter();

	float fIntakeSpeed;
	float fShootSpeed;
	float fKickerSpeed;
	float fRegressionSpeed;

	void Intake(float speed);
	void Shoot(float speed);
	void LowGoal();
	float GetShootSpeed();
	float GetIntakeSpeed();
	float GetShootSpeed_R(); //regression shooting
	float GetKickerSpeed();
	void StopShoot();
	void StopIntake();

	//util
	void InitDefaultCommand();
	void StartTimer();
	void StopTimer();
	bool IsSwitchSet();
	void InitializeCounter();
	double GetCurrentTime();
	double GetUltraAt(int port);
};


#endif
