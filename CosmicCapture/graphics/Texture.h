#pragma once

#include <string>
#include <GL/glew.h>


class Texture
{
public:
	Texture(const std::string& path, GLuint interpolation);

	void bind() const { glBindTexture(GL_TEXTURE_2D, mID); }
	static void unbind() { glBindTexture(GL_TEXTURE_2D, 0);  }

private:
	unsigned int mID{};
};

