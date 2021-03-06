#include "Vertex.h"
#include "GL\glut.h"
#include "Find.h"
#include <math.h>
#include <iostream>

float Epsilon = 1e-8;

Vec3f Vertex::calVertexPoint()
{
	int n = vEdgeList.size();
	if (vEdgeList.size() != vFaceList.size())
		cout << "error!\t" << "Edge"<< vEdgeList.size() << "\tFace" << vFaceList.size() << endl;

	// 1.Consider face vertex
	Vec3f face_point(0);
	for (int i = 0; i < n; ++i)
		face_point += vFaceList[i]->fMidVertex;
	face_point /= float(n);

	// 2.Consider midpoints for (original) edges touching P
	Vec3f edge_point(0);
	for (int i = 0; i < n; ++i)
		edge_point += vEdgeList[i]->eMidVertex;
	edge_point /= float(n);

	// 3.Consider P
	Vec3f P = Pos;

	Vec3f vertex_point = (face_point + 2 * edge_point + float(n - 3)*P) / float(n);
	return vertex_point;
}

bool Vertex::operator ==(const Vertex &v)
{
	if (abs(Pos.x - v.Pos.x) < Epsilon&&
		abs(Pos.y - v.Pos.y) < Epsilon&&
		abs(Pos.z - v.Pos.z) < Epsilon)
		return true;
	return false;
}

Vec3f Edge::calEdgePoint()
{
	Vec3f edgePoint = (eFaceList[0]->fMidVertex +
		eFaceList[1]->fMidVertex +
		eMidVertex) / 3;
	return edgePoint;
}

bool Edge::operator==(const Edge &e)
{
	// Edge1.v1==Edge2.v1 && Edge1.v2==Edge2.v2
	bool v1v1 = (*eVertexList[0]) == (*e.eVertexList[0]);
	bool v2v2 = (*eVertexList[1]) == (*e.eVertexList[1]);

	// Edge1.v1==Edge2.v2 && Edge1.v2==Edge2.v1
	bool v1v2 = (*eVertexList[1]) == (*e.eVertexList[0]);
	bool v2v1 = (*eVertexList[0]) == (*e.eVertexList[1]);

	if ((v1v1 && v2v2) || (v1v2 && v2v1))
		return true;
	return false;
}

void Face::show()
{
	glNormal3f(normal.x,normal.y,normal.z);
	for (int i = 0; i < fVertexList.size(); ++i)
		glVertex3f(fVertexList[i]->Pos.x, fVertexList[i]->Pos.y, fVertexList[i]->Pos.z);
}

void Face::addVertex(Vertex *&v, deque<Vertex *> &vertexQueue)
{
	Vertex *pos = findVertex(*v, vertexQueue);
	if (pos != nullptr)//vertex exist		
		v = pos;			
	else	
		//vertex does not exist			
		vertexQueue.push_back(v);
	fVertexList.push_back(v);
	v->vFaceList.push_back(this);
}

void Face::addEdge(Vertex &v1, Vertex &v2, deque<Edge *> &edgeQueue)
{	
	// Edge(v1, v2,-1) represent it just a try
	Edge *pos = findEdge(Edge(v1, v2, -1), edgeQueue);
	Edge *e1 = nullptr;
	if (pos != nullptr)//edge exist	
		e1 = pos;	
	else
	{
		//edge does not exist	
		e1 = new Edge(v1, v2, level);
		edgeQueue.push_back(e1);
	}		
	fEdgeList.push_back(e1);
	e1->eFaceList.push_back(this);
}
