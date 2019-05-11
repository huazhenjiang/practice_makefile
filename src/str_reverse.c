#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* str_reverse(char *str){
	int i=0,len;
	char temp;
	len=strlen(str)-1;
	
	while(i<len){
		
		temp=str[i];
		str[i]=str[len];
		str[len]=temp;
		i++;
		len--;		
	}
	
}
/*
void main(){
	char str[30]="Hello,World";
	
	printf("\r\nOriginal str:%s",str);
	
	str_reverse(str);
	printf("\r\nReverse str:%s",str);
}
*/
