#include <stdio.h>
#include <stdlib.h>
#define STACKINITSIZE 20//栈初始空间大小
#define INCREASEMENT 10//栈空间大小的增量

typedef struct BiTNode
{
	char data;//二叉树节点数据
	BiTNode *lchild,*rchild;//指向二叉树左子树和右子树的指针
}BiTNode,*BiTree,bitnode;//定义二叉树节点结构

typedef struct SqStack
{
	BiTNode *base;//栈底指针
	BiTNode *top;//栈顶指针
	int stacksize;//顺序栈空间大小
}SqStack;//定义顺序栈结构

//建立一个空栈，建立成功，返回1，失败，返回0
int InitStack(SqStack &S)
{
	S.base = (BiTNode*)malloc(STACKINITSIZE * sizeof(BiTNode));//20为栈的大小，可以更改
	if(!S.base)
		return 0;
	S.top = S.base;
	S.stacksize = STACKINITSIZE;
	return 1;
}

//进栈操作
int Push(SqStack &S,BiTNode e)
{
	if(S.top - S.base >= S.stacksize)
	{
		S.base = (BiTNode*)realloc(S.base,(STACKINITSIZE + INCREASEMENT) * sizeof(BiTNode));
		if(!S.base)
			return 0;
		S.stacksize = 30;
	}
	*S.top = e;
	S.top ++;
	return 1;
}

//出栈操作，若栈为空，则返回0；栈不为空，则返回1
int Pop(SqStack &S,BiTNode &e)
{
	if(S.base == S.top)
		return 0;
	S.top --;
	e = *S.top;
	return 1;
}

//判断栈是否为空，若栈为空，则返回true，栈不为空，则返回false
bool StackEmpty(SqStack S)
{
	if(S.base == S.top)
		return true;
	else
		return false;
}


//中序遍历二叉树
int InOrderTraverse(BiTree T)
{
	if(!T)
		return 0;
	SqStack S;
	int n = InitStack(S);//建立空栈
	if(!n)
		return 0;
	BiTree p = T;
	BiTNode e;//二叉树节点，用于存放从栈中取出的节点
	while(p || !StackEmpty(S))
	{
		if(p)
		{
			Push(S,*p);
			p = p->lchild;
		}
		else
		{
			Pop(S,e);
			printf("%c ",e.data);
			p = e.rchild;
		}
	}
	printf("\n");
	return 1;
}
void creatnode(bitnode *root,char key,char data)
{
    bitnode *newnode = NULL;
    newnode = (bitnode*)malloc(sizeof(bitnode));
    if(newnode == NULL)
    {
        printf("error!");
        exit(0);
    }
    newnode->lchild = NULL;
    newnode->rchild = NULL;
    newnode->data = data;
    if(key == 'l')
    {
        root->lchild = newnode;
    }
    if(key == 'r')
    {
        root->rchild = newnode;
    }
}
void init(bitnode *root)
{   
    root->data='-';
    creatnode(root,'l','+');
    creatnode(root,'r','/');
    creatnode(root->rchild,'r','f');
    creatnode(root->rchild,'l','e');
    creatnode(root->lchild,'l','a');
    creatnode(root->lchild,'r','*');
    creatnode(root->lchild->rchild,'l','b');
    creatnode(root->lchild->rchild,'r','-');
    creatnode(root->lchild->rchild->rchild,'l','c');
    creatnode(root->lchild->rchild->rchild,'r','d');
}
int main()
{
	bitnode root;
	init(&root);
	InOrderTraverse(&root);
	return 0;
}
