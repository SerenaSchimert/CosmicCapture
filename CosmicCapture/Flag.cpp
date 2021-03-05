#include "Flag.h"

#include <memory>



Flag::Flag(const ShaderProgram& shaderProgram, std::shared_ptr<Camera> camera) :
	Entity("models/flag.ply", "textures/blank.jpg", shaderProgram, camera)
{}

void Flag::attachPhysics(Physics& instance)
{
	PxShape* flag = instance.gPhysics->createShape(PxBoxGeometry(0.1f, 2.f, 0.1f), *instance.gMaterial, true); //create flag shape
	flag->setSimulationFilterData(PxFilterData(COLLISION_FLAG_OBSTACLE, COLLISION_FLAG_OBSTACLE_AGAINST, 0, 0));
	State::flagBody = instance.gPhysics->createRigidDynamic(PxTransform(PxVec3(-10.f, 2.f, -12.f)));
	//create static rigid body - wont move
	State::flagBody->attachShape(*flag);
	flag->release();
	instance.gScene->addActor(*State::flagBody);
	//----------------------------------------------------------
	//Trigger Shapes--------------------------------------------
	PxShape* pickupShape = instance.gPhysics->createShape(PxBoxGeometry(1.1f, 2.f, 1.1f), *instance.gMaterial, true);
	//trigger box for picking up the flag
	pickupShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	pickupShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	State::pickupBox = instance.gPhysics->createRigidStatic(PxTransform(PxVec3(-10.f, 2.f, -12.f)));
	State::pickupBox->attachShape(*pickupShape);
	instance.gScene->addActor(*State::pickupBox);

}

void Flag::draw(Physics& instance, const ShaderProgram& depthTexture, bool depth, const unsigned& depthMap)
{
	// Draw the flag
	PxTransform transform = State::flagBody->getGlobalPose();
	PxMat44 modelMatrix(transform);
	mGeometry->draw(modelMatrix, depthTexture, depth, depthMap);
}

void Flag::simulate(Physics& instance)
{
	// TODO: Assuming that there is only one vehicle, should change that at some point
	if (State::flagPickedUpBy[0]) {
		PxVec3 pos = State::vehicleRDs[0]->getGlobalPose().p;
		State::flagBody->setGlobalPose(PxTransform(PxVec3(pos.x, pos.y + 2.0f, pos.z)));
	}
	else if (State::flagPickedUpBy[1]) {
		PxVec3 pos = State::vehicleRDs[1]->getGlobalPose().p;
		State::flagBody->setGlobalPose(PxTransform(PxVec3(pos.x, pos.y + 2.0f, pos.z)));
	}
	else if (State::flagPickedUpBy[2]) {
		PxVec3 pos = State::vehicleRDs[2]->getGlobalPose().p;
		State::flagBody->setGlobalPose(PxTransform(PxVec3(pos.x, pos.y + 2.0f, pos.z)));
	}
	else if (State::flagPickedUpBy[3]) {
		PxVec3 pos = State::vehicleRDs[3]->getGlobalPose().p;
		State::flagBody->setGlobalPose(PxTransform(PxVec3(pos.x, pos.y + 2.0f, pos.z)));
	}
	else {
		State::flagBody->setGlobalPose(PxTransform(PxVec3(-10.f, 2.f, -12.f)));
	}
}

void Flag::cleanUpPhysics()
{
	PX_RELEASE(State::pickupBox);
	PX_RELEASE(State::flagBody);
}
