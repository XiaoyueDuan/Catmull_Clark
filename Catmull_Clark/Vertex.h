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
	int level=0;

	Vertex(Vec3f v,int l=0)
	{
		Pos = v;
		level = l;
	}

	Vertex(float x,float y, float z, int l = 0)
	{
		Pos.x = x;
		Pos.y = y;
		Pos.z = z;
		level = l;
	}

	Vec3f calVertexPoint();
	bool operator ==(const Vertex &v);
};

class Edge
{
public:
	Vec3f eMidVertex;
	vector<Vertex *> eVertexList;
	vector<Face *> eFaceList;
	int level = 0;

	Edge(Vertex &v1, Vertex &v2, int l = 0)
	{
		// add two vertex in vertex list
		eVertexList.push_back(&v1);
		eVertexList.push_back(&v2);

		if (l!= -1)
		{
			// add this edge to edge list of two vertexs
			v1.vEdgeList.push_back(this);
			v2.vEdgeList.push_back(this);
			level = l;
			eMidVertex = (v1.Pos + v2.Pos) / 2;
		}		
	}

	Vec3f calEdgePoint();
	bool operator==(const Edge &e);
};

class Face
{
private:
	void setNormal()
	{
		Vec3f edge1 = fVertexList[1]->Pos - fVertexList[0]->Pos;
		Vec3f edge2 = fVertexList[2]->Pos - fVertexList[0]->Pos;
		normal= edge1.crossProduct(edge2);
		normal.normalize();
	}
public:
	vector<Vertex *> fVertexList;
	vector<Edge *> fEdgeList;
	Vec3f normal;
	Vec3f fMidVertex;
	
	// Only Triangle mesh or quad mesh are accepted.
	//bool tri = false;
	bool quad = false;

	// Indicate the subdivision level, 0 represents no subdivision occurs
	int level = 0;

	void addEdge(Vertex &v1, Vertex &v2, deque<Edge *> &edgeQueue);
	void addVertex(Vertex *&v, deque<Vertex *> &vertexQueue);

	Face(Vertex *&v1, Vertex *&v2, Vertex *&v3, Vertex *&v4, deque<Vertex *> &vertexQueue, deque<Edge *> &edgeQueue, int l = 0)
	{		
		fMidVertex = ((*v1).Pos + (*v2).Pos + (*v3).Pos + (*v4).Pos) / 4;
		level = l;

		addVertex(v1, vertexQueue);
		addVertex(v2, vertexQueue);
		addVertex(v3, vertexQueue);
		addVertex(v4, vertexQueue);

		addEdge(*v1, *v2, edgeQueue);
		addEdge(*v2, *v3, edgeQueue);
		addEdge(*v3, *v4, edgeQueue);
		addEdge(*v4, *v1, edgeQueue);
		
		setNormal();
	}

	void show();
};
