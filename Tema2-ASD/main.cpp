#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;
ifstream f("date.in");

struct HeapNod {

	int key;
	HeapNod *l;
	HeapNod *n;

	HeapNod():
		l(NULL), n(NULL) {}

	///creaza nod
	HeapNod(int key_, HeapNod *l_, HeapNod *n_):
		key(key_), l(l_), n(n_) {}

		///adauga copil sau frate
	void addChild(HeapNod *nod) {
		if(l==NULL)
			l=nod;
		else {
			nod->n=l;
			l=nod;
		}
	}
};

bool Empty(HeapNod *nod) {
	return (nod==NULL);
}

///concatenare heapuri
HeapNod *Merge(HeapNod *A, HeapNod *B)
{
	if(A==NULL) return B;
	if(B==NULL) return A;

	///nodul mai mic devine parinte
	if(A->key < B->key) {
		A->addChild(B);
		return A;
	}
	else {
		B->addChild(A);
		return B;
	}

	return NULL;
}

///gasire minim
int Minim(HeapNod *nod) {
	return nod->key;
}

///inserare de noduri
HeapNod *Insert(HeapNod *nod, int key) {
	return Merge(nod, new HeapNod(key, NULL, NULL));
}

///ne ajuta la delete minim
HeapNod *Merge2(HeapNod *nod) {
	if(nod==NULL || nod->n == NULL)
		return nod;
	else {
		HeapNod *A, *B, *newNod;
		A=nod;
		B=nod->n;
		newNod=nod->n->n;

		A->n=NULL;
		B->n=NULL;

		return Merge(Merge(A,B), Merge2(newNod));
	}

	return NULL;
}

///delete minim
HeapNod *Delete(HeapNod *nod) {
	return Merge2(nod->l);
}

struct PairingHeap {
	HeapNod *root;

	PairingHeap():
		root(NULL) {}

	bool Empty(void) {
		return ::Empty(root);
	}

	int Minim(void) {
		return ::Minim(root);
	}

	void Insert(int key) {
		root= ::Insert(root, key);
	}

	void Delete(void) {
		root= ::Delete(root);
	}

	void Join(PairingHeap other) {
		root= ::Merge(root, other.root);
	}

};

int a[100], b[100], i,n;
int main()
{
    PairingHeap heap1, heap2;
    f>>n;
    for(i=1; i<=n; i++)
    {
        f>>a[i]>>b[i];
        if(a[i]==1) heap1.Insert(b[i]);
        if(a[i]==2) heap2.Insert(b[i]);
        if(a[i]==3 && b[i]==0) cout << heap1.Minim() << endl;
        if(a[i]==4 && b[i]==0) cout << heap2.Minim() << endl;
        if(a[i]==5 && b[i]==0) heap1.Delete();
        if(a[i]==6 && b[i]==0) heap2.Delete();
        if(a[i]==7 && b[i]==0) heap1.Join(heap2);

    }
    cout << heap1.Minim() << endl;

    cout<< (heap1.Empty()?"True":"False");

    return 0;
}
