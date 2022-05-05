#pragma once

#include <math.h>

#define PI 3.14159265359

struct vector2f
{
	// Two dimensinal vector
	double x, y;

	// Constructor with predefined default variables 
	vector2f(double x = 0, double y = 0) : x(x), y(y) {}

	// Overloading main operations with vectors
	vector2f& operator=(const vector2f& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	vector2f operator=(const double f)
	{
		x = f;
		y = f;
		return vector2f(x, y);
	}

	vector2f operator+(const vector2f& v)
	{
		return vector2f(v.x + x, v.y + y);
	}

	vector2f& operator+=(const vector2f& v)
	{
		this->x += v.x;
		this->y += v.y;
		return *this;
	}

	vector2f& operator-=(const vector2f& v)
	{
		this->x -= v.x;
		this->y -= v.y;
		return *this;
	}

	vector2f operator-(const vector2f& v)
	{
		return vector2f(x - v.x, y - v.y);
	}

	vector2f operator*(const double f)
	{
		return vector2f(f * x, f * y);
	}

	double operator*(vector2f v)
	{
		return v.x * x + v.y * y;
	}

	vector2f operator/(double f)
	{
		return vector2f(x / f, y / f);
	}

	// Finding unit vector of given one
	vector2f unit()
	{
		return vector2f(x, y) * (1 / (sqrt((double)(x * x + y * y))));
	}
};

// Function for circle of particles
static vector2f unitVecFromDeg(double deg)
{
	vector2f v;
	v.x = cos(deg * (PI / 180.0));
	v.y = sin(deg * (PI / 180.0));
	return v;
}
