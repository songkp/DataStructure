#pragma once
#define MyBinNodePosi(T) MyBinNode<T>*
#define stature(p) ((p) ?(p)->height : -1)


typedef enum { MyRB_RED, MyRB_BLACK } MyRBColor; //节点颜色
template <typename T> 
struct MyBinNode
{
	T data;
	MyBinNodePosi(T) parent;
	MyBinNodePosi(T) lc;
	MyBinNodePosi(T) rc;
	int height;
	int npl; //Null Path Length（左式堆，也可直接用height代替）
	MyRBColor color;

	// 构造函数
	MyBinNode() :
		parent(NULL), lc(null), rc(null), height(0), npl(1), color(MyRB_RED) {}
	MyBinNode(T e, MyBinNodePosi(T) p = NULL, MyBinNodePosi(T) lc = NULL, MyBinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, MyRBColor c = MyRB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c)
	{ }

	// 操作接口
	int size();//统计当前节点后代总数，亦即以其为根的子树的规模
	MyBinNodePosi(T) insertAsLC(T const&);	//作为当前节点的左孩子插入新节点
	MyBinNodePosi(T) insertAsRC(T const&);	//作为当前节点的右孩子插入新节点
	MyBinNodePosi(T) succ();  //取当前节点的直接后继

	template <typename VST> 
	void travLevel(VST&);//子树层次遍历
	template <typename VST>
	void travPre(VST&);//子树先序遍历
	template<typename VST>
	void travIn(VST&);//子树中序遍历
	template<typename VST>
	void travPost(VST&); //子树后序遍历
	bool operator < (MyBinNode const& bn)
	{
		return data < bn.data;
	}
	bool operator == (MyBinNode const& bn)
	{
		return data == bn.data;
	}

	MyBinNodePosi(T) zig();//顺时针旋转
	MyBinNodePosi(T) zag(); //逆时针旋转
};


#include "MyBinNode_implementation.h"