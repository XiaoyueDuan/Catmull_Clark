//#include "GL\glut.h"
//#include <stdio.h >
//#include <math.h>
//
//static GLfloat xRot = 0.0f;
//static GLfloat yRot = 0.0f;
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	GLfloat cube_mat_ambient[] = { 0.0, 1.0, 1.0, 1.0f };
//	GLfloat cube_mat_diffuse[] = { 0.0, 1.0, 1.0, 1.0f };
//	GLfloat cube_mat_specular[] = { 0.0, 1.0, 1.0, 1.0f };
//	//GLfloat cylinder_mat_emission[] = { 0.3, 0.3, 0.3, 1.0f };
//	//GLfloat cylinder_mat_shininess = 50.0f;
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT, cube_mat_ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_mat_specular);
//	//glMaterialfv(GL_FRONT, GL_EMISSION, cylinder_mat_emission);
//	//glMaterialf(GL_FRONT, GL_SHININESS, cylinder_mat_shininess);
//
//	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
//	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
//	glutSolidCube(1.0);
//
//	glutSwapBuffers();
//}
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
//	//glMatrixMode(GL_MODELVIEW);
//	//glLoadIdentity();
//	//glTranslatef(0.0, 0.0, -10.0);
//	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
//}
//
//void init()
//{
//	GLfloat source_position[] = { 1.0f, 2.0f, 3.0f, 1.0f };
//	GLfloat source_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	GLfloat source_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	GLfloat source_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glEnable(GL_DEPTH_TEST);
//	glShadeModel(GL_FLAT);
//
//	glLightfv(GL_LIGHT0, GL_POSITION, source_position);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, source_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, source_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, source_specular);
//
//	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
//	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
//	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//}
//
//void SpecialKeys(int key, int x, int y)
//{
//	if (key == GLUT_KEY_UP)
//		xRot -= 5.0f;
//
//	if (key == GLUT_KEY_DOWN)
//		xRot += 5.0f;
//
//	if (key == GLUT_KEY_LEFT)
//		yRot -= 5.0f;
//
//	if (key == GLUT_KEY_RIGHT)
//		yRot += 5.0f;
//
//	if (key > 356.0f)
//		xRot = 0.0f;
//
//	if (key < -1.0f)
//		xRot = 355.0f;
//
//	if (key > 356.0f)
//		yRot = 0.0f;
//
//	if (key < -1.0f)
//		yRot = 355.0f;
//
//	glutPostRedisplay();
//}
//
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(500, 500);
//	glutInitWindowPosition(100, 100);
//	glutCreateWindow("LookAt");
//	init();
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	//glutKeyboardFunc(keyboard);
//	glutSpecialFunc(SpecialKeys);
//	glutMainLoop();
//	return 0;
//}