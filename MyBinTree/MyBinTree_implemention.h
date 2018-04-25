
#pragma once
#include<algorithm>
#include "../stack/Stack.h" //引入栈模板类

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
	_size = 1; return _root = new MyBinNode<T>(e);//将e当作根节点插入空的二叉树
}

template <typename T>
MyBinNodePosi(T) MyBinTree<T>::insertAsLC(MyBinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;//e插入为x的左孩子
}

template <typename T>
MyBinNodePosi(T) MyBinTree<T>::insertAsRC(MyBinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;//e插入为x的右孩子
}

template <typename T> 
MyBinNodePosi(T) MyBinTree<T>::attachAsLC(MyBinNodePosi(T) x, MyBinTree<T>* &S)
{				//二叉树子树接入算法：将S当作节点x的左子树接入，S本身置空
	if (x->lc = s->root)
	{
		x->lc->parent = x; //接入
	}
	_size += S->_size;
	updateHeightAbove(x);//更新全树规模与x所有祖先的高度
	S->root = null;
	S->_size = 0;
	release(S);
	S = NULL;
	return x; //释放原树，返回接入位置
}

template <typename T> //二叉树子树接入算法：将S当作节点x的右子树接入，S本身置空
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

template <typename T> //二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
MyBinTree<T>* MyBinTree<T>::secede ( MyBinNodePosi(T) x )
{ 
   //assert: x为二叉树中的合法位置
   FromParentTo ( *x ) = NULL; //切断来自父节点的指针
   updateHeightAbove ( x->parent ); //更新原树中所有祖先的高度
   MyBinTree<T>* S = new MyBinTree<T>; S->_root = x; x->parent = NULL; //新树以x为根
   S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树
}
