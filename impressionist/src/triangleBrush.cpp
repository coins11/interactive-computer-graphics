#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "triangleBrush.h"

extern float frand();

TriangleBrush::TriangleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void TriangleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (float)size );

	BrushMove( source, target );
}

void TriangleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	if ( pDoc == NULL ) {
		printf( "TriangleBrush::BrushMove  document is NULL\n" );
		return;
	}

	ImpressionistUI* dlg=pDoc->m_pUI;
	int size = pDoc->getSize();
	float alpha = pDoc->getAlpha();

	int Ax = target.x - (.5 * size);
	int Bx = target.x + (.5 * size);
	int Cx = target.x;
	int Ay = target.y - (.5 * size);
	int By = target.y - (.5 * size);
	int Cy = target.y + (.5 * size);

	SetColorAlpha( source, alpha );
	glBegin(GL_POLYGON);
	glVertex2i( Ax, Ay );
	glVertex2i( Bx, By );
	glVertex2i( Cx, Cy );
	glEnd();
}

void TriangleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	glDisable(GL_BLEND);

}

