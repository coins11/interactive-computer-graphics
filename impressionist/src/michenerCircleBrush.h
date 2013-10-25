//
// pointBrush.h
//
// The header file for Point Brush. 
//

#ifndef MICHENERCIRCLEBRUSH_H
#define MICHENERCIRCLEBRUSH_H

#include "impBrush.h"

class MichenerCircleBrush : public ImpBrush
{
public:
	MichenerCircleBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
private:
	void Swap  (int* x, int* y);
	void Plot8 (int x, int y, int x0, int y0);
	void Circle (int x0, int y0, int r);
};

#endif
