#include <stdio.h>
#include <stdlib.h>

typedef struct treenode
{
    struct treenode *lnode;
    int key;
    int level;
    struct treenode *rnode;
}tnode;

tnode *insert(tnode *root,int num)
{
    int h=0;                           //current height
    tnode *tmp=root,*pre=NULL;
    if(root==NULL)
    {
        root=(tnode*)malloc(sizeof(tnode));
        root->key=num;
        root->level=0;
        root->lnode=NULL;
        root->rnode=NULL;               //create a new node
    }
    else
    {
        while(tmp!=NULL)
        {
            pre=tmp;
            if(tmp->key>num)
                tmp=tmp->lnode;
            else if(tmp->key<num)
                tmp=tmp->rnode;
            else
                return root;
            h++;                        //height will increase
        }
        if(pre->key>num)
        {
            pre->lnode=(tnode*)malloc(sizeof(tnode));
            pre->lnode->key=num;
            pre->lnode->level=h;
            pre->lnode->lnode=NULL;
            pre->lnode->rnode=NULL;
        }
        else
        {
            pre->rnode=(tnode*)malloc(sizeof(tnode));
            pre->rnode->key=num;
            pre->rnode->level=h;
            pre->rnode->lnode=NULL;
            pre->rnode->rnode=NULL;
        }
    }
    return root;
}
tnode *tdelete(tnode *root,int num)
{
    tnode *tmp=NULL,*del=root,*pre=NULL,*ptmp=NULL;     //tmp is the smallest right node
    if(root->key==num)                                  //the delete node is root
    {
        if(del->rnode!=NULL)                            //maybe right will have no node
        {
            tmp=root->rnode;
            while(tmp->lnode!=NULL)
            {
                ptmp=tmp;
                tmp=tmp->lnode;
            }
            if(del->rnode->lnode!=NULL)
                ptmp->lnode=NULL;
            tmp->lnode=del->lnode;
            while(tmp->rnode!=NULL)
                tmp=tmp->rnode;
            if(del->rnode!=tmp)
                tmp->rnode=del->rnode;
        }
        else if(del->lnode!=NULL)
        {
            tmp=root->lnode;
            while(tmp->rnode!=NULL)
            {
                ptmp=tmp;
                tmp=tmp->rnode;
            }
            if(del->lnode->rnode!=NULL)
                ptmp->rnode=NULL;
            while(tmp->lnode!=NULL)
                tmp=tmp->lnode;
            if(del->lnode!=tmp)
                tmp->lnode=del->lnode;
        }
        free(del);
        return tmp;
    }
    else                                    //others nodes deleted
    {
        while(del->key!=num&&del!=NULL)
        {
            pre=del;
            if(del->key>num)
                del=del->lnode;
            else
                del=del->rnode;
        }
        if(del!=NULL)
        {
            if(del->rnode!=NULL)
            {
                tmp=del->rnode;
                while(tmp->lnode!=NULL)
                {
                    ptmp=tmp;
                    tmp=tmp->lnode;
                }
                if(pre->key>num)
                    pre->lnode=tmp;
                else
                    pre->rnode=tmp;
                if(del->rnode->lnode!=NULL)
                    ptmp->lnode=NULL;
                tmp->lnode=del->lnode;
                while(tmp->rnode!=NULL)
                    tmp=tmp->rnode;
                if(del->rnode!=tmp)
                    tmp->rnode=del->rnode;
            }
            else if(del->lnode!=NULL)
            {
                tmp=del->lnode;
                while(tmp->rnode!=NULL)
                {
                    ptmp=tmp;
                    tmp=tmp->rnode;
                }
                if(pre->key>num)
                    pre->lnode=tmp;
                else
                    pre->rnode=tmp;
                if(del->lnode->rnode!=NULL)
                    ptmp->rnode=NULL;
                while(tmp->lnode!=NULL)
                    tmp=tmp->lnode;
                if(del->lnode!=tmp)
                    tmp->lnode=del->lnode;
            }
            else
            {
                if(pre->key>num)
                    pre->lnode=NULL;
                else
                    pre->rnode=NULL;
            }
            free(del);
        }
        else
            printf("error\n");              //there is no target node
    }
    return root;
}
void search(tnode *root,int num)
{
    tnode *tmp=root;
    while(tmp!=NULL)
    {
        if(tmp->key>num)
            tmp=tmp->lnode;
        else if(tmp->key<num)
            tmp=tmp->rnode;
        else
        {
            printf("%d is found.\n",num);
            return;
        }
    }
    printf("%d is not found.\n",num);
}
void infixorder(tnode *root)
{
    tnode *tmp=root;
    if(tmp!=NULL)
    {
        infixorder(tmp->lnode);
        printf("%d ",tmp->key);
        infixorder(tmp->rnode);
    }
}
void levelorder(tnode *root,int h)
{
    tnode *tmp=root;
    if(tmp!=NULL)
    {
        levelorder(tmp->lnode,h);
        if(tmp->level==h)                   //if it is the target level, it will be printed
            printf("%d ",tmp->key);
        levelorder(tmp->rnode,h);
    }
}
int main()
{
    int i=0,mode=0,input=0;
    tnode *root=NULL;
    while(1)
    {
        printf("Which feathers do you want?\n");
        printf("(1) Insert\n");
        printf("(2) Delete\n");
        printf("(3) Search\n");
        printf("(4) PrintInfixOrder\n");
        printf("(5) PrintLevelOrder\n");
        printf("(0) Exit\n");
        scanf("%d",&mode);
        if(mode==1)
        {
            printf("Insert a number: ");
            scanf("%d",&input);
            root=insert(root,input);
        }
        else if(mode==2)
        {
            printf("Delete a number: ");
            scanf("%d",&input);
            root=tdelete(root,input);
        }
        else if(mode==3)
        {
            printf("Search a number: ");
            scanf("%d",&input);
            search(root,input);
        }
        else if(mode==4)
        {
            infixorder(root);
            printf("\n");
        }
        else if(mode==5)
        {
            for(i=0;i<10;i++)
                levelorder(root,i);
            printf("\n");
        }
        else
            break;
    }
    return 0;
}
