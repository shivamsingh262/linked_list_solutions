#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
}*start;


void create(int val)
{
    struct Node *tmp;
    struct Node *q;
    tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->data = val;
    tmp->next = NULL;
    if(start==NULL)
    start = tmp;
    else
    {
        q = start;
        while(q->next!=NULL)
        {
            q = q->next;
        }
        q->next = tmp;
    }
}

void display(struct Node *st)
{
    struct Node *q;
    q = st;
    printf("\n");
    while(q!=NULL)
    {
        printf("%d ",q->data);
        q = q->next;
    }
}

void add_begin(struct Node **start,int val)
{
    struct Node *tmp;
    tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->data = val;
    tmp->next = *start;
    *start = tmp;
}

void add_end(int val)
{
    struct Node *tmp;
    tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->data = val;
    tmp->next = NULL;
    struct Node *q;
    q = start;
    while(q->next!=NULL)
    {
        q = q->next;
    }
    q->next = tmp;
}

void add_pos(int val,int pos)
{
    struct Node *tmp;
    tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->data = val;
    tmp->next = NULL;
    struct Node *q;
    q = start;
    int count = 1;
    while(count<pos)
    {
        count++;
        q = q->next;
    }
    tmp->next = q->next;
    q->next = tmp;
}

void del(int val)
{
    if (start->data == val)
    start = start->next;
    else
    {
        struct Node *q,*tmp;
        q = start;
        while(q->next->next!=NULL)
        {
            if(q->next->data==val)
            {
                tmp = q->next;
                q->next = tmp->next;
                free(tmp);
            }
            q = q->next;
        }
        if (q->next->data == val)
        {
            tmp = q->next;
            q->next = NULL;
            free(tmp);
        }
    }
}

void reverse()
{
    struct Node *p1,*p2,*p3;
    p1 = start;
    p2 = p1->next;
    p3 = p2->next;
    p1->next = NULL;
    p2->next = p1;
    while(p3!=NULL)
    {
        p1 = p2;
        p2 = p3;
        p3 = p3->next;
        p2->next = p1;
    }
    start = p2;
}
void display_even()
{
    int i = 1; //0 for odd
    struct Node *q;
    q = start;
    printf("\n");
    while(q!=NULL)
    {
        if(i%2==0)
        printf("%d ",q->data);
        q = q->next;
        i++;
    }
}
int count()
{
    int c = 0;
    struct Node *q;
    q = start;
    while(q!=NULL)
    {
        c++;
        q = q->next;
    }
    printf("\nCount: %d",c);
    return c;
}
int getN(int n)
{
    int c = 0;
    struct Node *q;
    q = start;
    while(q!=NULL)
    {
        c++;
        if(c==n)
        {
            printf("\n%drd item is %d",n,q->data);
            return q->data;
            break;
        }
        q = q->next;
    }
}
void sortedInsert(struct Node **st,int val)
{
    struct Node *q;
    q = *st;
    struct Node *tmp;
    tmp = (struct Node *)malloc(sizeof(struct Node));
    tmp->data = val;
    tmp->next = NULL;
    if (*st==NULL||(*st)->data>val)
    {
        tmp->next = *st;
        *st = tmp;
    }
    else
    {
        while(q->next!=NULL && q->next->data<val)
        q = q->next;
        tmp->next = q->next;
        q->next = tmp;
    }
}
void insertSort()
{
    struct Node *q;
    struct Node *res = NULL;
    struct Node *tmp;
    q = start;
    while(q!=NULL)
    {
       sortedInsert(&res,q->data);
       q = q->next;
    }
    start = res;
}
void append(struct Node **a,struct Node **b)//add b to end of a
{
    if (*a==NULL)
    *a = *b;
    else
    {
        struct Node *q;
        q = *a;
        while(q->next!=NULL)
        q = q->next;
        q->next = *b;
        *b = NULL;
    }
}
void frontBackSplit(struct Node *start,struct Node **ff,struct Node **bb)//split in 2 by half
{
    struct Node *a = start;
    struct Node *b = start->next;
    while(b!=NULL)
    {
        b = b->next;
        if(b!=NULL)
        {
            a = a->next;
            b = b->next;
        }
    }
    *ff = start;
    *bb = a->next;
    a->next = NULL;
}
void remDuplicates() //for sorted node remove adjacent node else use two loops
{
    //for O(n) try hash table
    int arr[100];
    struct Node *q,*p;
    q = start;
    p = start->next;
    arr[q->data] = q->data;//add in hash table
    while(q->next!=NULL)
    {
        if (arr[p->data]==p->data)//remove from hash table
        {
            q->next = p->next;
            struct Node *tmp = p->next;
            free(p);
            p = tmp;
        }
        else
        {
            arr[p->data] = p->data;
            q = p;
            p = p->next;
        }

    }

}
void moveNode(struct Node **b,struct Node **a)//move 1st from a and make it 1st of b
{
    struct Node *q = *a;
    *a = (*a)->next;
    q->next = *b;
    *b = q;
}
void alternateSplit(struct Node **a, struct Node **b)
{
    struct Node *q;
    q = start;
    struct Node dda,ddb;
    struct Node *da,*db;
    da = &dda;
    db = &ddb;
    dda.next = NULL;
    ddb.next = NULL;
    while(q!=NULL)
    {
        moveNode(&(da->next),&q);
        da = da->next;
        if(q!=NULL)
        {
            moveNode(&(db->next),&q);
            db = db->next;
        }
    }
    *a = dda.next;
    *b = ddb.next;
}
struct Node* shuffleMerge(struct Node *a, struct Node *b)
{
    struct Node *q = start;
    struct Node dd;
    struct Node *tmp = &dd;
    dd.next = NULL;
    while(1)
    {
        if(a==NULL){
            tmp->next = b;
            break;
        }
        else if(b==NULL){
            tmp->next = a;
            break;
        }
        else {
            moveNode(&(tmp->next),&a);
            tmp = tmp->next;
            moveNode(&(tmp->next),&b);
            tmp = tmp->next;
        }
    }
    return dd.next;
}
struct Node* sortedMerge(struct Node *a,struct Node *b)
{
    struct Node *q = start;
    struct Node dd;
    struct Node *tmp = &dd;
    dd.next = NULL;
    while(1)
    {
        if(a==NULL){
            tmp->next = b;
            break;
        }
        else if(b==NULL){
            tmp->next = a;
            break;
        }
        else
        {
            if(a->data<b->data)
            {
                moveNode(&(tmp->next),&a);
                tmp = tmp->next;
            }
            else if(b->data<a->data)
            {
                moveNode(&(tmp->next),&b);
                tmp = tmp->next;
            }
            else
            {
                moveNode(&(tmp->next),&a);
                tmp = tmp->next;
                moveNode(&(tmp->next),&b);
                tmp = tmp->next;
            }
        }
    }
    return dd.next;
}
void mergeSort(struct Node **st)
{
    struct Node *q = *st;
    struct Node *a;
    struct Node *b;
    if ((q==NULL)||(q->next==NULL))
    return;
    frontBackSplit(q,&a,&b);
    mergeSort(&a);
    mergeSort(&b);
    *st = sortedMerge(a,b);
}
struct Node* sortedIntersect(struct Node *a,struct Node *b)
{
    struct Node *tmp;
    struct Node dd;
    tmp = &dd;
    dd.next = NULL;
    while (a!= NULL && b!= NULL)
    {
        if(a->data == b->data)
        {
            add_begin(&(tmp->next),a->data);
            tmp = tmp->next;
            a = a->next;
            b = b->next;
        }
        else if (a->data<b->data)
        a=a->next;
        else
        b=b->next;
    }
    return dd.next;
}
void reverse2(struct Node **start)
{
    struct Node *tmp = *start;
    struct Node *res = NULL;
    while(tmp!= NULL)
    moveNode(&res,&tmp);
    *start = res;
}
struct Node* add_num(struct Node *a, struct Node *b)
{
    struct Node *res;
    int carry = 0,sum;
    while(a!=NULL&&b!=NULL)
    {
        sum = carry;
        if(a==NULL)
        {
            sum = sum + b->data;
            b = b->next;
        }
        else if(b==NULL)
        {
            sum = sum + a->data;
            a = a->next;
        }
        else
        {
            sum = sum + a->data + b->data;
            if(sum>10)
            {
                carry = 1;
                sum = sum%10;
            }
            else
            carry = 0;
            struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
            tmp->data = sum;
            tmp->next = NULL;
            printf("%d",tmp->data);
            res = tmp;
            res = res->next;
            a = a->next;
            b = b->next;
        }
    }
    display(res);
}
main()
{
   create(1);
   create(2);
   create(3);
   //sortedInsert(5);
   //sortedInsert(start,25);
   //insertSort();
   struct Node *res = NULL;
   sortedInsert(&res,5);
   sortedInsert(&res,7);
   sortedInsert(&res,5);
   //append(&start,&res);
   //display(start);
   //insertSort();
   //display(start);
   //struct Node *a = NULL,*b = NULL;
   //frontBackSplit(&a,&b);
   //display(a);
   //display(b);
   //remDuplicates();
   //display(start);
   //alternateSplit(&a,&b);
   //display(a);
   //display(b);
   //moveNode(&a,&b);
   //a = sortedIntersect(start,res);
   //a = start;
   //mergeSort(&a);
   //display(a);
   //reverse2(&start);
   //display(start);
   add_num(start,res);
}
