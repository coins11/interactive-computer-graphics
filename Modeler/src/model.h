#ifndef __MODEL_H__
#define __MODEL_H__

#include "modelerview.h"
#include <GL/glut.h>
#include <tuple>

extern int max_frame_count;

class Model : public ModelerView {
	private:
		int frame_count;
		std::tuple<float, float, float, float, float> angle;

	public:
		Model( int x, int y, int w, int h, char* label );
		void SetAutomaticAnimation();
		void SetManualAnimation();
		void BeginPaint();
		void EndPaint();
		void draw();
};

#endif
