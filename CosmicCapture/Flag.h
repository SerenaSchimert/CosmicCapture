#pragma once

#include "Entity.h"
#include "GlobalState.h"
#include "physics/VehicleFilterShader.h"

class Flag : public Entity
{
public:
	Flag(const ShaderProgram& shaderProgram, std::shared_ptr<Camera> camera);

	void attachPhysics(Physics& instance) override;
	void draw(Physics& instance, const ShaderProgram& depthTexture, bool depth, const unsigned& depthMap) override;
	void simulate(Physics& instance) override;
	void cleanUpPhysics() override;

};

