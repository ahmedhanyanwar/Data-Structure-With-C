#include <stdio.h>
#include <stdlib.h>


// Implement cache memory using c based on key
// if storage is full and you need to put new key not existed which node will be deleted?

// Node of cache
typedef struct node dll;
struct node{
    int data;
    int key;
    dll *next;
    dll *prev;
};

// Queue node
struct FIFO{
    int count,size;
    dll *front;
    dll *rear;
};
typedef struct FIFO queue;

void creatQueue(queue *top);
void enqueueFirstNode(queue *top,int data,int key);
void enqueue(queue *top,int element,int key);
void isEmpty(queue *top);
void printQueue(queue *top);
void writeQu(queue *top);

void deleteNode(queue *top,dll *wantDelet);
void deleteFirst(queue *top);

void keyPrint(queue *top,int key);
dll *ifKeyExi(queue *top,int key);

int main()
{
    queue qu;
    dll *header;
    int number,numOfOperation,funUse,sizeOfCache;
    int key;

    creatQueue(&qu);
    // Taking size of cache and number of operation
    printf("Insert cache size :  ");
    scanf("%d",&sizeOfCache);

    printf("Insert number of operation :  ");
    scanf("%d",&numOfOperation);

    qu.size=sizeOfCache;

    if(sizeOfCache==0)
        printf("Error.\n");

    else{
    while(numOfOperation!=0)
    {
        printf("\nPress:\n1- To insert a new key and number.\n2- To print an number of existence key.\n3- To print all elements in a cache.\n");
        scanf("%d",&funUse);
        switch(funUse)
        {
            case 1:
                printf("Insert the key and the number : ");
                scanf("%d",&key);
                scanf("%d",&number);
                if(qu.count==0)
                    enqueueFirstNode(&qu,number,key);
                else
                {
                    header=ifKeyExi(&qu,key);
                    if(header==NULL)
                    {
                        if(sizeOfCache>qu.count)
                            enqueue(&qu,number,key);
                        else
                        {
                            deleteFirst(&qu);
                            enqueue(&qu,number,key);
                        }
                    }
                    else
                    {
                        header->data=number;
                        header->key=key;
                        deleteNode(&qu,header);
                    }
                }
                break;
            case 2:
                printf("Insert the key you want to print it's number : ");
                scanf("%d",&key);
                keyPrint(&qu,key);
                break;
            case 3:
                writeQu(&qu);
                break;
            default:
                continue;
        }
        numOfOperation--;
    }
    }


}

void creatQueue(queue *top)
{
    top->front = NULL;
    top->rear  = NULL;
    top-> count  = 0;
    top=NULL;
}

void enqueueFirstNode(queue *top,int data,int key)
{
    dll *firstNode;

    firstNode =(dll *)malloc(sizeof(dll));

    if(firstNode==NULL)
    {
        printf("error");
    }
    else
    {
        top->front=firstNode;
        firstNode->data=data;
        firstNode->key=key;
        firstNode->prev=NULL;
        firstNode->next = NULL;
        top->rear  = firstNode;
        top-> count ++;
    }
}

void enqueue(queue *top,int data,int key)
{
    dll *newNode,*temp;

    temp=top->front;
    newNode =(dll *)malloc(sizeof(dll));

    if( newNode ==NULL)
        printf("error");
    else{
        newNode->data=data;
        newNode->key=key;
        newNode->next=NULL;
        newNode->prev =top->rear;
        (top->rear)->next = newNode;
        top->rear=newNode;
        top->count++;
    }
}

void deleteNode(queue *top,dll *wantDelet)
{
    dll *toFree,*newNode;
    int data,key;

    if(wantDelet==NULL)
        printf("error");
    else if(wantDelet==top->front)
        top->front=(top->front)->next;
    else if(wantDelet==top->rear)
        top->rear =(top->rear)->prev;

    toFree=wantDelet;
    data=toFree->data;
    key=toFree->key;
    if(wantDelet->prev!=NULL)
        (toFree->prev)->next=toFree->next;

    if(wantDelet->next!=NULL)
        (toFree->next)->prev=toFree->prev;

    free(toFree);
    if(top->front==NULL)
        enqueueFirstNode(top,data,key);
    else
        enqueue(top,data,key);

    top->count--;
}

void deleteFirst(queue *top)
{
    dll *toFree,*header;
    header=top->front;

    if(top->front==NULL){
        printf("error");
    }
    else{
        top->front=(top->front)->next;
        free(header);
        top->count--;
    }
}

void keyPrint(queue *top,int key)
{
    dll *header;

    header=ifKeyExi(top,key);
    if(header==NULL)
        printf("Not found\n");
    else if(header!=NULL&&header!=top->rear)
    {
        printf("%d\n",header->data);
        deleteNode(top,header);
    }
    else
    {
        printf("%d\n",header->data);
    }
}


dll *ifKeyExi(queue *top,int key)
{
    dll *header=top->front;
    while(header!=NULL)
    {
        if(key==header->key)
        {
            return header;
        }
        header=header->next;
    }
    return NULL;
}

void writeQu(queue *top)
{
    dll *temp=top->front;
    printf("\nCache elements:\n");
    while(temp!=NULL)
    {
        printf("Key = %d and number = %d\n",temp->key,temp->data);
        temp=temp->next;
    }
}

