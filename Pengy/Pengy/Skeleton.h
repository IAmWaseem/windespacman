#ifndef Skeleton_H
#define Skeleton_H

#include "Win.h"

class CSkeleton : public CWin
{
public:
	CSkeleton();
	~CSkeleton();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
private:
	MessageQueue* messageQueue;
	Level* level;
};

#endif
