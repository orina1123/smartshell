#include <stdio.h>
#include <string.h>

#define history_file_name "history_file"
#define N 100

#define alpha_1 1.0
#define alpha_2 0.0
#define alpha_3 0.0

int main(void){
	FILE *history_file;
	char train[105][500];
	char input_data[105][500];
	char tmp[500],tmp1[500];
	int i,j,k;
	int l[5];
	int train_id=0;
	int table1[105][105];
	int table2[105][105];
	int table3[105][105];
	
	/*
	if(alpha_1+alpha_2+alpha_3!=1.0){
		fprintf(stdout,"probability error!\n");
		return -1;
	}
	*/
	
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
			table1[i][j]=0;
			table2[i][j]=0;
			table3[i][j]=0;
		}
	}
	
	// table one
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
		table1[i][j]++;
	}
	
	// table two
	for(k=0;k<N-2;k++){
		for(i=0;i<train_id;i++){
			if(strcmp(train[i],input_data[k])==0){
				break;
			}
		}
		for(j=0;j<train_id;j++){
			if(strcmp(train[j],input_data[k+2])==0){
				break;
			}
		}
		table2[i][j]++;
	}

	// table three
	for(k=0;k<N-3;k++){
		for(i=0;i<train_id;i++){
			if(strcmp(train[i],input_data[k])==0){
				break;
			}
		}
		for(j=0;j<train_id;j++){
			if(strcmp(train[j],input_data[k+3])==0){
				break;
			}
		}
		table3[i][j]++;
	}


	
	for(i=0;i<train_id;i++){
		l[0]=0;
		l[1]=0;
		l[2]=0;
		
		for(j=0;j<train_id;j++){
			if(table1[i][j]>0){
				l[0]+=table1[i][j];
			}
		}
		for(j=0;j<train_id;j++){
			if(table2[i][j]>0){
				l[1]+=table2[i][j];
			}
		}
		for(j=0;j<train_id;j++){
			if(table3[i][j]>0){
				l[2]+=table3[i][j];
			}
		}

		if(l[0]>0 || l[1]>0 || l[2]>0){
			printf("\33[1;32m%s\33[m\n",train[i]);
			
			if(l[0]>0){
				printf("1:\n");
			}
			for(j=0;j<train_id;j++){
				if(table1[i][j]>0){
					printf("\33[1;33m	%s\33[m %.3lf %d/%d\n",train[j],(double)table1[i][j]/(double)l[0],table1[i][j],l[0]);
				}
			}

			if(l[1]>0){
				printf("2:\n");
			}
			for(j=0;j<train_id;j++){
				if(table2[i][j]>0){
					printf("\33[1;33m	%s\33[m %.3lf %d/%d\n",train[j],(double)table2[i][j]/(double)l[1],table2[i][j],l[1]);
				}
			}

			if(l[2]>0){
				printf("3:\n");
			}
			for(j=0;j<train_id;j++){
				if(table3[i][j]>0){
					printf("\33[1;33m	%s\33[m %.3lf %d/%d\n",train[j],(double)table3[i][j]/(double)l[2],table3[i][j],l[2]);
				}
			}
			printf("\n");
		}
	}	
	
	
	return 0;
}
