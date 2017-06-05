#pragma once
#include "Vertex.h"

Edge* findEdge(Edge &e, deque<Edge *> &edgeQueue)
{
	for (int i = 0; i < edgeQueue.size(); ++i)
		if (e == (*edgeQueue[i]))
			return edgeQueue[i];
	return nullptr;
}

Vertex* findVertex(Vertex &v, deque<Vertex *> &vertexQueue)
{
	for (int i = 0; i < vertexQueue.size(); ++i)
		if (v == (*vertexQueue[i]))
			return vertexQueue[i];

	return nullptr;
}