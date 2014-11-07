/*  
 *  Adrien Fabre - M1 - IL
 *
 *  Programmation systeme
 *
 *  TP 1 - ex 1
 *
 *  */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>


/* Handles a signal by printing its number when the signal arrives */
void signalHandler(int signum){
  printf ("\nHey! You got a signal %d\n", signum);

  /* In a real program there would be cleaning and closing instructions here */

  exit (signum);

}


int main (){

  int   fd[2], nbytes;
  char  msg[] = "Hello world\n";
  char  readbuffer[80];


  /* handler of SIGPIPE signal */
  signal (SIGPIPE, signalHandler);

  /* creating the pipe */
  pipe(fd);

  /* closing the pipe to test the signal we get */
  /* (comment the next line to let the pipe work properly) */
  //close ( fd[0] );

  /* writing msg into the pipe */
  write(fd[1], msg, (sizeof(msg)+1));

  /* reading the content of the pipe */
  nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
  printf("\nReceived string: %s", readbuffer);



  return (0);
}



