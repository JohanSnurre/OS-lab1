/*
 * Main source code file for lsh shell program
 *
 * You are free to add functions to this file.
 * If you want to add functions in a separate file(s)
 * you will need to modify the CMakeLists.txt to compile
 * your additional file(s).
 *
 * Add appropriate comments in your code to make it
 * easier for us while grading your assignment.
 *
 * Using assert statements in your code is a great way to catch errors early and make debugging easier.
 * Think of them as mini self-checks that ensure your program behaves as expected.
 * By setting up these guardrails, you're creating a more robust and maintainable solution.
 * So go ahead, sprinkle some asserts in your code; they're your friends in disguise!
 *
 * All the best!
 */
#include <assert.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The <unistd.h> header is your gateway to the OS's process management facilities.
#include <unistd.h>

#include "parse.h"

static void run_cmds(Command *);
static void print_cmd(Command *cmd);
static void print_pgm(Pgm *p);
void stripwhite(char *);

int main(void)
{
  //Function to execute Pipeline 
  int ExecutePipedCmd(Command *cmd_list,struct c *pgm){
    pid_t pid;
    int fd[2],ret;

    if(pipe(fd)==-1){
      perror("Fail on piping");
      exit(-1);
    }
    pid = fork();
    if(pid==-1){
      perror("Fail on fork process");
      exit(-1);
    }
    if(pid==0){
      close(fd[0]);
      dup2(fd[1],1);
      close(fd[1]);

      pgm = pgm->next;
      if(pgm->next !=NULL){
        //Recursive call of the function
        ExecutePipedCmd(cmd_list,pgm);
      }
      else{
        //Redirecting standard input 
        if(cmd->rstdin != NULL){
          int infd = open(cmd->rstdin,0);
          dup2(infd,0);
        }
        //Executing the command
        int re = execvp(pgm->pgm_list[0],pgm->pgm_list);
        if(re == -1){
          perror("ERROR : fail on executing Command ");
          exit(-1);
        }
      }
    }
    if(pid>0){
      close(fd[1]);
      dup2(fd[0],0);
      //Executing the command
      int re = execvp(pgm->pgm_list[0],pgm->pgm_list);
      if(re == -1){
        perror("ERROR : fail on executing Command ");
        exit(-1);
      }
    }
  }





  for (;;)
  {
    char *line;
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    char prompt[] = " > ";
    char login[64];
    strcpy(login, "(");
    strcat(login, getlogin());
    strcat(login, ")");
    strcat(cwd,login);
    strcat(cwd,prompt);
    line = readline(cwd);

    // If EOF encountered, exit shell
    if (!line)
    {
      break;
    }

    // Remove leading and trailing whitespace from the line
    stripwhite(line);

    // If stripped line not blank
    if (*line)
    {
      add_history(line);

      Command cmd;
      if (parse(line, &cmd) == 1)
      {

        if(strcmp(cmd.pgm->pgmlist[0], "cd") == 0){
          if(chdir(cmd.pgm->pgmlist[1]) != 0){
            printf("Some error with cd path");
          }
          continue;

        }
        else if(strcmp(cmd.pgm->pgmlist[0], "exit") == 0){
          printf("Exiting shell\n");
          break;


        }

        run_cmds(&cmd);
      }
      else
      {
        printf("Parse ERROR\n");
      }
    }

    // Clear memory
    free(line);
  }

  return 0;
}

/* Execute the given command(s).

 * Note: The function currently only prints the command(s).
 *
 * TODO:
 * 1. Implement this function so that it executes the given command(s).
 * 2. Remove the debug printing before the final submission.
 */
static void run_cmds(Command *cmd_list)
{

  int pid = fork();
  int status;
  struct c *pgm = cmd_list->pgm;

  //child process
  if(pid == 0){
      if(pgm->next != NULL){
        ExecutePipedCmd(cmd_list,pgm);
      }
    else{
      execvp(cmd_list->pgm->pgmlist[0], cmd_list->pgm->pgmlist);
   }
    
  }
  //some error
  else if(pid == -1){
    printf("Some error with fork");
    exit(EXIT_FAILURE);
  }
  //parent process
  else{


    //waiting for child
    if(waitpid(pid, &status, 0) > 0){

      printf("Child finished");


    }

  }




  print_cmd(cmd_list);
}

/*
 * Print a Command structure as returned by parse on stdout.
 *
 * Helper function, no need to change. Might be useful to study as inpsiration.
 */
static void print_cmd(Command *cmd_list)
{
  printf("------------------------------\n");
  printf("Parse OK\n");
  printf("stdin:      %s\n", cmd_list->rstdin ? cmd_list->rstdin : "<none>");
  printf("stdout:     %s\n", cmd_list->rstdout ? cmd_list->rstdout : "<none>");
  printf("background: %s\n", cmd_list->background ? "true" : "false");
  printf("Pgms:\n");
  print_pgm(cmd_list->pgm);
  printf("------------------------------\n");
}

/* Print a (linked) list of Pgm:s.
 *
 * Helper function, no need to change. Might be useful to study as inpsiration.
 */
static void print_pgm(Pgm *p)
{
  if (p == NULL)
  {
    return;
  }
  else
  {
    char **pl = p->pgmlist;

    /* The list is in reversed order so print
     * it reversed to get right
     */
    print_pgm(p->next);
    printf("            * [ ");
    while (*pl)
    {
      printf("%s ", *pl++);
    }
    printf("]\n");
  }
}


/* Strip whitespace from the start and end of a string.
 *
 * Helper function, no need to change.
 */
void stripwhite(char *string)
{
  size_t i = 0;

  while (isspace(string[i]))
  {
    i++;
  }

  if (i)
  {
    memmove(string, string + i, strlen(string + i) + 1);
  }

  i = strlen(string) - 1;
  while (i > 0 && isspace(string[i]))
  {
    i--;
  }

  string[++i] = '\0';
}
