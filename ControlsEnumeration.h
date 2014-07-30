//This class handels enumerations for Control statuses
#pragma once

class ControlsEnumeration
{
public:
	typedef enum CTRL_STATUS
	{
		CTRL_STATUS_INIT=0,
		CTRL_STATUS_MAIN,
		CTRL_STATUS_MOVING_CAMERA,
		CTRL_STATUS_QUIT
	};
};