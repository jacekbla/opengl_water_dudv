#include "Utility.h"
#include "DisplayManager.h"
#include "Loader.h"
#include "Renderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Camera.h"
#include "OBJLoader.h"
#include "Light.h"
#include "MasterRenderer.h"

#include "WaterShader.h"
#include "WaterRenderer.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"

void keyboard(unsigned char p_key, int p_x, int p_y)
{
	switch (p_key)
	{
	case 033:
	case 'q':
	case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
}

RawModel* rawModel_terrain;
TexturedModel* texturedModel_terrain;
Entity* terrain;

RawModel* rawModel_tree;
TexturedModel* texturedModel_tree;
Entity* tree;

RawModel* rawModel_tree2;
TexturedModel* texturedModel_tree2;
Entity* tree2;

RawModel* rawModel_elephant;
TexturedModel* texturedModel_elephant;
Entity* elephant;

Renderer* renderer;
StaticShader* shader;
Camera* camera;
Light* light;
MasterRenderer* masterRenderer;

std::vector<WaterTile>* waterTile;
WaterRenderer* waterRenderer;
WaterShader* waterShader;
WaterFrameBuffers* fbos;

void display(void)
{
	//entity->increasePosition(0.0f, 0.0f, -0.002f);
	//entity->increaseRotation(0.0f, 1.0f, 0.0f);
	camera->move();

	glEnable(GL_CLIP_DISTANCE0);

	//render reflection texture to fbo
	fbos->bindReflectionFrameBuffer();
	float distance = 2 * (camera->getPosition().y - waterTile->at(0).getHeight());
	float originalCameraY = camera->getPosition().y;
	camera->setPosition(glm::vec3(camera->getPosition().x, originalCameraY - distance, camera->getPosition().z));
	camera->invertPitch();
	masterRenderer->processEntity(*terrain);
	masterRenderer->processEntity(*tree);
	masterRenderer->processEntity(*tree2);
	masterRenderer->processEntity(*elephant);
	masterRenderer->render(*light, *camera, glm::fvec4(0.0f, 1.0f, 0.0f, -waterTile->at(0).getHeight() + 0.5f));
	camera->setPosition(glm::vec3(camera->getPosition().x, originalCameraY, camera->getPosition().z));
	camera->invertPitch();
	fbos->unbindCurrentFrameBuffer();

	//render refraction texture to fbo
	fbos->bindRefractionFrameBuffer();
	masterRenderer->processEntity(*terrain);
	masterRenderer->processEntity(*tree);
	masterRenderer->processEntity(*tree2);
	masterRenderer->processEntity(*elephant);
	masterRenderer->render(*light, *camera, glm::fvec4(0.0f, -1.0f, 0.0f, waterTile->at(0).getHeight() + 0.5f));


	//render to screen
	glDisable(GL_CLIP_DISTANCE0);
	fbos->unbindCurrentFrameBuffer();
	masterRenderer->processEntity(*terrain);
	masterRenderer->processEntity(*tree);
	masterRenderer->processEntity(*tree2);
	masterRenderer->processEntity(*elephant);
	masterRenderer->render(*light, *camera, glm::fvec4(0.0f, -1.0f, 0.0f, -1.0f));
	waterRenderer->render(*waterTile, *camera);

	DisplayManager::updateDisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	DisplayManager::createDisplay();

	Loader loader;

	rawModel_terrain = &loadOBJ("res/lake1.obj", loader);
	ModelTexture texture(loader.loadTexture("res/green.bmp"));
	texture.setShineDamper(30.0f);
	texture.setReflectivity(0.4f);
	texturedModel_terrain = new TexturedModel(*rawModel_terrain, texture);

	rawModel_tree = &loadOBJ("res/tree_noleaves.obj", loader);
	ModelTexture texture_tree(loader.loadTexture("res/brown.bmp"));
	texture_tree.setShineDamper(20.0f);
	texture_tree.setReflectivity(0.3f);
	texturedModel_tree = new TexturedModel(*rawModel_tree, texture_tree);

	rawModel_tree2 = &loadOBJ("res/tree_noleaves.obj", loader);
	ModelTexture texture_tree2(loader.loadTexture("res/brown.bmp"));
	texture_tree2.setShineDamper(20.0f);
	texture_tree2.setReflectivity(0.3f);
	texturedModel_tree2 = new TexturedModel(*rawModel_tree2, texture_tree2);

	rawModel_elephant = &loadOBJ("res/elephun.obj", loader);
	ModelTexture texture2(loader.loadTexture("res/empty.bmp"));
	texture2.setShineDamper(10.0f);
	texture2.setReflectivity(0.0f);
	texturedModel_elephant = new TexturedModel(*rawModel_elephant, texture2);

	shader = new StaticShader();
	terrain = new Entity(*texturedModel_terrain, glm::vec3(0.0f, -3.0f, -7.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	tree = new Entity(*texturedModel_tree, glm::vec3(-4.0f, -1.5f, -12.0f), 0.0f, 40.0f, 0.0f, 1.0f);
	tree2 = new Entity(*texturedModel_tree2, glm::vec3(1.4f, -1.9f, -13.0f), 0.0f, 150.0f, 0.0f, 1.3f);
	elephant = new Entity(*texturedModel_elephant, glm::vec3(0.0f, -1.0f, -11.0f), 5.0f, 225.0f, 0.0f, 0.3f);
	light = new Light(glm::vec3(20.0f, -20.0f, -20.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	camera = new Camera();
	renderer = new Renderer(*shader);
	
	masterRenderer = new MasterRenderer();

	//water
	fbos = new WaterFrameBuffers();
	waterShader = new WaterShader();
	waterRenderer = new WaterRenderer(loader, *waterShader, renderer->getProjectionMatrix(), *fbos);
	waterTile = new std::vector<WaterTile>({ WaterTile(0.0f, -7.0f, -2.5f) });

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();


	fbos->cleanUp();
	waterShader->cleanUp();
	masterRenderer->cleanUp();
	loader.cleanUp();
	delete camera;
	delete light;
	delete terrain;
	delete texturedModel_terrain;
	delete elephant;
	delete texturedModel_elephant;
	delete tree;
	delete tree2;
	delete texturedModel_tree;
	delete texturedModel_tree2;
	delete shader;
	delete renderer;
	delete masterRenderer;
	delete waterTile;
	delete waterShader;
	delete waterRenderer;
	delete fbos;
	DisplayManager::closeDisplay();

	return 0;
}