#pragma once


class Camera
{
public:

	int const CAMERA_MAX_VELOCITY = 10;

	Camera(int x, int y, int const* CAMERA_MAX_X, int const* CAMERA_MAX_Y);
	~Camera();
	int getCameraX();
	int getCameraY();
	bool setCameraPos(int x, int y);

private:

	int x;
	int y;
	int const* CAMERA_MAX_X;
	int const* CAMERA_MAX_Y;

};

