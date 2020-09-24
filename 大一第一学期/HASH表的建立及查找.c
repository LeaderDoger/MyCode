#include "base.h"
#define KEYLENGTH 13                   /* 关键词字符串的最大长度 */


typedef int ElementType; /* 关键词类型用字符串 */
typedef int Index;                     /* 散列地址类型 */
//单链表
typedef struct LNode* PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******** 以上是单链表的定义 ********/

typedef struct TblNode* HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    List Heads;    /* 指向链表头结点的数组 */
};

//创建散列表，散列表的大小最好为质数
HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = TableSize;

    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    /* 初始化表头结点 */
    for (i = 0; i < H->TableSize; i++) {
        H->Heads[i].Data = i;
        H->Heads[i].Next = NULL;
    }

    return H;
}

Index Hash(ElementType Key, int TableSize)
{
    return Key % TableSize;
}

Position Find(HashTable H, ElementType Key,int* count)
{
    Position P;
    Index Pos;
    
    *count = 1;
    Pos = Hash(Key, H->TableSize); /* 初始散列位置 */
    P = H->Heads[Pos].Next; /* 从该链表的第1个结点开始 */
    /* 当未到表尾，并且Key未找到时 */
    while (P && P->Data != Key) {
        P = P->Next;
        (*count)++;
    }
    return P; /* 此时P或者指向找到的结点，或者为NULL */
}

Status Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos,count;

    P = Find(H, Key,&count);
    if (!P) { /* 关键词未找到，可以插入 */
        NewCell = (Position)malloc(sizeof(struct LNode));
        NewCell->Data = Key;
        Pos = Hash(Key, H->TableSize); /* 初始散列位置 */
        /* 将NewCell插入为H->Heads[Pos]链表的第1个结点 */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return TRUE;
    }
    else { /* 关键词已存在 */
        printf("键值已存在\n");
        return FALSE;
    }
}

Status Delete(HashTable H, ElementType Key,int *count)
{
    Position q,p;
    Index Pos;

    *count = 1;
    Pos = Hash(Key, H->TableSize);
    q = H->Heads[Pos].Next;


    if (Key == q->Data) {
        H->Heads[Pos].Next = q->Next;
        free(q);
        return 1;
    }
    else {
        p = q->Next;
        while (p && p->Data != Key) {
            q = p;
            p = p->Next;
            (*count)++;
        }
        if (p) {
            q->Next = p->Next;
            free(p);
            return 1;
        }
        else return 0;
    }
}

void DestroyTable(HashTable H)
{
    int i;
    Position P, Tmp;

    /* 释放每个链表的结点 */
    for (i = 0; i < H->TableSize; i++) {
        P = H->Heads[i].Next;
        while (P) {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads); /* 释放头结点数组 */
    free(H);        /* 释放散列表结点 */
}



int main()
{
    int nums[50] = { 241,267,934,300,969,724,478,758,762,664,
        305,345,281,227,561,691,795,942,228,836,
        591,404,902,353,492,582,821,516,718,895,
        847,326,571,538,469,912,268,899,435,494,
        903,811,322,933,273,864,941,711,453,668 };
    HashTable H;
    int i,key,count;
    Position P;

    for (i = 0; i < 50; i++) {
        printf("%d",nums[i]);
        if (i % 5 == 4)printf("\n");
        else printf(",");
    }
    H = CreateTable(KEYLENGTH);
    for (i = 0; i < 50; i++)
        Insert(H, nums[i]);
    printf("请输入要查找的数字；");
    scanf("%d", &key);
    if (P = Find(H, key, &count))printf("键值已存在,查找次数为:%d\n", count);
    else printf("键值不存在\n");

    printf("请输入要删除的数字；");
    scanf("%d", &key);
    if (Delete(H, key, &count))printf("键值已删除,查找次数为:%d\n", count);
    else printf("键值不存在\n");
    DestroyTable(H);
}