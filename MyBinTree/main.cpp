#pragma once

#include <iostream>
using namespace std;

#include "../_share/util.h"
#include "../UniPrint/print.h"
#include "MyBinTree.h"
#include "print_MybinNode.h"

static int countbin = 0;
template <typename T> //元素类型
void printMyBin(MyBinTree<T> & bt) 
{ //引用
	printf("%s[%d][%p]*%d:\n", typeid (bt).name(), &bt, &bt, bt.size()); //基本信息
	Bitmap* branchType = new Bitmap; //记录当前节点祖先的方向
	printBinTree(bt.root(), -1, ROOT, branchType); //树状结构
	release(branchType); printf("\n");
}
template <typename T>
void  printMyBin(MyBinTree<T>* s) //所有指针
{
	if (!s)
	{
		printf("1 \a\n");
	}
	s ? printMyBin(*s) : printf("<NULL>");
}


/******************************************************************************************
* 二叉树各种派生类的统一打印
******************************************************************************************/
template <typename T> //元素类型
static void printBinTree(MyBinNodePosi(T) bt, int depth, int type, Bitmap* bType) {
	if (!bt) return;
	if (-1 < depth) //设置当前层的拐向标志
		R_CHILD == type ? bType->set(depth) : bType->clear(depth);
	printBinTree(bt->rc, depth + 1, R_CHILD, bType); //右子树（在上）
	pMyBinNode(bt);
	printf(" *");
	for (int i = -1; i < depth; i++) //根据相邻各层
	if ((0 > i) || bType->test(i) == bType->test(i + 1)) //的拐向是否一致，即可确定
		printf("      "); //是否应该
	else  
		printf("│    "); //打印横线
	switch (type)
	{
		case  R_CHILD:  printf("┌─");  break;
		case  L_CHILD:  printf("└─");  break;
		default:  printf("──");  break; //root
	}
	pMyBinNode(bt);
#if defined(DSA_HUFFMAN)
	if (IsLeaf(*bt)) bType->print(depth + 1); //输出Huffman编码
#endif
	printf("\n");
	printBinTree(bt->lc, depth + 1, L_CHILD, bType); //左子树（在下）
}


int testID = 0; //测试编号

// 随机生成期望高度为h的二叉树
template <typename T> bool randomBinTree(MyBinTree<T> & bt, MyBinNodePosi(T) x, int h) {
	if (0 >= h) return false; //至多h层
	if (0 < dice(h)) //以1/h的概率终止当前分支的生长
		randomBinTree(bt, bt.insertAsLC(x, dice((T)h * h * h)), h - 1);
	if (0 < dice(h)) //以1/h的概率终止当前分支的生长
		randomBinTree(bt, bt.insertAsRC(x, dice((T)h * h * h)), h - 1);
	return true;
}

// 在二叉树中随机确定一个节点位置
template <typename T> MyBinNodePosi(T) randomPosiInBinTree(MyBinNodePosi(T) root) {
	if (!HasChild(*root))
		return root;
	if (!HasLChild(*root))
		return dice(6) ? randomPosiInBinTree(root->rc) : root;
	if (!HasRChild(*root))
		return dice(6) ? randomPosiInBinTree(root->lc) : root;
	return dice(2) ?
		randomPosiInBinTree(root->lc) :
		randomPosiInBinTree(root->rc);
}

template <typename T>
void   testBinTree(int h) { //测试二叉树
	countbin++;
	printf("countbin = %d \n", countbin);
	printf("\n  ==== Test %2d. Generate a binTree of height <= %d ***********************\n", testID++, h);
	MyBinTree<T> bt;

	printMyBin(bt);

	bt.insertAsRoot(dice((T)h * h * h));
	printMyBin(bt);

	randomBinTree<T>(bt, bt.root(), h);
	printMyBin(bt);

	printf("\n  ==== Test %2d. Double and increase all nodes by traversal***********************\n", testID++);
	bt.travPre(Double<T>());
	printf("\n  ==== 00000000*******\n");
	bt.travPre(Increase<T>());
	printf("\n  ==== 1111111*************\n");
	printMyBin(bt);
	printf("\n  ==== 222222************\n");
	bt.travIn(Double<T>()); bt.travIn(Increase<T>());
	printMyBin(bt);
	printf("\n  ==== 3333333333*********\n");
	bt.travPost(Double<T>()); bt.travPost(Increase<T>());
	printMyBin(bt);
	printf("\n  ==== 444444444******\n");
	bt.travLevel(Double<T>()); bt.travLevel(Increase<T>());
	printf("\n  ==== 5555555555*****\n");
	printMyBin(bt);
	Hailstone<T> he; 
	bt.travIn(he); 
	printMyBin(bt);
	printf("\n  ==== Test %2d. Remove/release subtrees in the Tree***********************\n", testID++);
	while (!bt.empty()) {
		MyBinNodePosi(T) p = randomPosiInBinTree(bt.root()); //随机选择一个节点
		if (dice(2)) {
			printf("removing "); 
			print(p->data); 
			printf(" ...\n");
			printf("%d node(s) removed\n", bt.remove(p)); printMyBin(bt);
		}
		else {
			printf("releasing "); 
			print(p->data); 
			printf(" ...\n");
			MyBinTree<T>* S = bt.secede(p); printMyBin(S);
			printf("%d node(s) released\n", S->size()); release(S); printMyBin(bt);
		}
	}
}

#include <exception>  
int main(int argc, char* argv[]) { //测试二叉树
//	if (2 > argc) { printf("Usage: %s <size of test>\n", argv[0]); return 1; }
	srand((unsigned int)time(NULL));
	printf("input tree height:\n");
	int height = 0;
	scanf("%d", &height);
	//testBinTree<int>(atoi(argv[1])); //元素类型可以在这里任意选择
	try	
	{
		testBinTree<int>(height); //元素类型可以在这里任意选择
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
	}
	cout<<"count = " << countbin;
	system("pause");
	return 0;
}