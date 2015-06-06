#include <stdio.h>
#include <string.h>

#define history_file_name "history_file"
#define N 100

int main(void){
	FILE *history_file;
	char train[105][500];
	char input_data[105][500];
	char tmp[500],tmp1[500];
	int i,j,k,l;
	int train_id=0;
	int table[105][105];
	if((history_file=fopen(history_file_name,"r"))<0){
		fprintf(stdout,"History file error!\n");
	}
	
	//fgets(train[0],490,history_file);
	//printf("%s\n",train[0]);
	
	for(i=0;i<N;i++){
		fgets(tmp,490,history_file);
		for(j=13;j<strlen(tmp)-1;j++){
			tmp1[j-13]=tmp[j];
		}
		tmp1[j-13]='\0';
		
		strcpy(input_data[i],tmp1);
		if(train_id==0){
			strcpy(train[0],tmp1);
			train_id++;
		}
		else{
			k=0;
			for(j=0;j<train_id;j++){
				if(strcmp(tmp1,train[j])==0){
					k++;
				}
			}
			if(k==0){
				strcpy(train[train_id],tmp1);
				train_id++;
			}
			else{
				//printf("-%d %s\n",i+31,tmp1);
			}
		}
		
	}
	printf("\33[1;36mtotal data %d\33[m\n",train_id);

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			table[i][j]=0;
		}
	}
	
	for(k=0;k<N-1;k++){
		for(i=0;i<train_id;i++){
			if(strcmp(train[i],input_data[k])==0){
				break;
			}
		}
		for(j=0;j<train_id;j++){
			if(strcmp(train[j],input_data[k+1])==0){
				break;
			}
		}
		table[i][j]++;
	}
	
	k=0;
	for(i=0;i<train_id;i++){
		l=0;
		for(j=0;j<train_id;j++){
			if(table[i][j]>0){
				l+=table[i][j];
			}
		}
		if(l>0){
			printf("\33[1;32m%s\33[m\n",train[i]);
			for(j=0;j<train_id;j++){
				if(table[i][j]>0){
					printf("\33[1;33m	%s\33[m %.2lf\n",train[j],(double)table[i][j]/(double)l);
					k++;
				}
			}
			printf("\n");
		}
	}
	printf("\33[1;31mtable size %d\33[m\n",k);

	return 0;
}
