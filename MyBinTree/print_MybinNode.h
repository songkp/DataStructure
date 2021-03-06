
/******************************************************************************************
* BinTree节点
******************************************************************************************/

template <typename T> 
void pMyBinNode(MyBinNode<T>& node)
{
	//UniPrint test = new UniPrint();
	//test.p(node.data); //数值
	UniPrint::p(node.data);
	/******************************************************************************************
	* height & NPL
	******************************************************************************************/
#if   defined(DSA_LEFTHEAP)
	printf("(%-2d)", node.npl); //NPL
#elif defined(DSA_BST)
	printf("(%-2d)", node.height); //高度
#elif defined(DSA_AVL)
	printf("(%-2d)", node.height); //高度
#elif defined(DSA_REDBLACK)
	printf("(%-2d)", node.height); //高度
#elif defined(DSA_SPLAY)
	printf("(%-2d)", node.height); //高度
#endif
	/******************************************************************************************
	* 父子链接指针
	******************************************************************************************/
	printf(
		((node.lc && &node != node.lc->parent) ||
		(node.rc && &node != node.rc->parent)) ?
		"@" : " "
		);
	/******************************************************************************************
	* 节点颜色
	******************************************************************************************/
#if defined(DSA_REDBLACK)
	printf(node.color == RB_BLACK ? "B" : " "); //（忽略红节点）
#endif
	/******************************************************************************************
	* 父子（黑）高度、NPL匹配
	******************************************************************************************/
#if   defined(DSA_PQ_COMPLHEAP)
	//高度不必匹配
#elif defined(DSA_PQ_LEFTHEAP)
	printf( //NPL
		(node.rc && node.npl != 1 + node.rc->npl) ||
		(node.lc && node.npl >  1 + node.lc->npl) ?
		"%%" : " "
		);
#elif defined(DSA_REDBLACK)
	printf(BlackHeightUpdated(node) ? " " : "!"); //黑高度
#else
	printf(HeightUpdated(node) ? " " : "!"); //（常规）高度
#endif
	/******************************************************************************************
	* 左右平衡
	******************************************************************************************/
#if defined(DSA_AVL)
	if (!AvlBalanced(node)) printf("X"); //AVL平衡
	else if (0 < BalFac(node)) printf("\\"); //AVL平衡
	else if (BalFac(node) < 0) printf("/"); //AVL平衡
	else printf("-"); //AVL平衡
#elif defined(DSA_REDBLACK)
	if (!Balanced(node)) printf("X"); //RB平衡
	else if (0 < BalFac(node)) printf("\\"); //RB平衡
	else if (BalFac(node) < 0) printf("/"); //RB平衡
	else printf("-"); //RB平衡
#else
	//平衡无所谓
#endif
}

template <typename T>
void  pMyBinNode(MyBinNode<T>* s) //所有指针
{
	s ? pMyBinNode(*s) : printf("<NULL>");
} //统一转为引用
