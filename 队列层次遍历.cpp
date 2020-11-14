//c语言实现二叉树层次遍历（借助队列实现）

#include <stdio.h>
#include <stdlib.h>
 
//二叉链表类型定义
typedef struct btnode
{
char data;
struct btnode *lchild,*rchild;
}bitree,*Bitree,bitnode,Bitnode;


//链队列类型定义
typedef struct LinkQueueNode
{
bitree *data;
struct LinkQueueNode *next;
}LKQueNode;


typedef struct LKQueue
{
LKQueNode *front,*rear;
}LKQue;


//初始化队列
void InitQueue(LKQue *LQ)
{
LKQueNode *p;
p = (LKQueNode*)malloc(sizeof(LKQueNode));
LQ->front = p;
LQ->rear = p;
LQ->front->next = NULL;
}


//判断队列是否为空
int EmptyQueue(LKQue *LQ)
{
if(LQ->front == LQ->rear)
return 1;
else 
return 0;
}


//入队列
void EnQueue(LKQue *LQ,Bitree x)
{
LKQueNode *p;
p = (LKQueNode*)malloc(sizeof(LKQueNode));
p->data = x;
p->next = NULL;
LQ->rear->next = p;
LQ->rear = p;
}


//出队列
int OutQueue(LKQue *LQ)
{
LKQueNode *s;
if ( EmptyQueue(LQ))
{
exit(0);
return 0;
}
else
{
s = LQ->front->next;
LQ->front->next = s->next;
if(s->next == NULL)
LQ->rear = LQ->front;
free(s);
return 1;
}
}


//取队列首元素
Bitree GetHead(LKQue *LQ)
{
LKQueNode *p;
bitree *q;
if(EmptyQueue(LQ))
return q;
else 
{
p = LQ->front->next;
return p->data;
}
} 


//建二叉树
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


//访问节点
void Visit(Bitree p)
{
printf("%c",p->data); //输出是char
}


//树的高度
int height(Bitree t)
{
int ld,rd;
if(t == NULL) 
return 0;
else 
{
ld = height(t->lchild);
rd = height(t->rchild);
return 1 + (ld>rd?ld:rd);
}
}
 
//层次遍历 
void LevelOrder(Bitree bt)
{
LKQue Q;
Bitree p;
InitQueue(&Q);
if(bt != NULL)
{
EnQueue(&Q,bt);
while(!EmptyQueue(&Q))
{
p = GetHead(&Q);
OutQueue(&Q);
Visit(p);
if(p->lchild != NULL)  
EnQueue(&Q,p->lchild);
if(p->rchild != NULL)  
EnQueue(&Q,p->rchild);
}
}
}


int main()
{
	bitnode root;
	init(&root);


LevelOrder(&root);


printf("\n\n");
}
