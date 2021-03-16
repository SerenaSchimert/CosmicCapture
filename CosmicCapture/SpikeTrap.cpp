#include "SpikeTrap.h"

#include "GlobalState.h"
#include "physics/VehicleFilterShader.h"
#include <fmt/format.h>

SpikeTrap::SpikeTrap(const std::shared_ptr<Camera>& camera): Entity(
	"models/spike_trap.obj", "textures/blank.jpg", camera)
{
	spikeTrapState state;
	m_id = State::spike_trap_states.size();

	State::spike_trap_states.push_back(state);
}

void SpikeTrap::draw(Physics& instance, const ShaderProgram& depthTexture, bool depth)
{
	// Only draw when actually placed
	if (!hasOwningVehicle())
	{
	const PxMat44 modelMatrix(body->getGlobalPose());
		mGeometry->draw(modelMatrix, depthTexture, depth);
	}
}

void SpikeTrap::simulate(Physics& instance)
{
	// Waiting for global activation
	// (gives some time for the player that placed the spike trap to move out of the way)
	if (active && !State::spike_trap_states[m_id].active)
	{
		activationTimer += 1.0f;
		if (activationTimer >= ACTIVATION_TIME)
		{
			State::spike_trap_states[m_id].active = true;
			activationTimer = 0.0f;
			active = false;
		}
	}

	// Prevent the vehicle from moving while caught in the spike trap
	if (State::spike_trap_states[m_id].inUse && hasAffectedVehicle())
	{
		mAffectedVehicle.value()->setToRestState();
		affectionTimer += 1.0f;
		if (affectionTimer > AFFECTION_TIME)
		{
			State::spike_trap_states[m_id].inUse = false;
			mAffectedVehicle.reset();
			affectionTimer = 0.0f;
			State::spike_trap_states[m_id].finished = true;
		}
	}
}

void SpikeTrap::cleanUpPhysics()
{
	PX_RELEASE(body);
	PX_RELEASE(State::spike_trap_states[m_id].triggerBody);
}

bool SpikeTrap::processInput(const std::map<MovementFlags, bool>& inputs, Physics& instance)
{
	const bool spaceReleased = inputs.at(MovementFlags::ACTION);
	if (!spaceReleased)
	{
		if (hasOwningVehicle())
		{
			PxVec3 currentVehiclePos = mOwnerVehicle.value()->getRigidDynamicActor()->getGlobalPose().p;
			fmt::print("Current vehicle position: ({}, {}, {})\n", currentVehiclePos.x, currentVehiclePos.y, currentVehiclePos.z);
			currentVehiclePos.y -= 2.0f; // Move down slightly

			PxShape* spikeTrapMarker = instance.gPhysics->createShape(PxBoxGeometry(1.0f, 2.0f, 1.0f), *instance.gMaterial, true);
			spikeTrapMarker->setSimulationFilterData(PxFilterData(COLLISION_FLAG_SCENERY, COLLISION_FLAG_SCENERY_AGAINST, 0, 0));
			body = instance.gPhysics->createRigidStatic(PxTransform(currentVehiclePos));
			body->attachShape(*spikeTrapMarker);
			spikeTrapMarker->release();
			instance.gScene->addActor(*body);

			PxShape* speedboostPickupTriggerShape = instance.gPhysics->createShape(PxBoxGeometry(1.1f, 2.f, 1.1f), *instance.gMaterial, true);
			//trigger box for running into the spike trap
			speedboostPickupTriggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
			speedboostPickupTriggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
			State::spike_trap_states[m_id].triggerBody = instance.gPhysics->createRigidStatic(PxTransform(currentVehiclePos));
			State::spike_trap_states[m_id].triggerBody->attachShape(*speedboostPickupTriggerShape);
			instance.gScene->addActor(*State::spike_trap_states[m_id].triggerBody);

			mOwnerVehicle.reset(); // No longer attached to the vehicle
			fmt::print("Placed the spike trap!\n");
			active = true;
			return true;
		}
	}

	return false;
}