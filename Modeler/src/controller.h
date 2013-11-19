#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "modelerapp.h"

enum CONTROLLERS {
	FRAME_CONTROLS,
	FOLD_ANGLE1,
	FOLD_ANGLE2,
	FOLD_ANGLE3,
	FOLD_ANGLE4,
	FOLD_ANGLE5,
    NUM_CONTROLS,
};

extern void SetController( ModelerControl* controls );

#endif
