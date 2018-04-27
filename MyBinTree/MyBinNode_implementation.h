
#pragma once
#include "../stack/Stack.h" //引入栈模板类

/******************************************************************************************
* MyBinNode状态与性质的判断
******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

#define HeightUpdated(x) /*高度更新常规条件*/ \
	/*DSA*/        ((x).height == 1 + max(stature((x).lc), stature((x).rc)))

/******************************************************************************************
* 与MyBinNode具有特定关系的节点及指针
******************************************************************************************/
#define sibling(p) /*兄弟*/ \
	(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x) /*叔叔*/ \
	(IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)

#define FromParentTo(x) /*来自父亲的引用*/ \
	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

template <typename T>
int MyBinNode<T>::size() { //统计当前节点后代总数，即以其为根的子树规模
	int s = 1; //计入本身
	if (lc) s += lc->size(); //递归计入左子树规模
	if (rc) s += rc->size(); //递归计入右子树规模
	return s;
}

template <typename T>
MyBinNodePosi(T) MyBinNode<T>::insertAsLC(T const& e)
{
	return lc = new MyBinNode(e, this);//将e作为当前节点的左孩子插入二叉树
}

template <typename T>
MyBinNodePosi(T) MyBinNode<T>::insertAsRC(T const& e)
{
	return rc = new MyBinNode(e, this);//将e作为当前节点的右孩子插入二叉树
}

template <typename T>
MyBinNodePosi(T) MyBinNode<T>::succ()
{
	MyBinNodePosi(T) s = this;
	if (rc) //若有右孩子，则直接后继必在右子树中，具体地就是
	{			//右子树中最靠左（最小）的节点
		s = rc;
		while (HasLChild(*s))
		{
			s = s->lc;
		}
	}
	else //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是逆向地沿右向分支，不断朝左上方移动
	{
		while (IsRChild(*s))
		{
			s = s->parent;
		}
		s = s->parent;	//最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}

	return s;
}

template <typename T, typename VST> //元素类型、操作器
void travPre_R(MyBinNodePosi(T) x, VST& visit)
{
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}



template <typename T, typename VST> //元素类型、操作器
void travPre_I1(MyBinNodePosi(T) x, VST& visit) { //二叉树先序遍历算法（迭代版#1）
	Stack<MyBinNodePosi(T)> S; //辅助栈
	if (x) S.push(x); //根节点入栈
	while (!S.empty()) { //在栈变空之前反复循环
		x = S.pop();
		visit(x->data); //弹出并访问当前节点，其非空孩子的入栈次序为先右后左
		if (HasRChild(*x)) S.push(x->rc);
		if (HasLChild(*x)) S.push(x->lc);
	}
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST> //元素类型、操作器
static void visitAlongLeftBranch(MyBinNodePosi(T) x, VST& visit, Stack<MyBinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data);
		if (HasRChild(*x))
			S.push(x->rc);//右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
		x = x->lc; //沿左分支深入一层
	}
}

template <typename T, typename VST> //元素类型、操作器
void travPre_I2(MyBinNodePosi(T) x, VST& visit)//二叉树先序遍历算法（迭代版#2）
{
	Stack<MyBinNodePosi(T)> S;
	
	while (x!=nullptr)
	{		
		visitAlongLeftBranch(x, visit, S);
		if (S.empty())
			break;
		x = S.pop();	//弹出下一批的起点
	}
}

template <typename T> template <typename VST> //元素类型、操作器
void MyBinNode<T>::travPre(VST& visit) 
{ //二叉树先序遍历算法统一入口
	
	int i = rand() % 3;
	switch (i)
	{ 
		//此处暂随机选择以做测试，共三种选择		
	case 1:
		printf("\n  ==== travPre_I1  ====\n"); 
		travPre_I1(this, visit);		
		break; //迭代版#1
	case 2: 
		printf("\n  ==== travPre_I2  ====\n"); 
		travPre_I2(this, visit);
		
		break; //迭代版#2
	default:
		printf("\n  ==== travPre_R  ====\n");
		travPre_R(this, visit);
		
		break; //递归版
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_R(MyBinNodePosi(T) x, VST& visit) //二叉树中序遍历算法（递归版）
{
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

template<typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongLeftBranch(MyBinNodePosi(T) x, Stack<MyBinNodePosi(T)>& S)
{
	while (x)
	{
		S.push(x);
		x = x->lc; //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
	}
}
template <typename T, typename VST> //元素类型、操作器
void travIn_I1(MyBinNodePosi(T) x, VST& visit)
{
	Stack<MyBinNodePosi(T)> S; //辅助栈
	while (true)
	{
		goAlongLeftBranch(x, S);
		if (S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rc; //转向右子树
	}
}


template <typename T, typename VST> //元素类型、操作器
void travIn_I2(MyBinNodePosi(T) x, VST& visit)//二叉树中序遍历算法（迭代版#2）
{
	Stack<MyBinNodePosi(T)> S; //辅助栈
	while (true)
	{
		if (x)
		{
			S.push(x);
			x = x->lc;
		}
		else if (!S.empty())
		{
			x = S.pop();
			visit(x->data);
			x = x->rc;
		}
		else
			break;
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I3(MyBinNodePosi(T) x, VST& visit) //二叉树中序遍历算法（迭代版#3，无需辅助栈）
{
	bool backtrack = false;
	while (true)
	if (!backtrack && HasLChild(*x))
		x = x->lc;
	else
	{
		visit(x->data);
		if (HasRChild(*x))
		{
			x = x->rc;
			backtrack = true;
		}
		else
		{
			if (!(x = x->succ()))
				break; //回溯（含抵达末节点时的退出返回）
			backtrack = true; //并设置回溯标志
		}
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I4(MyBinNodePosi(T) x, VST& visit) //二叉树中序遍历（迭代版#4，无需栈或标志位）
{
	while (true)
	if (HasLChild(*x)) //若有左子树，则
		x = x->lc; //深入遍历左子树
	else { //否则
		visit(x->data); //访问当前节点，并
		while (!HasRChild(*x)) //不断地在无右分支处
		if (!(x = x->succ()))
			return; //回溯至直接后继（在没有后继的末节点处，直接退出）
		else
			visit(x->data); //访问新的当前节点
		x = x->rc; //（直至有右分支处）转向非空的右子树
	}
}

template <typename T> template<typename VST>
void MyBinNode<T>::travIn(VST& visit)
{
	switch (rand() % 5)
	{
	case 1: travIn_I1(this, visit); break; //迭代版#1
	case 2: travIn_I2(this, visit); break; //迭代版#2
	case 3: travIn_I3(this, visit); break; //迭代版#3
	case 4: travIn_I4(this, visit); break; //迭代版#4
	default: travIn_R(this, visit); break; //递归版
	}
}

template <typename T, typename VST> //元素类型、操作器
void  travPost_R(MyBinNodePosi(T) x, VST& visit)//二叉树后序遍历算法（递归版）
{
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}


template <typename T, typename VST>
void  travPost_I(MyBinNodePosi(T) x, VST& visit)  //二叉树的后序遍历（迭代版）
{
	Stack<MyBinNodePosi(T)> S; //辅助栈
	if (x) S.push(x); //根节点入栈
	while (!S.empty())
	{
		MyBinNodePosi(T) tempNode = S.top();
		if (tempNode != x->parent) //若栈顶非当前节点之父（则必为其右兄），此时需
			//在以其右兄为根之子树中，找到HLVFL（相当于递归深入其中）
		{
			while (MyBinNodePosi(T) rightNode = S.top())
			if (HasRChild(*rightNode))
				S.push(rightNode->rc);
			else
				S.push(rightNode->lc);
			S.pop();
		}
		x = S.pop();
		visit(x->data); //弹出栈顶（即前一节点之后继），并访问之
	}
}
template <typename T> template <typename VST> //元素类型、操作器
void MyBinNode<T>::travPost(VST& visit) { //二叉树后序遍历算法统一入口
	switch (rand() % 2) { //此处暂随机选择以做测试，共两种选择
	case 1: travPost_I(this, visit); break; //迭代版
	default: travPost_R(this, visit); break; //递归版
	}
}

/*DSA*/#include "../queue/queue.h" //引入队列
template <typename T> template <typename VST> //元素类型、操作器
void  MyBinNode<T>::travLevel(VST& visit) { //二叉树层次遍历算法
	Queue<MyBinNodePosi(T)> Q; //辅助队列
	Q.enqueue(this); //根节点入队
	while (!Q.empty()) { //在队列再次变空之前，反复迭代
		MyBinNodePosi(T) x = Q.dequeue(); visit(x->data); //取出队首节点并访问之
		if (HasLChild(*x)) Q.enqueue(x->lc); //左孩子入队
		if (HasRChild(*x)) Q.enqueue(x->rc); //右孩子入队
	}
}
