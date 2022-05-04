#pragma once

#include "Particle.h"
#include <stdlib.h>
#include <stdio.h>

class Solver
{
public:
	// Constructor and Destructor
	Solver();
	~Solver();

	/// Methods //
	void initialize();
	void update();
	void addParticle(vector2f pos, vector2f vel = vector2f(0.0f, 0.0f));
	void addParticle(float mass, vector2f pos, vector2f vel = vector2f(0.0f, 0.0f));

	/// Variables
	Particle* particles[MAX_NUMBER_OF_PARTICLES];

	float worldSize_width;
	float worldSize_height;

	int currentParticles = 0;

private:
	// Methods
	void integration();
	void calculateDensityPressure();
	void calculateForces();

	//Variables
	vector2f gravity;
};