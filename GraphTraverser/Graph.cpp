#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <iostream>
#include "InsertionSort.h"
#include <set>

#define DFS_FIRST_PATH
using namespace std;
Graph::Graph()
{
	m_pVHead = nullptr;
	m_vSize = 0;
	adj = nullptr;
}
Graph::Graph(int vsize)
{
	m_vSize = vsize;
	Vertex ** root = &m_pVHead;
	for (int i = 0; i < m_vSize; i++) {
		input<Vertex>(root, i, 0);
	}
	adj = new list< pair<int, int> >[m_vSize];
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
	while (t) {
		if (t->GetKey() == startVertexKey) break;
		t = t->GetNext();
	}
	if (t) {
		t->AddEdge(endVertexKey, weight);
	}
	adj[endVertexKey].push_back(make_pair(startVertexKey, weight));
	adj[startVertexKey].push_back(make_pair(endVertexKey, weight));
}

Vertex * Graph::FindVertex(int key)
{
	Vertex * t = m_pVHead;
	while (t) {
		if (t->GetKey() == key) return t;
		t = t->GetNext();
	}
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

void Graph::Print(std::ofstream & fout)
{
	int size = m_vSize;
	int ** data;
	data = new int*[size];
	for (int i = 0; i < size; i++) {
		data[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			data[i][j] = 0;
		}
	}

	Vertex * v = m_pVHead;
	Edge * e;
	for (v = m_pVHead; v != nullptr; v=v->GetNext()) {
		for (e = v->GetHeadOfEdge(); e != nullptr; e = e->GetNext()) {
			data[v->GetKey()][e->GetKey()] = e->GetWeight();
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << data[i][j] << " ";
		}
		cout << endl;
	}
}

bool Graph::IsNegativeEdge()
{
	Vertex * v;
	Edge * e;

	for (v = m_pVHead; v != nullptr; v = v->GetNext()) {
		for (e = v->GetHeadOfEdge(); e != nullptr; e = e->GetNext()) {
			if (e->GetWeight() < 0) return true;
		}
	}
	return false;
}

std::vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey)
{
	return std::vector<int>();
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	if (m_pVHead = nullptr) throw 101; // Graph not Exist
	if (!FindVertex(startVertexKey) || !FindVertex(endVertexKey)) throw 100;	// Invalidate Vertex Keys
	// Create a set to store vertices that are being
	// prerocessed
	set< pair<int, int> > setds;

	// Create a vector for distances and initialize all
	// distances as infinite (infinite)
	vector<int> dist(m_vSize, 0);

	// Insert source itself in Set and initialize its
	// distance as 0.
	setds.insert(make_pair(0, startVertexKey));
	dist[startVertexKey] = 0;

	/* Looping till all shortest distance are finalized
	then setds will become empty */
	while (!setds.empty())
	{
		// The first vertex in Set is the minimum distance
		// vertex, extract it from set.
		pair<int, int> tmp = *(setds.begin());
		setds.erase(setds.begin());

		// vertex label is stored in second of pair (it
		// has to be done this way to keep the vertices
		// sorted distance (distance must be first item
		// in pair)
		int u = tmp.second;

		// 'i' is used to get all adjacent vertices of a vertex
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent
			// of u.
			int v = (*i).first;
			int weight = (*i).second;

			//  If there is shorter path to v through u.
			if (dist[v] > dist[u] + weight)
			{
				/*  If distance of v is not I then it must be in
				our set, so removing it and inserting again
				with updated less distance.
				Note : We extract only those vertices from Set
				for which distance is finalized. So for them,
				we would never reach here.  */
				if (dist[v] != 0)
					setds.erase(setds.find(make_pair(dist[v], v)));

				// Updating distance of v
				dist[v] = dist[u] + weight;
				setds.insert(make_pair(dist[v], v));
			}
		}
	}
	return dist;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
	return std::vector<int>();
}

std::vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	return std::vector<int>();
}

bool Graph::isEmpty()
{
	if (m_pVHead) return false;
	return true;
}

void Graph::_initAdj(int size)
{
	adj = new list< pair<int, int> >[size];
}
