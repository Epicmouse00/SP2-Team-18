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
		GEO_OBSTACLE_LONG,

		//OBJ Models
		GEO_PLANE,
		GEO_CURSOR,
		GEO_PLAYER,
    
		//Menu buttons
		GEO_BUTTON,

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
	void		InitObstacles(unsigned int noOfObstacles);

	void		UpdateDelayTime(double dt);
	void		UpdateCamMovement();
	void		UpdateAppPolygon();
	void		UpdateMenuIndex();
	void		UpdatePlayerStrafe(double dt);
	void		UpdatePlayerJump(double dt);
	void		UpdateMainMenuCursor();
	void		UpdateGameChooseCursor();

	void		RenderPlayer();
	void		RenderMainMenuButtons();
	void		RenderGameChooseButtons();
	void		RenderObstacles();
	void		RenderSkybox();

	unsigned	m_vertexArrayID;
	Mesh*		meshList[NUM_GEOMETRY];

	unsigned	m_programID;
	unsigned	m_parameters[U_TOTAL];

	//Variables
	bool b_exit = false;
	const unsigned int numberOfRows = 100;
	float Movement;
	bool Lane1;
	bool Lane2;
	bool Lane2a;
	bool Lane3;
	bool Lane3a;
	bool Lane4;
	float Jump;
	float delayTime;

	bool JumpPressed;

	//Skybox

	//Text
	void		RenderText(Mesh* mesh, std::string text, Color color);

	void		RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	
	//Camera
	Camera3		camera;

	MS			modelStack, viewStack, projectionStack;

	Light		light[4];

	//cursor defined in .cpp

	int			gameState = E_MAINMENU;
	int			gameMode = MODE_VS;
	
	void		RenderMesh(Mesh *mesh, bool enableLight);
	Obstacle	obstacleList[4][100] = { NULL };
};
#endif
