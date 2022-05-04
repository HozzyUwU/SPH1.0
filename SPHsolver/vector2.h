#pragma once

#include <math.h>

#define PI 3.14159265359

struct vector2f
{
	// Two dimensinal vector
	float x, y;

	// Constructor with predefined default variables 
	vector2f(float x = 0, float y = 0) : x(x), y(y) {}

	// Overloading main operations with vectors
	vector2f& operator=(const vector2f& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	vector2f operator=(const float f)
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

	vector2f operator*(const float f)
	{
		return vector2f(f * x, f * y);
	}

	float operator*(vector2f v)
	{
		return v.x * x + v.y * y;
	}

	vector2f operator/(float f)
	{
		return vector2f(x / f, y / f);
	}

	// Finding unit vector of given one
	vector2f unit()
	{
		return vector2f(x, y) * (1 / (sqrt((double)(x * x + y * y))));
	}
};
