#include <stdio.h>

/*****************数据类型定义*****************/

#define MAXSIZE 10    //顺序表的最大长度
typedef int KeyType;  //关键字类型为整数类型
typedef int InfoType; //其他数据为整数类型

typedef struct Info
{
    KeyType key;        //关键字项
    InfoType otherinfo; //其他数据项
} RecType;              //记录类型

typedef struct List
{
    RecType r[MAXSIZE + 1]; //r[0] 闲置或用作哨兵单元
    int length;             //顺序表长度
} SqList;                   //顺序表类型

typedef SqList HeapType; //堆采用顺序表储存表示

/*****************函数声明*****************/

void HeapAdjust(HeapType *H, int s, int m); //筛选大顶堆
void HeapSort(HeapType *H);                 //堆排序

void Merge(RecType SR[], RecType *TR[], int i, int m, int n); //合并相邻有序序列
void MSort(RecType SR[], RecType *TR1[], int s, int t);       //2-路归并排序
//归并排序有点问题

void PrintList(SqList L);         //输出顺序表
void PrintRecType(RecType *RT[]); //输出 RecType 数组
/*****************函数定义*****************/

void HeapAdjust(HeapType *H, int s, int m)
{
    //已知 H.r[s...m] 中记录的关键字除 H.r[s].key 外均满足堆的定义
    //本函数调整 H.r[s] 的关键字
    //使 H.r[s...m] 成为一个大顶堆
    RecType rc = H->r[s];               //将 H.r[s] 的记录赋给临时变量
    for (int j = 2 * s; j <= m; j *= 2) //沿 key 较大的子节点向下筛选
    {                                   //从左子树(2s)开始
        if (j < m && (H->r[j].key < H->r[j + 1].key))
        { //若左子树小于右子树则移动到右子树
            ++j;
        }
        if (rc.key >= H->r[j].key)
        { //若 H.r[s] 的值大于等于左/右子树中的较大数
            break;
        }
        H->r[s] = H->r[j];
        s = j;
    }
    H->r[s] = rc; //将 H.r[s] 插入位点
} //筛选大顶堆

void HeapSort(HeapType *H)
{
    //对顺序表H进行堆排序
    for (int i = H->length / 2; i > 0; i--) //此处为什么从中间开始?
    {                                       //因为最下面的叶子数是 length / 2 所以从倒数第二层开始
        HeapAdjust(H, i, H->length);        //把初始 H.r[1...H==.length] 建成大顶堆
    }
    printf("\n--- H in Heap Adjust for The First Time ---");
    PrintList(*H);
    for (int i = H->length; i > 1; i--)
    {
        RecType tmp = H->r[1]; //将堆顶元素和当前未经排序子序列 H.r[1...i] 中
        H->r[1] = H->r[i];     //最后一个元素相交换
        H->r[i] = tmp;
        HeapAdjust(H, 1, i - 1); //将 H.r[1...i-1] 重新调整为大顶堆
    }
    printf("\n--- H After Heap Sort ---");
    PrintList(*H);
} //堆排序

void Merge(RecType SR[], RecType *TR[], int i, int m, int n)
{
    //将有序的 SR[i...m] 和 SR[m+1...n] 归并为有序的 TR[i...n]
    int j, k, p;
    for (j = m + 1, k = i; i <= m && j <= n; ++k)
    { //将SR中记录由小到大的并入TR
        if (SR[i].key > SR[j].key)
            *TR[k] = SR[i++];
        else
            *TR[k] = SR[j++];
    }
    if (i <= m)
        for (; k <= n && i <= m; k++)
            *TR[k] = SR[i++];
    if (j <= n)
        for (; k <= n && j <= n; k++)
            *TR[k] = SR[j++];
} //合并相邻有序序列

void MSort(RecType SR[], RecType *TR1[], int s, int t)
{
    //将 SR[s...t] 归并排序为 TR1[s...t]
    RecType TR2[MAXSIZE + 1];
    if (s == t)
        *TR1[s] = SR[s];
    else
    {
        int mid = (s + t) / 2;      //将 SR[s...t] 平分为 SR[s...m] 和 SR[m+1...t]
        MSort(SR, TR2, s, mid);     //递归的将 SR[s...m] 归并为有序的 TR2[s...m]
        MSort(SR, TR2, mid + 1, t); //递归的将 SR[m+1...t] 归并为有序的 TR2[m+1...t]
        Merge(TR2, TR1, s, mid, t); //将 TR2[s...m] 和 TR2[m+1..t] 归并到 TR1[s...t]
    }
    PrintRecType(TR1);
} //递归形式的 2-路归并排序

void PrintList(SqList L)
{
    puts("\n");
    for (int i = 1; i <= MAXSIZE; i++)
    {
        printf("%d  ", L.r[i].key);
    }
    printf("\n");
} //输出顺序表

void PrintRecType(RecType *RT[])
{
    puts("\n");
    for (int i = 1; i <= MAXSIZE; i++)
    {
        printf("%d  ", RT[i]->key);
    }
    printf("\n");
} //输出 RecType 数组

void main()
{
    SqList L;
    L.length = MAXSIZE;
    int temp[MAXSIZE + 1] = {-1, 6, 7, 5, 18, 3, 9, 12, 14, 2, 21};

    for (int i = 0; i < MAXSIZE + 1; i++)
    {
        L.r[i].key = temp[i];
    }

    HeapSort(&L);
}
