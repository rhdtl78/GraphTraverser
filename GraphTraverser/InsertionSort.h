#pragma once
#include "Vertex.h"
#include "Edge.h"
using namespace std;
template<class T>
void input(T **root, int key, int weight);
template<class T>
void input(T **root, int key, int weight) {
	T *tmp;
	T *search = *root;

	tmp = new T(key, weight);

	if (*root == nullptr) {
		*root = tmp;
		return;
	}
	if (tmp->GetKey() < (*root)->GetKey()) {
		tmp->SetNext(*root);
		*root = tmp;
	}
	else {
		while (1) {
			if (tmp->GetKey() == search->GetKey()) {
				delete tmp;
				break;
			}
			if (search->GetNext() == nullptr) {
				search->SetNext(tmp);
				break;
			}
			if (tmp->GetKey() < search->GetNext()->GetKey()) {
				tmp->SetNext(search->GetNext());
				search->SetNext(tmp);
				break;
			}
			search = search->GetNext();
		}
	}
}