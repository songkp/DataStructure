
#pragma once
#include<algorithm>
#include "../stack/Stack.h" //����ջģ����

template <typename T> 
int MyBinTree<T>::updateHeight(MyBinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x ->lc), stature(x->rc));
}

template <typename T>
void MyBinTree<T>::updateHeightAbove(MyBinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template <typename T> 
MyBinNodePosi(T) MyBinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new MyBinNode<T>(e);//��e�������ڵ����յĶ�����
}

template <typename T>
MyBinNodePosi(T) MyBinTree<T>::insertAsLC(MyBinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;//e����Ϊx������
}

template <typename T>
MyBinNodePosi(T) MyBinTree<T>::insertAsRC(MyBinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;//e����Ϊx���Һ���
}

template <typename T> 
MyBinNodePosi(T) MyBinTree<T>::attachAsLC(MyBinNodePosi(T) x, MyBinTree<T>* &S)
{				//���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
	if (x->lc = s->root)
	{
		x->lc->parent = x; //����
	}
	_size += S->_size;
	updateHeightAbove(x);//����ȫ����ģ��x�������ȵĸ߶�
	S->root = null;
	S->_size = 0;
	release(S);
	S = NULL;
	return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //���������������㷨����S�����ڵ�x�����������룬S�����ÿ�
MyBinNodePosi(T) MyBinTree<T>::attachAsRC(MyBinNodePosi(T) x, MyBinTree<T>* &S)
{
	if (x->rc = S->root)
	{
		x->rc->parent = x;
		_size += s->_size;
		updateHeightAbove(x);
		S->_root = null;
		S->_size = 0;
		release(S);
		S = NULL;
		return x;
	}
}

template <typename T>
int MyBinTree<T>::remove(MyBinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template <typename T> 
static int removeAt(MyBinNodePosi(T) x)
{
	if(!x)
		return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	release(x->data);
	release(x);
	return n;
}

template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
MyBinTree<T>* MyBinTree<T>::secede ( MyBinNodePosi(T) x )
{ 
   //assert: xΪ�������еĺϷ�λ��
   FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
   updateHeightAbove ( x->parent ); //����ԭ�����������ȵĸ߶�
   MyBinTree<T>* S = new MyBinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
   S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}
