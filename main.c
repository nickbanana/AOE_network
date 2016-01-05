#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 99

typedef struct activity
{
    int start;  //the starting node of this activity
    int end;    //the ending node of this activity
    int value;  //the working time of this activity
    int early;  //earliest time that this activity can occur
    int late;   //latest time that this activity can occur
    int slack;  //late-early   if slack==0 => critical path
} ACTIVITY;

typedef struct node
{
    int early;
    int late;
} NODE;


int raw[MAX][MAX];
ACTIVITY list[MAX];
NODE node_list[MAX];
int Node_count;
int Activity_count;

void read();
void reset();
void calculation();
void output();

int main()
{
    reset();
    read();
    calculation();
    output();
    return 0;
}

void reset()
{
    int i,j;
    Node_count=0;
    Activity_count=0;

    for(i=0;i<99;i++)
    {
        for(j=0;j<99;j++)
        {
            raw[i][j]=0;
        }
        list[i].start=0;
        list[i].end=0;
        list[i].early=0;
        list[i].late=0;
        list[i].slack=0;
        list[i].value=0;
        node_list[i].early=0;
        node_list[i].late=0;
    }
}

void read()
{
    int i,j;
    FILE *fptr;
    char fname[99];
    printf("Please enter filename(include .txt):");
    scanf("%s",&fname);
    fptr=fopen(fname,"r");
    fscanf(fptr,"%d", &Node_count);
    for(i=0;i<Node_count;i++)
    {
        for(j=0;j<Node_count;j++)
        {
            fscanf(fptr,"%d", &raw[i][j]);
            if(raw[i][j]!=0)
            {
                list[Activity_count].start=i;
                list[Activity_count].end=j;
                list[Activity_count].value=raw[i][j];
                Activity_count++;
            }
        }
    }
    fclose(fptr);

}

void calculation()
{
    int i,j,current_Act;
    current_Act=0;
    //first decide the early time table
    for(i=0;i<Node_count;i++)
    {
        for(j=0;j<Node_count;j++)   //scan through array
        {
            if(raw[i][j]!=0)
            {
                if(node_list[j].early<node_list[i].early+list[current_Act].value)
                {
                    node_list[j].early=node_list[i].early+list[current_Act].value;

                }
                list[current_Act].early=node_list[i].early;
                current_Act++;
            }
        }
    }

}

void output()
{
    int i,j;
    for(i=0;i<Node_count;i++)
    {
        printf("%d ",node_list[i].early);
    }
    printf("\n");
    for(i=0;i<Activity_count;i++)
    {
        printf("%d ",list[i].early);
    }
}
