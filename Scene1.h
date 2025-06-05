#pragma once

#include "GameEngine.h"

class Scene1 : public Game
{
	void loadScene() override
	{
		// Set the window title
		glfwSetWindowTitle(renderWindow, "Scene 1");

		// Set the clear color
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		// Build and use the shader program
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		GLuint shaderProgram = BuildShaderProgram(shaders);

		// Make the shader program "current" Not needed if transformations are stored in uniform buffers
		//glUseProgram(shaderProgram);

		SharedMaterials::setUniformBlockForShader(shaderProgram);
		SharedTransformations::setUniformBlockForShader(shaderProgram);
		SharedLighting::setUniformBlockForShader(shaderProgram);
	
		// ****** Blue Sphere  *********
		GameObjectPtr sphereObject2 = std::make_shared<GameObject>();

		addChildGameObject(sphereObject2);
		sphereObject2->setPosition(vec3(0.0f, 0.0f, -40.0f), WORLD);

		Material sphereMaterial2;
		sphereMaterial2.setDiffuseTexture(Texture::GetTexture("Textures/Earthmap.jpg")->getTextureObject());

		sphereMaterial2.setTextureMode(DECAL);

		std::shared_ptr<SphereMeshComponent> sphereMesh2 = std::make_shared<SphereMeshComponent>(shaderProgram, sphereMaterial2, 10.0f, 16, 32);
		sphereObject2->addComponent(sphereMesh2);

		sphereObject2->addComponent(make_shared<ArrowRotateComponent>(glm::radians(25.0f)));

	}
};
