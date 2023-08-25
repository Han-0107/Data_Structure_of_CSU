#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<cmath>
#include<windows.h>
using namespace std;
#define MAXSIZE 1000
#define OK 1
#define ERROR 0
typedef int Status;
typedef int SElemType;
typedef char TElmType;
typedef TElmType SqBiTree[MAXSIZE];
//链式存储结构
typedef struct BiNode {
	TElmType data;
	struct BiNode* lchild, * rchild;
}BiNode, * BiTree;

//循环队列的基本操作
typedef struct {
	BiNode data[MAXSIZE];
	int front;
	int rear;
}ddd;

ddd Q;

//初始化一个空队列
void InitQueue(ddd &Q)
{
	Q.front = 0;
	Q.rear = 0;
}
//判断队列是否为空
Status QueueEmpty(ddd &Q) {
	if (Q.front == Q.rear) return OK;
	else
		return ERROR;
}

//入队
void EnQueue(ddd &Q, BiTree e) {
	if ((Q.rear + 1) % MAXSIZE == Q.front) {//队列满的判断
		cout << "队满" << endl;
		return;
	}
	Q.data[Q.rear] = *e;  //将元素e赋值给队尾
	Q.rear = (Q.rear + 1) % MAXSIZE; //rear指针向后移一个位置，在末尾则转到数组头部
}

//出队
void DeQueue(ddd &Q, BiTree e)
{
	if (Q.front == Q.rear) {
		cout << "队空" << endl;
		return;
	}
	*e = Q.data[Q.front]; //将队头元素赋值给e
	Q.front = (Q.front + 1) % MAXSIZE; //front指针向后移一位置，若到最后转到数组头部
}

//顺序二叉树(适合满二叉树，缺点浪费空间）

//二叉树的遍历

//递归算法
void Pre(BiTree T) {//前序
	if (T == NULL) return;
	else {
		cout << T->data;
		Pre(T->lchild);
		Pre(T->rchild);
	}
}

void InOrder(BiTree T) {//中序
	if (T == NULL) return ;
	else {
		InOrder(T->lchild);
		cout << T->data;
		InOrder(T->rchild);
	}
}

void Post(BiTree T) {//后序
	if (T == NULL) return;
	else {
		Post(T->lchild);
		Post(T->rchild);
		cout << T->data;
	}
}


//二叉树的层次遍历算法（从上到下，从左到右）
void LevelOrder(BiTree T) {
	BiTree p= (BiNode*)malloc(sizeof(BiNode));   ddd qu;
	InitQueue(qu);
	if(T!=NULL) EnQueue(qu, T);
	cout << "层序=：";
	while (!QueueEmpty(qu)) {
		DeQueue(qu, p);  //出队结点p
		cout << p->data;  //访问结点p
		if (p->lchild != NULL)EnQueue(qu, p->lchild);
		if (p->rchild != NULL)EnQueue(qu, p->rchild);
	}
}

//二叉树的建立（先序）
Status CreatBiTree(BiTree& T) {
	char c;
	cin >> c;
	if (c == '^')T = NULL;
	else {
		if (!(T = (BiNode*)malloc(sizeof(BiNode))))
			exit(OVERFLOW);
		T->data = c;
		CreatBiTree(T->lchild);  //构建他的左子树
		CreatBiTree(T->rchild);  //构建他的右子树
	}
	return OK;
}


//计算二叉树的深度（左子树深度为m，右子树深度为n，计算最大的，最后加一）
int Depth(BiTree T) {
	int m, n;
	if (T == NULL) return 0;
	else {
		m = Depth(T->lchild);
		n = Depth(T->rchild);
		if (m > n) return (m + 1);
		else return (n + 1);
	}
}

//计算二叉树的节点（左树＋右数结点+1）
int NodeCount(BiTree T) {
	int m, n;
	if (T == NULL) return 0;
	else {
		m = NodeCount(T->lchild);
		n = NodeCount(T->rchild);
		return m + n + 1;
	}
}

//计算二叉树的叶子结点（左子树叶子结点的个数+右子树叶子结点的个数）
int LeadCount(BiTree T) {
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else {
		return LeadCount(T->lchild) + LeadCount(T->rchild);
	}
}

int main() {         //输出样例ABDH^^^E^^CF^^G^^
	BiTree T; cout << "请以前序的方式输入字符串，空格用 ^ 代替" << endl;
	CreatBiTree(T);
	cout << "前序=：";Pre(T); cout << endl;
	cout << "中序=："; InOrder(T); cout << endl;
	cout << "后序=："; Post(T); cout << endl;
	LevelOrder(T); cout << endl;
	cout << "叶子数=："; cout << LeadCount(T); cout << endl;
	cout << "深度=：";   cout << Depth(T);     cout << endl;
	return 0;
}

