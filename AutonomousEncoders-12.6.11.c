#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Sensor, S3,     GYRO,                sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     HTPB,                sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorNormal, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
#pragma config(SrvoPosition,  Position01,            234, 128, 249, 141,  58, 128, 128, 128)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Sensor, S3,     GYRO,                sensorI2CHiTechnicGyro)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

#include "common.h"

#include "HTPB-driver.h"

#include "HTGYRO-driver.h"
#include "HTAC-driver.h"
//#include "drivers/HTSMUX-driver.h"
//#include "drivers/HTGYRO-driver.h"
#include "HTEOPD-driver.h"

void move(int distance, int speed)
{
  distance = distance*1400;
  int one, two, three, four;
  nMotorEncoder[motorE] = 0;
  nMotorEncoder[motorD] = 0;

  while(nMotorEncoder[motorE] > -distance)  // while the right encoder value is less than 0:
  {
    motor[motorG] = 100;           // set mtr_S1_C1_1 to speed 75
    motor[motorF]  = 100;          // set mtr_S1_C1_2 to speed 75
      eraseDisplay();
  one = nMotorEncoder[motorD];
  two = nMotorEncoder[motorE];
  three = nMotorEncoder[motorF];
  four = nMotorEncoder[motorG];
  nxtDisplayCenteredTextLine(1, "Motor One: %4d", one);
  nxtDisplayCenteredTextLine(2, "Motor Two: %4d", two);
  //nxtDisplayCenteredTextLine(3, "Motor Three: %4d", three);
  //nxtDisplayCenteredTextLine(4, "Motor Four: %4d", four);

   wait1Msec(50);
  }
    motor[motorF] = 0;              // set mtr_S1_C1_1 to speed 0
    motor[motorG]  = 0;              // set mtr_S1_C1_2 to speed 0
    wait1Msec(50);
}

void initialize()
{
  HTGYROstartCal(S3);
}

void turn(int angle, short speed)  // Steven Mostovoy
{
	if (angle < 0)
	{
		angle *= -1;
		speed *= -1;
	}
	wait1Msec(200);

	HTGYROstartCal(S3);
	wait1Msec(200);
	int gyro[3] = {0,0,0};
	int gyroMid[3] = {0,0,0};
	int gyroFinal[4] = {0,0,0,0};
	motor[motorF] = speed;
	motor[motorG] = -speed;
	int integral = 0;
	while (true)
	{
		for (int i = 2; i > 0; --i)
			gyro[i] = gyro[i-1];
		gyro[0] = HTGYROreadRot(S3);

		float mu = 10.0/11.0;

		gyroMid[0] = gyro[0];
		for (int i = 1; i < 3; ++i)
			gyroFinal[i] = mu * (gyro[i] - gyroMid[i-1]) + gyroMid[i-1];

		for (int i = 3; i > 0; --i)
			gyroFinal[i] = gyroMid[i-1];
		gyroFinal[0] = gyroMid[1];

		integral += (gyroFinal[0] + gyroFinal[1]*2 + gyroFinal[2]*2 + gyroFinal[3])/6;

		//writeDebugStreamLine("%d", integral);
		if (abs(integral * 0.0604) > angle) break;
		wait1Msec(10);
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
}

task main()
{
  initialize();
  move(4.2, 100);
  /*
  turn(90, 100);
  move(1000, 100);
  turn(180, 100);
  move(2000, 100);
  turn(-100, 100);
  */
}
