#include <stdio.h>

/*****************数据类型定义*****************/

#define MAXSIZE 10    //顺序表的最大长度
typedef int KeyType;  //关键字类型为整数类型
typedef int InfoType; //其他数据为整数类型

typedef struct Info
{
    KeyType key;        //关键字项
    InfoType otherinfo; //其他数据项
} RedType;              //记录类型

typedef struct List
{
    RedType r[MAXSIZE + 1]; //r[0]闲置或用作哨兵单元
    int length;             //顺序表长度
} SqList;                   //顺序表类型

/*****************函数声明*****************/

void InsertSort(SqList *L); //插入排序

void BInsertSort(SqList *L); //折半插入排序

void ShellInsert(SqList *L, int dk);          //单趟希尔插入排序
void ShellSort(SqList *L, int dlta[], int t); //希尔排序

int Paritition(SqList *L, int low, int high); //标准分割函数
void QuickSort(SqList *L, int low, int high); //快速排序

void PrintList(SqList L); //输出顺序表

/*****************函数定义*****************/

void InsertSort(SqList *L)
{
    //对顺序表L做直接插入排序
    int i, j;
    for (i = 2; i < L->length; i++) //r[0]为哨兵单元
    {
        if (L->r[i].key < L->r[i - 1].key)
        {                          //若要插入的元素比其前一位元素小
            L->r[0] = L->r[i];     //将要插入的元素复制为哨兵
            L->r[i] = L->r[i - 1]; //将其前一位元素后移

            for (j = i - 2; L->r[0].key < L->r[j].key; --j)
            {
                L->r[j + 1] = L->r[j]; //记录后移
            }
            L->r[j + 1] = L->r[0]; //插入到正确位置
        }
        printf("\n--- L at the %d turn of InsertSort ---", i - 1);
        PrintList(*L);
    }
} //插入排序

void BInsertSort(SqList *L)
{
    //对顺序表L做折半插入排序
    int i, j;
    int low, high, mid;
    for (i = 2; i < L->length; ++i)
    {
        L->r[0] = L->r[i]; //将L.r[i]暂存到L.r[0]
        low = 1;
        high = i - 1; //高位是要插入元素的前一位
        while (low <= high)
        {
            mid = (low + high) / 2; //折半
            if (L->r[0].key < L->r[mid].key)
                high = mid - 1; //插入点在低半区
            else
                low = mid + 1; //插入点在高半区
        }
        for (j = i - 1; j >= high + 1; --j)
        {                          //为什么此处用*high*做界限？
            L->r[j + 1] = L->r[j]; //记录后移
        }
        L->r[high + 1] = L->r[0]; //插入

        printf("\n--- L at the %d turn of BInsertSort ---", i - 1);
        PrintList(*L);
    }
} //折半插入排序

void ShellInsert(SqList *L, int dk)
{
    //对顺序表L做 *一趟* 希尔插入排序
    //前后记录位置的增量是 dk 而不是 1
    //r[0]只是暂存单元，不是哨兵，当 j<=0 时，插入位置已找到
    int i, j;
    for (i = dk + 1; i < L->length; ++i)
    {
        if (L->r[i].key < L->r[i - dk].key)
        {                      //需将r[i]插入有序增量子表
            L->r[0] = L->r[i]; //暂存在r[0]
            for (j = i - dk; j > 0 && (L->r[0].key < L->r[j].key); j -= dk)
            {
                L->r[j + dk] = L->r[j]; //记录后移，空出插入位置
            }
            L->r[j + dk] = L->r[0]; //插入
        }
    }
} //单趟希尔插入排序

void ShellSort(SqList *L, int dlta[], int t)
{
    //按增量dlta[0...t-1]顺序对顺序表L做希尔排序
    for (int i = 0; i < t; ++i)
    {
        ShellInsert(L, dlta[i]); //一趟增量为dlta[k]的希尔排序

        printf("\n--- L at the %d turn of ShellSort with Delta = %d ---", i, dlta[i]);
        PrintList(*L);
    }
} //希尔排序

int Paritition(SqList *L, int low, int high)
{                              //分割函数
    L->r[0] = L->r[low];       //用子表的第一个元素做枢轴记录
    int pivot = L->r[low].key; //记录枢轴关键字
    while (low < high)         //从子表两端交替向中间扫描
    {
        while (low < high && L->r[high].key >= pivot)
        {
            --high;
        }
        L->r[low] = L->r[high]; //将比枢轴记录小的记录移到低端
        while (low < high && L->r[low].key <= pivot)
        {
            ++low;
        }
        L->r[high] = L->r[low]; //将比枢轴记录大的记录移到高端
    }
    L->r[low].key = L->r[0].key; //枢轴记录到位
    return low;                  //返回枢轴位置
} //标准分割函数

void QuickSort(SqList *L, int low, int high)
{ //对顺序表中的子序列L.r[low...high]快速排序
    int pivotloc;
    if (low < high)
    {                                        //长度大于1
        pivotloc = Paritition(L, low, high); //将L.r[low...high]一分为二

        printf("\n--- L of QuickSort with PivotLoc = %d ---", pivotloc);
        PrintList(*L);

        QuickSort(L, low, pivotloc - 1);  //对低子表递归排序
        QuickSort(L, pivotloc + 1, high); //对高子表递归排序
    }
} //快速排序

void PrintList(SqList L)
{
    puts("\n");
    for (int i = 1; i < MAXSIZE + 1; i++)
    {
        printf("%d  ", L.r[i].key);
    }
    printf("\n");
} //输出顺序表

void main()
{
    SqList L;
    L.length = MAXSIZE + 1;
    int temp[MAXSIZE + 1] = {-1, 5, 19, 21, 8, 13, 2, 37, 45, 10, 6};

    int dlta[4] = {5, 3, 2, 1};
    int t = 4;

    for (int i = 0; i < MAXSIZE + 1; i++)
    {
        L.r[i].key = temp[i];
    }

    int choice = 0;
    printf("\n*********************************");
    PrintList(L);
    printf("Which Algorithm?\n");
    printf("1.Insert Sort\n");
    printf("2.Binary Insert Sort\n");
    printf("3.Shell Sort\n");
    printf("4.Quick Sort\n");
    printf("*********************************\n");

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        InsertSort(&L);
        break;

    case 2:
        BInsertSort(&L);
        break;

    case 3:
        ShellSort(&L, dlta, t);
        break;

    case 4:
        QuickSort(&L, 0, MAXSIZE);  //注意此处 high 的值
        break;

    default:
        break;
    }
}
