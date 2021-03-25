#pragma once
#include "Entity.h"
#include "GlobalState.h"
#include "physics/VehicleFilterShader.h"
class DoorSwitchZone : public Entity {
public:
	DoorSwitchZone(const ShaderProgram& shaderProgram, std::shared_ptr<Camera> camera);
	void attachPhysics(Physics& instance) override;
	void draw(Physics& instance, const ShaderProgram& depthTexture, bool depth, const unsigned& depthMap) override;
	void simulate(Physics& instance) override;
	void cleanUpPhysics() override;

	float affectionTimer = 0;
	constexpr static float AFFECTION_TIME = 10.0f * 60.0f; // The boost will speed up the player for 10 second
};