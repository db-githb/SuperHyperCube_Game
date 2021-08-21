#pragma once

class Quaternion
{
public:
	Quaternion(float x, float y, float z, float w);
	float length();
	
	Quaternion* normalize();
	Quaternion* conjugate();
	Quaternion* multiply(Quaternion r);
	
	
	float getX();
	float getY();
	float getZ();
	float getW();

	float setX();
	float setY();
	float setZ();
	float setW();
	
	
	
private:
	float x, y, z, w;
};