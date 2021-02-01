#include <string>
#include <fmt/format.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Window.h"
#include "graphics/Geometry.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Texture.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

//PHYSX Stuff----------------------------------------------------------
#include <ctype.h>


#include "physx/PxPhysicsAPI.h"
#include "physx/vehicle/PxVehicleSDK.h"
#define PX_RELEASE(x) if(x){x->release();x=NULL;}

using namespace physx;

PxDefaultErrorCallback gErrorCallback;
PxDefaultAllocator gAllocator;
PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;

PxCooking* gCooking = NULL;

PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

//VehicleSceneQueryData* gVehicleSceneQueryData = NULL;
PxBatchQuery* gBatchQuery = NULL;

PxVehicleDrivableSurfaceToTireFrictionPairs* gFrictionPairs = NULL;

PxRigidStatic* gGroundPlane = NULL;
PxVehicleDrive4W* gVehicle4W = NULL;

bool					gIsVehicleInAir = true;


void initPhysics() {
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
	bool recordMemoryAllocations = true;
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), recordMemoryAllocations, gPvd);
	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(PxTolerancesScale()));
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	PxU32 numWorkers = 1;
	gDispatcher = PxDefaultCpuDispatcherCreate(numWorkers);
	sceneDesc.cpuDispatcher = gDispatcher;

	gScene = gPhysics->createScene(sceneDesc);

	fmt::print("Physx initialized\n");
}

void cleanupPhysics()
{	
	PX_RELEASE(gMaterial);
	PX_RELEASE(gCooking);
	PX_RELEASE(gScene);
	PX_RELEASE(gDispatcher);
	PX_RELEASE(gPhysics);
	fmt::print("Physx cleaned up\n");
} 
//---------------------------------------------------------------------


int main(int argc, char** args) {
	// TODO: Make the window resizable
	const GLint width = 1280, height = 720;

	// View pipeline
	const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	glm::mat4 model(1.0f);
	auto view = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -3.0f });
	auto projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	Window window("Cosmic Capture", width, height);
	ShaderProgram shaderProgram("shaders/main.vert", "shaders/main.frag");
	shaderProgram.compile();

	CpuGeometry cpuGeom;
	cpuGeom.vertices = {
		{0.5f,  0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, -0.5f, 0.0f},
		{-0.5f,  0.5f, 0.0f}
	};
	cpuGeom.cols = {
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 1.0f}
	};
	cpuGeom.texCoords = {
		{1.0f, 1.0f},
		{1.0f, 0.0f},
		{0.0f, 0.0f},
		{0.0f, 1.0f}
	};
	cpuGeom.indices = {
		0, 1, 3,
		1, 2, 3
	};

	GpuGeometry gpuGeometry;
	gpuGeometry.uploadData(cpuGeom);

	const Texture texture("textures/wall.jpg", GL_LINEAR);
	texture.bind();

	initPhysics();

	// Loop until the user closes the window
	while (true) {
		if (SDL_PollEvent(&window.event)) {
			if (window.event.type == SDL_QUIT) break;
		}
		window.startImGuiFrame();
		Window::clear();

		shaderProgram.use();

		// View pipeline
		const auto modelLoc = glGetUniformLocation(static_cast<unsigned int>(shaderProgram), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		const auto viewLoc = glGetUniformLocation(static_cast<unsigned int>(shaderProgram), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		const auto projectionLoc = glGetUniformLocation(static_cast<unsigned int>(shaderProgram), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		gpuGeometry.drawData();

		ImGui::Begin("Framerate Counter!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window.swap();
	}

	cleanupPhysics();

	return 0;
}


