// https://stackoverflow.com/questions/23882112/how-to-add-the-static-libraries-to-the-project-in-visual-studio

#include <string> 
#include "GL\glut.h"
#include "Vertex.h"
#include <math.h>

int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;
int angleX = 0, angleY=0;
float Ortho = 5;
deque<Face *> faceQueue;
deque<Edge *> edgeQueue;
deque<Vertex *> vertexQueue;

void reshape(int w, int h)
{
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	float scale = float(w) / float(h);

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	
	glLoadIdentity();	
	gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat cube_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0f };
	GLfloat cube_mat_diffuse[] = { 0.0, 0.3, 0.3, 1.0f };
	GLfloat cube_mat_specular[] = { 0.3, 0.3, 0.3, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, cube_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_mat_specular);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();	
	{
		glRotatef(angleX, 1.0f, 0.0f, 0.0f);
		glRotatef(angleY, 0.0f, 1.0f, 0.0f);		

		glBegin(GL_QUADS);        // Draw The Cube Using quads
		for (int i = 0; i < faceQueue.size(); ++i)
			faceQueue[i]->show();
	}
	glPopMatrix();
	
	glEnd();            // End Drawing The Cube
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e'://up
		angleX = -5;
		angleY = 0;
		glutPostRedisplay();
		break;
	case 'd'://down
		angleX = 5;
		angleY = 0;
		glutPostRedisplay();
		break;
	case 's'://left
		angleX = 0;
		angleY = -5;
		glutPostRedisplay();
		break;
	case 'f'://right
		angleX = 0;
		angleY = 5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void initLight()
{
	// Initialize
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_LIGHT0);
	// Add light
	GLfloat source_position[] = { 3.0f, 3.0f, 3.0f, 1.0f };
	GLfloat source_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat source_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat source_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, source_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, source_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, source_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, source_specular);
	glEnable(GL_LIGHTING);
}

void initGeo()
{
	// 8 Vertexs
	Vertex *v0 = new Vertex(1.0f, 1.0f, -1.0f);	//top
	Vertex *v1 = new Vertex(-1.0f, 1.0f, -1.0f);
	Vertex *v2 = new Vertex(-1.0f, 1.0f, 1.0f);
	Vertex *v3 = new Vertex(1.0f, 1.0f, 1.0f);

	Vertex *v4 = new Vertex(1.0f, -1.0f, -1.0f);	//bottom
	Vertex *v5 = new Vertex(-1.0f, -1.0f,-1.0f);
	Vertex *v6 = new Vertex(-1.0f, -1.0f, 1.0f);
	Vertex *v7 = new Vertex(1.0f, -1.0f, 1.0f);
	
	// 6 faces
	Face *f0=new Face(v0, v1, v2, v3, vertexQueue, edgeQueue);//top
	Face *f1=new Face(v7, v6, v5, v4, vertexQueue, edgeQueue);//bottom
	Face *f2=new Face(v1, v5, v6, v2, vertexQueue, edgeQueue);//left
	Face *f3=new Face(v0, v3, v7, v4, vertexQueue, edgeQueue);//right
	Face *f4=new Face(v2, v6, v7, v3, vertexQueue, edgeQueue);//front
	Face *f5=new Face(v0, v4, v5, v1, vertexQueue, edgeQueue);//back

	faceQueue.push_back(f0);
	faceQueue.push_back(f1);
	faceQueue.push_back(f2);
	faceQueue.push_back(f3);
	faceQueue.push_back(f4);
	faceQueue.push_back(f5);
}

bool subdivision(deque<Face *> &faceQueue, 
				 deque<Edge *> &edgeQueue,
				 deque<Vertex *> &vertexQueue, 
				 int l)
{
	l = (l<=3)?l:3;
	Face *f = faceQueue.front();
	int currentLevel = f->level;
	while (f->level < l)
	{
		//  (a, edge_pointab, face_pointabcd, edge_pointda)
		//	(b, edge_pointbc, face_pointabcd, edge_pointab)
		//	(c, edge_pointcd, face_pointabcd, edge_pointbc)
		//	(d, edge_pointda, face_pointabcd, edge_pointcd)
		Vertex *face_pointabcd = new Vertex(f->fMidVertex, f->level + 1);

		// 2. Calculate edge point
		Vertex *edge_pointab = new Vertex(f->fEdgeList[0]->calEdgePoint(), f->level + 1);
		Vertex *edge_pointbc = new Vertex(f->fEdgeList[1]->calEdgePoint(), f->level + 1);
		Vertex *edge_pointcd = new Vertex(f->fEdgeList[2]->calEdgePoint(), f->level + 1);
		Vertex *edge_pointda = new Vertex(f->fEdgeList[3]->calEdgePoint(), f->level + 1);

		// 3. Calculate vertex point
		Vertex *a = new Vertex(f->fVertexList[0]->calVertexPoint(), f->level + 1);
		Vertex *b = new Vertex(f->fVertexList[1]->calVertexPoint(), f->level + 1);
		Vertex *c = new Vertex(f->fVertexList[2]->calVertexPoint(), f->level + 1);
		Vertex *d = new Vertex(f->fVertexList[3]->calVertexPoint(), f->level + 1);

		faceQueue.push_back(new Face(a, edge_pointab, face_pointabcd, edge_pointda, vertexQueue, edgeQueue, f->level + 1));
		faceQueue.push_back(new Face(b, edge_pointbc, face_pointabcd, edge_pointab, vertexQueue, edgeQueue, f->level + 1));
		faceQueue.push_back(new Face(c, edge_pointcd, face_pointabcd, edge_pointbc, vertexQueue, edgeQueue, f->level + 1));
		faceQueue.push_back(new Face(d, edge_pointda, face_pointabcd, edge_pointcd, vertexQueue, edgeQueue, f->level + 1));

		faceQueue.pop_front();
		// Get the next face to be subdivided
		f = faceQueue.front();
		// If the level 
		if (f->level > currentLevel)
		{
			while (vertexQueue.front()->level == currentLevel)
				vertexQueue.pop_front();
			while (edgeQueue.front()->level == currentLevel)
				edgeQueue.pop_front();

			currentLevel = f->level;
		}
	}
	return true;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Catmull_Clark");

	initLight();
	initGeo();
	subdivision(faceQueue,edgeQueue,vertexQueue, 0);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	system("PAUSE ");
	return 0;
}