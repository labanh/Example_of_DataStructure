#include<stdio.h>
#include<stdlib.h>

typedef struct Bitnode{
    char data;
    struct Bitnode *lchild,*rchild;
}bitnode;

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

void inorder(bitnode *bt)
{
if(bt!=NULL) {
inorder(bt->lchild);
printf("%c\t",bt->data);
inorder(bt->rchild);
} 
}

int main()
{
	bitnode root;
	init(&root);
	inorder(&root);
}


