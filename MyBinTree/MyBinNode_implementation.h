
#pragma once
#include "../stack/Stack.h" //����ջģ����

/******************************************************************************************
* MyBinNode״̬�����ʵ��ж�
******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )

#define HeightUpdated(x) /*�߶ȸ��³�������*/ \
	/*DSA*/        ((x).height == 1 + max(stature((x).lc), stature((x).rc)))

/******************************************************************************************
* ��MyBinNode�����ض���ϵ�Ľڵ㼰ָ��
******************************************************************************************/
#define sibling(p) /*�ֵ�*/ \
	(IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x) /*����*/ \
	(IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)

#define FromParentTo(x) /*���Ը��׵�����*/ \
	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))

template <typename T>
int MyBinNode<T>::size() { //ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
	int s = 1; //���뱾��
	if (lc) s += lc->size(); //�ݹ������������ģ
	if (rc) s += rc->size(); //�ݹ������������ģ
	return s;
}

template <typename T>
MyBinNodePosi(T) MyBinNode<T>::insertAsLC(T const& e)
{
	return lc = new MyBinNode(e, this);//��e��Ϊ��ǰ�ڵ�����Ӳ��������
}

template <typename T>
MyBinNodePosi(T) MyBinNode<T>::insertAsRC(T const& e)
{
	return rc = new MyBinNode(e, this);//��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
}

template <typename T>
MyBinNodePosi(T) MyBinNode<T>::succ()
{
	MyBinNodePosi(T) s = this;
	if (rc) //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
	{			//�������������С���Ľڵ�
		s = rc;
		while (HasLChild(*s))
		{
			s = s->lc;
		}
	}
	else //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���������������֧�����ϳ����Ϸ��ƶ�
	{
		while (IsRChild(*s))
		{
			s = s->parent;
		}
		s = s->parent;	//����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}

	return s;
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPre_R(MyBinNodePosi(T) x, VST& visit)
{
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}



template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I1(MyBinNodePosi(T) x, VST& visit) { //��������������㷨��������#1��
	Stack<MyBinNodePosi(T)> S; //����ջ
	if (x) S.push(x); //���ڵ���ջ
	while (!S.empty()) { //��ջ���֮ǰ����ѭ��
		x = S.pop();
		visit(x->data); //���������ʵ�ǰ�ڵ㣬��ǿպ��ӵ���ջ����Ϊ���Һ���
		if (HasRChild(*x)) S.push(x->rc);
		if (HasLChild(*x)) S.push(x->lc);
	}
}

//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template <typename T, typename VST> //Ԫ�����͡�������
static void visitAlongLeftBranch(MyBinNodePosi(T) x, VST& visit, Stack<MyBinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data);
		if (HasRChild(*x))
			S.push(x->rc);//�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
		x = x->lc; //�����֧����һ��
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(MyBinNodePosi(T) x, VST& visit)//��������������㷨��������#2��
{
	Stack<MyBinNodePosi(T)> S;
	
	while (x!=nullptr)
	{		
		visitAlongLeftBranch(x, visit, S);
		if (S.empty())
			break;
		x = S.pop();	//������һ�������
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void MyBinNode<T>::travPre(VST& visit) 
{ //��������������㷨ͳһ���
	
	int i = rand() % 3;
	switch (i)
	{ 
		//�˴������ѡ���������ԣ�������ѡ��		
	case 1:
		printf("\n  ==== travPre_I1  ====\n"); 
		travPre_I1(this, visit);		
		break; //������#1
	case 2: 
		printf("\n  ==== travPre_I2  ====\n"); 
		travPre_I2(this, visit);
		
		break; //������#2
	default:
		printf("\n  ==== travPre_R  ====\n");
		travPre_R(this, visit);
		
		break; //�ݹ��
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_R(MyBinNodePosi(T) x, VST& visit) //��������������㷨���ݹ�棩
{
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

template<typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongLeftBranch(MyBinNodePosi(T) x, Stack<MyBinNodePosi(T)>& S)
{
	while (x)
	{
		S.push(x);
		x = x->lc; //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
	}
}
template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I1(MyBinNodePosi(T) x, VST& visit)
{
	Stack<MyBinNodePosi(T)> S; //����ջ
	while (true)
	{
		goAlongLeftBranch(x, S);
		if (S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rc; //ת��������
	}
}


template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I2(MyBinNodePosi(T) x, VST& visit)//��������������㷨��������#2��
{
	Stack<MyBinNodePosi(T)> S; //����ջ
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

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I3(MyBinNodePosi(T) x, VST& visit) //��������������㷨��������#3�����踨��ջ��
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
				break; //���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
			backtrack = true; //�����û��ݱ�־
		}
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I4(MyBinNodePosi(T) x, VST& visit) //���������������������#4������ջ���־λ��
{
	while (true)
	if (HasLChild(*x)) //��������������
		x = x->lc; //�������������
	else { //����
		visit(x->data); //���ʵ�ǰ�ڵ㣬��
		while (!HasRChild(*x)) //���ϵ������ҷ�֧��
		if (!(x = x->succ()))
			return; //������ֱ�Ӻ�̣���û�к�̵�ĩ�ڵ㴦��ֱ���˳���
		else
			visit(x->data); //�����µĵ�ǰ�ڵ�
		x = x->rc; //��ֱ�����ҷ�֧����ת��ǿյ�������
	}
}

template <typename T> template<typename VST>
void MyBinNode<T>::travIn(VST& visit)
{
	switch (rand() % 5)
	{
	case 1: travIn_I1(this, visit); break; //������#1
	case 2: travIn_I2(this, visit); break; //������#2
	case 3: travIn_I3(this, visit); break; //������#3
	case 4: travIn_I4(this, visit); break; //������#4
	default: travIn_R(this, visit); break; //�ݹ��
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void  travPost_R(MyBinNodePosi(T) x, VST& visit)//��������������㷨���ݹ�棩
{
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}


template <typename T, typename VST>
void  travPost_I(MyBinNodePosi(T) x, VST& visit)  //�������ĺ�������������棩
{
	Stack<MyBinNodePosi(T)> S; //����ջ
	if (x) S.push(x); //���ڵ���ջ
	while (!S.empty())
	{
		MyBinNodePosi(T) tempNode = S.top();
		if (tempNode != x->parent) //��ջ���ǵ�ǰ�ڵ�֮�������Ϊ�����֣�����ʱ��
			//����������Ϊ��֮�����У��ҵ�HLVFL���൱�ڵݹ��������У�
		{
			while (MyBinNodePosi(T) rightNode = S.top())
			if (HasRChild(*rightNode))
				S.push(rightNode->rc);
			else
				S.push(rightNode->lc);
			S.pop();
		}
		x = S.pop();
		visit(x->data); //����ջ������ǰһ�ڵ�֮��̣���������֮
	}
}
template <typename T> template <typename VST> //Ԫ�����͡�������
void MyBinNode<T>::travPost(VST& visit) { //��������������㷨ͳһ���
	switch (rand() % 2) { //�˴������ѡ���������ԣ�������ѡ��
	case 1: travPost_I(this, visit); break; //������
	default: travPost_R(this, visit); break; //�ݹ��
	}
}

/*DSA*/#include "../queue/queue.h" //�������
template <typename T> template <typename VST> //Ԫ�����͡�������
void  MyBinNode<T>::travLevel(VST& visit) { //��������α����㷨
	Queue<MyBinNodePosi(T)> Q; //��������
	Q.enqueue(this); //���ڵ����
	while (!Q.empty()) { //�ڶ����ٴα��֮ǰ����������
		MyBinNodePosi(T) x = Q.dequeue(); visit(x->data); //ȡ�����׽ڵ㲢����֮
		if (HasLChild(*x)) Q.enqueue(x->lc); //�������
		if (HasRChild(*x)) Q.enqueue(x->rc); //�Һ������
	}
}
