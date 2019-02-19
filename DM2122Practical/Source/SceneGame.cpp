#include "SceneGame.h"

#include "GL\glew.h"
#include "shader.hpp"

#include "Mtx44.h" 
#include "Application.h"

#include "Vertex.h"
#include "Utility.h"

#include "LoadTGA.h"

const unsigned int numberOfRows = 100;
const float	laneSpacing = 22.5f; // 7.5 x 3
Menu		menu;
Cursor		mainMenuCursor(4);
Cursor		gameChooseCursor(3);
Cursor		leaderboardCursor(3);
Car			Player(true);
Car			Opponent(false);
Obstacle	obstacleList[4][numberOfRows];
PowerUps	powerupList[4][numberOfRows / 2];


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
	InitCursors();
	InitObstacles(numberOfRows);
	InitPowerUps(numberOfRows);
	gameBalance.setBalance(gameSave.getBalance());
	InitVariables();
	//PlaySound(TEXT("Music\\SUICIDESILENCEYouOnlyLiveOnce.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	Player.setTexture(gameShop.getEquip());
	UpdateCarTexture();
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
	UpdateCar(dt);
	UpdateCursor();
	UpdateLight();
	UpdateCam(dt);
	UpdateShop(dt);
	UpdatePowerUps(dt);
}

static const float SKYBOXSIZE = 10000.f;

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
	//RenderMesh(meshList[GEO_AXES], false);

	////////// RENDER GAME MODELS HERE ////////// [Hint: Arrangement of these are very important]

	// Menu backdrop

	// MainMenu Button
	RenderMainMenuButtons();

	// GameChoose Button
	RenderGameChooseButtons();

	// Leaderboard
	RenderLeaderboard();

	// Gameplay UI

	// Player + Opponent
	RenderCar();

	// Coins

	// Shop
	RenderShop();

	// Items
	RenderPowerUps();

	// Obstacles
	RenderObstacles();

	// Track
	RenderTrack();

	// Others?

	////////// RENDER GAME MODELS HERE //////////
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
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 0, 0);
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
	camera.Init(Vector3(0.f, 1.5f, -10.f), Vector3(0.f, 1.5f, 180.f), Vector3(0.f, 1.f, 0.f));
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

	//Title Bar
	meshList[GEO_TITLE] = MeshBuilder::GenerateOBJ("Menu", "OBJ//Title.obj");
	meshList[GEO_TITLE]->textureID = LoadTGA("image//TitleBar.tga");

	// Menu Button
	meshList[GEO_BUTTON] = MeshBuilder::GenerateOBJ("Menu", "OBJ//Button3.obj");
	meshList[GEO_BUTTON]->textureID = LoadTGA("image//ButtonType3.tga");

	// Menu cursor
	meshList[GEO_CURSOR] = MeshBuilder::GenerateOBJ("Cursor", "OBJ//Cursor.obj");
	meshList[GEO_CURSOR]->textureID = LoadTGA("image//Cursor texture.tga");

	//Win/Lose
	meshList[GEO_WINLOSE] = MeshBuilder::GenerateOBJ("Win/lose", "OBJ//WinLoseBar.obj");
	meshList[GEO_WINLOSE]->textureID = LoadTGA("image//WinLosePlane.tga");

	// Leaderboard
	meshList[GEO_LEADERBOARD] = MeshBuilder::GenerateOBJ("Leaderboard", "OBJ//LeaderBoard.obj");
	meshList[GEO_LEADERBOARD]->textureID = LoadTGA("image//LeaderBoard.tga");

	// Gameplay UI

	// Player
	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ("Player Car", "OBJ//gray.obj");
	meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_grey.tga");

	// Opponent
	meshList[GEO_OPPONENT] = MeshBuilder::GenerateOBJ("Opponent Car", "OBJ//gray.obj");
	meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_grey.tga");

	// Coins

	// Items
	meshList[GEO_SPEED] = MeshBuilder::GenerateCube("Speed Power-Up", Color(0, 0, 0), 1.f, 1.f, 1.f);
	meshList[GEO_SHIELD] = MeshBuilder::GenerateCube("Shield Power-Up", Color(1, 0, 0), 1.f, 1.f, 1.f);
	meshList[GEO_DOUBLE] = MeshBuilder::GenerateCube("Double Time Power-Up", Color(0, 1, 0), 1.f, 1.f, 1.f);
	meshList[GEO_FLIGHT] = MeshBuilder::GenerateCube("Flight Power-Up", Color(0, 0, 1), 1.f, 1.f, 1.f);

	// Shop
	meshList[GEO_DISPLAY] = MeshBuilder::GenerateOBJ("Display", "OBJ//gray.obj");
	meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_grey.tga");

	// Obstacles (1	x	1	x	1)
	meshList[GEO_OBSTACLE_DEFAULT] = MeshBuilder::GenerateCube("Obstacle_Default", Color(1, 1, 1), 1.f, 1.f, 1.f);

	// Obstacles (1	x	4	x	1)
	meshList[GEO_OBSTACLE_TALL] = MeshBuilder::GenerateCube("Obstacle_Tall", Color(1, 1, 1), 1.f, 1.f, 1.f);

	// Track
	meshList[GEO_TRACK] = MeshBuilder::GenerateOBJ("Tunnel", "OBJ//tunnelProto.obj");
	meshList[GEO_TRACK]->textureID = LoadTGA("image//Tunnel.tga");

	// Others?

	////////// ADD GAME MODELS HERE //////////
}

void SceneGame::InitProjection()
{
	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);
}

void SceneGame::InitCursors()
{
	mainMenuCursor.addNewPosition(5.f, 3.f, 0);
	mainMenuCursor.addNewPosition(5.f, 1.f, 1);
	mainMenuCursor.addNewPosition(5.f, -1.f, 2);
	mainMenuCursor.addNewPosition(5.f, -3.f, 3);
	gameChooseCursor.addNewPosition(5.f, 3.f, 0);
	gameChooseCursor.addNewPosition(5.f, 0.f, 1);
	gameChooseCursor.addNewPosition(5.f, -3.f, 2);
	leaderboardCursor.addNewPosition(10.f, 10.f, 0);
	leaderboardCursor.addNewPosition(0.f, 10.f, 1);
	leaderboardCursor.addNewPosition(5.f, -3.f, 2);
}

void SceneGame::InitVariables()
{
	playerBoost = 0.f;
	opponentBoost = 0.f;
	delayTime = 0;
	powerupRotation = 0;
	displayRotation = 0;
	leftCursor = 0;
	rightCursor = 0;
	Player.setPlayerForward(-150.f);
}

void SceneGame::InitObstacles(unsigned int noOfRows)
{
	for (int row = 0; row < (int)noOfRows; ++row)
	{
		for (int lane = 0; lane < 4; ++lane)
		{
			if (rand() % 2)
			//if (1)
			{
				Obstacle temp(rand() % 2);
				//Obstacle temp(1);
				temp.setX((-(float)lane * laneSpacing) + (laneSpacing * (float)1.5));
				temp.setY(0);
				temp.setZ((float)(400 * row + 1000));
				temp.setActive(true);
				obstacleList[lane][row] = temp;
			}
			else
			{
				obstacleList[lane][row].setActive(false);
			}
		}
		//At least one obstacle is a Default in a row
		int randomLane = rand() % 4;
		Obstacle temp(0);
		temp.setX((-(float)randomLane * laneSpacing) + (laneSpacing * (float)1.5));
		temp.setY(0);
		temp.setZ((float)(400 * row + 1000));
		temp.setActive(true);
		obstacleList[randomLane][row] = temp;

	}
}

void SceneGame::InitPowerUps(unsigned int noOfRows)
{
	powerupRotation = 0;
	for (int row = 0; row < (int)(noOfRows / 2); row++)
	{
		for (int lane = 0; lane < 4; lane++)
		{
			if ((rand() % 4) == 0)
			{
				PowerUps temp;
				temp.setX((-(float)lane * laneSpacing) + (laneSpacing * (float)1.5));
				temp.setY(0);
				temp.setZ((float)(800 * row + 800));
				temp.setActive(true);
				powerupList[lane][row] = temp;
			}
			else
			{
				powerupList[lane][row].setActive(false);
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

void SceneGame::UpdateCam(double dt)
{

	if (!camera.getActive())
	{
		if (menu.getIndex() == E_GAME)
		{
			const float camAgile = 0.4f;
			//camera.setPosition(Vector3(0.f, 50.f, -50.f + 3.f * Opponent.getForward()), Vector3((camAgile * 3.f) * (float)Opponent.getMovement(), (camAgile * 3.f) * (float)Opponent.getJump(), 120.f + 3.f * Opponent.getForward()), Vector3(0.f, 1.f, 0.f));
			camera.setPosition(Vector3(0.f, 50.f, -50.f + 3.f * Player.getForward()), Vector3((camAgile * 3.f) * (float)Player.getMovement(), (camAgile * 3.f) * (float)Player.getJump(), 120.f + 3.f * Player.getForward()), Vector3(0.f, 1.f, 0.f));
		}
		else
		{
			camera.setPosition(Vector3(0.f, 1.5f, -10.f), Vector3(0.f, 1.5f, 180.f), Vector3(0.f, 1.f, 0.f));
		}
	}
	camera.Update(dt);
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

void SceneGame::UpdateCar(double dt)
{
	if (menu.getIndex() == E_GAME)
	{
		//Player
		Player.UpdatePlayerForward(dt, playerBoost);
		Player.UpdatePlayerJump(dt, (Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W') || Application::IsKeyPressed(VK_SPACE)));
		if (Player.UpdatePlayerStrafe(dt, delayTime, (Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')), (Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D'))))
			delayTime = 0.f;

		if (menu.getGameMode() == MODE_VS)
		{
			//Opponent
			Opponent.UpdatePlayerForward(dt, opponentBoost);
			AImovement AI(Opponent.getLane(), Opponent.getForward(), obstacleList, powerupList);
			Opponent.UpdatePlayerJump(dt, AI.getJump());
			if (Opponent.UpdatePlayerStrafe(dt, delayTime, AI.getLeft(), AI.getRight()))
				delayTime = 0.f;
		}
		UpdateCarCollision();
		UpdateCarSpeed(dt);
	}
}

void SceneGame::UpdateCarTexture()
{
	switch (Player.getTexture())
	{
	case CAR_GREY:
		meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_grey.tga");
		break;
	case CAR_CYAN:
		meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_cyan.tga");
		break;
	case CAR_ORANGE:
		meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_orange.tga");
		break;
	case CAR_RED:
		meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_red.tga");
		break;
	case CAR_GREEN:
		meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_green.tga");
		break;
	default:
		meshList[GEO_PLAYER]->textureID = LoadTGA("image//car_grey.tga");
		break;

	}
	/*switch (Opponent.getTexture())
	{
	case CAR_GREY:
		meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_grey.tga");
		break;
	case CAR_CYAN:
		meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_cyan.tga");
		break;
	case CAR_ORANGE:
		meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_orange.tga");
		break;
	case CAR_RED:
		meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_red.tga");
		break;
	case CAR_GREEN:
		meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_green.tga");
		break;
	default:
		meshList[GEO_OPPONENT]->textureID = LoadTGA("image//car_grey.tga");
		break;

	}*/
}

void SceneGame::UpdateCarCollision()
{
	if (Player.collisionObstacle(obstacleList))
		playerBoost -= 30.f;
	if (Player.collisionPowerUp(powerupList))
	{
		int row = 0;
		float forward = 3 * Player.getForward();
		if (forward / 800 > 0) // Row in front of car
			row = ((int)forward / 800);
		powerupList[Player.getLane()][row].setActive(false);
		playerBoost += 10.f;
	}
	if (menu.getGameMode() == MODE_VS)
	{
		if (Opponent.collisionObstacle(obstacleList))
			opponentBoost -= 30.f;
		if (Opponent.collisionPowerUp(powerupList))
		{
			int row = 0;
			float forward = 3 * Opponent.getForward();
			if (forward / 800 > 0) // Row in front of car
				row = ((int)forward / 800);
			powerupList[Opponent.getLane()][row].setActive(false);
			opponentBoost += 10.f;
		}
	}
}

void SceneGame::UpdateCarSpeed(double dt)
{
	playerBoost += (dt * 10.f);
	if (playerBoost < 0.f)
		playerBoost = 0.f;
	else if (playerBoost > 60.f)
		playerBoost = 60.f;
	if (menu.getGameMode() == MODE_VS)
	{
		opponentBoost += (dt * 10.f);
		if (opponentBoost < 0.f)
			opponentBoost = 0.f;
		else if (opponentBoost > 50.f)
			opponentBoost = 50.f;
	}
}

void SceneGame::UpdatePowerUps(double dt)
{
	powerupRotation += float(dt) * 90.f;
}

void SceneGame::UpdateCursor()
{
	UpdateMainMenuCursor();
	UpdateGameChooseCursor();
	UpdateLeaderboardCursor();
}

void SceneGame::UpdateMainMenuCursor()
{
	if (menu.getIndex() == E_MAINMENU)
	{
		if ((Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) && delayTime >= 1.f) //Cursor stuff
		{
			mainMenuCursor.updatePositionIndex(-1);
			delayTime = 0;
		}

		if ((Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) && delayTime >= 1.f)
		{
			mainMenuCursor.updatePositionIndex(1);
			delayTime = 0;
		}

		if ((Application::IsKeyPressed(VK_RETURN) || Application::IsKeyPressed(VK_SPACE)) && delayTime >= 1.f)
		{
			delayTime = 0;
			b_exit = menu.menuChange(mainMenuCursor.getIndex());
			for (int i = 0; i < mainMenuCursor.getIndex() + 1; i++)
			{
				mainMenuCursor.updatePositionIndex(-1);
			}
		}
	}
}

void SceneGame::UpdateGameChooseCursor()
{
	if (menu.getIndex() == E_GAMECHOOSE)
	{
		if ((Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) && delayTime >= 1.f) //Cursor stuff
		{
			gameChooseCursor.updatePositionIndex(-1);
			delayTime = 0;
		}

		if ((Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) && delayTime >= 1.f)
		{
			gameChooseCursor.updatePositionIndex(1);
			delayTime = 0;
		}

		if ((Application::IsKeyPressed(VK_RETURN) || Application::IsKeyPressed(VK_SPACE)) && delayTime >= 1.f)
		{
			delayTime = 0;
			menu.menuChange(gameChooseCursor.getIndex());
			gameChooseCursor.updatePositionIndex(-1);
			gameChooseCursor.updatePositionIndex(-1);
		}
	}
}

void SceneGame::UpdateLeaderboardCursor()
{
	if (menu.getIndex() == E_LEADERBOARD)
	{
		if ((Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')) && delayTime >= 1.f)
		{
			if (leaderboardCursor.getIndex() != 2)
			{
				leaderboardCursor.updatePositionIndex(-1);
				delayTime = 0;
			}
			else
			{
				delayTime = 0;
			}
		}

		if ((Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D')) && delayTime >= 1.f)
		{
			if (leaderboardCursor.getIndex() != 1)
			{
				leaderboardCursor.updatePositionIndex(1);
				delayTime = 0;
			}
			else
			{
				delayTime = 0;
			}
		}

		if ((Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S')) && delayTime >= 1.f)
		{
			if (leaderboardCursor.getIndex() == 0)
			{
				leaderboardCursor.updatePositionIndex(1);
				leaderboardCursor.updatePositionIndex(1);
				delayTime = 0;
			}
			else if (leaderboardCursor.getIndex() == 1)
			{
				leaderboardCursor.updatePositionIndex(1);
				delayTime = 0;
			}
			else
			{
				delayTime = 0;
			}
		}
		if ((Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W')) && delayTime >= 1.f)
		{
			if (leaderboardCursor.getIndex() == 2)
			{
				leaderboardCursor.updatePositionIndex(-1);
				leaderboardCursor.updatePositionIndex(-1);
				delayTime = 0;
			}
			else
			{
				delayTime = 0;
			}
		}
		if ((Application::IsKeyPressed(VK_RETURN) || Application::IsKeyPressed(VK_SPACE)) && delayTime >= 1.f)
		{
			if (leaderboardCursor.getIndex() == 2)
			{
				menu.menuChange(leaderboardCursor.getIndex());
				leaderboardCursor.updatePositionIndex(-1);
				leaderboardCursor.updatePositionIndex(-1);
				delayTime = 0;
			}
			else
			{
				delayTime = 0;
			}
		}
	}
}

void SceneGame::UpdateShop(double dt)
{
	if (menu.getIndex() == E_SHOP)
	{
		displayRotation += float(dt) * 45.f;
		if (gameShop.getIndex() != 4)
		{
			rightCursor = 0;

			if ((Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D')) && delayTime >= 1.f)
			{
				delayTime = 0;
				gameShop.nextIndex();

				switch (gameShop.getIndex())
				{
				case 0:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_grey.tga");
					break;
				case 1:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_cyan.tga");
					break;
				case 2:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_orange.tga");
					break;
				case 3:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_red.tga");
					break;
				case 4:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_green.tga");
					break;
				}
			}
		}
		else
		{
			rightCursor = 50;
		}
	
		if (gameShop.getIndex() != 0)
		{
			leftCursor = 0;

			if ((Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A')) && delayTime >= 1.f)
			{
				delayTime = 0;
				gameShop.previousIndex();

				switch (gameShop.getIndex())
				{
				case 0:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_grey.tga");
					break;
				case 1:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_cyan.tga");
					break;
				case 2:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_orange.tga");
					break;
				case 3:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_red.tga");
					break;
				case 4:
					meshList[GEO_DISPLAY]->textureID = LoadTGA("image//car_green.tga");
					break;
				}
			}
		}
		else
		{
			leftCursor = 50;
		}

		if ((Application::IsKeyPressed(VK_RETURN) || Application::IsKeyPressed(VK_SPACE)) && delayTime >= 1.f)
		{
			delayTime = 0;
			if (!gameShop.isOwned() && (gameBalance.getBalance() >= gameShop.getCost()))
			{
				gameBalance.deductBalance(gameShop.getCost());
				gameShop.setOwned();

				gameSave.setBalance(gameBalance.getBalance());
				gameSave.setColour(gameShop.getIndex());
			}
			else if (gameShop.isOwned())
			{
				gameShop.setEquip();
				gameSave.setEquip(gameShop.getEquip());
				Player.setTexture(gameShop.getEquip());
				UpdateCarTexture();
			}
			gameSave.save();
		}
		if (Application::IsKeyPressed(VK_BACK) && delayTime >= 1.f)
		{
			delayTime = 0;
			gameShop.resetIndex();
			menu.menuChange(0);
		}
	}
}

void SceneGame::UpdateLight()
{
		light[0].position.Set(camera.position.x, camera.position.y + 20.f, camera.position.z + 100.f);
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

void SceneGame::RenderCar()
{
	if (menu.getIndex() == E_GAME)
	{
		//Player
		modelStack.PushMatrix();
		modelStack.Translate(-9, 0, 50.f);
		modelStack.Rotate(0, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		modelStack.Translate(Player.getMovement(), Player.getJump(), Player.getForward());
		RenderMesh(meshList[GEO_PLAYER], true);
		modelStack.PopMatrix();

		if (menu.getGameMode() == MODE_VS)
		{
			//Opponent
			modelStack.PushMatrix();
			modelStack.Translate(-9, 0, 50.f);
			modelStack.Rotate(0, 0, 1, 0);
			modelStack.Scale(3, 3, 3);
			modelStack.Translate(Opponent.getMovement(), Opponent.getJump(), Opponent.getForward());
			RenderMesh(meshList[GEO_OPPONENT], true);
			modelStack.PopMatrix();
		}
	}
}

//Launch Screen Selection
void SceneGame::RenderMainMenuButtons()
{
	// Render menu buttons
	if (menu.getIndex() == E_MAINMENU)
	{
		const float textTranslate = -3.f;
		std::string text;

		//Title
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.2f, 0.f);
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_TITLE], false);
		modelStack.PopMatrix();

		//Play
		text = "Play";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 1.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Shop
		text = "Shop";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Leaderboard
		text = "Leaderboard";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -0.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Quit
		text = "Quit";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -1.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Cursor
		float sideMove = 5.f;
		modelStack.PushMatrix();
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Translate(mainMenuCursor.getX(), mainMenuCursor.getY(), 0.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(-45, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();
	}
}

//LeaderBoard Selection
void SceneGame::RenderLeaderboard()
{
	if (menu.getIndex() == E_LEADERBOARD)
	{
		const float textTranslate = -3.f;
		std::string text;

		// Time Leaderboard button
		text = "Time Leaderboard";
		modelStack.PushMatrix();
		modelStack.Translate(2.5f, 5.f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.35f / 1.f), (0.35f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.1f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		// VS Leaderboard button
		text = "VS Leaderboard";
		modelStack.PushMatrix();
		modelStack.Translate(-2.5f, 5.f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.35f / 1.f), (0.35f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.9f, 0.1f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Back
		text = "Back";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -1.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Cursor
		modelStack.PushMatrix();
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Translate(leaderboardCursor.getX(), leaderboardCursor.getY(), 0.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(-45, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
	
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();
	}
}

// Game Mode Seleciton
void SceneGame::RenderGameChooseButtons()
{
	// Render gamechoose buttons
	if (menu.getIndex() == E_GAMECHOOSE)
	{
		const float textTranslate = -3.f;
		std::string text;

		//VS Mode
		text = "VS Mode";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 1.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Time Mode
		text = "Time Mode";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Back
		text = "Back";
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -1.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		//Cursor
		float sideMove = 5.f;
		modelStack.PushMatrix();
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		modelStack.Translate(gameChooseCursor.getX(), gameChooseCursor.getY(), 0.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(-45, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();
	}
}

void SceneGame::RenderShop()
{
	// Render gamechoose buttons
	if (menu.getIndex() == E_SHOP)
	{
		string colour;
		string cost = "$";
		string balance = to_string(gameBalance.getBalance());

		switch (gameShop.getIndex())
		{
		case 0:
			colour = "Grey";
			break;
		case 1:
			colour = "Cyan";
			break;
		case 2:
			colour = "Orange";
			break;
		case 3:
			colour = "Red";
			break;
		case 4:
			colour = "Monster";
			break;
		}

		if (gameShop.isOwned())
		{
			if (gameShop.isEquip())
				cost = "Equipped";
			else
				cost = "Owned";
		}
		else
		{
			cost += to_string(gameShop.getCost());
		}

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 50.f);
		modelStack.Rotate(displayRotation, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_DISPLAY], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(30 + leftCursor, 0, 50.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(135, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-30 - rightCursor, 0, 50.f);
		modelStack.Rotate(180, 1.f, 0.f, 0.f);
		modelStack.Rotate(-45, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_CURSOR], false);
		modelStack.PopMatrix();

		const float textTranslate = -3.f;
		std::string text = "Hello, world!";

		text = colour;
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 3.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		text = cost; //Outputs Owned if owned, else output price
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -1.5f, 0.f);
		modelStack.Scale(1.f, 0.5f, 0.5f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.5f / 1.f), (0.5f / 0.5f), 0.5f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();

		text = "Balance: $";
		text += balance;
		modelStack.PushMatrix();
		modelStack.Translate(-3.f, 5.f, 0.f);
		modelStack.Scale(0.8f, 0.4f, 0.4f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		RenderMesh(meshList[GEO_BUTTON], false);
		modelStack.Scale((0.3f / 0.8f), (0.3f / 0.4f), 0.3f);
		modelStack.Translate(((float)text.size() / textTranslate) + 0.7f, 0.f, 0.f);
		RenderText(meshList[GEO_TEXT], text, Color(0.f, 1.f, 1.f));
		modelStack.PopMatrix();
	}
}

void SceneGame::RenderTrack()
{
	if (menu.getIndex() == E_GAME)
	{
		//int temp = 0;
	
		for (int i = 0; i < 100; i++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0.f, -8.f, 35500.f);
			//modelStack.Rotate(temp, 0, 1, 0);
			modelStack.Scale(10.f, 10.f, 3000.f);
			RenderMesh(meshList[GEO_TRACK], false);
			modelStack.PopMatrix();
		}
	}

}

void SceneGame::RenderObstacles()
{
	// Render obstacles
	if (menu.getIndex() == E_GAME)
	{
		for (size_t lane = 0; lane < 4; ++lane)
		{
			for (size_t row = 0; row < numberOfRows; ++row)
			{
				if (obstacleList[lane][row].getZ() > camera.position.z && obstacleList[lane][row].getZ() < camera.position.z + 5000.f && obstacleList[lane][row].getActive())
				{
					modelStack.PushMatrix();
					modelStack.Translate(obstacleList[lane][row].getX(), obstacleList[lane][row].getY(), obstacleList[lane][row].getZ());
					if (10 + obstacleList[lane][row].getObstacleType() == GEO_OBSTACLE_DEFAULT)
					{
						modelStack.Scale(10.f, 10.f, 10.f);
						modelStack.Translate(0.f, 0.5f, 0.f);
						RenderMesh(meshList[GEO_OBSTACLE_DEFAULT], false);
					}
					else if (10 + obstacleList[lane][row].getObstacleType() == GEO_OBSTACLE_TALL)
					{
						modelStack.Scale(10.f, 40.f, 10.f);
						modelStack.Translate(0.f, 0.5f, 0.f);
						RenderMesh(meshList[GEO_OBSTACLE_TALL], false);
					}
					modelStack.PopMatrix();
				}
			}
		}
	}
}

void SceneGame::RenderPowerUps()
{
	if (menu.getIndex() == E_GAME)
	{
		for (size_t lane = 0; lane < 4; ++lane)
		{
			for (size_t row = 0; row < numberOfRows / 2; ++row)
			{
				if (powerupList[lane][row].getZ() > camera.position.z && powerupList[lane][row].getZ() < camera.position.z + 5000.f && powerupList[lane][row].getActive())
				{
					modelStack.PushMatrix();
					modelStack.Translate(powerupList[lane][row].getX(), powerupList[lane][row].getY(), powerupList[lane][row].getZ());
					switch (powerupList[lane][row].getType())
					{
					case 0:
						modelStack.Translate(0.f, 7.5f, 0.f);
						modelStack.Rotate(powerupRotation, 0.f, 1.f, 0.f);
						modelStack.Scale(10.f, 10.f, 10.f);
						RenderMesh(meshList[GEO_SPEED], false);
						break;
					case 1:
						modelStack.Translate(0.f, 7.5f, 0.f);
						modelStack.Rotate(powerupRotation, 0.f, 1.f, 0.f);
						modelStack.Scale(10.f, 10.f, 10.f);
						RenderMesh(meshList[GEO_SHIELD], false);
						break;
					case 2:
						modelStack.Translate(0.f, 7.5f, 0.f);
						modelStack.Rotate(powerupRotation, 0.f, 1.f, 0.f);
						modelStack.Scale(10.f, 10.f, 10.f);
						RenderMesh(meshList[GEO_FLIGHT], false);
						break;
					case 3:
						modelStack.Translate(0.f, 7.5f, 0.f);
						modelStack.Rotate(powerupRotation, 0.f, 1.f, 0.f);
						modelStack.Scale(10.f, 10.f, 10.f);
						RenderMesh(meshList[GEO_DOUBLE], false);
						break;
					}
					modelStack.PopMatrix();
				}
			}
		}
	}
}