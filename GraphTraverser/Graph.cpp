#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <iostream>
#include "InsertionSort.h"
#include <set>
#include <cstdio>
#include <queue>
#include <functional>
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
	m_pVHead->SeeAllVertex();
	cout << endl;
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
		cout << t->GetKey() << " 의 인접 리스트 : ";
		(t->GetHeadOfEdge())->SeeAllEdges();
		cout << endl;
	}
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
	data = makeMatrix();
	if (!data) throw 202;
	fout << "====== PRINT ======" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fout << data[i][j] << " ";
		}
		fout << endl;
	}
	fout << "===================" << endl;
	for (int i = 0; i < size; i++) {
		delete data[i];
	}
	delete data;
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
bool Graph::isConnected(int x, int y) {
	int ** data = makeMatrix();
	return (data[x][y] != 0);
}
int ** Graph::makeMatrix()
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
	for (v = m_pVHead; v != nullptr; v = v->GetNext()) {
		for (e = v->GetHeadOfEdge(); e != nullptr; e = e->GetNext()) {
			data[v->GetKey()][e->GetKey()] = e->GetWeight();
		}
	}
	return data;
}

vector<int> Graph::findWay(int startVertexKey, int endVertexKey, int dist)
{
	Stack<Vertex*> s;
	int i = 0;
	Vertex * v = FindVertex(startVertexKey);
	Vertex * prev = v;
	Edge * t = nullptr;
	bool *visited = new bool[m_vSize];
	int weight = 0;
	std::vector<int> result;

	for (i = 0; i < m_vSize; i++)
		visited[i] = false;

	s.Push(v);
	visited[v->GetKey()] = true;
	while (!s.IsEmpty()) {
		Vertex * vt = s.Top();
		if (vt != prev) {
			t = prev->FindEdge(vt->GetKey());
			weight += t->GetWeight();
		}
		if (weight > dist) {
			weight -= t->GetWeight();
			s.Pop();
		}
		else {
			prev = vt;
			result.push_back(vt->GetKey());
			if (vt->GetKey() == endVertexKey) break;

			t = vt->GetHeadOfEdge();
			while (t) {
				vt = FindVertex(t->GetKey());
				t = t->GetNext();
				s.Push(vt);
			}
		}
	}
	result.push_back(weight);
	return result;
}



std::vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey)
{
	if (m_pVHead == nullptr) throw 202;
	if (0 > startVertexKey || 0 > endVertexKey) throw 201;
	if (!FindVertex(startVertexKey) || !FindVertex(endVertexKey)) throw 200;	// Invalidate Vertex Keys
	Stack<Vertex*> s;
	int i = 0;
	Vertex * v = FindVertex(startVertexKey);
	Vertex * prev = v;
	Edge * t;
	bool *visited = new bool[m_vSize];
	int weight = 0;
	std::vector<int> result;

	for (i = 0; i < m_vSize; i++)
		visited[i] = false;

	s.Push(v);
	visited[v->GetKey()] = true;
	while (!s.IsEmpty()) {
		Vertex * vt = s.Top();
		if (vt != prev) {
			t = prev->FindEdge(vt->GetKey());
			weight += t->GetWeight();
		}
		prev = vt;
		result.push_back(vt->GetKey());
		if (vt->GetKey() == endVertexKey) break;
		t = vt->GetHeadOfEdge();


		while (t) {
			vt = FindVertex(t->GetKey());
			t = t->GetNext();
			s.Push(vt);
		}
	}
	result.push_back(weight);
	return result;
}

void watchDist(vector<int> dist) {
	std::vector<int>::iterator it;            
	for (it = dist.begin(); it != dist.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
}
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
	cout << "Start : " << startVertexKey << endl;
	cout << "Dest : " << endVertexKey << endl;
	if (m_pVHead == nullptr) throw 202; // Graph not Exist
	if (0 > startVertexKey || 0 > endVertexKey) throw 201;
	if (!FindVertex(startVertexKey) || !FindVertex(endVertexKey)) throw 200;	// Invalidate Vertex Keys

	set< pair<int, int> > setds;
	Stack<Vertex*> s;
	// Create a vector for distances and initialize all
	vector<int> dist(m_vSize, 999);
	vector<int> result;
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

		int u = tmp.second;
		cout << u << " ";
		if (u == endVertexKey) break;
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
				if (dist[v] != 999)
					setds.erase(setds.find(make_pair(dist[v], v)));

				// Updating distance of v
				dist[v] = dist[u] + weight;
				setds.insert(make_pair(dist[v], v));
			}
		}
	}
	cout << endl;
	result = findWay(startVertexKey, endVertexKey, dist[endVertexKey]);
	return result;
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
