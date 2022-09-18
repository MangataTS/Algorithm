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
	
	//��ȡ�����ĸ߶�
	int GetHeight(AvlNode<T> *root) {
		if(root != NULL)
			return root->height;
		return 0;
	}
	
	//���������ĸ߶�
	int MaxHeight(AvlNode<T> *root) {
		if(root == NULL) return 0;
		return std::max(GetHeight(root->left),GetHeight(root->right)) + 1;
	}
	
	//�ж��Ƿ�ʧȥƽ��
	bool Check_Balance(AvlNode<T> *a, AvlNode<T> *b) {
		return abs(GetHeight(a) - GetHeight(b)) == 2;
	}
	/*
    �ⲿ������AVL����������������������������
    */
	//���ΪLL��ת��LL�ĺ������������������������½�㣩
	AvlNode<T>* LeftLeftRotate(AvlNode<T> *root) {
		AvlNode<T> *lchild = root->left;//��¼һ�������������
		root->left = lchild->right;//������������������Ϊ����������
		lchild->right = root;//���������ĸ���Ϊ���������ĸ���Ȼ������������ָ��֮ǰ�ĸ�
		
		//����һ�µ�ǰ�����ĸ����ĸ�height
		lchild->height = MaxHeight(lchild);
		//����һ�±�����ȥ�Ľ�㣬����ǰ�����ĸ������������ĸ�height
		root->height = MaxHeight(root);
		
		return lchild;//����������ת����µĸ�
	}
	
	//���ΪRR��ת��RR�ĺ������������������������½�㣩
	AvlNode<T>* RightRightRotate(AvlNode<T> *root) {
		AvlNode<T> *rchild = root->right;
		root->right = rchild->left;
		rchild->left = root;
		
		rchild->height = MaxHeight(rchild);
		root->height = MaxHeight(root);
		
		return rchild;
	}
	
	AvlNode<T>* LeftRightRotate(AvlNode<T> *root) {
		root->left = RightRightRotate(root->left);//�ȶ����������н���RR��ת
		root = LeftLeftRotate(root);//Ȼ��Ը��ڵ����LL��ת
		return root;
	}
	
	AvlNode<T>* RightLeftRotate(AvlNode<T> *root) {
		root->right = LeftLeftRotate(root->right);//�ȶ����������н���LL��ת
		root = RightRightRotate(root);//Ȼ��Ը��ڵ����LL��ת
		return root;
	}
	
	//��AVL���в���Ԫ��ֵΪvalue�Ľ��
	AvlNode<T>* ValueFind(AvlNode<T> *root,T value) {
		while(root != NULL && root->key != value) {
			if(root->key > value) root = root->left;//��������
			else root = root->right;//��������
		}
		return root;//û�ҵ��Ļ��᷵��NULL
	}
	
	AvlNode<T>* MinNode(AvlNode<T> *root) {
		if(root == NULL) return NULL;//����һ�¿��������
		if(root->left == NULL) return root;
		return MinNode(root->left);
	}
	
	AvlNode<T>* MaxNode(AvlNode<T> *root) {
		if(root == NULL) return NULL;//����һ�¿��������
		if(root->right == NULL) return root;
		return MaxNode(root->right);
	}
	
	//��AVL���в���Ԫ��ֵΪT�Ľ��
	AvlNode<T>* InsetNode(AvlNode<T> *root,T value) {
		if(root == NULL) {
			root = new AvlNode<T>(value);
		} else if(root->key > value) {//����������
			root->left = InsetNode(root->left,value);
			if(Check_Balance(root->left,root->right)) {//��������������ʧȥƽ��
				if(value < root->left->key) //��Ϊ���������������������ϣ����Խ���LL��ת
					root = LeftLeftRotate(root);
				else //�����������������������ϣ�����LR��ת
					root = LeftRightRotate(root);
			}
		} else {//����������
			root->right = InsetNode(root->right,value);
			if(Check_Balance(root->right,root->left)) {//��������������ʧȥƽ��
				if(value < root->right->key)//��Ϊ���������������������ϣ����Խ���RL��ת
					root = RightLeftRotate(root);
				else //��Ϊ���������������������ϣ����Խ���RR��ת
					root = RightRightRotate(root);
			}
		}
		root->height = MaxHeight(root);//������߶�
		return root;
	}
	
	//ɾ�����
	AvlNode<T>* DeleteNode(AvlNode<T> *root, AvlNode<T> *node) {
		if(root == NULL) return NULL;
		if(root->key == node->key) { //�ҵ���ɾ���Ľ��
			if(root->left != NULL && root->right != NULL) {
				//���ɾ���Ľ�������������������Ϊ��
				if(GetHeight(root->left) > GetHeight(root->right)) {
					//������������������ߵĻ�������������
					//һ���ҵ���ǰ���������������ֵ���
					AvlNode<T> *max_node = MaxNode(root->left);
					//��������������������ֵ������ǰ�ĸ��ڵ�
					root->key = max_node->key;
					//����ɾ�������������ֵ�Ľ�㣨��Ϊ������һ����ֻ������������û���������������
					root->left = DeleteNode(root->left,max_node);
				} else {
					//�����������������߻������,ͬ��������
					//һ���ҵ���ǰ�����������ϵ���Сֵ���
					AvlNode<T> *min_node = MinNode(root->right);
					//�������������������Сֵ������ǰ�ĸ��ڵ�
					root->key = min_node->key;
					//����ɾ������������Сֵ��㣨������ͬ��һ����һ��ֻ������������û���������������
					root->right = DeleteNode(root->right,min_node);
				}
			} else {//����������Ϊ�գ�������������Ϊ�գ�������������Ϊ��
				AvlNode<T> *tmp = root;//��¼��ɾ���Ľ��
				if(root->left == NULL) //���������Ϊ�գ���ô�����������̳У���Ȼ������Ҳ������һ��������
					root = root->right;
				else //�����������̳�
					root = root->left;
				delete tmp;
			}
		}
		else if(root->key > node->key) {//ɾ���Ľ������ڵ�
			root->left = DeleteNode(root->left,node);
			if(Check_Balance(root->right,root->left)) {//���������ܻ�ʧ��
				AvlNode<T> *TempRightNode = root->right;
				if(GetHeight(TempRightNode->left) > GetHeight(TempRightNode->right))
					root = RightLeftRotate(root);//RR��
				else
					root = RightRightRotate(root);//RL��
			}
		} else {//ɾ���Ľ����������
			root->right = DeleteNode(root->right,node);
			if(Check_Balance(root->left,root->right)) {//���������ܻᷢ��ʧ��
				AvlNode<T> *TempLeftNode = root->left;
				if(GetHeight(TempLeftNode->left) > GetHeight(TempLeftNode->right))
					root = LeftLeftRotate(root);//LL��
				else
					root = LeftRightRotate(root);//LR��
			}
		}
		if(root)
			root->height = MaxHeight(root);
		return root;
	}
	
	
	//�������
	void PreOrder(AvlNode<T> *root) {
		if(root == NULL) return;
		std::cout<<root->key<<"->";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	//�������
	void InOrder(AvlNode<T> *root) {
		if(root == NULL) return;
		InOrder(root->left);
		std::cout<<root->key<<"->";
		InOrder(root->right);
	}
	//�������
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
		std::cout<<"�������Ϊ��"<<std::endl;
		Tree->PreOrder(Tree->root);
		std::cout<<"\n�������Ϊ��"<<std::endl;
		Tree->InOrder(Tree->root);
		std::cout<<std::endl;
	}
	std::cout<<"hello"<<std::endl;
	AvlNode<int> *p = Tree->ValueFind(Tree->root,5);
	Tree->DeleteNode(Tree->root,p);
	std::cout<<"-----------"<<std::endl;
	std::cout<<"�������Ϊ��"<<std::endl;
	Tree->PreOrder(Tree->root);
	std::cout<<"\n�������Ϊ��"<<std::endl;
	Tree->InOrder(Tree->root);
	
	return 0;
}

/*
output��
-----------
�������Ϊ��
1->
�������Ϊ��
1->
-----------
�������Ϊ��
1->2->
�������Ϊ��
1->2->
-----------
�������Ϊ��
2->1->3->
�������Ϊ��
1->2->3->
-----------
�������Ϊ��
2->1->3->4->
�������Ϊ��
1->2->3->4->
-----------
�������Ϊ��
2->1->4->3->5->
�������Ϊ��
1->2->3->4->5->
-----------
�������Ϊ��
4->2->1->3->5->6->
�������Ϊ��
1->2->3->4->5->6->
-----------
�������Ϊ��
4->2->1->3->6->5->7->
�������Ϊ��
1->2->3->4->5->6->7->
-----------
�������Ϊ��
4->2->1->3->6->5->7->8->
�������Ϊ��
1->2->3->4->5->6->7->8->
hello
-----------
�������Ϊ��
4->2->1->3->7->6->8->
�������Ϊ��
1->2->3->4->6->7->8->
*/


