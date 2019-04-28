#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *next;
    struct node *prev;
}NODE;

NODE *add(NODE *first,int num)
{
    NODE *tmpnode=first,*newnode=NULL;
    if(first==NULL)                         //there is no number at first, so give it new space
    {
        first=(NODE*)malloc(sizeof(NODE));
        first->key=num;
        first->prev=NULL;
        first->next=NULL;
    }
    else if(first->prev==NULL)              //the second data. linked with the first node
    {
        newnode=(NODE*)malloc(sizeof(NODE));
        newnode->key=num;
        newnode->prev=newnode->next=first;
        first->prev=first->next=newnode;
    }
    else
    {
        tmpnode=tmpnode->prev;                  //let temp node be the first previous
        newnode=(NODE*)malloc(sizeof(NODE));    //so the new node will between temp node and first
        newnode->key=num;
        newnode->prev=tmpnode;
        newnode->next=first;
        tmpnode->next=newnode;
        first->prev=newnode;
    }
    return first;
}

NODE *del(NODE *delnode,int dir)
{
    NODE *prevnode=delnode->prev,*nextnode=delnode->next;
    prevnode->next=nextnode;                    //let previous node link with next node
    nextnode->prev=prevnode;
    free(delnode);                              //delete the node
    if(dir==1)
        return prevnode;
    else
        return nextnode;
}

int play(NODE *first,int dir,int skip)
{
    int i;
    NODE *tmpnode=first;
    while(tmpnode!=tmpnode->next)               //only left the temp node
    {
        for(i=0;i<skip-1;i++)
        {
            if(dir==1)
                tmpnode=tmpnode->prev;
            else
                tmpnode=tmpnode->next;
        }
        tmpnode=del(tmpnode,dir);
    }
    return tmpnode->key;
}

void list(NODE *first)
{
    NODE *tmpnode=first->next;
    printf("The persons in circular list are:\n%d",first->key);
    while(tmpnode!=first)
    {
        printf("   %d",tmpnode->key);
        tmpnode=tmpnode->next;
    }
    printf("\n");
}
int main()
{
    int item=0,skip=0,dir=0,num=0,total=0,last=0,i=1;
    FILE *fp=fopen("a.txt","r");
    NODE *first=NULL;
    printf("========================================\n");
    printf("=                                      =\n");
    printf("= Which items do you want to choose?   =\n");
    printf("= (1) Read numbers from a file.        =\n");
    printf("= (2) Input new numbers                =\n");
    printf("= (0) Quit                             =\n");
    printf("=                                      =\n");
    printf("========================================\n");
    scanf("%d",&item);
    if(item==1)
    {
        while(fscanf(fp,"%d,",&num)!=EOF)
        {
            printf("No.%d :%d\n",i,num);
            first=add(first,num);
            i++;
        }
    }
    else if(item==2)
    {
        printf("How many numbers do you want to add ?");
        scanf("%d",&total);
        for(i=1;i<=total;i++)
        {
            printf("No.%d :",i);
            scanf("%d",&num);
            first=add(first,num);
        }
    }
    else if(item==0)
        return 0;
    list(first);
    printf("Enter thr number of persons to be skipped: ");
    scanf("%d",&skip);
    printf("which direction do you want to choose ? (1)Left (2)Right\n");
    scanf("%d",&dir);
    last=play(first,dir,skip);
    printf("The person to survive is : %d\n",last);
    return 0;
}
