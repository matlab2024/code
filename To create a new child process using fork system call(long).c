
// To create a new child process using fork system call.

/* Process creation - fork.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
main ()
{
  pid_t pid;
  int x = 5;
  pid = fork ();
  x++;
  if (pid < 0)
    {
      printf ("Process creation error");
      exit (-1);
    }
  else if (pid == 0)
    {
      printf ("Child process:");
      printf ("\nProcess id is %d", getpid ());
      printf ("\nValue of x is %d", x);
      printf ("\nProcess id of parent is %d\n", getppid ());
    }
  else
    {
      printf ("\nParent process:");
      printf ("\nProcess id is %d", getpid ());
      printf ("\nValue of x is %d", x);
      printf ("\nProcess id of shell is %d\n", getppid ());
    }
}



// To block a parent process until child completes using wait system call.


/* Wait for child termination - wait.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
main()
{
int i, status;
pid_t pid;
pid = fork();
if (pid < 0)
{
printf("\nProcess creation
failure\n"); exit(-1);
}
else if(pid > 0)
{
wait(NULL);
printf ("\nParent starts\nEven Nos:
"); for (i=2;i<=10;i+=2)
printf ("%3d",i); printf
("\nParent ends\n");
}
else if (pid == 0)
{
printf ("Child starts\nOdd Nos:
"); for (i=1;i<10;i+=2)
printf ("%3d",i);
printf ("\nChild ends\n");
}
}


//To load an executable program in a child processes exec system call.


/* Load a program in child process - exec.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
main (int argc, char *argv[])
{
  pid_t pid;
  int i;
  if (argc != 3)
    {
      printf ("\nInsufficient arguments to load program");
      printf ("\nUsage: ./a.out <path> <cmd>\n");
      exit (-1);
    }
  switch (pid = fork ())
    {
    case -1:
      printf ("Fork
failed");
      exit (-1);
    case 0:
      printf ("Child process\n");
      i = execl (argv[1], argv[2], 0);
      if (i < 0)
	{
	  printf ("%s program not loaded using exec
system call\n", argv[2]);
	  exit (-1);
	}
    default:
      wait (NULL);
      printf ("Child
Terminated\n");
      exit (0);
    }




//To display directory contents using readdir system call.

/* Directory content listing - dirlist.c */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
main (int argc, char *argv[])
{
  struct dirent *dptr;
  DIR *dname;
  if (argc != 2)
    {
      printf ("Usage: ./a.out
<dirname>\n");
      exit (-1);
    }
  if ((dname = opendir (argv[1])) == NULL)
    {
      perror (argv[1]);
      exit (-1);
    }
  while (dptr = readdir (dname))
    printf ("%s\n", dptr->d_name);
  closedir (dname);
}



//To display file status using stat system call.

/* File status - stat.c
*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
int main (int argc, char *argv[])
{
  struct stat file;
  int n;
  if (argc != 2)
    {
      printf ("Usage: ./a.out <filename>\n");
      exit (-1);
    }
  if ((n = stat (argv[1], &file)) == -1)
    {
      perror (argv[1]);
      exit (-1);
    }
  printf ("User id : %d\n", file.st_uid);
  printf ("Group id : %d\n", file.st_gid);
  printf ("Block size : %d\n", file.st_blksize);
  printf ("Blocks allocated : %d\n", file.st_blocks);
  printf ("Inode no. : %d\n", file.st_ino);
  printf ("Last accessed : %s", ctime (&(file.st_atime)));
  printf ("Last modified : %s", ctime (&(file.st_mtime)));
  printf ("File size : %d bytes\n", file.st_size);
  printf ("No. of links : %d\n", file.st_nlink);
  printf ("Permissions : ");
  printf ((S_ISDIR (file.st_mode)) ? "d" : "-");
  printf ((file.st_mode & S_IRUSR) ? "r" : "-");
  printf ((file.st_mode & S_IWUSR) ? "w" : "-");
  printf ((file.st_mode & S_IXUSR) ? "x" : "-");
  printf ((file.st_mode & S_IRGRP) ? "r" : "-");
  printf ((file.st_mode & S_IWGRP) ? "w" : "-");
  printf ((file.st_mode & S_IXGRP) ? "x" : "-");
  printf ((file.st_mode & S_IROTH) ? "r" : "-");
  printf ((file.st_mode & S_IWOTH) ? "w" : "-");
  printf ((file.st_mode & S_IXOTH) ? "x" : "-");
  printf ("\n");
  if (file.st_mode & S_ IFREG)
    printf ("File type : Regular\n");
  if (file.st_mode & S_ IFDIR)
    printf ("File type : Directory\n");
}
