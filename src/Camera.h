#pragma once


class Camera
{
public:

	int const CAMERA_MAX_VELOCITY = 10;

	Camera(int x, int y, int const* CAMERA_MAX_X, int const* CAMERA_MAX_Y);
	~Camera();
	double getCameraX();
	double getCameraY();
	bool setCameraPos(double x, double y);

private:

	double x;
	double y;
	int const* CAMERA_MAX_X;
	int const* CAMERA_MAX_Y;

};

