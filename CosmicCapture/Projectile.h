#pragma once
#include "Entity.h"
#include "GlobalState.h"
#include "physics/Physics.h"
#include "physics/VehicleFilterShader.h"


class Projectile : public Entity
{
	public:
		Projectile(std::shared_ptr<Camera> camera);
		void attachPhysics(Physics& instance) override;
		void draw(Physics& instance, const ShaderProgram& depthTexture, bool depth, const unsigned& depthMap) override;
		void simulate(Physics& instance) override;
		void cleanUpPhysics() override;

		void attachVehicle(PxVehicleDrive4W* vehicle) { mVehicles.push_back(vehicle); }
	private:
		std::vector<PxVehicleDrive4W*> mVehicles;
};

