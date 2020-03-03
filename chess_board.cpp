#include "glut.h"
#include "graphics.h"
#include "chess_board.h"

int buffer = 1000;

void DrawMainBoard(int x, int z) {
	// DRAW RED SQUARES
	if (x % 2000 == 0 && z % 2000 != 0 || x % 2000 != 0 && z % 2000 == 0) {
		GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x, 0, z, x, 0, z + buffer, x + buffer, 0, z + buffer, x + buffer, 0, z);
		}
	// DRAW GRAY SQUARES
	else {
		GLfloat mat_amb_diff2[] = {1.0f, 1.0f, 1.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x, 0, z, x, 0, z + buffer, x + buffer, 0, z + buffer, x + buffer, 0, z);

	}
	//Draw black border around all positions	
	GLfloat mat_amb_diff2[] = {0.0f, 0.0f, 0.0f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	
	DrawQuadOutline(x, 1.1, z, x, 1.1, z + buffer, x + buffer, 1.1, z + buffer, x + buffer, 1.1, z);

}

void DrawXZeroLip(int x, int z) {
	//DRAW RED LIP
	if (x % 2000 == 0 && z % 2000 != 0 || x % 2000 != 0 && z % 2000 == 0) {
		GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x, 0, z, x, 0, z + buffer, x, (-1 * buffer), z + buffer, x, (-1 * buffer), z);
		}
	//else if (x % 2000 != 0 && z % 2000 == 0) {
	//	GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
	//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	//	DrawQuad(x, 0, z, x, 0, z + buffer, x, (-1 * buffer), z + buffer, x, (-1 * buffer), z);
	//}
	//DRAW GRAY LIP
	else {
		GLfloat mat_amb_diff2[] = {1.0f, 1.0f, 1.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x, 0, z, x, 0, z + buffer, x, (-1 * buffer), z + buffer, x, (-1 * buffer), z);

	}

	GLfloat mat_amb_diff2[] = {0.0f, 0.0f, 0.0f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	DrawQuadOutline(x, 0, z, x, 0, z + buffer, x, (-1 * buffer), z + buffer, x, (-1 * buffer), z);


}

void DrawXMaxLip(int x, int z) {
	//DRAW RED LIP
	if (x % 2000 == 0 && z % 2000 != 0 || x % 2000 != 0 && z % 2000 == 0) {
		GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x + buffer, 0, z, x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer, (-1 * buffer), z);
		}
	//else if (x % 2000 != 0 && z % 2000 == 0) {
	//	GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
	//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	//	DrawQuad(x + buffer, 0, z, x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer, (-1 * buffer), z);
	//}
	//DRAW GRAY LIP
	else {
		GLfloat mat_amb_diff2[] = {1.0f, 1.0f, 1.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x + buffer, 0, z, x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer, (-1 * buffer), z);

	}

	GLfloat mat_amb_diff2[] = {0.0f, 0.0f, 0.0f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	DrawQuadOutline(x + buffer, 0, z, x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer, (-1 * buffer), z);

}

void DrawZZeroLip(int x, int z) {
	//DRAW RED LIP
	if (x % 2000 == 0 && z % 2000 != 0 || x % 2000 != 0 && z % 2000 == 0) {
		GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x + buffer, 0, z, x + buffer, (-1 * buffer), z, x + buffer + (-1 * buffer), (-1 * buffer), z, x +  buffer + (- 1 * buffer), 0, z);
		}
	//else if (x % 2000 != 0 && z % 2000 == 0) {
	//	GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
	//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	//	DrawQuad(x + buffer, 0, z, x + buffer, (-1 * buffer), z, x + buffer + (-1 * buffer), (-1 * buffer), z, x +  buffer + (- 1 * buffer), 0, z);
	//}
	//DRAW GRAY LIP
	else {
		GLfloat mat_amb_diff2[] = {1.0f, 1.0f, 1.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x + buffer, 0, z, x + buffer, (-1 * buffer), z, x + buffer + (-1 * buffer), (-1 * buffer), z, x +  buffer + (- 1 * buffer), 0, z);

	}
	
	GLfloat mat_amb_diff2[] = {0.0f, 0.0f, 0.0f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	DrawQuadOutline(x + buffer, 0, z, x + buffer, (-1 * buffer), z, x + buffer + (-1 * buffer), (-1 * buffer), z, x +  buffer + (- 1 * buffer), 0, z);

}

void DrawZMaxLip(int x, int z) {
	//DRAW RED LIP
	if (x % 2000 == 0 && z % 2000 != 0 || x % 2000 != 0 && z % 2000 == 0) {
		GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer + (-1 * buffer), (-1 * buffer), z + buffer, x +  buffer + (- 1 * buffer), 0, z + buffer);
		}
	//else if (x % 2000 != 0 && z % 2000 == 0) {
	//	GLfloat mat_amb_diff2[] = {1.0f, 0.0f, 0.0f, 1.0};
	//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	//	DrawQuad(x + buffer, 0, z, x + buffer, (-1 * buffer), z, x + buffer + (-1 * buffer), (-1 * buffer), z, x +  buffer + (- 1 * buffer), 0, z);
	//}
	//DRAW GRAY LIP
	else {
		GLfloat mat_amb_diff2[] = {1.0f, 1.0f, 1.0f, 1.0};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
		DrawQuad(x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer + (-1 * buffer), (-1 * buffer), z + buffer, x +  buffer + (- 1 * buffer), 0, z + buffer);

	}
	
	GLfloat mat_amb_diff2[] = {0.0f, 0.0f, 0.0f, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff2);
	DrawQuadOutline(x + buffer, 0, z + buffer, x + buffer, (-1 * buffer), z + buffer, x + buffer + (-1 * buffer), (-1 * buffer), z + buffer, x +  buffer + (- 1 * buffer), 0, z + buffer);

}
