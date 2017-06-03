#pragma once
#include <vector>
#include <deque>
#include "Geometry.h"

using namespace std;

class Face;
class Edge;

class Vertex
{
public:
	Vec3f Pos;
	vector<Edge *> vEdgeList;
	vector<Face *> vFaceList;

	Vertex(float x,float y, float z)
	{
		Pos.x = x;
		Pos.y = y;
		Pos.z = z;
	}

	Vec3f calVertexPoint()
	{		
		int n = vEdgeList.size();

		// 1.Consider face vertex
		Vec3f face_point(0);
		for (int i = 0; i < n; ++i)
			face_point += vFaceList[i]->fMidVertex;
		face_point /= n;

		// 2.Consider midpoints for (original) edges touching P
		Vec3f edge_point(0);
		for (int i = 0; i < n; ++i)
			edge_point += vEdgeList[i]->eMidVertex;
		edge_point /= n;

		// 3.Consider P
		Vec3f P=Pos;

		Vec3f vertex_point= (face_point+ 2*edge_point+(n-3)*P)/n;
		return vertex_point;
	}
};

class Edge
{
public:
	Vec3f eMidVertex;
	vector<Vertex *> eVertexList;
	vector<Face *> eFaceList;

	Edge(Vertex &v1, Vertex &v2)
	{
		// add two vertex in vertex list
		eVertexList.push_back(&v1);
		eVertexList.push_back(&v2);

		// add this edge to edge list of two vertexs
		v1.vEdgeList.push_back(this);
		v2.vEdgeList.push_back(this);

		eMidVertex = (v1.Pos + v2.Pos) / 2;
	}

	Vec3f calEdgePoint()
	{		
		Vec3f edgePoint = (eFaceList[0]->fMidVertex + 
						   eFaceList[1]->fMidVertex+
						   eMidVertex * 2) / 4;
		return edgePoint;
	}
};

class Face
{
private:
	void setNormal()
	{
		normal=fVertexList[0]->Pos.crossProduct(fVertexList[1]->Pos);
	}
public:
	vector<Vertex *> fVertexList;
	vector<Edge *> fEdgeList;
	Vec3f normal;
	Vec3f fMidVertex;
	
	bool tri = false;
	bool quad = false;

	Face(Vertex &v1, Vertex &v2, Vertex &v3)
	{
		// Vertex
		v1.vFaceList.push_back(this);
		v2.vFaceList.push_back(this);
		v3.vFaceList.push_back(this);

		// Face
		tri = true;
		fVertexList.push_back(&v1);
		fVertexList.push_back(&v2);
		fVertexList.push_back(&v3);

		Edge *e1 = new Edge(v1, v2);
		Edge *e2 = new Edge(v2, v3);
		Edge *e3 = new Edge(v3, v1);

		fEdgeList.push_back(e1);
		fEdgeList.push_back(e2);
		fEdgeList.push_back(e3);

		// Edge
		e1->eFaceList.push_back(this);
		e2->eFaceList.push_back(this);
		e3->eFaceList.push_back(this);

		setNormal();
		fMidVertex = (v1.Pos + v2.Pos + v3.Pos ) / 3;
	}

	Face(Vertex &v1, Vertex &v2, Vertex &v3, Vertex &v4)
	{
		// Vertex
		v1.vFaceList.push_back(this);
		v2.vFaceList.push_back(this);
		v3.vFaceList.push_back(this);
		v4.vFaceList.push_back(this);

		// Face
		quad = true;
		fVertexList.push_back(&v1);
		fVertexList.push_back(&v2);
		fVertexList.push_back(&v3);
		fVertexList.push_back(&v4);

		Edge *e1 = new Edge(v1, v2);
		Edge *e2 = new Edge(v2, v3);
		Edge *e3 = new Edge(v3, v4);
		Edge *e4 = new Edge(v4, v1);

		fEdgeList.push_back(e1);
		fEdgeList.push_back(e2);
		fEdgeList.push_back(e3);
		fEdgeList.push_back(e4);

		// Edge
		e1->eFaceList.push_back(this);
		e2->eFaceList.push_back(this);
		e3->eFaceList.push_back(this);
		e4->eFaceList.push_back(this);
				
		setNormal();
		fMidVertex = (v1.Pos + v2.Pos + v3.Pos + v4.Pos) / 4;
	}

	void subdivision(deque<Face *> &faceQueue)
	{
		// 1. Calculate face point
		Vec3f face_point = fMidVertex;

		// 2. Calculate edge point
		Vec3f edge_point1 = fEdgeList[0]->calEdgePoint();
		Vec3f edge_point2 = fEdgeList[1]->calEdgePoint();
		Vec3f edge_point3 = fEdgeList[2]->calEdgePoint();
		Vec3f edge_point4 = fEdgeList[3]->calEdgePoint();

		// 3. Calculate vertex point
		Vec3f vertex_point1 = fVertexList[0]->calVertexPoint();
		Vec3f vertex_point2 = fVertexList[1]->calVertexPoint();
		Vec3f vertex_point3 = fVertexList[2]->calVertexPoint();
		Vec3f vertex_point4 = fVertexList[3]->calVertexPoint();

		Face *f = new Face(fMidVertex, edge_point1, vertex_point1, edge_point2);
		faceQueue.push_back(new Face(fMidVertex, edge_point1, vertex_point1, edge_point2));
	}
};
