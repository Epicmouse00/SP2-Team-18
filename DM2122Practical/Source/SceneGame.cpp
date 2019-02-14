#include "SceneGame.h"

#include "GL\glew.h"
#include "shader.hpp"

#include "Mtx44.h" 
#include "Application.h"

#include "Vertex.h"
#include "Utility.h"

#include "LoadTGA.h"

Menu menu;
Cursor		mainMenuCursor(3.f, -2.f, 4);
Cursor		gameChooseCursor(3.f, -3.f, 3);

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	srand((unsigned int)time(NULL));
	InitDefault();
	InitLights();
	InitCamera();
	InitMeshes();
	InitObstacles(numberOfRows);

	// Set initial game state
	gameState = E_MAINMENU;

	InitProjection();
}

//static float ROT_LIMIT = 45.0f;
//static float SCALE_LIMIT = 5.0f;
//static const float LSPEED = 30.0f;

//////////////////// Update function ////////////////////

void SceneGame::Update(double dt)
{
	UpdateDelayTime(dt);
	UpdateAppPolygon();
	UpdateMenuIndex();
	//Controls / Interactions / etcs.
	/////////////MOVEMENT V1.0 (UNREFINED)/////////////
	UpdatePlayerStrafe(dt);
	UpdatePlayerJump(dt);
	/////////////MOVEMENT V1.0 (UNREFINED)/////////////

	UpdateMainMenuCursor();
	UpdateGameChooseCursor();

	UpdateCamMovement();
	camera.Update(dt);
}

static const float SKYBOXSIZE = 2000.f;

//Temp Variables
Mtx44 MVP, modelView, modelView_inverse_transpose;

//////////////////// Render function ////////////////////

void SceneGame::Render()
{
	//Clear color & depth buffer every frame 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	RenderSkybox();
	RenderMesh(meshList[GEO_AXES], false);

	////////// RE	NDER GAME MODELS HERE ////////// [Hint: Arrangement of these are very important]

	// Menu backdrop

	// MainMenu Button
	RenderMainMenuButtons();

	// GameChoose Button
	RenderGameChooseButtons();

	// Gameplay UI

	// Player
	RenderPlayer();

	// Opponent

	// Coins

	// Items

	// Obstacles
	RenderObstacles();

	// Track

	// Others?

	////////// RENDER GAME MODELS HERE //////////
	RenderTextOnScreen(meshList[GEO_TEXT], "J and L to move between Lanes", Color(0, 1, 0), 2, 1, 4);
}

//Exit Function
void SceneGame::Exit()
{
	//Clean up

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i] != NULL)
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

bool SceneGame::getExit()
{
	return b_exit;
}





////////// Init Methods //////////
void SceneGame::InitDefault()
{
	//Set Background Color
	glClearColor(0.0f, 0.f, 0.4f, 0.0f);
	//Enable depth test
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glEnable(GL_CULL_FACE);
	//Default to Fill Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders 
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");

	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	//Variables
	Movement = 0;
	Jump = 0;
	delayTime = 0;

	JumpPressed = false;
}

void SceneGame::InitLights()
{
	//First Light
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Use our shader 
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Initialize Light Parameters
	//First Light
	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(0, 60, 30);
	light[0].color.Set(1, 1, 1);
	light[0].power = 5;
	light[0].kC = 0.1f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.0f;
	light[0].spotDirection.Set(0.0f, 5.0f, 0.0f);

	glUniform1f(m_parameters[U_LIGHT0_TYPE], (GLfloat)light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
}

void SceneGame::InitCamera()
{
	camera.Init(Vector3(0, 1.5, -10), Vector3(0, 0, 180), Vector3(0, 1, 0));
}

void SceneGame::InitMeshes()
{
	//Initialize all meshes to NULL
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Plane", Color(1, 1, 1), 1);
	meshList[GEO_PLANE] = MeshBuilder::GenerateQuad("Plane", Color(0, 0, 0), 50);

	//TEXT
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);

	//Skybox
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("SkyFront", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("SkyBack", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("SkyTop", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("SkyLeft", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("SkyRight", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("SkyBottom", Color(1, 1, 1), 1.f);

	//Texture Load
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	//Skybox
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	////////// ADD GAME MODELS HERE //////////

	// Menu backdrop

	// Menu Button
	meshList[GEO_BUTTON] = MeshBuilder::GenerateQuad("Button", Color(0.2f, 0.2f, 0.2f), 1.f);

	// Menu cursor
	meshList[GEO_CURSOR] = MeshBuilder::GenerateOBJ("Cursor", "OBJ//Cursor.obj");
	meshList[GEO_CURSOR]->textureID = LoadTGA("image//Cursor texture.tga");

	// Gameplay UI

	// Player
	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ("Player Car", "OBJ//gray.obj");
	meshList[GEO_PLAYER]->textureID = LoadTGA("image//gray.tga");

	// Opponent

	// Coins

	// Items

	// Obstacles (1	x	1	x	1)
	meshList[GEO_OBSTACLE_DEFAULT] = MeshBuilder::GenerateCube("Obstacle_Default", Color(1, 1, 1), 1.f, 1.f, 1.f);

	// Obstacles (1	x	4	x	1)
	meshList[GEO_OBSTACLE_TALL] = MeshBuilder::GenerateCube("Obstacle_Tall", Color(1, 1, 1), 1.f, 1.f, 1.f);

	// Obstacles (1	x	0.1	x	10)
	meshList[GEO_OBSTACLE_LONG] = MeshBuilder::GenerateCube("Obstacle_Long", Color(1, 1, 1), 1.f, 0.1f, 10.f);

	// Track

	// Others?

	////////// ADD GAME MODELS HERE //////////
}

void SceneGame::InitProjection()
{
	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}

void SceneGame::InitObstacles(unsigned int noOfObstacles)
{
	for (int lane = 0; lane < 4; ++lane)
	{
		for (int row = 0; row < (int)noOfObstacles; ++row)
		{
			if (rand() % 2)
			{
				Obstacle temp;
				temp.setX(((float)lane * 18) - 27);
				temp.setY(0);
				temp.setZ(200 * (float)row + 250);
				temp.setActive(true);
				obstacleList[lane][row] = temp;
			}
		}
	}
}






////////// Update Methods //////////
void SceneGame::UpdateDelayTime(double dt)
{
	//Delay Time
	if (delayTime <= 5.f)
	{
		delayTime += (float)(5.f * dt);
	}
}

void SceneGame::UpdateCamMovement()
{
	if (Application::IsKeyPressed('Z'))
		camera.Enable();
	if (Application::IsKeyPressed('X'))
		camera.Disable();
}

void SceneGame::UpdateAppPolygon()
{
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void SceneGame::UpdateMenuIndex()
{
	//Sets the current gameState 
	gameState = menu.getIndex();
}

void SceneGame::UpdatePlayerStrafe(double dt)
{
	if (gameState == E_GAME)
	{
	/////////////MOVEMENT V1.1 (UNREFINED)/////////////

	//Player Move Left 1st Column
		if (Application::IsKeyPressed('J'))
		{
			if (Jump <= 0)
			{
				if (Movement < 6)
				{
					Movement += (float)(50 * dt);
				}
				if (Movement > 7)
				{
					Movement -= (float)(50 * dt);
				}
			}
		}
		//Player Move Right 2nd Column
		if (Application::IsKeyPressed('H'))
		{
			if (Jump <= 0)
			{
				if (Movement < 12)
				{
					Movement += (float)(50 * dt);
				}

			}
		}

		//Player MoveRight 3rd Column
		if (Application::IsKeyPressed('K'))
		{
			if (Jump <= 0)
			{
				if (Movement > 0)
				{
					Movement -= (float)(50 * dt);
				}
				if (Movement < -1)
				{
					Movement += (float)(50 * dt);
					delayTime = 0;
				}
			}
		}
		//Player Move Right 4th Column
		if (Application::IsKeyPressed('L'))
		{
			if (Jump <= 0)
			{
				if (Movement > -6)
				{
					Movement -= (float)(50 * dt);
				}
			}
		}
	}
}

void SceneGame::UpdatePlayerJump(double dt)
{
	if (gameState == E_GAME)
	{
	//Player Jump
		if (Application::IsKeyPressed('I'))
		{
			JumpPressed = true;
		}
		else
		{
			JumpPressed = false;
		}

		if (JumpPressed == true)
		{
			if (Jump < 5.0f)
			{
				Jump += (float)(50 * dt);
			}
		}
		else
		{
			if (Jump > 0)
			{
				Jump -= (float)(50 * dt);
			}
		}
	}
}

void SceneGame::UpdateMainMenuCursor()
{
	if (menu.getIndex() == E_MAINMENU)
	{
		if (Application::IsKeyPressed(VK_UP) && delayTime >= 1.f) //Cursor stuff
		{
			mainMenuCursor.updatePositionIndex(-1);
			delayTime = 0;
		}

		if (Application::IsKeyPressed(VK_DOWN) && delayTime >= 1.f)
		{
			mainMenuCursor.updatePositionIndex(1);
			delayTime = 0;
		}

		if (Application::IsKeyPressed(VK_RETURN) && delayTime >= 1.f)
		{
			delayTime = 0;
			menu.setIndex(mainMenuCursor.getIndex());
		}
	}
}

void SceneGame::UpdateGameChooseCursor()
{
	if (gameState == E_GAMECHOOSE)
	{
		if (Application::IsKeyPressed(VK_UP) && delayTime >= 1.f) //Cursor stuff
		{
			gameChooseCursor.updatePositionIndex(-1);
			delayTime = 0;
		}

		if (Application::IsKeyPressed(VK_DOWN) && delayTime >= 1.f)
		{
			gameChooseCursor.updatePositionIndex(1);
			delayTime = 0;
		}

		if (Application::IsKeyPressed(VK_RETURN) && delayTime >= 1.f)
		{
			delayTime = 0;
		}
	}
}






////////// Render Methods //////////

//Mesh Renderer
void SceneGame::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

//SkyBox Renderer
void SceneGame::RenderSkybox()
{
	//Left
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	//Right
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//Front
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//Back
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//Top
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	//Bottom
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

//Text Renderer
void SceneGame::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}

}

////////// Render Methods //////////

//Mesh Renderer
void SceneGame::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

//SkyBox Renderer
void SceneGame::RenderSkybox()
{
	//Left
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	//Right
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	//Front
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//Back
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//Top
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	//Bottom
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

//Text Renderer
void SceneGame::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.7f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

//Text on Screen
void SceneGame::RenderTextOnScreen(Mesh * mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.7f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneGame::RenderPlayer()
{
	if (gameState == E_GAME)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-9, 0, 50.f);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		modelStack.Translate(Movement, 0, 0);
		modelStack.Translate(0, Jump, 0);
		RenderMesh(meshList[GEO_PLAYER], true);
		modelStack.PopMatrix();
	}
}

void SceneGame::RenderMainMenuButtons()
{
	// Render menu buttons
	if (gameState == E_MAINMENU)
	{
		const float textTranslate = -3.f;
		std::string text;

		//Play
		text = "Play";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 1.5f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 0.9f, 1.f));
		modelStack.PopMatrix();

		//Shop
		text = "Shop";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.5f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 0.9f, 1.f));
		modelStack.PopMatrix();

		//Leaderboard
		text = "Leaderboard";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -0.5f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 0.9f, 1.f));
		modelStack.PopMatrix();

		//Quit
		text = "Quit";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -1.5f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(1.f, 0.f, 0.f));
		modelStack.PopMatrix();

		//Cursor
		float sideMove = 5.f;
		modelStack.PushMatrix();
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Translate(sideMove, mainMenuCursor.outputPosition(), 0.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(-45, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();
	}

}

void SceneGame::RenderGameChooseButtons()
{
	// Render gamechoose buttons
	if (gameState == E_GAMECHOOSE)
	{
		const float textTranslate = -3.f;
		std::string text;

		//VS Mode
		text = "VS Mode";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 1.5f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 0.9f, 1.f));
		modelStack.PopMatrix();

		//Time Mode
		text = "Time Mode";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 0.9f, 1.f));
		modelStack.PopMatrix();

		//Back
		text = "Back";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -1.5f, 0.f);
		modelStack.Scale(4.f, 0.8f, 1.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((float)(0.5 / 4), (float)(0.5 / 0.8), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.5f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(1.f, 0.f, 0.f));
		modelStack.PopMatrix();

		//Cursor
		float sideMove = 5.f;
		modelStack.PushMatrix();
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Translate(sideMove, gameChooseCursor.outputPosition(), 0.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(-45, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();
	}
}

void SceneGame::RenderObstacles()
{
	// Render obstacles
	if (gameState == E_GAME)
	{
		for (size_t lane = 0; lane < 4; ++lane)
		{
			for (size_t row = 0; row < numberOfRows; ++row)
			{
				if (obstacleList[lane][row].getActive())
				{
					modelStack.PushMatrix();
					modelStack.Translate(obstacleList[lane][row].getX(), obstacleList[lane][row].getY(), obstacleList[lane][row].getZ());
					modelStack.Scale(10.f, 10.f, 10.f);
					RenderMesh(meshList[10 + obstacleList[lane][row].getObstacleType()], false);
					modelStack.PopMatrix();
				}
			}
		}
	}
}