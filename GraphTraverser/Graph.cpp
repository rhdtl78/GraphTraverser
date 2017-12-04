#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include "InsertionSort.h"
#include <set>

#define DFS_FIRST_PATH

Graph::Graph()
{
	m_pVHead = nullptr;
	m_vSize = 0;
}
Graph::~Graph()
{
	delete m_pVHead;
}

void Graph::AddVertex(int vertexKey)
{
	Vertex ** root = &m_pVHead;
	input<Vertex>(root, vertexKey, 0);
	m_vSize++;
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)
{
	Vertex * t = m_pVHead;
	Edge * e;
	while (t) {
		if (t->GetKey() == startVertexKey) break;
		t = t->GetNext();
	}
	if (t) {
		t->AddEdge(endVertexKey, weight);
	}
	else {
		input<Vertex>(&m_pVHead, startVertexKey, weight);
		m_vSize++;
		m_pVHead->AddEdge(endVertexKey, weight);
	}
}

Vertex * Graph::FindVertex(int key)
{
	Vertex * t;
	return nullptr;
}

int Graph::Size() const
{
	return m_vSize;
}

void Graph::Clear()
{
	Vertex * t = m_pVHead;
	while (t) {
		m_pVHead = m_pVHead->GetNext();
		delete t;
		t = m_pVHead;
	}
}
