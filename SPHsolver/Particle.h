#pragma once

#include "vector2.h"

// Defining main variables for calculations
// Time step etc
#define MAX_NUMBER_OF_PARTICLES 5000
#define H 0.06 // h
#define HH H*H // h*h
#define PARTICLE_MASS 0.05 // Default mass of each particle
#define DEFALT_DENSITY 1000.0  // The density of a small portion of a fluid in a Lorentz frame in which that portion of the fluid is at rest
#define GAS_CONSTANT 1.0 
#define VISCOSITY 6.5 // ???
#define DT 0.003 // Delta time

// Gravity forces 
#define GRAVITY_X 0.0
#define GRAVITY_Y -9.8

// Kernels
#define POLY6 315.0/(64.0 * PI * (H*H*H*H*H*H*H*H*H)) // W poly6 kernel for density 
#define SPIKY_GRAD -45.0 / (PI*(H*H*H*H*H*H)) // Spiky kernel for pressure
#define VISC_KERNEL	 45.0 / (PI*(H*H*H*H*H*H)) // Viscosity kernel
#define SELF_POLY6 315.0/(64.0 * PI * (H*H*H)) // When distance between particles == 0

// Boundary settings
#define BOUNDARY 0.0005
#define BOUND_DAMPING 0.0; // -0.5

struct Particle
{
	// Scalar variables
	float mass;
	float density;
	float pressure;

	// Vector variables
	vector2f position;
	vector2f velocity;
	vector2f evelocity;
	vector2f acceleration;

	// Constructor 
	Particle(vector2f position, vector2f velocity, int id)
	{
		mass = PARTICLE_MASS;
		density = DEFALT_DENSITY;
		pressure = 0.f;
		acceleration = 0.f;

		this->position = position;
		this->velocity = velocity;
	}
};