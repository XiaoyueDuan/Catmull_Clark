// https://stackoverflow.com/questions/23882112/how-to-add-the-static-libraries-to-the-project-in-visual-studio

#include <string> 
#include "GL\glut.h"

int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;


void reshape(int w, int h)
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	float scale = float(w) / float(h);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(-Ortho*scale, Ortho*scale, -Ortho, Ortho);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	//// Initialize
	//glClear(GL_COLOR_BUFFER_BIT);
	//cpTable.clear();
	//ceTable.clear();

	//geoTrasProcessor proc;
	//proc.getScreenPos(orig_vertices, scrn_vertices);
	//proc.trans2classifiedPolygon(scrn_vertices, polygons, cpTable, ceTable);

	//scanlineProccer scanproc;
	//scanproc.scanlineZbuffer(cpTable, ceTable, SCREEN_WIDTH);

	//cout << "Finish a frame!" << endl;
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Z-buffer");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

	system("PAUSE ");
	return 0;
}