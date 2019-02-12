#ifndef SCENE_1_H 
#define SCENE_1_H

#include "Scene.h" 

#include "Camera.h" 
#include "Camera3.h"

#include "Mesh.h"
#include "MeshBuilder.h"

#include "MatrixStack.h"
#include "Light.h"

class Scene1 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,

		//Lightings
		GEO_LIGHTBALL,
		GEO_LIGHTCRYSTAL,

		//SkyBox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		//Text
		GEO_TEXT,

		//Character
		GEO_HAT,
		GEO_HATSTAR,
		GEO_HATSIDE,

		GEO_HEAD,
		GEO_EYE1,
		GEO_PUPIL1,
		GEO_EYE2,
		GEO_PUPIL2,

		GEO_MOUTHSKIN,
		GEO_MOUTH,

		GEO_BODY,
		GEO_BELLY,
		GEO_BELLYSTAR,

		GEO_LEFTSHOULDER,
		GEO_LEFTARM,
		GEO_LEFTARM2,
		GEO_LEFTHAND,

		GEO_RIGHTSHOULDER,
		GEO_RIGHTARM,
		GEO_RIGHTARM2,
		GEO_RIGHTHAND,

		GEO_LEFTLEG,
		GEO_LEFTLEG2,
		GEO_LEFTFOOT,

		GEO_RIGHTLEG,
		GEO_RIGHTLEG2,
		GEO_RIGHTFOOT,

		//Laser Gun
		GEO_FRONTCONE,
		GEO_BACKCONE,
		GEO_BARREL,
		GEO_BARRELCIRCLE,
		GEO_BODYCOVER,
		GEO_GUNBODY,
		GEO_HANDLE,
		GEO_BULLET,

		//OBJ Models
		GEO_CONSOLE,
		GEO_PLATFORM,
		GEO_PLATFORM2,
		GEO_CRYSTAL,
		GEO_CSTAND,
		GEO_CRYSTAL2,
		GEO_CSTAND2,
		GEO_CPILLAR,
		GEO_STAIR1,
		GEO_STAIR2,
		GEO_CHAIR1,
		GEO_PANEL1,
		GEO_LEVER,
		GEO_LEVERBASE,
		GEO_SWHEEL,
		GEO_SWHEELSTAND,
		GEO_PLATFORMWHEEL,
		GEO_BOAT,
		GEO_LEFTWING,
		GEO_RIGHTWING,
		GEO_MISSILE,
		GEO_BUTTON,
		GEO_MONITOR,

		GEO_PLANE,
		NUM_GEOMETRY,
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

		U_TOTAL,
	};

public:
	Scene1();
	~Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void Hat();
	void Head();
	void Body();

	void RightArm();
	void LaserGun();

	void LeftArm();

	void RightLeg();
	void LeftLeg();

	void chair();
	void stairs();
	void pillar();

	void crystalstand();
	void crystalleft();

	void consoleLeft();
	void consoleRight();

	void lever();

	void WheelStand();
	void SWheel();

	void leftWing1();
	void rightWing1();
	void leftWing2();
	void rightWing2();
	void leftWing3();
	void rightWing3();


private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;

	float rotateLeftArm;
	float rotateRightArm;

	float rotateLeftLeg;
	float rotateRightLeg;

	float ArmAim;
	float ArmAim2;

	float LaserShootX;
	float LaserShootY;

	float crystalRotate;

	float leverPull;
	float delayTime;
	float rotateWheel;
	float SkyboxRotate;
	float chairNum;
	
	//Left
	float WingSimulation1;
	float WingSimulation2;
	//Right
	float WingSimulation3;
	float WingSimulation4;

	float ButtonPress;
	float missleShoot;

	bool idle;
	bool AnimateAim;
	bool AnimateShoot;
	bool leverflip;
	bool chairFlip;
	bool buttonPressed;
	bool missileLaunch;

	//Skybox Stuffs
	void RenderSkybox();

	//For Text Stuffs
	void RenderText(Mesh* mesh, std::string text, Color color);

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	//Camera camera;
	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[4];
	
	void RenderMesh(Mesh *mesh, bool enableLight);
};
#endif
