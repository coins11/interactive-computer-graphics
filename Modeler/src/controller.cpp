#include "controller.h"
#include "model.h"

void SetController( ModelerControl* controls )
{
    controls[FRAME_CONTROLS] = ModelerControl( "Frame Number", 0, (float)max_frame_count, 1, 0 );
	controls[FOLD_ANGLE1] = ModelerControl( "Fold Angle1", 0.f, 90, 0.01f, 0.0f );
	controls[FOLD_ANGLE2] = ModelerControl( "Fold Angle2", 0.f, 90, 0.01f, 0.0f );
	controls[FOLD_ANGLE3] = ModelerControl( "Fold Angle3", 0.f, 90, 0.01f, 0.0f );
	controls[FOLD_ANGLE4] = ModelerControl( "Fold Angle4", 0.f, 90, 0.01f, 0.0f );
	controls[FOLD_ANGLE5] = ModelerControl( "Fold Angle5", 0.f, 90, 0.01f, 0.0f );
}
