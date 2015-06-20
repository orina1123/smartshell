#include <stdio.h>
#include <string.h>

#define history_file_name "/nfs/inm_master/03/r03944012/AI/final/predict/history_file_1"
#define N 100
#define train_N 60

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
	int train_id;
	int table1[105][105];
	int table2[105][105];
	int table3[105][105];
	int window_start=0;
	int window_end=train_N;
	int find;
	char answer[105];
	double p_answer;

	int eva=0;
	int eva1=0;
	int reverse=0;
	
	/*
	if(alpha_1+alpha_2+alpha_3!=1.0){
		fprintf(stdout,"probability error!\n");
		return -1;
	}
	*/
RESTART:
	
	train_id=0;
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
		else if(window_start<=i && i<window_end){
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
		}
		
	}
	//printf("\33[1;36mtotal data %d\33[m\n",train_id);

	
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			table1[i][j]=0;
			table2[i][j]=0;
			table3[i][j]=0;
		}
	}
	
	// table one
	for(k=window_start;k<window_end-1;k++){
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
	for(k=window_start;k<window_end-2;k++){
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
	for(k=window_start;k<window_end-3;k++){
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

	//find table1
	find=0;
	p_answer=0;
	//printf("\33[1;31m%s\33[m:\n",input_data[window_end-1]);
	for(j=0;j<train_id;j++){
		l[0]=0;
		l[1]=0;
		l[2]=0;
		
		for(i=0;i<train_id;i++){
			if(table1[i][j]>0){
				l[0]+=table1[i][j];
			}
			if(table2[i][j]>0){
				l[1]+=table2[i][j];
			}
			if(table3[i][j]>0){
				l[2]+=table3[i][j];
			}
		}
		
		if(strcmp(train[j],input_data[window_end-1])==0){
			for(i=0;i<train_id;i++){
				if(table1[i][j]!=0 && input_data[window_end][0]==train[i][0]){
					//printf("eva %s %lf %d/%d\n",train[i],(double)table1[i][j]/(double)l[0],table1[i][j],l[0]);
					if(p_answer==0.0 || p_answer<(double)table1[i][j]/(double)l[0]){
						find=1;
						strcpy(answer,train[i]);
						p_answer=(double)table1[i][j]/(double)l[0];
					}
				}
			}
		}
	}
	/*
	printf("\33[1;31m%5d ",window_end);
	if(find==0){
		printf("Not found!\n");
	}
	else{
		printf("\33[1;33m%s %lf\33[m %s\n",answer,p_answer,input_data[window_end]);
	}
	*/
	
	if(strcmp(input_data[window_end],answer)==0){
		eva+=1;
	}

	for(i=window_end-1;i>0;i--){
		if(input_data[window_end][0]==input_data[i][0]){
			if(strcmp(input_data[window_end],input_data[i])==0){
				reverse++;
			}
			break;
		}
	}
	if(find==0){
		printf("Not found!\n");
	}

	printf("%5d \33[1;31m%s \33[32m%s \33[m%s %lf\n",window_end,input_data[window_end],input_data[i],answer,p_answer);

	if(window_end<N-1){
		window_start+=1;
		window_end+=1;
		goto RESTART;
	}
	
	printf("evaluation = %lf, train_N = %d\n",(double)eva/(double)(N-train_N),train_N);
	printf("reverse search = %lf, train_N = %d\n",(double)reverse/(double)(N-train_N),train_N);
	printf("%d\n",reverse);
	
	return 0;
}
