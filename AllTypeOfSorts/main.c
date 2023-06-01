#include <stdio.h>
#include <stdlib.h>

void swap(int *,int *);
//Selection Sort
void selectionSort(int [],int );
//Bubble Sort
void bubbleSort(int [],int );
//Insertion Sort
void insertionSort(int [],int );
//Quick Sort Partition Sort
int partitionProcess(int [], int , int );
void quickSortPartition(int [], int , int );
//Merge Sort
void merge(int [], int , int , int );
void mergeSort(int [], int , int );
//Shell Sort
void shellSort(int [], int );
//Heap Sort
void heapify(int [],int ,int );
void buildHeap(int [],int );
void heapSort(int [],int );
//Read&write array
void readArray (int [],int );
void writeArray(int [],int );

int main()
{
    int sizeOfArray,*array,switchChose;

    printf("Enter size Of array : ");
    scanf("%d",&sizeOfArray);
    array =(int *)calloc(sizeOfArray,sizeof(int));


    printf("Enter %d elements of array : \n",sizeOfArray);
    readArray(array,sizeOfArray);
    printf("\n*************************************************************\n");
    printf("press 1 :for selection sort algorithm .\npress 2 :for bubble sort algorithm .\n");
    printf("press 3 :for insertion sort algorithm .\npress 4 :for quick sort algorithm .\n");
    printf("press 5 :for merge sort algorithm .\npress 6 :for shell sort algorithm .\n");
    printf("press 7 :for heap(tree) sort algorithm .\n");
    printf("Select sort algorithm : ");
    scanf("%d",&switchChose);
    printf("\n*************************************************************\n");
    switch(switchChose)
    {
        case 1:
            selectionSort(array,sizeOfArray);
            printf("The result of selection sort is : \n");
            break;
        case 2:
            bubbleSort(array,sizeOfArray);
            printf("The result of bubble sort is : \n");
            break;
        case 3:
            insertionSort(array,sizeOfArray);
            printf("The result of insertion sort is : \n");
            break;
        case 4:
            quickSortPartition(array, 0, sizeOfArray - 1);
            printf("The result of quick sort is : \n");
            break;
        case 5:
            mergeSort(array, 0, sizeOfArray-1);
            printf("The result of merge sort is : \n");
            break;
        case 6:
            shellSort(array,sizeOfArray);
            printf("The result of shell sort is : \n");
            break;
        case 7:
            heapSort(array,sizeOfArray);
            printf("The result of heap sort is : \n");
            break;
        default:
            printf("Error try again\n");
            exit(1);
            break;
    }

    writeArray(array,sizeOfArray);
    printf("*************************************************************\n");
    printf("\n**************************DONE*******************************\n");
    free(array);
    return 0;
}

void swap(int *x,int *y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y= temp;
}

/////////////      SELECTION SORT           ///////////////////////////
void selectionSort(int arr[],int size)
{
    int minPos =0,i,j,temp;
    for(i=0;i<size-1;i++)
    {
        minPos = i;
        for(j=i+1;j<size;j++)
        {
            if(arr[j]<arr[minPos])
                minPos = j;
        }
        swap(&arr[i],&arr[minPos]);
    }
}

/////////////      BUBBLE SORT           ///////////////////////////
void bubbleSort(int arr[],int size)
{
    int i,j,sortedCondation;

    for(i=0;i<size-1;i++)
    {
        sortedCondation = 0;
        for(j=0;j<size-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                sortedCondation = 1;
            }
        }
        if(sortedCondation==0)
            break;
    }
}

/////////////      INSERTION SORT           ///////////////////////////
void insertionSort(int arr[],int size)
{
    int hole,value,i;

    for(i=1;i<size;i++)
    {
        value = arr[i];
        hole = i;

        while(hole>0&&arr[hole-1]>value)
        {
            arr[hole]=arr[hole-1];
            hole --;
        }
        arr[hole] = value;
    }
}

/////////////      QUICK SORT           ///////////////////////////
int partitionProcess(int arr[] , int start, int end)
{
    int lastIndex,j;
    int pivot = arr[start];

    lastIndex = end+1;

    for(j = end; j > start; j--)
    {
        if (arr[j] > pivot)
        {
            lastIndex--;
            swap(&arr[j] , &arr[lastIndex]);
        }
    }

    swap(&arr[start] , &arr[lastIndex - 1]);

    return (lastIndex - 1);
}

void quickSortPartition(int arr[] ,int start, int end)
{
    int pivotIndex;
    if (start < end)
    {
        pivotIndex = partitionProcess(arr , start, end);
        quickSortPartition(arr , start, pivotIndex - 1);
        quickSortPartition(arr , pivotIndex + 1, end);
    }
}

/////////////      MERGE SORT           ///////////////////////////
void merge(int arr[], int first, int mid, int last)
{
    int i, j, k;
    int sizeL = mid - first + 1;
    int sizeR = last - mid;
    int leftArr[sizeL], rightArr[sizeR];

    for (i = 0; i < sizeL; i++)
        leftArr[i] = arr[first + i];
    for (j = 0; j < sizeR; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = first;
    while (i < sizeL && j < sizeR)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < sizeL) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < sizeR) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int first, int last)
{
    int mid;
    if (first < last)
    {
        mid = first + (last - first) / 2;

        mergeSort(arr, first, mid);
        mergeSort(arr, mid + 1, last);

        merge(arr, first, mid, last);
    }
}

/////////////      SHELL SORT           ///////////////////////////
void shellSort(int array[], int size)
{
    int numOfinterval,i,j,temp;
    for (numOfinterval = size/2 ; numOfinterval > 0; numOfinterval/=2)
    {
        for(i=numOfinterval;i<size;i++)
        {
            temp = array[i];

            for (j= i;j >= numOfinterval && array[j - numOfinterval] > temp; j -= numOfinterval)
                array[j] = array[j - numOfinterval];

            array[j] = temp;
        }
    }
}

/////////////      HEAP SORT           ///////////////////////////
void heapify(int arr[],int size,int index)
{
    int left,right,lowest;
    left =2*index+1;
    right =2*index+2;

    if(left<size&&arr[index]<arr[left])
        lowest =left;
    else
        lowest =index;

    if(right<size&&arr[lowest]<arr[right])
        lowest =right;

    if(lowest!=index)
    {
        swap(&arr[index],&arr[lowest]);
        heapify(arr,size,lowest);
    }
}

void buildHeap(int arr[],int size)
{
    int i;
    for(i=(size/2);i>=0;i--)
        heapify(arr,size,i);
}

void heapSort(int arr[],int size)
{
    int i;
    buildHeap(arr,size);
    for(i=size-1;i>=1;i--)
    {
        swap(&arr[0],&arr[i]);
        size-=1;
        heapify(arr,size,0);
    }
}
//////////////////////////////////////////////////////////////////

void readArray(int arr[],int size)
{
    int i;
    for(i=0;i<size;i++)
        scanf("%d",&arr[i]);
}

void writeArray(int arr[],int size)
{
    int i;
    for(i=0;i<size;i++)
        printf("%d\t",arr[i]);
    printf("\n");
}
