#include "SPHMethods.h"

Solver::Solver()
{

}

Solver::~Solver()
{
	free(particles);
}

// Default settings
void Solver::initialize()
{
	worldSize_width = 1.0f;
	worldSize_height = 1.0f;

	gravity.x = GRAVITY_X;
	gravity.y = GRAVITY_Y;
}

// Calculating forces each frame
void Solver::update()
{
	calculateDensityPressure();

	calculateForces();

	integration();
}

void Solver::calculateDensityPressure()
{
	for (int i = 0; i < currentParticles; i++)
	{
		particles[i]->density = 0.0f;

		for (int j = 0; j < currentParticles; j++)
		{
			// Finding vector between particles
			vector2f r = particles[i]->position - particles[j]->position;
			// Distance in power of 2 for equations
			float r2 = r * r;

			// Neighbour condition
			if (r2 >= HH || r2 < 1e-12)
			{
				continue;
			}

			// Calculating density
			// pi = sum[mj * Wpoly6(h^2 - r^2)^3]  (4.2 and 4.20)
			particles[i]->density += particles[j]->mass * POLY6 * pow(HH - r2, 3);
		}

		// Addition density of current particle 
		particles[i]->density += particles[i]->mass * SELF_POLY6;

		// Calculating individual pressure by equation of state by R. H. Cole
		particles[i]->pressure = (pow(particles[i]->density / DEFALT_DENSITY, 7) - 1) * GAS_CONSTANT;
	}
}

void Solver::calculateForces()
{
	for (int i = 0; i < currentParticles; i++)
	{
		// Default acceleration equals to zero
		particles[i]->acceleration = 0;

		for (int j = 0; j < currentParticles; j++)
		{
			if (i == j)
				continue;

			// Finding vector between two particles
			vector2f r0 = particles[i]->position - particles[j]->position;
			// Finding vector magnitude
			float r2 = r0.x * r0.x + r0.y * r0.y;

			if (r2 < HH && r2 > 1e-12)
			{
				float r = sqrt(r2);

				// Part for F_pressure and F_viscosity
				float part = particles[j]->mass / particles[j]->density / 2;
				float Kr = H - r;
				float Kp = SPIKY_GRAD * Kr * Kr;

				// Calculating F_pressure (4.4)
				float tempForce = part * (particles[i]->pressure + particles[j]->pressure) * Kp;
				particles[i]->acceleration -= r0 / r * tempForce;

				vector2f rV = particles[j]->evelocity - particles[i]->evelocity;

				float Kv = VISC_KERNEL * (H - r); //t2W
				tempForce = part * VISCOSITY * Kv;
				particles[i]->acceleration += rV * tempForce; // f viscocity
			}
		}
		particles[i]->acceleration = particles[i]->acceleration / particles[i]->density; //ai = dui/dt = Fi/pi
	}
}

void Solver::integration()
{
	for (int i = 0; i < currentParticles; i++)
	{
		particles[i]->velocity += particles[i]->acceleration * DT + gravity * DT;
		particles[i]->position += particles[i]->velocity * DT;

		if (particles[i]->position.x >= worldSize_width)
		{
			particles[i]->velocity.x = particles[i]->velocity.x * BOUND_DAMPING;
			particles[i]->position.x = worldSize_width - BOUNDARY;
		}

		if (particles[i]->position.x < 0.f)
		{
			particles[i]->velocity.x = particles[i]->velocity.x * BOUND_DAMPING;
			particles[i]->position.x = BOUNDARY;
		}

		if (particles[i]->position.y >= worldSize_height)
		{
			particles[i]->velocity.y = particles[i]->velocity.y * BOUND_DAMPING;
			particles[i]->position.y = worldSize_height - BOUNDARY;
		}

		if (particles[i]->position.y < 0.f)
		{
			particles[i]->velocity.y = particles[i]->velocity.y * BOUND_DAMPING;
			particles[i]->position.y = BOUNDARY;
		}

		particles[i]->evelocity = (particles[i]->evelocity + particles[i]->velocity) / 2.f;
	}
}

void Solver::addParticle(vector2f pos, vector2f vel)
{
	if (currentParticles <= MAX_NUMBER_OF_PARTICLES)
	{
		particles[currentParticles] = new Particle(pos, vel, currentParticles);
		particles[currentParticles]->mass = PARTICLE_MASS;
		currentParticles++;
	}
}

void Solver::addParticle(float mass, vector2f pos, vector2f vel)
{
	if (currentParticles <= MAX_NUMBER_OF_PARTICLES)
	{
		particles[currentParticles] = new Particle(pos, vel, currentParticles);
		particles[currentParticles]->mass = mass;
		currentParticles++;
	}
}