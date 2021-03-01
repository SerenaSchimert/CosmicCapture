#include "Entity.h"

Entity::Entity(const char* modelPath, const char* texturePath, const ShaderProgram& shader, std::shared_ptr<Camera> camera)
{
	mGeometry = std::make_unique<Model>(modelPath, texturePath, shader, camera);
}