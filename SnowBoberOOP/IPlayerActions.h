#pragma once

class IPlayerActions {
public :
	virtual void jump(long gameFrame) = 0;

	virtual void crouch() = 0;
};
