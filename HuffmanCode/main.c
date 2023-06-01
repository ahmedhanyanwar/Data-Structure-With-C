#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_TREE_HT 1000

/* Huffman code encoding and decoding */
// Doing this implementation using priority queue & binary tree
// I implement queue using linked list

// nodeQ is the Huffman node which contain the character and frequency of it
struct nodeQ{
    char character;
    int frequency;
    struct nodeQ *left,*right;
    struct nodeQ *next;
};
typedef struct nodeQ huffmanNode;
huffmanNode *header = NULL;


void enqueue(char ,int ,huffmanNode *,huffmanNode *);  //o[n]
huffmanNode *dequeue();    //o[1]

void charAndFreq(char arr[]);//o[n^2] can improve it using sort

huffmanNode *coding();//o[n];
void decoding(char arr[],huffmanNode *root);//o[n]

void printArray(int arr[], int n);

void printHCodes(huffmanNode *root, int arr[], int top);
int isLeaf(huffmanNode *root);

int main()
{
    int arr[MAX_TREE_HT], top = 0;
    char firstString[10000],secoundString[10000];
    huffmanNode *root; // Tree node

    printf("Enter letter you want to get letter code from : \n");
    // using gets() not scanf() to take all phrase including white space
    gets(firstString);

    charAndFreq(firstString); // Know frequency of each letter in the letter
    root=coding();// coding function which use tree

    printf("\nHuffman code table :\n");
    printf("--------------------------\n");
    printHCodes(root, arr, top);
    printf("--------------------------\n");

    printf("Enter code which you want to decode : \n");
    gets(secoundString);

    decoding(secoundString,root);
    return 0;
}

// Enqueue of priority queue (note: we push the tree node into the queue)
void enqueue(char value,int frequency,huffmanNode *left,huffmanNode *right)
{
    huffmanNode *temp,*q;

    temp =(huffmanNode*)malloc(sizeof(huffmanNode));
    temp->character = value;
    temp->frequency = frequency;
    temp->left=left;
    temp->right=right;

    // header at first = Null
    // we say [value >header->character ] because we take the letter which has high ASCII value first
    if(header == NULL || frequency < header->frequency||((frequency == header->frequency)&& value >header->character))
    {
        temp->next = header;
        header = temp;
    }
    else
    {
        q = header;
        // using this while to to reach to the proper position to put letter in it
        while((q->next != NULL)&&((q->next->frequency < frequency)||((q->next->frequency == frequency)&& q->next->character >= value) ))
            q=q->next;

        temp->next = q->next;
        q->next = temp;
    }
}

// Dequeue which return the subtree root
huffmanNode *dequeue()
{
    huffmanNode *temp;
    temp = header;
    header = header->next;
    return temp;
}

// Know frequency of each letter in the letter
void charAndFreq(char arr[])
{
    int i,j,sizeOfString = strlen(arr);
    int freq=0;

    for(i=0;i<sizeOfString;i++)
    {
        for(j=i+1;j<sizeOfString;j++)
        {
            if(arr[j]==arr[i]&&arr[j]!='!')
            {
                freq++;
                arr[j]='!'; // because it has a low ASCII value
            }
        }
        if(arr[i]!='!') //using priority queue to take lowest freq and high ASCII value first
        {
            enqueue(arr[i],freq+1,NULL,NULL);
            freq=0;
        }
    }
}

// implement tree which leaf contain Huffman node
huffmanNode *coding()
{
    huffmanNode *min1,*min2;
    while(header->next!=NULL)
    {
        min1=dequeue();
        min2=dequeue();
        enqueue('\0',min1->frequency+ min2->frequency,min1,min2); // Null has 0 ASCII value
    }

    return dequeue();
}

// turn code into letter using binary tree
void decoding(char arr[],huffmanNode *root)
{
    int i=0;
    huffmanNode *head=root;

    while(arr[i]!='\0')
    {
        if(arr[i]=='0')
            head=head->left;
        else
            head=head->right;

        if(head->left==NULL&&head->right==NULL)
        {
            printf("%c",head->character);
            head=root;
        }
        i++;
    }
}

// Recursive function to print code of each character
void printHCodes(huffmanNode *root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printHCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printHCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {
        printf("|  %c   | ", root->character);
        printArray(arr, top);
    }
}

// Print the array
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

// Boolean function to check if the word is leaf or not because all Huffman letter is a leaf node
int isLeaf(huffmanNode *root)
{
    return !(root->left) && !(root->right);
}
