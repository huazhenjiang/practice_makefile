#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcat_imp(char *str1, char *str2)
{
	int i,j;
	int save=0;
	
	i=0;
	j=0;
	if((str1 == NULL)||(str2 == NULL))
		return -1;
		
	while(str1[i] != '\0'){
		//save ++;
		i++;
	}
	while(str2[j] != '\0'){
		str1[i] = str2[j];
		i++;
		j++;
	}
	str1[i]='\0';


	return 0;		
}

int strncat_imp(char *str1,char *str2, int num){
	int i,j;
	int res=0;
	if((str1==NULL)||(str2==NULL))
		return -1;
	
	i=0;
	j=0;
	//res = sizeof(str1)-strlen(str1);
	//printf("\r\nsizeof(str1):%d,strlen(str1):%d",sizeof(str1),strlen(str1));	
	while(str1[i] != '\0'){
		i++;
	}
	
	//if(num >res){
	//	printf("\r\nWithout enough mem.num:%d,res:%d",num,res);
	//}
	
	while((str2[j] != '\0')&&(num!=0)){
		//if(num>0){
			str1[i]=str2[j];
			i++;
			j++;
			num--;
		//}
		
	}
	str1[i]='\0';
	return 0;
	
}
/*
void main(){
	char str1[30]="1234567";
	char str2[30]="890123";
	char str3[30]="abcdefghijklmnopqrstuvwxyz";
	char str4[10]="0123456789";
	
	printf("\r\nsizeof(str3):%d",sizeof(str3));
	
	printf("\r\nOriginal str1:%s",str1);
	printf("\r\nOriginal str2:%s",str2);
	
	strcat_imp(str1,str2);
	printf("\r\nStrcat str1 and str2:%s",str1);
	
	strncat_imp(str3,str4,3);
	printf("\r\nStrncat(nor) str3 and str4:%s",str3);
	
	//strncat_imp(str3,str4,2);
	//printf("\r\nStrncat(over) str3 and str4:%s",str3);	
}
*/
