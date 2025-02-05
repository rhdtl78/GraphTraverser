#include "Vertex.h"
#include "InsertionSort.h"
#include <iostream>
Vertex::Vertex():m_key(0),m_size(0),m_pEHead(nullptr),m_pNext(nullptr)
{
}

Vertex::Vertex(int key):Vertex()
{
	m_key = key;
}

Vertex::Vertex(int key, int weight):Vertex(key)
{
}

Vertex::~Vertex()
{
	Clear();
}

void Vertex::SetNext(Vertex * pNext)
{
	m_pNext = pNext;
}

int Vertex::GetKey() const
{
	return m_key;
}

Vertex * Vertex::GetNext() const
{
	return m_pNext;
}

int Vertex::Size() const
{
	return m_size;
}

void Vertex::AddEdge(int edgeKey, int weight)
{
	input(&m_pEHead, edgeKey, weight);
	m_size++;
}

Edge * Vertex::GetHeadOfEdge() const
{
	return m_pEHead;
}

void Vertex::Clear()
{
	Edge * e;
	while (m_pEHead) {
		e = m_pEHead;
		m_pEHead = m_pEHead->GetNext();
		delete e;
	}
}

void Vertex::SeeAllVertex()
{
	std::cout << m_key << " ";
	if (m_pNext) m_pNext->SeeAllVertex();
}

Edge * Vertex::FindEdge(int key)
{
	Edge * t = m_pEHead;
	while (t) {
		if (t->GetKey() == key) return t;
		t = t->GetNext();
	}
	return nullptr;
}
