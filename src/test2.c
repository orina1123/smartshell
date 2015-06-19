#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
 
static char** my_completion(const char*, int ,int);
char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);
void history_init(void);
 
char* cmd [] ={ "hello", "world", "hell" ,"word", "quit", " " };
char* his [12];

char* buffer;

FILE* log_f;
 
int main()
{
    int ret;
    char *buf;
    buffer = (char *) malloc(sizeof(char)*200);
    rl_attempted_completion_function = my_completion;
//    log_f = fopen("log", "w");
    history_init();
 
    while((buf = readline("\n &gt;&gt; "))!=NULL) {
        //enable auto-complete
        rl_bind_key('\t',rl_complete);
        printf("cmd [%s]\n",buf);
        if (strcmp(buf,"quit")==0)
            break;
        if (buf[0]!=0)
            add_history(buf);
    }
 
    free(buf);
//    fclose(log_f);

 
    return 0;
}
static char** my_completion( const char * text , int start,  int end)
{
    char **matches;
    int ret;
    char str[5]="test"; 
    matches = (char **)NULL;
 
    if (start == 0)
        matches = rl_completion_matches ((char*)text, &my_generator);
    else
        rl_bind_key('\t',rl_abort);
    if (matches != NULL){
        char *string;
/*
	char *cptr = matches;
	int counter = 0;

        while (cptr != NULL){
		string = matches[counter++];
        
        	fprintf(log_f,"\n\n==%s\n", string);
		//printf("\n");
        	cptr = matches + counter;
        }
*/
    }
//    printf("rl_line_buffer: %s\n", rl_line_buffer);
//    ret = printf("rl_point: %s\n", rl_point);
//    printf("%s\n", buffer);
    rl_on_new_line();

 
    return (matches);
 
}
 
char* my_generator(const char* text, int state)
{
    static int list_index, len;
    char *name;
    char *r;
    
    if (!state) {
        list_index = 0;
        len = strlen (text);
    }
    //while (name = cmd[list_index]) {
    while (name = his[list_index]) {
        //printf("name: %s\n", name); 
        if (strncmp (name, text, len) == 0){
            //r = (char*) xmalloc ((strlen (name) + 1));
            //strcpy(r, name);
            //strncat(r, prob, 4);
            //printf("\n%s", r);
            //strcat(buffer, r);
            //free(r);
            return (dupstr(name));
        }
        list_index++;
    }
 
    return (char*)NULL;
 
}

void history_init(void){
    register int i;
    register HIST_ENTRY **the_list;
    //read_history ("/home/lilian/.bash_history");
    read_history_range ("/home/lilian/.bash_history", 490, 500);
    the_list = history_list ();
    for(i=0; i<10; i++){
       his[i] = (char*) xmalloc(strlen(the_list[i]->line) + 1);
       strcpy(his[i], the_list[i]->line);
       printf("%s\n", his[i]);
    }
}

char * dupstr (char* s) {
  char *r;
 
  r = (char*) xmalloc ((strlen (s) + 1));
  strcpy (r, s);
  return (r);
}
 
void * xmalloc (int size)
{
    void *buf;
 
    buf = malloc (size);
    if (!buf) {
        fprintf (stderr, "Error: Out of memory. Exiting.'n");
        exit (1);
    }
 
    return buf;
}
