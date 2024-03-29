// (your name here)
// Chess animation starter kit.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;
#include "glut.h"
#include "graphics.h"
#include "chess_board.h"


// Global Variables
//Colors
// here and in graphics.h
GLdouble redMaterial[] = {0.7, 0.1, 0.2, 1.0};
GLdouble greenMaterial[] = {0.1, 0.7, 0.4, 1.0};
GLdouble brightGreenMaterial[] = {0.1, 0.9, 0.1, 1.0};
GLdouble blueMaterial[] = {0.1, 0.2, 0.7, 1.0};
GLdouble whiteMaterial[] = {1.0, 1.0, 1.0, 1.0};

double screen_x = 600;
double screen_y = 500;


double GetTime()
{
	static clock_t start_time = clock();
	clock_t current_time = clock();
	double total_time = double( current_time - start_time ) / CLOCKS_PER_SEC;
	return total_time;
}

// Outputs a string of text at the specified location.
void text_output(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}

// Given the three triangle points x[0],y[0],z[0],
//		x[1],y[1],z[1], and x[2],y[2],z[2],
//		Finds the normal vector n[0], n[1], n[2].
void FindTriangleNormal(double x[], double y[], double z[], double n[])
{
	// Convert the 3 input points to 2 vectors, v1 and v2.
	double v1[3], v2[3];
	v1[0] = x[1] - x[0];
	v1[1] = y[1] - y[0];
	v1[2] = z[1] - z[0];
	v2[0] = x[2] - x[0];
	v2[1] = y[2] - y[0];
	v2[2] = z[2] - z[0];
	
	// Take the cross product of v1 and v2, to find the vector perpendicular to both.
	n[0] = v1[1]*v2[2] - v1[2]*v2[1];
	n[1] = -(v1[0]*v2[2] - v1[2]*v2[0]);
	n[2] = v1[0]*v2[1] - v1[1]*v2[0];

	double size = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	n[0] /= -size;
	n[1] /= -size;
	n[2] /= -size;
}

// Loads the given data file and draws it at its default position.
// Call glTranslate before calling this to get it in the right place.

void DrawPiece(const char filename[], double t)
{
	double delay = 1;
	t -= delay;
	if (t < 0) {
		t = 0;
	}	
	// Try to open the given file.
	char buffer[200];
	ifstream in(filename);
	if(!in)
	{
		cerr << "Error. Could not open " << filename << endl;
		exit(1);
	}

	double x[100], y[100], z[100]; // stores a single polygon up to 100 vertices.
	int done = false;
	int verts = 0; // vertices in the current polygon
	int polygons = 0; // total polygons in this file.
	do
	{
		in.getline(buffer, 200); // get one line (point) from the file.
		int count = sscanf_s(buffer, "%lf, %lf, %lf", &(x[verts]), &(y[verts]), &(z[verts]));
		done = in.eof();
		if(!done)
		{
			if(count == 3) // if this line had an x,y,z point.
			{
				verts++;
			}
			else // the line was empty. Finish current polygon and start a new one.
			{
				if(verts>=3)
				{
					glBegin(GL_POLYGON);
					double n[3];
					FindTriangleNormal(x, y, z, n);
					glNormal3dv(n);
					for(int i=0; i<verts; i++)
					{
						glVertex3d( x[i] + n[i] * 1000 * t, y[i], z[i] + n[i] * 1000 * t);
					}
					glEnd(); // end previous polygon
					polygons++;
					verts = 0;
				}
			}
		}
	}
	while(!done);

	if(verts>0)
	{
		cerr << "Error. Extra vertices in file " << filename << endl;
		exit(1);
	}

}



void DrawPiece(const char filename[])
{
	// Try to open the given file.
	char buffer[200];
	ifstream in(filename);
	if(!in)
	{
		cerr << "Error. Could not open " << filename << endl;
		exit(1);
	}

	double x[100], y[100], z[100]; // stores a single polygon up to 100 vertices.
	int done = false;
	int verts = 0; // vertices in the current polygon
	int polygons = 0; // total polygons in this file.
	do
	{
		in.getline(buffer, 200); // get one line (point) from the file.
		int count = sscanf_s(buffer, "%lf, %lf, %lf", &(x[verts]), &(y[verts]), &(z[verts]));
		done = in.eof();
		if(!done)
		{
			if(count == 3) // if this line had an x,y,z point.
			{
				verts++;
			}
			else // the line was empty. Finish current polygon and start a new one.
			{
				if(verts>=3)
				{
					glBegin(GL_POLYGON);
					double n[3];
					FindTriangleNormal(x, y, z, n);
					glNormal3dv(n);
					for(int i=0; i<verts; i++)
					{
						glVertex3d(x[i], y[i], z[i]);
					}
					glEnd(); // end previous polygon
					polygons++;
					verts = 0;
				}
			}
		}
	}
	while(!done);

	if(verts>0)
	{
		cerr << "Error. Extra vertices in file " << filename << endl;
		exit(1);
	}

}


void DrawQuad(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4)
{
	glBegin(GL_QUADS);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);

	glVertex3d(x2, y2, z2);
	glVertex3d(x3, y3, z3);

	glVertex3d(x3, y3, z3);
	glVertex3d(x4, y4, z4);

	glVertex3d(x4, y4, z4);
	glVertex3d(x1, y1, z1);

	glEnd();
}

void DrawQuadOutline(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4)
{
	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);

	glVertex3d(x2, y2, z2);
	glVertex3d(x3, y3, z3);

	glVertex3d(x3, y3, z3);
	glVertex3d(x4, y4, z4);

	glVertex3d(x4, y4, z4);
	glVertex3d(x1, y1, z1);

	glEnd();
}

void DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}


enum View {bottom, top, left, right, centerFly};
View current_view = bottom;
//side View Right
double eyer[3] = {-6000, 9000, 4000};
double atr[3]  = {4000, 0, 4000};
//Side View Left
double eyel[3] = {14000, 9000, 4000};
double atl[3]  = {4000, 0, 4000};
//Back View
double eye[3] = {4000, 9000, -5000};
double at[3]  = {4000, 0, 4000};
//TOP View
double eyet[3] = {4000, 9000, 13000};
double att[3]  = {4000, 0, 4000};
//FLY View
double eyef[3] = {-6000, 9000, 2500};
double atf[3]  = {4000, 0, 4000};


//
// GLUT callback functions
//

// As t goes from t0 to t1, set v between v0 and v1 accordingly.
void Interpolate(double t, double t0, double t1,
	double & v, double v0, double v1)
{
	double ratio = (t - t0) / (t1 - t0);
	if (ratio < 0)
		ratio = 0;
	if (ratio > 1)
		ratio = 1;
	v = v0 + (v1 - v0)*ratio;
}

//void EvalCurve(float t, double & p0, double p1, double p2, double p3)
//{
//
//	for (int i = 0; i < 3; i++)
//	{
//		p1 = p1 * (1 - t) * (1 - t) * (1 - t) + 3 * p1.p[i] * (1 - t) * (1 - t) * t + 3 * p2.p[i] * (1 - t) * t * t + p3.p[i] * t * t * t;
//		p2 = p2 * (1 - t) * (1 - t) * (1 - t) + 3 * p1.p[i] * (1 - t) * (1 - t) * t + 3 * p2.p[i] * (1 - t) * t * t + p3.p[i] * t * t * t;
//		p3 = p3 * (1 - t) * (1 - t) * (1 - t) + 3 * p1.p[i] * (1 - t) * (1 - t) * t + 3 * p2.p[i] * (1 - t) * t * t + p3.p[i] * t * t * t;
//	}
//}

//interpolate following a 3rd point into the y axis
void Interpolate(double t, double t0, double t1, double& v, double v0, double v1, double v2){
	//need the y postiong of  p0, p1, p2 and we need the z position of p0, p1, p2
	//the y and z postitions should be clalculated completely independently of eachother
	//z = pow((1 - t), 3) * x + 3 * t * pow((1 - t), 2) * x + 3 * (1 - t) * pow(t, 2) * x + pow(t, 3) * x;
	//y = pow((1 - t), 3) * y + 3 * t * pow((1 - t), 2) * y + 3 * (1 - t) * pow(t, 2) * y + pow(t, 3) * y;
}

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	double t = GetTime();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	if (current_view == bottom) {
	gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,1,0);
	}
	else if (current_view == ::left){
		gluLookAt(eyel[0], eyel[1], eyel[2],  atl[0], atl[1], atl[2],  0,1,0);
	}
	else if (current_view == ::right) {
		gluLookAt(eyer[0], eyer[1], eyer[2],  atr[0], atr[1], atr[2],  0,1,0);
	}
	else if (current_view == ::top) {
		gluLookAt(eyet[0], eyet[1], eyet[2], att[0], att[1], att[2], 0, 1, 0);
	}
	else if (current_view == ::centerFly) {
	//double eyef[3] = {-6000, 9000, 2500};
	//double atf[3]  = {4000, 0, 4000};

	//double eyer[3] = {-6000, 9000, 4000};
	//double atr[3]  = {4000, 0, 4000};
	
	//double eyel[3] = {14000, 9000, 4000};
	//double atl[3]  = {4000, 0, 4000};
		double eyeX;
		double eyeY;
		double eyeZ;
		double atX;
		double atY;
		Interpolate(t, 2, 5, eyeX, -8000, 16000);
		Interpolate(t, 2, 5, atX, 8000, 0);
		Interpolate(t, 2, 3.5, eyeY, 9000, 3000);
		if (t > 3.5) {
			Interpolate(t, 3.5, 5, eyeY, 3000, 9000);
		}
	//RECENTER
		if (t > 5) {
			//recenterATX
			Interpolate(t, 5, 6, atX, 0, 4000);
			//recenterEYEX
			Interpolate(t, 5, 6, eyeX, 16000, 14000);
		}
		Interpolate(t, 5, 6, eyeZ, 2500, 4000);
	
		//Interpolate(t, 2, 5, eyeY,  )
		gluLookAt(eyeX, eyeY, eyeZ, atX, atf[1], atf[2], 0, 1, 0);

	}

	//gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,1,0); // Y is up!

	/************************************************************************************************************************************

				WRITE MODELS TO GPU

	*************************************************************************************************************************************/

	enum piece_numbers { pawn = 100, king, queen, rook, bishop, knight };

	glNewList(pawn, GL_COMPILE);
	DrawPiece("PAWN.POL");
	glEndList();

	glNewList(king, GL_COMPILE);
	DrawPiece("KING.POL");
	glEndList();

	glNewList(queen, GL_COMPILE);
	DrawPiece("QUEEN.POL");
	glEndList();


	glNewList(rook, GL_COMPILE);
	DrawPiece("ROOK.POL");
	glEndList();


	glNewList(bishop, GL_COMPILE);
	DrawPiece("BISHOP.POL");
	glEndList();

	glNewList(knight, GL_COMPILE);
	DrawPiece("KNIGHT.POL");
	glEndList();


	/************************************************************************************************************************************

				WHITE'S BOARDS SPACE

	*************************************************************************************************************************************/


	// Set the color for one side (white), and draw its 16 pieces.
	GLfloat mat_amb_diff1[] = {1.0f, 1.0f, 1.0f,1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);

	int characterSizebuffer = 500;
	double z;
	double x;
	double y;
	double angle;
	double scaleSize;

	for(int x = 0 + characterSizebuffer; x < 8000 + characterSizebuffer; x += 1000)
	{
		Interpolate(t, 1, 3, z,  1000 + (.5 * characterSizebuffer), 3000 + .5 * characterSizebuffer);
		Interpolate(t, 2, 3 , y, 0, 2000 );
		Interpolate(t, 2, 3 , y, 0, 2000 );
		glPushMatrix();
		glTranslatef(x, y, z + characterSizebuffer);
	
		if ((x - characterSizebuffer) % 2000 == 0) {
			Interpolate(t, 3, 3.5, angle, 0, -45);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}
		else {
			Interpolate(t, 3, 3.5, angle, 0, 45);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}

		if ((x - characterSizebuffer) % 2000 == 0) {
			Interpolate(t, 3.5, 4.5, angle, 0, 90);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}
		else {
			Interpolate(t, 3.5, 4.5, angle, 0, -90);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}

	// Rotates to hit other pieces
		//if ((x - characterSizebuffer) % 2000 == 0) {
		//	Interpolate(t, 4.5, 5.5, angle, 0, -270);
		//	glRotated(angle, 1, 0, 0);
		//	glTranslated(0, 0, 0);
		//}

		
		glCallList(pawn);
		glPopMatrix();
	}
	
	//if (t > 3.5 && t < 4.5) {
	//
	//	glPushMatrix();
	//	glTranslatef(x, 0, z + characterSizebuffer);
	//	glCallList(pawn);
	//	glPopMatrix();
	//}

	glPushMatrix();
	glTranslatef(4000 + characterSizebuffer, 0, 0 + characterSizebuffer);
	glCallList(queen);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3000 + characterSizebuffer, 0, 0 + characterSizebuffer);
	glCallList(king);
	glPopMatrix();



	glPushMatrix();
	// Take other rook
	Interpolate(t, 5, 7, z, 0, 7000);
	glTranslatef(7000 + characterSizebuffer, 0, z + characterSizebuffer);
	glCallList(rook);
	glPopMatrix();

	glPushMatrix();
	Interpolate(t, 6.87, 8, z, 0, -10000);
	glTranslatef(0000 + characterSizebuffer, 0, z + characterSizebuffer);
	glCallList(rook);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(6000 + characterSizebuffer, 0, 0 + characterSizebuffer);
	glCallList(knight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1000 + characterSizebuffer, 0, 0 + characterSizebuffer);
	glCallList(knight);
	glPopMatrix();

		

	glPushMatrix();
	glTranslatef(5000 + characterSizebuffer, 0, 0 + characterSizebuffer);
	glCallList(bishop);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2000 + characterSizebuffer, 0, 0 + characterSizebuffer);
	glCallList(bishop);
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(4000, 0, 1000);	for(int x=1000; x<=8000; x+=1000)
	//{
	//	glPushMatrix();
	//	glTranslatef(x, 0, 7000);
	//	DrawPiece("PAWN.POL");
	//	glPopMatrix();
	//}

	//DrawPiece("KING.POL");
	//glPopMatrix();

	//double z;
	//Interpolate(t, 1.0, 3.0, z, 1000, 5000);
	//glPushMatrix();
	//glTranslatef(5000, 0, z);
	//DrawPiece("QUEEN.POL");
	//glPopMatrix();

	//glPushMatrix();
	//glTranslatef(6000, 0, 1000);
	//DrawPiece("BISHOP.POL");
	//glPopMatrix();

	/************************************************************************************************************************************

				BLACK'S BOARDS SPACE

	*************************************************************************************************************************************/

	// Set the color for one side (black), and draw its 16 pieces.
	GLfloat mat_amb_diff2[] = {0.1f, 0.1f, 0.1f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	
	//double x;
	//Interpolate(t, 4.0, 6.0, x, 4000, 2000);
	//glPushMatrix();
	//glTranslatef(x, 0, 8000);
	//DrawPiece("KING.POL");
	//glPopMatrix();

	//shift for size of piece as to not sure where they are measured from
	for(int x = 0 + characterSizebuffer; x<8000 + characterSizebuffer; x+=1000)
	{
		Interpolate(t, 1, 3, z, 6000, 4000 - (.5 * characterSizebuffer));
		Interpolate(t, 2, 3 , y, 0, 2000 );
		glPushMatrix();
		glTranslatef(x, y, z + characterSizebuffer );

		if ((x - characterSizebuffer) % 2000 == 0){
			Interpolate(t, 3, 3.5, angle, 0, -45);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}
		else {
			Interpolate(t, 3, 3.5, angle, 0, 45);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}
	
		if ((x - characterSizebuffer) % 2000 == 0) {
			Interpolate(t, 3.5, 4.5, angle, 0, 90);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}
		else {
			Interpolate(t, 3.5, 4.5, angle, 0, -90);
			glRotated(angle, 1, 0, 0);
			glTranslated(0, 0, 0);
		}

	//HIT ON BOTTOM AT t = 5.5
		//if ((x - characterSizebuffer) % 2000 == 0) {
		//	if (t > 5.5) {
		//		Interpolate(t, 5.5, 6.5, z, 4000 - (.5 * characterSizebuffer), 15000);
		//		glTranslated(0, y, z - 6000);

		//	}
		//}

			
		glCallList(pawn);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(4000 + characterSizebuffer, 0, 7000 + characterSizebuffer);
	glCallList(queen);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3000 + characterSizebuffer, 0, 7000 + characterSizebuffer);
	glCallList(king);
	glPopMatrix();


	glPushMatrix();
	//react to rook take
	Interpolate(t, 6.87, 10, z, 7000, 20000);
	glTranslatef(7000 + characterSizebuffer, 0, z + characterSizebuffer);
	glCallList(rook);
	glPopMatrix();

	glPushMatrix();
	//Take Rook
	Interpolate(t, 5, 7, z, 7000, 0);
	glTranslatef(0000 + characterSizebuffer, 0, z + characterSizebuffer);
	glCallList(rook);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(6000 + characterSizebuffer, 0, 7000 + characterSizebuffer);
	glRotated(180, 0, 1, 0);
	glCallList(knight);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1000 + characterSizebuffer, 0, 7000 + characterSizebuffer);
	glRotated(180, 0, 1, 0);
	glCallList(knight);
	glPopMatrix();

		

	glPushMatrix();
	glTranslatef(5000 + characterSizebuffer, 0, 7000 + characterSizebuffer);
	glCallList(bishop);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2000 + characterSizebuffer, 0, 7000 + characterSizebuffer);
	glCallList(bishop);
	glPopMatrix();



	/************************************************************************************************************************************

				 BOARD SPACE

	*************************************************************************************************************************************/

	//Draw the board
	int buffer = 1000;
	
	for (int x = 0; x < 8000; x += buffer) {
		for (int z = 0; z < 8000; z += buffer) {
			
			//DRAW CLOSE SIDE LIP x = 0
			if (x == 0) {
				DrawXZeroLip(x, z);
			}
		
			// DRAW FAR SIDE LIP X = 8000
			if (x == 7000) {
				DrawXMaxLip(x, z);
			}

			//DRAW TOP LIP
			if (z == 7000 ) {
				DrawZMaxLip(x, z);
			}
			
			//DRAW BOTTOM LIP	
			if (z == 0) {
				DrawZZeroLip(x, z);
			}
			
			DrawMainBoard(x, z);
		}
	}

	GLfloat light_position[] = {1,2,-.1f, 0}; // light comes FROM this vector direction.
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // position first light

	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;

		case 'b':
			current_view = ::bottom;
			break;
		
		case 't':
			current_view = ::top;
			break;

		case 'l':
			current_view = ::left;
			break;

		case 'f':
			current_view = ::centerFly;
			break;

		case 'r':
			current_view = ::right;
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}



void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble) w/(GLdouble) h;
	gluPerspective( 
	/* field of view in degree */ 45.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ 100, /* Z far */ 30000.0);
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	SetPerspectiveView(w,h);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	// set material's specular properties
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// set light properties
	GLfloat light_position[] = {(float)eye[0], (float)eye[1], (float)eye[2],1};
	GLfloat white_light[] = {1,1,1,1};
	GLfloat low_light[] = {.3f,.3f,.3f,1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // position first light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); // specify first light's color
	glLightfv(GL_LIGHT0, GL_SPECULAR, low_light);

	glEnable(GL_DEPTH_TEST); // turn on depth buffering
	glEnable(GL_LIGHTING);	// enable general lighting
	glEnable(GL_LIGHT0);	// enable the first light.
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(10, 10);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("Shapes");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glClearColor(1,1,1,1);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
