#include "glut.h"

void text_output(double x, double y, char *string);
void DrawCircle(double x1, double y1, double radius);
void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawQuad(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4);
void DrawLine(double x1, double y1, double x2, double y2);


// "Prototypes" of some color variables defined in graphics.cpp
extern GLdouble redMaterial[];
extern GLdouble greenMaterial[];
extern GLdouble brightGreenMaterial[];
extern GLdouble blueMaterial[];
extern GLdouble whiteMaterial[];
