#ifndef __MODEL_H__
#define __MODEL_H__

#include "modelerview.h"
#include <GL/glut.h>

extern int max_frame_count;

class Model : public ModelerView {
	private:
		int frame_count;

	public:
		Model( int x, int y, int w, int h, char* label );
		void SetAutomaticAnimation();
		void SetManualAnimation();
		void BeginPaint();
		void EndPaint();
		void draw();
};

#endif
