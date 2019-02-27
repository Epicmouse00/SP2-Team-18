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
