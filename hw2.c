#include <stdio.h>
#include <stdlib.h>

int main()
{
    int chA[3]={1,3,5},chB[3]={2,4,6},foodA=0,foodB=0,cave[2]={0,0},i;
    FILE *fp=fopen("result.txt","w");
    for(i=0;i<200;i++)
    {
        if(cave[1]!=0)  //cave is full
        {
            if(cave[1]%2==1)    //cave1 is teamA
            {
                if(chA[1]==0)
                    chA[1]=cave[1];
                else
                    chA[2]=cave[1];
                foodA++;    //the mice stay 1 turn
            }
            else
            {
                if(chB[1]==0)
                    chB[1]=cave[1];
                else
                    chB[2]=cave[1];
                foodB++;
            }
            if(cave[0]%2==1)    //cave2 is teamA
            {
                chA[2]=cave[0];
                foodA+=2;   //the mice stay 2 turn
            }
            else
            {
                chB[2]=cave[0];
                foodB+=2;
            }
            cave[0]=0;
            cave[1]=0;
        }
        if(foodA<foodB)     //let mouse enter the cave
        {
            if(cave[0]==0)
                cave[0]=chA[0];
            else
                cave[1]=chA[0];
            chA[0]=chA[1];
            chA[1]=chA[2];
            chA[2]=0;   //let mouse go forward
        }
        else if(foodA>foodB)
        {
            if(cave[0]==0)
                cave[0]=chB[0];
            else
                cave[1]=chB[0];
            chB[0]=chB[1];
            chB[1]=chB[2];
            chB[2]=0;
        }
        else        //if two channel have same food, teamA will enter the cave before teamB
        {
            if(cave[0]==0)
            {
                cave[0]=chA[0];
                chA[0]=chA[1];
                chA[1]=chA[2];
                chA[2]=0;
            }
            else
            {
                cave[1]=chB[0];
                chB[0]=chB[1];
                chB[1]=chB[2];
                chB[2]=0;
            }
        }
        if(i==16||i==86||i==199)
        {
            fprintf(fp,"Round %d\n",i+1);
            fprintf(fp,"Channel A food: %d\n",foodA);
            fprintf(fp,"Channel B food: %d\n\n",foodB);
            fprintf(fp,"Cave:\n %d",cave[0]);
            if(cave[1]!=0)
                fprintf(fp," %d",cave[1]);
            fprintf(fp,"\n\nChannel A:\n %d",chA[0]);
            if(chA[1]!=0)
                fprintf(fp," %d",chA[1]);
            if(chA[2]!=0)
                fprintf(fp," %d",chA[2]);
            fprintf(fp,"\nChannel B:\n %d",chB[0]);
            if(chB[1]!=0)
                fprintf(fp," %d",chB[1]);
            if(chB[2]!=0)
                fprintf(fp," %d",chB[2]);
            fprintf(fp,"\n\n");
        }
    }
    return 0;
}
