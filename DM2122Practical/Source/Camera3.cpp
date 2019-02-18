#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera3::Update(double dt)
{
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);

	static const float CAMERA_SPEED = 90.f;

	if (Application::IsKeyPressed('Z'))
		active = true;
	if (Application::IsKeyPressed('X'))
		active = false;

	if (active)
	{
		//Movement
		if (Application::IsKeyPressed('A'))
		{
			position = position - right;
			target = position + view;
		}
		if (Application::IsKeyPressed('D'))
		{
			position = position + right;
			target = position + view;
		}
		if (Application::IsKeyPressed('W'))
		{
			position = position + view.Normalized();
			target = position + view;
		}
		if (Application::IsKeyPressed('S'))
		{
			position = position - view.Normalized();
			target = position + view;
		}


		//Camera Movement
		else if (Application::IsKeyPressed(VK_LEFT))
		{
			float yaw = (float)(CAMERA_SPEED * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			up = rotation * up;
			view = rotation * view;
			target = position + view;
		}
		else if (Application::IsKeyPressed(VK_RIGHT))
		{
			float yaw = (float)(-CAMERA_SPEED * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			up = rotation * up;
			view = rotation * view;
			target = position + view;;
		}
		else if (Application::IsKeyPressed(VK_UP))
		{
			float pitch = (float)(CAMERA_SPEED * dt);
			view = (target - position).Normalized();
			right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);

			right = rotation * right;
			view = rotation * view;
			target = position + view;
		}
		else if (Application::IsKeyPressed(VK_DOWN))
		{
			float pitch = (float)(-CAMERA_SPEED * dt);
			view = (target - position).Normalized();
			right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);

			right = rotation * right;
			view = rotation * view;
			target = position + view;
		}
		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

bool Camera3::getActive()
{
	return active;
}

void Camera3::setPosition(const Vector3 & pos, const Vector3 & target, const Vector3 & up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();
}
