//#include "GL\glut.h"
//
//float playerX = 0.0f;
//float playerY = 0.0f;
//float playerZ = 15.0f;
//
///*
//* Initialise the data used
//* for creating our light.
//*/
//
//float ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
//float diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
//float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//float position[4] = { -5.0f, 0.0f, 0.0f, 1.0f };
//
//float spotDirection[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
//float spotArc = 45.0f;
//float spotCoefficient = 0.0f; // Ranges from 0 to 128.
//
//void positionLight() {
//	/*
//	* Tell OpenGL where we want our light
//	* placed and since we're creating a spotlight,
//	* we need to set the direction from which
//	* light emanates.
//	*/
//	glLightfv(GL_LIGHT0, GL_POSITION, position);
//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
//}
//
//void display() {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glLoadIdentity();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	gluLookAt(playerX, playerY, playerZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
//
//	/*
//	* Tell OpenGL we want all the following
//	* objects in our scene to have lighting
//	* applied to them.
//	*/
//	glEnable(GL_LIGHTING);
//
//	/*
//	* Position the lights AFTER the model View matrix
//	* has been set up.
//	*/
//	positionLight();
//	glutSolidSphere(1.0f, 50, 50);
//	glPushMatrix();
//	glTranslatef(-7.0f, 5.0f, 0.0f);
//	glutSolidSphere(1.0f, 50, 50);
//	glPopMatrix();
//
//	/*
//	* We don't need the lighting anymore
//	* so disable it.
//	*/
//	glDisable(GL_LIGHTING);
//	glPushMatrix();
//	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
//
//	/*
//	* create a small red cube where the light
//	* is.
//	*/
//	glTranslatef(position[0], position[1], position[2]);
//	glutSolidCube(0.2f);
//	glPopMatrix();
//	glutSwapBuffers();
//}
//
//void reshape(int x, int y) {
//	glMatrixMode(GL_PROJECTION);
//	glViewport(0, 0, x, y);
//	glLoadIdentity();
//	gluPerspective(60.0, (GLdouble)x / (GLdouble)y, 1.0, 100.0);
//	glMatrixMode(GL_MODELVIEW);
//}
//
//void initLighting() {
//	/*
//	* Tell OpenGL we want to use
//	* the first light, GL_LIGHT0.
//	*/
//	glEnable(GL_LIGHT0);
//
//	/*
//	* Set the ambient, diffuse and specular
//	* colour properties for LIGHT0.
//	*/
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//
//	/*
//	* We're going to make GL_LIGHT0 a spotlight.
//	* Set the angle of the cone of light and
//	* how uniform the dispersion of light is.
//	*/
//	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotArc);
//	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotCoefficient);
//
//}
//
//int main(int argc, char **argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("Adding Lighting");
//
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//
//	glEnable(GL_DEPTH_TEST);
//
//	/*
//	* setup the lighting once
//	* in our program.
//	*/
//	initLighting();
//	glutMainLoop();
//
//	return 0;
//}