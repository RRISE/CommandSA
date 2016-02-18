#include "Shooter.h"
#include "../RobotMap.h"
#include <sstream>

Shooter::Shooter() :
Subsystem("Shooter")
{
	pCollectorMotor = new CANTalon(TALON_COLLECTOR);
	pShooterMotorRight = new CANTalon(TALON_RIGHT_SHOOTER);
	pShooterMotorLeft = new CANTalon(TALON_LEFT_SHOOTER);

	pShooterMotorLeft->SetInverted(true);

	prefs = Preferences::GetInstance();
	fShootSpeed = prefs->GetFloat("ShootSpeed", 0.0f);
	fIntakeSpeed = prefs->GetFloat("IntakeSpeed", 0.0f);
	fKickerSpeed =prefs->GetFloat("KickerSpeed", 0.0f);

	limitSwitch = new DigitalInput(9);
	counter = new Counter(limitSwitch);
	frontUltra = new AnalogInput(ULTRASONIC_FRONT_ANIPORT);

	pTimer = new Timer;
}

void Shooter::Intake(float speed)
{
	pCollectorMotor->Set(-speed);
}

void Shooter::Shoot(float speed)
{
	pShooterMotorRight->Set(speed);
	pShooterMotorLeft->Set(speed);
}


void Shooter::LowGoal()
{
	pCollectorMotor->Set(0.75);
}

void Shooter::StartTimer()
{
	pTimer->Start();
}

double Shooter::GetCurrentTime()
{
	return pTimer->Get();
}

void Shooter::StopTimer()
{
	pTimer->Stop();
	pTimer->Reset();
}


float Shooter::GetShootSpeed()
{
	fShootSpeed = prefs->GetFloat("ShootSpeed", 0.6f);
	return fShootSpeed;
}

////hypothesis
float Shooter::GetShootSpeed_R(){
	int degree = prefs->GetFloat("degree", 1);
	double displacement = GetUltraAt(ULTRASONIC_FRONT_ANIPORT);
	float output = 0;

	for(int i = 0; i < degree + 1; i++){
		std::ostringstream oss;
		oss << "theta_" << i;
		std::string prefsKey = oss.str();
		output = output + prefs->GetFloat(prefsKey, 0.0) * pow(displacement, i);
	}
	return output;
}

float Shooter::GetIntakeSpeed()
{
	fIntakeSpeed = prefs->GetFloat("IntakeSpeed", 0.5f);
	return fIntakeSpeed;
}

float Shooter::GetKickerSpeed(){
	fKickerSpeed =prefs->GetFloat("KickerSpeed", 1.0f);
	return fKickerSpeed;
}

bool Shooter::IsSwitchSet() {
	return limitSwitch->Get();
	//return counter->Get() > 0;
}

void Shooter::InitializeCounter() {
	counter->Reset();
}



void Shooter::StopIntake()
{
	pCollectorMotor->Set(0);
}

void Shooter::StopShoot()
{
	pShooterMotorRight->Set(0);
	pShooterMotorLeft->Set(0);
}


void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double Shooter::GetUltraAt(int port){
	switch(port){
	case ULTRASONIC_FRONT_ANIPORT:
		return frontUltra->GetAverageVoltage() * ULTRASONIC_READING_TO_INCH / ULTRASONIC_SCALEFACTOR;
		break;
	default:
		return 9999.9; //impossible value
	}
}

