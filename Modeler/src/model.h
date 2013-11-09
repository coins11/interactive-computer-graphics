//=============================================================================
// ƒtƒ@ƒCƒ‹: model.h
//=============================================================================
// ƒ‚ƒfƒ‹‚Ìİ’èE•`‰æ‚ğ§Œä
//=============================================================================

#ifndef __MODEL_H__
#define __MODEL_H__

// ƒwƒbƒ_ƒtƒ@ƒCƒ‹‚ÌƒCƒ“ƒNƒ‹[ƒh
#include "animator.h"
#include <math.h>

// ƒtƒŒ[ƒ€”Ô†‚ÌÅ‘å’l
int max_frame_count = 500;

//
// ƒvƒŠƒ~ƒeƒBƒu
//

static void drawDumpling()
{
	// ‹ø‚ğ•`‰æ
	glPushMatrix();
	  glTranslated( -5, 0, 0 );
	  glRotated( 90, 0, 1, 0 );
	  drawCylinder( 5, 0.2, 0.2 );
	glPopMatrix();

	// ’cq‚ğ•`‰æ
	for ( int i=0; i<3; i++ ) {
	  glPushMatrix();
	    glTranslated( 2*i-2, 0, 0 );
	    drawSphere( 1.2 );
	  glPopMatrix();
	}
}

static void drawTriangle(Vec3d A, Vec3d B, Vec3d C)
{
	// –@üƒxƒNƒgƒ‹‚ÌŒvZ
	Vec3d N = ( A-C) ^ ( B-C );

	// ƒ|ƒŠƒSƒ“‚Ì•`‰æ
	glBegin( GL_TRIANGLES );
	  glNormal3d( N[0], N[1], N[2] );
	  glVertex3d( A[0], A[1], A[2] );
	  glVertex3d( B[0], B[1], B[2] );
	  glVertex3d( C[0], C[1], C[2] );
	glEnd();
}

static void drawTorus(double R, double r)
{
	// o—Í‚·‚éƒ‚ƒfƒ‹‚ÌŠî–{î•ñ
	int div_t   = 100;// t‚Ì•ªŠ„”
	int div_p   = 100;// p‚Ì•ªŠ„”

	// •Ï‰»‚³‚¹‚éƒpƒ‰ƒ[ƒ^(”}‰î•Ï”)
	// http://ja.wikipedia.org/wiki/%E3%83%88%E3%83%BC%E3%83%A9%E3%82%B9#.E3.83.89.E3.83.BC.E3.83.8A.E3.83.84.E5.9E.8B
	double t = 0;
	double p = 0;

	// ƒpƒ‰ƒ[ƒ^‚Ì•ÏˆÊ
	double dt = 2*M_PI/(div_t);
	double dp = 2*M_PI/(div_p);

	int i,j;

	// À•W

	// À•W‚ÌŒvZ
	Vec3d *ps = new Vec3d[div_t * div_p];
	int k = 0;
	for(i=0, t=0; i < div_t; i++, t+=dt) {
	  for(j=0, p=0; j < div_p; j++, p+=dp) {
	    double x = R * cos(t) + r * cos(p) * cos(t);
	    double y = R * sin(t) + r * cos(p) * sin(t);
	    double z = r * sin(p);
		ps[k++] = Vec3d(x,y,z);
	  }
	}

	// –Ê‚ÌŒvZ
	for(i=0; i < div_t; i++) {
	  for(j=0; j < div_p; j++) {
	    int v0 = i*div_p + j;
	    int v1 = (i+1)%div_t*div_p + j;
	    int v2 = (i+1)%div_t*div_p + (j+1)%div_p;
		drawTriangle(ps[v0], ps[v1], ps[v2]);

	    //v0 = v0;
	    v1 = v2;
	    v2 = i*div_p + (j+1)%div_p;
		drawTriangle(ps[v0], ps[v1], ps[v2]);
	  }
	}

	delete[] ps;
}

static void drawEllipsoid(double rx, double ry, double rz)
{
	// o—Í‚·‚éƒ‚ƒfƒ‹‚ÌŠî–{î•ñ
	int div_phi   = 100;// ƒ³•ûŒü‚Ì•ªŠ„”
	int div_theta = 100;// ƒÆ•ûŒü‚Ì•ªŠ„”

	// •Ï‰»‚³‚¹‚éƒpƒ‰ƒ[ƒ^
	// http://ja.wikipedia.org/wiki/%E6%A5%B5%E5%BA%A7%E6%A8%99%E7%B3%BB#.E7.90.83.E5.BA.A7.E6.A8.99_.28Spherical_Polar_Coordinates.29
	double phi = 0;
	double theta = 0;

	// ƒpƒ‰ƒ[ƒ^‚Ì•ÏˆÊ
	double dtheta = M_PI/(div_theta);
	double dphi   = 2*M_PI/(div_phi);

	int i,j;

	// À•W‚ÌŒvZ
	Vec3d *ps = new Vec3d[div_phi * (div_theta + 1)];
	int k = 0;
	for(i=0, theta=0; i <= div_theta; i++, theta+=dtheta) {
	  for(j=0, phi=0; j < div_phi; j++, phi+=dphi) {
	    double x = rx * sin(theta) * cos(phi);
	    double y = ry * sin(theta) * sin(phi);
	    double z = rz * cos(theta);
		ps[k++] = Vec3d(x,y,z);
	  }
	}

	// –Ê‚ÌŒvZ
	for(i=0; i < div_theta; i++) {
	  for(j=0; j < div_phi; j++) {
	    int v0 = i*div_phi + j;
	    int v1 = (i+1)*div_phi + j;
	    int v2 = (i+1)*div_phi + (j+1)%div_phi;
		drawTriangle(ps[v0], ps[v1], ps[v2]);

	    //v0 = v0;
	    v1 = v2;
	    v2 = i*div_phi + (j+1)%div_phi;
		drawTriangle(ps[v0], ps[v1], ps[v2]);
	  }
	}

	delete[] ps;
}

static double curve_cup(double z)
{
	return 2 + cos(M_PI * pow(z * 20.0, 1.7) * 0.01);
}

static void drawRevolution(double (*curve)(double))
{
	int i,j;

	// o—Í‚·‚éƒ‚ƒfƒ‹‚ÌŠî–{î•ñ
	double height = 1;
	int div_z = 100;
	int div_phi = 100;

	double *r = new double[div_z+1];
	for(i=0; i<=div_z; i++) {
		//r[i] = 1 + cos(PI*i/div_z*2);
		//r[i] = 2 + cos(M_PI*pow(i * 20.0 / div_z, 1.7) * 0.01);
		r[i] = curve((double)i / div_z);
	}

	// •Ï‰»‚³‚¹‚éƒpƒ‰ƒ[ƒ^
	double z = -0.5 * height;
	double phi;

	// ƒpƒ‰ƒ[ƒ^‚Ì•ÏˆÊ
	double dz   = height/div_z;
	double dphi = 2*M_PI/div_phi;

	// À•W‚ÌŒvZ
	Vec3d *ps = new Vec3d[div_phi * (div_z + 1)];
	int k = 0;
	for(i=0; i <= div_z; i++, z+=dz) {
	  for(j=0, phi=0; j < div_phi; j++, phi+=dphi) {
	    double x = r[i] * sin(phi);
	    double y = r[i] * cos(phi);
	    //fprintf(fout, "v %f %f %f\n", x, -z, y);
		ps[k++] = Vec3d(x,-z,y);
	  }
	}

	// –Ê‚ÌŒvZ
	for(i=0; i < div_z; i++) {
	  for(j=0; j < div_phi; j++) {
	    int v0 = i*div_phi + j;
	    int v1 = (i+1)*div_phi + j;
	    int v2 = (i+1)*div_phi + (j+1)%div_phi;
	    //fprintf(fout, "f %d %d %d\n", v0+1, v1+1, v2+1);
		drawTriangle(ps[v0], ps[v1], ps[v2]);

	    //v0 = v0;
	    v1 = v2;
	    v2 = i*div_phi + (j+1)%div_phi;
	    //fprintf(fout, "f %d %d %d\n", v0+1, v1+1, v2+1);
		drawTriangle(ps[v0], ps[v1], ps[v2]);
	  }
	}

	delete[] ps;
}

static void drawRevolution(int n, float c[][2])
{
	int i,j;

	// o—Í‚·‚éƒ‚ƒfƒ‹‚ÌŠî–{î•ñ
	int div_phi = 100;

  // •Ï‰»‚³‚¹‚éƒpƒ‰ƒ[ƒ^
  double phi;
  double dphi = 2*M_PI/div_phi;

  // À•W‚ÌŒvZ
  Vec3d *ps = new Vec3d[div_phi * (n+1)];
  int k = 0;
  for(i=0; i < n; i++) {
    for(j=0, phi=0; j < div_phi; j++, phi+=dphi) {
      double x = (c[i][0]) * sin(phi) * 0.1;
      double y = (c[i][0]) * cos(phi) * 0.1;
      double z = (c[i][1]) * 0.1;
      //fprintf(fout, "v %f %f %f\n", x, -z, y);
      ps[k++] = Vec3d(x,-z,y);
    }
  }

  // –Ê‚ÌŒvZ
  for(i=0; i < n; i++) {
    for(j=0; j < div_phi; j++) {
      int v0 = i*div_phi + j;
      int v1 = (i+1)*div_phi + j;
      int v2 = (i+1)*div_phi + (j+1)%div_phi;
      //fprintf(fout, "f %d %d %d\n", v0+1, v1+1, v2+1);
      drawTriangle(ps[v0], ps[v1], ps[v2]);

      //v0 = v0;
      v1 = v2;
      v2 = i*div_phi + (j+1)%div_phi;
      //fprintf(fout, "f %d %d %d\n", v0+1, v1+1, v2+1);
      drawTriangle(ps[v0], ps[v1], ps[v2]);
    }
  }

	delete[] ps;
}

static void drawPondeRing(double R)
{
  double dr = M_PI / 4;
  for(int i = 0; i < 8; ++i)
  {
    glPushMatrix();
      glTranslated(R * sin(i * dr), R * cos(i * dr), 0);
      drawSphere(1);
    glPopMatrix();
  }
}

double curve_body(double z)
{
	return abs(sin(z * M_PI * 2)) + pow(sin(z * M_PI), 2);
}

double curve_head(double z)
{
  return 
  pow(z, 0) * -0.00279909391803798 + 
  pow(z, 1) * 5.19175917413233 + 
  pow(z, 2) * -16.8718027194796 + 
  pow(z, 3) * 28.0849625347318 + 
  pow(z, 4) * -16.3769116011162 ;
}

// ModelƒNƒ‰ƒX‚Ì’è‹`iModelerViewƒNƒ‰ƒX‚ğŒp³j
class Model : public ModelerView {
  private:
    //```````````````````````````````````
    //‘æ3T‰Û‘è
    //---------------------------------------------------------------------

    // ƒtƒŒ[ƒ€”Ô†
    int frame_count;

    //-------------------------------------------------------------------------
    // §Œä•Ï”
    //-------------------------------------------------------------------------

    // ```•Ï”‚ğ’Ç‰Á```
    Vec3d center;
    Vec3d head;

    //```````````````````````````````````

  public:
    // ƒRƒ“ƒXƒgƒ‰ƒNƒ^iƒX[ƒp[ƒNƒ‰ƒX‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^‚ğŒÄ‚Ño‚·j
    Model( int x, int y, int w, int h, char* label ) : ModelerView( x, y, w, h, label )
  {
    //```````````````````````````````````
    //‘æ3T‰Û‘è
    //---------------------------------------------------------------------

    // ƒtƒŒ[ƒ€”Ô†‚Ì‰Šú‰»
    frame_count = 0;

    //---------------------------------------------------------------------
    // ‰Šú‰»
    //---------------------------------------------------------------------

    // ```•Ï”‚ğ‰Šú‰»```
    head = Vec3d(10, -10, 10);

    //```````````````````````````````````
  }

    //```````````````````````````````````
    //‘æ3T‰Û‘è
    //---------------------------------------------------------------------

    // ©“®ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìİ’è
    void SetAutomaticAnimation()
    {
      //-----------------------------------------------------------------
      // ƒAƒjƒ[ƒVƒ‡ƒ“
      //-----------------------------------------------------------------

      // ```ƒvƒƒOƒ‰ƒ€‚ğ‹Lq```

      //-----------------------------------------------------------------
    }

    // è“®ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìİ’è
    void SetManualAnimation()
    {
      //-----------------------------------------------------------------
      // ƒAƒjƒ[ƒVƒ‡ƒ“
      //-----------------------------------------------------------------

      // ```ƒvƒƒOƒ‰ƒ€‚ğ‹Lq```

      //-----------------------------------------------------------------
    }

    //```````````````````````````````````

    // •`‰æ‚Ì‘Oˆ—
    void BeginPaint()
    {
      // ”¼“§–¾ˆ—‚ğ—LŒø‰»
      glEnable( GL_BLEND );
      // ¬‡•û–@‚Ìw’è
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    // •`‰æ‚ÌŒãˆ—
    void EndPaint()
    {
      // ”¼“§–¾ˆ—‚ğ–³Œø‰»
      glDisable( GL_BLEND );
    }

    void drawLionHead()
    {
      glPushMatrix();

      // ‚½‚Ä‚ª‚İ
      setDiffuseColor(1.0f, 0.74f, 0.0f);
      drawPondeRing(2.3);

      // “ª‚Ì–{‘Ì
      setDiffuseColor(1.0f, 0.94f, 0.0f);
      glTranslated(0, 0, -0.3);
      //glScaled(1, 1, 1.1);
      drawSphere(1.6);

      // Œû
      glPushMatrix();
        glTranslated(-0.35, -0.6, -1.3);
        drawSphere(0.4);
      glPopMatrix();

      glPushMatrix();
        glTranslated(0.35, -0.6, -1.3);
        drawSphere(0.4);
      glPopMatrix();

      // –Ú
      glPushMatrix();
        setDiffuseColor(0.3f, 0.3f, 0.3f);
        glTranslated(-0.7, 0.3, -1.3);
        drawSphere(0.2);
      glPopMatrix();

      glPushMatrix();
        glTranslated(0.7, 0.3, -1.3);
        drawSphere(0.2);
      glPopMatrix();

      // •@
      glPushMatrix();
        setDiffuseColor(1.0f, 0.3f, 0.3f);
        glTranslated(0.0, -0.3, -1.5);
        drawSphere(0.25);
      glPopMatrix();

      glPopMatrix();
    }

    void drawLionBody()
    {
	  	glPushMatrix();
	  		glScaled(2, 2, 3);
        drawSphere(1);
	  	glPopMatrix();
    }

    void drawLionLeg()
    {

      int n = 40;
      float c[][2] = {
        2.000000, 2.000000, 17.289001, 3.230000, 29.752014, 6.680000, 39.683014, 11.990000, 47.376007, 18.799999, 53.125000, 26.750000, 57.223999, 35.480000, 59.967010, 44.630001, 61.648010, 53.840000, 62.561005, 62.750000,
        63.000000, 71.000000, 63.000000, 71.000000, 62.544006, 86.606003, 62.351990, 101.648003, 62.388000, 116.162003, 62.615997, 130.184006, 63.000000, 143.750000, 63.503998, 156.895996, 64.092010, 169.658005, 64.727997, 182.072006,
        65.376007, 194.173996, 66.000000, 206.000000, 66.000000, 206.000000, 69.886993, 218.128006, 73.216003, 229.343994, 76.088989, 239.695999, 78.608002, 249.231995, 80.875000, 258.000000, 82.992004, 266.048004, 85.061005, 273.424011,
        87.183990, 280.175995, 89.463013, 286.351990, 92.000000, 292.000000, 92.000000, 292.000000, 91.816010, 297.536011, 91.127991, 303.287994, 89.731995, 309.171997, 87.424011, 315.104004, 84.000000, 321.000000, 79.256012, 326.776001,
      };

      glScaled(0.08, 0.13, 0.08);
      drawRevolution(n, c);
    }

    void drawBody()
    {
      glPushMatrix();
      glScaled(1, 3, 1);
      drawRevolution(&curve_body);
      glPopMatrix();
    }

    // ƒIƒuƒWƒFƒNƒg‚Ì•`‰æ
    void draw()
    {
      //```````````````````````````````````
      //‘æ3T‰Û‘è
      //---------------------------------------------------------------------
      // ©“®ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìˆ—
      if ( IsAutomaticAnimation() && frame_count<max_frame_count ) {
        // ƒtƒŒ[ƒ€”Ô†‚ÌXV
        SetSliderValue( FRAME_CONTROLS, ++frame_count );
        // ©“®ƒAƒjƒ[ƒVƒ‡ƒ“
        SetAutomaticAnimation();
      }
      // è“®ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìˆ—
      else {
        // ƒtƒŒ[ƒ€”Ô†‚ğæ“¾
        frame_count = (int)GetSliderValue( FRAME_CONTROLS );
        // è“®ƒAƒjƒ[ƒVƒ‡ƒ“
        SetManualAnimation();
      }
      //```````````````````````````````````

      // ƒX[ƒp[ƒNƒ‰ƒX‚Ì•`‰æƒƒ\ƒbƒh‚ğƒR[ƒ‹i•K{j
      ModelerView::draw();

      // •`‰æŠJn
      BeginPaint();

      //---------------------------------------------------------------------
      // ƒIƒuƒWƒFƒNƒg‚ğ•`‰æ
      //---------------------------------------------------------------------

      // ```ƒvƒƒOƒ‰ƒ€‚ğ‹Lq```

      //drawDumpling();

      //drawTorus(4, 2);
      //drawEllipsoid(3, 4, 5);

      //glScaled(1, 5, 1);
      //drawRevolution(&curve_cup);

      //glScaled(1, 3, 1);
      //drawRevolution(&curve_head);

      //drawHead();
      //drawBody();

      //setAmbientColor(0.1f, 0.84f, 0.0f);

      glPushMatrix();

        setDiffuseColor(1.0f, 0.94f, 0.0f);
        drawLionBody();

        // ‘«
        glPushMatrix();
          glTranslated(1, 0, -1);
          glRotated(10, 1, 0, 1);
          drawLionLeg();
        glPopMatrix();

        glPushMatrix();
          glTranslated(-1, 0, -1);
          glRotated(10, 1, 0, -1);
          drawLionLeg();
        glPopMatrix();

        glPushMatrix();
          glTranslated(1, 0, 1.5);
          glRotated(-10, 1, 0, -1);
          drawLionLeg();
        glPopMatrix();

        glPushMatrix();
          glTranslated(-1, 0, 1.5);
          glRotated(-10, 1, 0, 1);
          drawLionLeg();
        glPopMatrix();

        // ‚µ‚Á‚Û
        glPushMatrix();
          glTranslated(0, 0, 2);
          double l = 0.5;
          double r = 0.2;
          for(; r>=0.1; r-=0.008, l-=0.01) {
            drawCylinder(l, 0.02 + r, r);
            glTranslated(0, 0, l);
            glRotated(10, -1, 0, 0);
          }
          glScaled(0.2, 0.2, 0.2);
          drawPondeRing(1.5);
        glPopMatrix();

        // “ª
        glPushMatrix();
          glTranslated(0, 1, -3);
          drawLionHead();
        glPopMatrix();

      glPopMatrix();

      // ‰a
      glPushMatrix();
        setDiffuseColor(0.62f, 0.32f, 0.17f);
        glTranslated(0, -5, -5);
        glRotated(90, 1, 0.1, 0);
        drawTorus(1.5,0.75);
      glPopMatrix();

      //---------------------------------------------------------------------

      // •`‰æI—¹
      EndPaint();
    }
};

// __MODEL_H__
#endif
