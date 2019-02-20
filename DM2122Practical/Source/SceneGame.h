#ifndef SCENE_GAME_H 
#define SCENE_GAME_H

#include "Scene.h" 

#include "Camera.h" 
#include "Camera3.h"

#include "Mesh.h"
#include "MeshBuilder.h"

#include "MatrixStack.h"
#include "Light.h"

#include "Obstacle.h"
#include "Cursor.h"
#include "Menu.h"
#include "PowerUps.h"
#include "Car.h"
#include "AImovement.h"
#include "Shop.h"
#include "Saving.h"
#include "Currency.h"

class SceneGame : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,

		//Lightings
		GEO_LIGHTBALL,

		//SkyBox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		//Text
		GEO_TEXT,

		//GAME MODELS
		GEO_OBSTACLE_DEFAULT,
		GEO_OBSTACLE_TALL,

		//Track
		GEO_TRACK,

		GEO_PLANE,
		GEO_CURSOR,
		GEO_WINLOSE,
		GEO_LEADERBOARD,
		GEO_PLAYER,
		GEO_OPPONENT,
		GEO_TITLE,

		//Power Ups
		GEO_SPEED,
		GEO_DOUBLE,
		GEO_FLIGHT,
		GEO_SHIELD,
    
		//Menu buttons
		GEO_BUTTON,

		//Shop
		GEO_DISPLAY,

		//Keep this at the back
		NUM_GEOMETRY
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,

		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,

		//Light 1
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		//Light 2
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		//Light 3
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		//Light 4
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_NUMLIGHTS,
		U_LIGHTENABLED,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
	
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL
	};

	enum gameStates
	{
		E_MAINMENU,
		E_GAMECHOOSE,
		E_GAME,
		E_SHOP,
		E_LEADERBOARD,
		E_WINLOSE	
	};

	enum gameModes
	{
		MODE_VS,
		MODE_TIME
	};

	enum carText
	{
		CAR_GREY,
		CAR_CYAN,
		CAR_ORANGE,
		CAR_RED,
		CAR_GREEN
	};

public:
					SceneGame();
					~SceneGame();
	virtual void	Init();
	virtual void	Update(double dt);
	virtual void	Render();
	virtual void	Exit();
	virtual bool	getExit();

private:
	void		InitDefault();
	void		InitLights();
	void		InitCamera();
	void		InitMeshes();
	void		InitProjection();
	void		InitCursors();
	void		InitVariables();
	void		InitObstacles(unsigned int noOfRows);
	void		InitPowerUps(unsigned int noOfRows);

	void		UpdateDelayTime(double dt);
	void		UpdateCam(double dt);
	void		UpdateAppPolygon();
	void		UpdateCar(double dt);
	void		UpdateCarTexture();
	void		UpdateCarCollision();
	void		UpdateCarSpeed(double dt);
	void		UpdatePowerUps(double dt);
	void		UpdateCursor();
	void		UpdateMainMenuCursor();
	void		UpdateGameChooseCursor();
	void		UpdateLeaderboardCursor();
	void		UpdateLight();
	void		UpdateShop(double dt);
	void		UpdateUI();

	void		RenderCar();
	void		RenderMainMenuButtons();
	void		RenderGameChooseButtons();
	void		RenderLeaderboard();
	void		RenderObstacles();
	void		RenderPowerUps();
	void		RenderSkybox();
	void		RenderShop();
	void		RenderUI();
	void		RenderTrack();

	unsigned	m_vertexArrayID;
	Mesh*		meshList[NUM_GEOMETRY];

	unsigned	m_programID;
	unsigned	m_parameters[U_TOTAL];

	//Variables
	bool b_exit = false;
	float delayTime;
	float powerupRotation;
	float displayRotation;
	float leftCursor;
	float rightCursor;
	float playerBoost;
	float opponentBoost;

	//Skybox

	//Text
	void		RenderText(Mesh* mesh, std::string text, Color color);

	void		RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	
	//Camera
	Camera3		camera;

	MS			modelStack, viewStack, projectionStack;

	Light		light[4];

	//cursor defined in .cpp
	
	void		RenderMesh(Mesh *mesh, bool enableLight);
	Saving		gameSave;
	Currency	gameBalance;
	Shop		gameShop;
};
#endif
