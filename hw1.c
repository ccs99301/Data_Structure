#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10],arr1[100],arr2[100];
}database;
database table[50];
int big_cmp(int *num1,int *num2)
{
    int cmp=0,i=0;
    for(i=199;i>=0&&num1[i]==0&&num2[i]==0;i--)
    while(cmp==0&&i>=0)
    {
        if(num1[i]>num2[i])
            cmp=1;
        else if(num1[i]<num2[i])
            cmp=2;
        else
            i--;
    }
    return cmp;
}
void big_add(int *num1,int *num2,int *ans)
{
    int i=0;
    for(i=0;i<200;i++)
        ans[i]=0;
    for(i=0;i<200;i++)
    {
        ans[i]=num1[i]+num2[i];
        if(ans[i]>9)
        {
            ans[i]-=10;
            ans[i+1]+=1;
        }
    }
}
void big_cut(int *num1,int *num2,int *ans)
{
    int i=0,cmp=big_cmp(num1,num2);
    for(i=0;i<200;i++)
        ans[i]=0;
    if(cmp==1)
    {
        for(i=0;i<200;i++)
        {
            if(num1[i]<num2[i])
            {
                ans[i]=num1[i]-num2[i]+10;
                num1[i+1]-=1;
            }
            else
                ans[i]=num1[i]-num2[i];
        }
    }
    else if(cmp==2)
    {
        for(i=0;i<200;i++)
        {
            if(num2[i]<num1[i])
            {
                ans[i]=num2[i]-num1[i]+10;
                num2[i+1]-=1;
            }
            else
                ans[i]=num2[i]-num1[i];
        }
        for(i=199;i>=0;i--)
            if(ans[i]!=0)
            {
                ans[i]*=(-1);
                break;
            }
    }
}
void big_mul(int *num1,int *num2,int *ans)
{
    int i=0,j=0,shift=0;
    for(i=0;i<200;i++)
        ans[i]=0;
    for(i=0;i<200;i++)
        for(j=0;i+j<200;j++)
        {
            ans[i+j]+=num1[i]*num2[j];
            ans[i+j]+=shift;
            shift=ans[i+j]/10;
            ans[i+j]%=10;
        }
}
void big_div(int *num1,int *num2,int *ans,int *rem)
{
    int i=0,tmp[200],cmp=big_cmp(num1,num2);
    for(i=0;i<200;i++)
    {
        ans[i]=0;
        rem[i]=0;
        tmp[i]=num1[i];
    }
    cmp=big_cmp(tmp,num2);
    if(cmp==2)
        for(i=0;i<200;i++)
            rem[i]=num2[i];
    else
    {
        for(i=0;i<200;i++)
            rem[i]=num1[i];
        while(cmp!=2)
        {
            big_cut(rem,num2,tmp);
            cmp=big_cmp(tmp,num2);
            ans[0]+=1;
            for(i=0;i<200;i++)
            {
                if(ans[i]>9)
                {
                    ans[i]-=10;
                    ans[i+1]+=1;
                }
                rem[i]=tmp[i];
            }
        }
    }
}
int main()
{
    int num1[200],num2[200],big[200],rem[200],len=0,i=0,j=0,k=0,last=0,option=0,read=0;
    char str[200],fname[50],data[200];
    FILE *fp,*fpr=fopen("result.txt","a");
    for(i=0;i<200;i++)
    {
        num1[i]=0;
        num2[i]=0;
        big[i]=0;
    }
    while(1)
    {
        printf("What do you want to do?\n\n");
        printf("\t1) Read numbers from a file.\n\t2) Show the input numbers\n\t3) Write numbers to a file\n\t4) Calculate the big numbers\n\t0) Exit\n\n> ");
        scanf("%d",&option);
        if(option==1)
        {
            printf("Please input the file name:");
            scanf("%s",fname);
            fp=fopen(fname,"a");
            if(fp!=NULL)
            {
                printf("%s reads successfully\n",fname);
                fscanf(fp,"%s");
                while(!feof(fp))
                {
                    fscanf(fp,"%s",data);
                    for(i=0;data[i]!=',';i++)
                        table[last].id[i]=data[i];
                    i++;
                    for(j=0;data[i]!=',';j++)
                        table[last].arr1[j]=data[i++];
                    i++;
                    for(j=0;data[i]!='\0';j++)
                        table[last].arr2[j]=data[i++];
                    last++;
                }
                read=1;
            }
        }
        else if(option==2)
        {
            printf("Here is your records\n\n");
            for(i=0;i<last-1;i++)
            {
                printf("No.%d:",i);
                len=strlen(table[i].arr1);
                if(len==1)
                    printf("%c.00E+000 , ",table[i].arr1[0]);
                else if(len==2)
                    printf("%c.%c0E+001 , ",table[i].arr1[0],table[i].arr1[1]);
                else if(len>2&&len<10)
                    printf("%c.%c%cE+00%d , ",table[i].arr1[0],table[i].arr1[1],table[i].arr1[2],len-1);
                else if(len<100)
                    printf("%c.%c%cE+0%d , ",table[i].arr1[0],table[i].arr1[1],table[i].arr1[2],len-1);
                else
                    printf("%c.%c%cE+%d , ",table[i].arr1[0],table[i].arr1[1],table[i].arr1[2],len-1);
                len=strlen(table[i].arr2);
                if(len==1)
                    printf("%c.00E+000\n",table[i].arr2[0]);
                else if(len==2)
                    printf("%c.%c0E+001\n",table[i].arr2[0],table[i].arr2[1]);
                else if(len>2&&len<10)
                    printf("%c.%c%cE+00%d\n",table[i].arr2[0],table[i].arr2[1],table[i].arr2[2],len-1);
                else if(len<100)
                    printf("%c.%c%cE+0%d\n",table[i].arr2[0],table[i].arr2[1],table[i].arr2[2],len-1);
                else
                    printf("%c.%c%cE+%d\n",table[i].arr2[0],table[i].arr2[1],table[i].arr2[2],len-1);
            }
        }
        else if(option==3)
        {
            printf("No.%d\n",last);
            printf("Number1:");
            scanf("%s",table[last-1].arr1);
            printf("Number2:");
            scanf("%s",table[last-1].arr2);
            sprintf(table[last-1].id,"%d",last);
            fprintf(fp,"%s",table[last-1].id);
            fprintf(fp,"%s",table[last-1].arr1);
            fprintf(fp,"%s\n",table[last-1].arr2);
            last++;
        }
        else if(option==4)
        {
            while(1)
            {
                printf("=============================================\n=                                           =\n");
                printf("= Which operators do you want to choose?    =\n");
                printf("= (+) Addition                              =\n");
                printf("= (-) Subtraction                           =\n");
                printf("= (*) Multiplication                        =\n");
                printf("= (/) Division                              =\n");
                printf("= (q) Quit                                  =\n");
                printf("=                                           =\n=============================================\n");
                scanf("%c",&option);
                if(option=='+')
                {
                    while(1)
                    {
                        printf("=============================================\n=                                           =\n");
                        printf("= Which item do you want to choose?         =\n");
                        printf("= (1) Load the existing numbers by ID       =\n");
                        printf("= (2) Input two numbers to calculate        =\n");
                        printf("= (0) Quit                                  =\n");
                        printf("=                                           =\n=============================================\n");
                        scanf("%d",&option);
                        if(option==1)
                        {
                            if(read==0)
                            {
                                printf("Must read csv file first!\n");
                                break;
                            }
                            printf("What index do you want to read ? ");
                            scanf("%d",&i);
                            printf("First number  :%s\nSecond number :%s\n",table[i].arr1,table[i].arr2);
                            len=strlen(table[i].arr1);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=table[i].arr1[j]-'0';
                            len=strlen(table[i].arr2);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=table[i].arr2[j]-'0';
                            big_add(num1,num2,big);
                            printf("\tSum : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("\n");
                            break;
                        }
                        else if(option==2)
                        {
                            printf("First number  :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=str[j]-'0';
                            printf("Second number :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=str[j]-'0';
                            big_add(num1,num2,big);
                            printf("\tSum : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("\n");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        fprintf(fpr,"%d",big[j]);
                                        j--;
                                    }
                            fprintf(fpr,"\n");
                            break;
                        }
                        else if(option==0)
                            break;
                    }
                }
                else if(option=='-')
                {
                    while(1)
                    {
                        printf("=============================================\n=                                           =\n");
                        printf("= Which item do you want to choose?         =\n");
                        printf("= (1) Load the existing numbers by ID       =\n");
                        printf("= (2) Input two numbers to calculate        =\n");
                        printf("= (0) Quit                                  =\n");
                        printf("=                                           =\n=============================================\n");
                        scanf("%d",&option);
                        if(option==1)
                        {
                            if(read==0)
                            {
                                printf("Must read csv file first!\n");
                                break;
                            }
                            printf("What index do you want to read ? ");
                            scanf("%d",&i);
                            printf("First number  :%s\nSecond number :%s\n",table[i].arr1,table[i].arr2);
                            len=strlen(table[i].arr1);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=table[i].arr1[j]-'0';
                            len=strlen(table[i].arr2);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=table[i].arr2[j]-'0';
                            big_cut(num1,num2,big);
                            printf("\tDifference : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("\n");
                            break;
                        }
                        else if(option==2)
                        {
                            printf("First number  :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=str[j]-'0';
                            printf("Second number :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=str[j]-'0';
                            big_cut(num1,num2,big);
                            printf("\tDifference : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("\n");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        fprintf(fpr,"%d",big[j]);
                                        j--;
                                    }
                            fprintf(fpr,"\n");
                            break;
                        }
                        else if(option==0)
                            break;
                    }
                }
                else if(option=='*')
                {
                    while(1)
                    {
                        printf("=============================================\n=                                           =\n");
                        printf("= Which item do you want to choose?         =\n");
                        printf("= (1) Load the existing numbers by ID       =\n");
                        printf("= (2) Input two numbers to calculate        =\n");
                        printf("= (0) Quit                                  =\n");
                        printf("=                                           =\n=============================================\n");
                        scanf("%d",&option);
                        if(option==1)
                        {
                            if(read==0)
                            {
                                printf("Must read csv file first!\n");
                                break;
                            }
                            printf("What index do you want to read ? ");
                            scanf("%d",&i);
                            printf("First number  :%s\nSecond number :%s\n",table[i].arr1,table[i].arr2);
                            len=strlen(table[i].arr1);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=table[i].arr1[j]-'0';
                            len=strlen(table[i].arr2);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=table[i].arr2[j]-'0';
                            big_mul(num1,num2,big);
                            printf("\tProduct : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("\n");
                            break;
                        }
                        else if(option==2)
                        {
                            printf("First number  :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=str[j]-'0';
                            printf("Second number :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=str[j]-'0';
                            big_mul(num1,num2,big);
                            printf("\tProduct : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("\n");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        fprintf(fpr,"%d",big[j]);
                                        j--;
                                    }
                            fprintf(fpr,"\n");
                            break;
                        }
                        else if(option==0)
                            break;
                    }
                }
                else if(option=='/')
                {
                    while(1)
                    {
                        printf("=============================================\n=                                           =\n");
                        printf("= Which item do you want to choose?         =\n");
                        printf("= (1) Load the existing numbers by ID       =\n");
                        printf("= (2) Input two numbers to calculate        =\n");
                        printf("= (0) Quit                                  =\n");
                        printf("=                                           =\n=============================================\n");
                        scanf("%d",&option);
                        if(option==1)
                        {
                            if(read==0)
                            {
                                printf("Must read csv file first!\n");
                                break;
                            }
                            printf("What index do you want to read ? ");
                            scanf("%d",&i);
                            printf("First number  :%s\nSecond number :%s\n",table[i].arr1,table[i].arr2);
                            len=strlen(table[i].arr1);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=table[i].arr1[j]-'0';
                            len=strlen(table[i].arr2);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=table[i].arr2[j]-'0';
                            big_div(num1,num2,big,rem);
                            printf("\tQuotient : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("......");
                            for(j=199;j>=0;j--)
                                if(rem[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",rem[j]);
                                        j--;
                                    }
                            printf("\n");
                            break;
                        }
                        else if(option==2)
                        {
                            printf("First number  :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num1[len-j-1]=str[j]-'0';
                            printf("Second number :");
                            scanf("%s",str);
                            len=strlen(str);
                            for(j=len-1;j>=0;j--)
                                num2[len-j-1]=str[j]-'0';
                            big_div(num1,num2,big,rem);
                            printf("\tQuotient : ");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",big[j]);
                                        j--;
                                    }
                            printf("......");
                            for(j=199;j>=0;j--)
                                if(rem[j]!=0)
                                    while(j>=0)
                                    {
                                        printf("%d",rem[j]);
                                        j--;
                                    }
                            printf("\n");
                            for(j=199;j>=0;j--)
                                if(big[j]!=0)
                                    while(j>=0)
                                    {
                                        fprintf(fpr,"%d",big[j]);
                                        j--;
                                    }
                            fprintf(fpr,"......");
                            for(j=199;j>=0;j--)
                                if(rem[j]!=0)
                                    while(j>=0)
                                    {
                                        fprintf(fpr,"%d",rem[j]);
                                        j--;
                                    }
                            fprintf(fpr,"\n");
                            break;
                        }
                        else if(option==0)
                            break;
                    }
                }
                else if(option=='q')
                    break;
            }
            for(i=0;i<200;i++)
                big[i]=0;
        }
        else if(option==0)
            break;
    }
    return 0;
}
