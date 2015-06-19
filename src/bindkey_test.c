#include <stdio.h>

#include <readline/readline.h>

int my_cool_readline_func (int count, int key) {
   printf ("key pressed: %d\n", key);
   printf ("count: %d\n", count);
   rl_on_new_line ();
   return 0;
}

int main(void) {
     rl_command_func_t my_cool_readline_func;
     rl_bind_key ('\t', my_cool_readline_func);
     rl_bind_key (27, my_cool_readline_func); /* ascii code for ESC */
     rl_bind_keyseq ("\\C-a", my_cool_readline_func);

     while (1) {
         char *line = readline ("rl> ");
     }
}
