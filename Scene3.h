#pragma once

#include "GameEngine.h"

class Scene3 : public Game
{

	void loadScene() override
	{
		// Set the window title
		glfwSetWindowTitle(renderWindow, "Scene 3");

		// Set the clear color
		glClearColor(YELLOW_RGBA.r, YELLOW_RGBA.g, YELLOW_RGBA.b, YELLOW_RGBA.a);

		// Build shader program
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "Shaders/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "Shaders/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};

		// Build the shader program
		GLuint shaderProgram = BuildShaderProgram(shaders);

		// Make the shader program "current" Not needed if transformations are stored in uniform buffers
		//glUseProgram(shaderProgram);

		// Set up uniform blocks
		SharedTransformations::setUniformBlockForShader(shaderProgram);
		SharedMaterials::setUniformBlockForShader(shaderProgram);
		SharedLighting::setUniformBlockForShader(shaderProgram);

		// ****** boxGameObject *********

		GameObjectPtr boxGameObject = std::make_shared<GameObject>();
		this->addChildGameObject(boxGameObject);
		boxGameObject->setPosition(vec3(0.0f, -5.0f, 0.0f), WORLD);

		Material boxMat;

		boxMat.setDiffuseTexture(Texture::GetTexture("Textures/wood.png")->getTextureObject());
		std::shared_ptr<BoxMeshComponent> boxMesh = std::make_shared<BoxMeshComponent>(shaderProgram, boxMat,  100.0f, 1.0f, 100.0f);

		boxGameObject->addComponent(boxMesh);
		boxGameObject->gameObjectName = "box - STATIONARY";
	
		//// ****** dinoGameObject *********

		GameObjectPtr dinoObject = std::make_shared<GameObject>();
		this->addChildGameObject(dinoObject);
		std::shared_ptr<ModelMeshComponent> dino = std::make_shared<ModelMeshComponent>("Assets/Dinosaur/Trex.obj", shaderProgram);
		dinoObject->addComponent(dino);
		dinoObject->setPosition(vec3(4.0f, -3.0f, -2.0f), WORLD);
		dinoObject->setRotation(glm::rotate(-PI/6.0f, UNIT_Y_V3), WORLD);

		GameObjectPtr jetObject = std::make_shared<GameObject>();
		this->addChildGameObject(jetObject);

		std::shared_ptr <MeshComponent> jet = make_shared<ModelMeshComponent>("Assets/Worm/Frew Worm Monster.obj", shaderProgram);
		jetObject->addComponent(jet);

		jetObject->setPosition(vec3(-4.0f, -3.0f, 0.0f), WORLD);
		jetObject->setScale(vec3(0.05f, 0.05f, 0.05f));

	} // end loadScene

};