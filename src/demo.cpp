#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <readline/readline.h>
#include <readline/history.h>
 
static char** my_completion(const char*, int ,int);
char* my_generator(const char*,int);
char * dupstr (char*);
void *xmalloc (int);
void history_init(char*);
 
const char* cmd [] ={ "hello", "world", "hell" ,"word", "quit", " " };
char* his [12];

//char* buffer;
std::string candidate_list;
 
int main(int argc, char* argv[])
{
    int ret;
    char *buf;
    //buffer = (char *) malloc(sizeof(char)*200);
    rl_attempted_completion_function = my_completion;

    history_init(argv[1]);
 
    while((buf = readline("\n== SmartShell ==> "))!=NULL) { //TODO working directory
        //enable auto-complete
        rl_bind_key('\t',rl_complete);
        //rl_bind_key('\t',rl_menu_complete);
        printf("cmd [%s]\n",buf);
		
		if (strcmp(buf,"quit")==0)
            break;
        if (buf[0]!=0)
            add_history(buf);
		
		//execute the entered command
		system(buf);


    }
 
    //free(buf);
 
    return 0;
}
static char** my_completion( const char * text , int start,  int end)
{
    char **matches;
    int ret;
    char str[5]="test"; 
    matches = (char **)NULL;
 	//printf("[[%s]] %d,%d\n", text, start, end);  //text contains only ONE argument (seperated by blanks)
    //if (start == 0)
        //matches = rl_completion_matches ((char*)text, &my_generator);//TODO implement our func. to generate matches (replace rl_completion_matches())
        matches = rl_completion_matches ((char*)rl_line_buffer, &my_generator);
    //else //** file completion part
    //    rl_bind_key('\t',rl_abort);
    if (matches != NULL){
        char *string;
        string = matches[0];
//        printf("\n\n==%s\n", string);
//        printf("\n");
    }
//    printf("rl_line_buffer: %s\n", rl_line_buffer);
//    ret = printf("rl_point: %s\n", rl_point);

	/*printf("%s\n", buffer);
	buffer[0] = "\0"; //empty the buffer*/
	printf("%s\n", candidate_list.c_str());
	candidate_list.clear();
    
	//new prompt
	//rl_delete_text(0, end);
	rl_on_new_line();
	rl_bind_key('\t',rl_complete);
 
	//process matches, remove the part before start
	int i=0;	
	while(matches[i] != NULL)
	{
		//printf("^^%s\n", matches[i]);
		strcpy(matches[i], std::string(matches[i]).substr(start).c_str()); //FIXME (in our own completion_matches func.)
		++i;
	}
	
    return (matches);
 
}
 
char* my_generator(const char* text, int state)
{
    static int list_index, len;
    char *name;
    char *r;
    char prob[5]="15%\n";
    
    if (!state) {
        list_index = 0;
        len = strlen (text);
    }
    //while (name = cmd[list_index]) {
    while (name = his[list_index]) {
        list_index++;
        //printf("name: %s\n", name); 
        if (strncmp (name, text, len) == 0){
			/*
            r = (char*) xmalloc ((strlen (name) + 5));
            strcpy(r, name);
            //strncat(r, prob, 4);
            strcat(r, prob);
            //printf("\n%s", r);
            strcat(buffer, "\n");
            strcat(buffer, r);
            free(r);
			*/
			candidate_list += "\n" + std::string(name) + " 15%";
            return (dupstr(name));

        }
    }
 
    /* If no names matched, then return NULL. */
    return ((char *)NULL);
 
}

void history_init(char* hist_file){
    register int i;
    register HIST_ENTRY **the_list;
    //read_history ("/home/lilian/.bash_history");
    //read_history_range ("/home/lilian/.bash_history", 490, 500);
    read_history(hist_file);
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
