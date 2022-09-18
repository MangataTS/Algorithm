#include<cstring>
#include<iostream>
#include<algorithm>

template<typename T>
class AvlNode {
public:
	T key;
	int height;
	AvlNode *left,*right;
	AvlNode(int key) {
		this->key = key;
		this->height = 0;
		this->left = this->right = NULL;
	}
	~AvlNode() {
		
	}
};

template<typename T>
class AvlTree {
public:
	
	AvlNode<T> *root;
	
	AvlTree() {
		this->root = NULL;
	}
	
	//获取树结点的高度
	int GetHeight(AvlNode<T> *root) {
		if(root != NULL)
			return root->height;
		return 0;
	}
	
	//更新树结点的高度
	int MaxHeight(AvlNode<T> *root) {
		if(root == NULL) return 0;
		return std::max(GetHeight(root->left),GetHeight(root->right)) + 1;
	}
	
	//判断是否失去平衡
	bool Check_Balance(AvlNode<T> *a, AvlNode<T> *b) {
		return abs(GetHeight(a) - GetHeight(b)) == 2;
	}
	/*
    这部分完善AVL的左旋、右旋、左右旋、右左旋
    */
	//简称为LL旋转（LL的含义是左子树的左子树插入新结点）
	AvlNode<T>* LeftLeftRotate(AvlNode<T> *root) {
		AvlNode<T> *lchild = root->left;//记录一下左子树根结点
		root->left = lchild->right;//将左子树的右子树变为根的左子树
		lchild->right = root;//将左子树的根变为整个子树的根，然后让其右子树指向之前的根
		
		//更新一下当前子树的根结点的高height
		lchild->height = MaxHeight(lchild);
		//更新一下被旋下去的结点，即当前子树的根的右子树结点的高height
		root->height = MaxHeight(root);
		
		return lchild;//返回子树旋转后的新的根
	}
	
	//简称为RR旋转（RR的含义是右子树的右子树插入新结点）
	AvlNode<T>* RightRightRotate(AvlNode<T> *root) {
		AvlNode<T> *rchild = root->right;
		root->right = rchild->left;
		rchild->left = root;
		
		rchild->height = MaxHeight(rchild);
		root->height = MaxHeight(root);
		
		return rchild;
	}
	
	AvlNode<T>* LeftRightRotate(AvlNode<T> *root) {
		root->left = RightRightRotate(root->left);//先对左子树进行进行RR旋转
		root = LeftLeftRotate(root);//然后对根节点进行LL旋转
		return root;
	}
	
	AvlNode<T>* RightLeftRotate(AvlNode<T> *root) {
		root->right = LeftLeftRotate(root->right);//先对右子树进行进行LL旋转
		root = RightRightRotate(root);//然后对根节点进行LL旋转
		return root;
	}
	
	//在AVL树中查找元素值为value的结点
	AvlNode<T>* ValueFind(AvlNode<T> *root,T value) {
		while(root != NULL && root->key != value) {
			if(root->key > value) root = root->left;//在左子树
			else root = root->right;//在右子树
		}
		return root;//没找到的话会返回NULL
	}
	
	AvlNode<T>* MinNode(AvlNode<T> *root) {
		if(root == NULL) return NULL;//特判一下空树的情况
		if(root->left == NULL) return root;
		return MinNode(root->left);
	}
	
	AvlNode<T>* MaxNode(AvlNode<T> *root) {
		if(root == NULL) return NULL;//特判一下空树的情况
		if(root->right == NULL) return root;
		return MaxNode(root->right);
	}
	
	//在AVL树中插入元素值为T的结点
	AvlNode<T>* InsetNode(AvlNode<T> *root,T value) {
		if(root == NULL) {
			root = new AvlNode<T>(value);
		} else if(root->key > value) {//插入左子树
			root->left = InsetNode(root->left,value);
			if(Check_Balance(root->left,root->right)) {//插入左子树后发现失去平衡
				if(value < root->left->key) //因为插入结点左子树的左子树上，所以进行LL旋转
					root = LeftLeftRotate(root);
				else //插入结点在左子树的右子树上，所以LR旋转
					root = LeftRightRotate(root);
			}
		} else {//插入右子树
			root->right = InsetNode(root->right,value);
			if(Check_Balance(root->right,root->left)) {//插入右子树后发现失去平衡
				if(value < root->right->key)//因为插入结点右子树的左子树上，所以进行RL旋转
					root = RightLeftRotate(root);
				else //因为插入结点右子树的右子树上，所以进行RR旋转
					root = RightRightRotate(root);
			}
		}
		root->height = MaxHeight(root);//计算结点高度
		return root;
	}
	
	//删除结点
	AvlNode<T>* DeleteNode(AvlNode<T> *root, AvlNode<T> *node) {
		if(root == NULL) return NULL;
		if(root->key == node->key) { //找到了删除的结点
			if(root->left != NULL && root->right != NULL) {
				//如果删除的结点的左树和右子树都不为空
				if(GetHeight(root->left) > GetHeight(root->right)) {
					//如果左子树比右子树高的话，分三步进行
					//一、找到当前结点的左子树的最大值结点
					AvlNode<T> *max_node = MaxNode(root->left);
					//二、将这个左子树的最大值赋给当前的根节点
					root->key = max_node->key;
					//三、删除左子树的最大值的结点（因为这个结点一定是只有左子树或者没有左子树的情况）
					root->left = DeleteNode(root->left,max_node);
				} else {
					//右子树和左子树更高或者相等,同样分三步
					//一、找到当前结点的右子树上的最小值结点
					AvlNode<T> *min_node = MinNode(root->right);
					//二、将这个右子树的最小值赋给当前的根节点
					root->key = min_node->key;
					//三、删除右子树的最小值结点（和上面同理，一定是一个只有右子树或者没有右子树的情况）
					root->right = DeleteNode(root->right,min_node);
				}
			} else {//左右子树都为空，或者是左子树为空，或者是右子树为空
				AvlNode<T> *tmp = root;//记录下删除的结点
				if(root->left == NULL) //如果左子树为空，那么就由右子树继承（当然右子树也可能是一个空树）
					root = root->right;
				else //否则左子树继承
					root = root->left;
				delete tmp;
			}
		}
		else if(root->key > node->key) {//删除的结点在左节点
			root->left = DeleteNode(root->left,node);
			if(Check_Balance(root->right,root->left)) {//右子树可能会失衡
				AvlNode<T> *TempRightNode = root->right;
				if(GetHeight(TempRightNode->left) > GetHeight(TempRightNode->right))
					root = RightLeftRotate(root);//RR旋
				else
					root = RightRightRotate(root);//RL旋
			}
		} else {//删除的结点在右子树
			root->right = DeleteNode(root->right,node);
			if(Check_Balance(root->left,root->right)) {//左子树可能会发生失衡
				AvlNode<T> *TempLeftNode = root->left;
				if(GetHeight(TempLeftNode->left) > GetHeight(TempLeftNode->right))
					root = LeftLeftRotate(root);//LL旋
				else
					root = LeftRightRotate(root);//LR旋
			}
		}
		if(root)
			root->height = MaxHeight(root);
		return root;
	}
	
	
	//先序遍历
	void PreOrder(AvlNode<T> *root) {
		if(root == NULL) return;
		std::cout<<root->key<<"->";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	//中序遍历
	void InOrder(AvlNode<T> *root) {
		if(root == NULL) return;
		InOrder(root->left);
		std::cout<<root->key<<"->";
		InOrder(root->right);
	}
	//后序遍历
	void PostOrder(AvlNode<T> *root) {
		if(root == NULL) return;
		PostOrder(root->left);
		PostOrder(root->right);
		std::cout<<root->key<<"->";
	}
	
	
};

int main()
{
	
	AvlTree<int> * Tree = new AvlTree<int>();
	int n = 8;
	for(int i = 1;i <= n; ++i) {
		Tree->root = Tree->InsetNode(Tree->root,i);
		std::cout<<"-----------"<<std::endl;
		std::cout<<"先序遍历为："<<std::endl;
		Tree->PreOrder(Tree->root);
		std::cout<<"\n中序遍历为："<<std::endl;
		Tree->InOrder(Tree->root);
		std::cout<<std::endl;
	}
	std::cout<<"hello"<<std::endl;
	AvlNode<int> *p = Tree->ValueFind(Tree->root,5);
	Tree->DeleteNode(Tree->root,p);
	std::cout<<"-----------"<<std::endl;
	std::cout<<"先序遍历为："<<std::endl;
	Tree->PreOrder(Tree->root);
	std::cout<<"\n中序遍历为："<<std::endl;
	Tree->InOrder(Tree->root);
	
	return 0;
}

/*
output：
-----------
先序遍历为：
1->
中序遍历为：
1->
-----------
先序遍历为：
1->2->
中序遍历为：
1->2->
-----------
先序遍历为：
2->1->3->
中序遍历为：
1->2->3->
-----------
先序遍历为：
2->1->3->4->
中序遍历为：
1->2->3->4->
-----------
先序遍历为：
2->1->4->3->5->
中序遍历为：
1->2->3->4->5->
-----------
先序遍历为：
4->2->1->3->5->6->
中序遍历为：
1->2->3->4->5->6->
-----------
先序遍历为：
4->2->1->3->6->5->7->
中序遍历为：
1->2->3->4->5->6->7->
-----------
先序遍历为：
4->2->1->3->6->5->7->8->
中序遍历为：
1->2->3->4->5->6->7->8->
hello
-----------
先序遍历为：
4->2->1->3->7->6->8->
中序遍历为：
1->2->3->4->6->7->8->
*/


