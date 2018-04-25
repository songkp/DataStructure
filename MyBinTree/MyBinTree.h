#pragma once


#include "MyBinNode.h"
template <typename T> class MyBinTree
{
protected:
	int _size;
	MyBinNodePosi(T) _root;
	virtual int updateHeight(MyBinNodePosi(T) x);
	void updateHeightAbove(MyBinNodePosi(T) x);
public:
	MyBinTree() :_size(0), _root(NULL) {}
	~MyBinTree() 
	{
		if (0 <_size)
		{
			remove(_root);
		}
	}
	int size() const { return _size; }
	bool empty() const
	{
		return !_root;
	}
	MyBinNodePosi(T) root() const
	{
		return _root;
	}

	MyBinNodePosi(T) insertAsRoot(T const& e);
	MyBinNodePosi(T) insertAsLC(MyBinNodePosi(T) x, T const& e);
	MyBinNodePosi(T) insertAsRC(MyBinNodePosi(T) x, T const& e);
	MyBinNodePosi(T) attachAsLC(MyBinNodePosi(T) x, MyBinTree<T>* &T);
	MyBinNodePosi(T) attachAsRC(MyBinNodePosi(T) x, MyBinTree<T>* &T);
	int remove(MyBinNodePosi(T) x);
	MyBinTree<T>* secede(MyBinNodePosi(T) x); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
	template <typename VST>
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
	template<typename VST>
	void travPre(VST& visit)
	{
		printf("\n travPre(VST& visit) \n");
		if (_root) _root->travPre(visit);
	}
	template<typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }

	bool operator<(MyBinTree<T> const& t)
	{
		return _root && t._root&&lt(_root, t._root);
	}
	bool operator== (MyBinTree<T> const& t) //�е���
	{
		return _root && t._root && (_root == t._root);
	}
	/*DSA*/
	/*DSA*/void stretchToLPath() { stretchByZag(_root); } //����zag��ת��ת��Ϊ������
	/*DSA*/void stretchToRPath() { stretchByZig(_root, _size); } //����zig��ת��ת��Ϊ������
};
#include "MyBinTree_implemention.h"