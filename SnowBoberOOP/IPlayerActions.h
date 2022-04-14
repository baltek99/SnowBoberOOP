#pragma once

class IPlayerActions {
public :
	virtual void jump(long gameFrame);

	virtual void crouch();
};
