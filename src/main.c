#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/base64.h"
#include "../include/str_reverse.h"
#include "../include/strcat_imp.h"
void printOutput(int *array, int leng){
	int i;
	for(i=0;i<leng;i++)
		printf("%d ", array[i]);
}

void swap(int *a,int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
}

int partition(int *input, int front, int end){
	int i,j;
	int pivot;
	i= front -1;
	//pivot = input[end];
	pivot = *(input+end);
	
	for(j=front;j<end;j++){
		if(input[j]<pivot){
			i++;
			//swap(&input[i],&input[j]);
			swap((input+i),(input+j));
		}
	}
	i++;
	swap(&input[i],&input[end]);
	return i;
	
}

void QuickSort(int *arr,int front, int end){
	int pivot;
	if(front<end){
		pivot=partition(arr, front, end);
		QuickSort(arr,0,pivot-1);
		QuickSort(arr,pivot+1,end);
	}
	
}

void BubbleSort(int *arr, int num){
	
	int i,j;
	
	j=num-1;
	
	while(j>1){
		
		for(i=0;i<j;i++){
			if(arr[i]<arr[i+1]){
				
			}
			else if(arr[i]>arr[i+1]){
				swap(&arr[i],&arr[i+1]);
			}
			else{
				
			}			
		}
		j--;
	}
}

void main(){
	
	int raw_array[10]={5,45,23,66,9,78,1,8,30,55};
	int num;
	num = sizeof(raw_array)/sizeof(raw_array[0]);
	
	printf("\r\nOriginal Array:");
	printOutput(raw_array,num);

	QuickSort(raw_array,0,num-1);
	printf("\r\nQuick Sorting Array:");
	printOutput(raw_array,num);	
	
	BubbleSort(raw_array,num);
	printf("\r\nBubble Sorting Array:");
	printOutput(raw_array,num);

	char str[30]="Hello,World";
	
	printf("\r\nOriginal str:%s",str);
	
	str_reverse(str);
	printf("\r\nReverse str:%s\r\n",str);
		
}
