/*  mygrep: A simple example to show how regular */
/*  expressions are used in the Gnu C library. */
/*  See the Gnu documentation for information about */
/*  regular expressions: http://www.gnu.org */
/*  Usage: ./mygrep -f <filename> -p <pattern> */

/*  author: Ben Tindale <ben@bluesat.unsw.edu.au> */
/*  (C) 2000 Ben Tindale */


#include <stdio.h>
#include <stdlib.h>
#include <regex.h> /* Provides regular expression matching */
#include <strings.h> /* String utillity functions */
#include <errno.h> /* Handle errors */

int  match_patterns(regex_t *r, FILE *FH)
{
  char line[1024];
  int line_no=1; /* Count the line numbers for nice output */
  size_t no_sub = r->re_nsub+1; /* How many matches are there in a line? */
  regmatch_t *result;
  char *cp; /* Char pointer */
  int start=0; /* The offset from the beginning of the line */

  if((result = (regmatch_t *) malloc(sizeof(regmatch_t) * no_sub))==0)
    {
      perror("No more memory - aaaagh! (Die kicking and screaming.)");
      exit(EXIT_FAILURE);
    }
  
  while((cp=fgets(line, 1023, FH))!=NULL)
    {
      while(regexec(r, line+start, no_sub, result, 0)==0) /* Found a match */
	{
	  printf("Line %d: %s", line_no, line);
	  start +=result->rm_eo; /* Update the offset */
	}
      line_no++;
    }
  return EXIT_SUCCESS;
}

int do_regex(regex_t *r, char *p, char *f)
{
  int err_no=0; /* For regerror() */
  FILE *FH=NULL; /* File handle */
  if((err_no=regcomp(r, p, 0))!=0) /* Compile the regex */
    {
      size_t length; 
      char *buffer;
      length = regerror (err_no, r, NULL, 0);
      buffer = malloc(length);
      regerror (err_no, r, buffer, length);
      fprintf(stderr, "%s\n", buffer); /* Print the error */
      free(buffer);
      regfree(r);
      return EXIT_FAILURE;
    }
  if((FH=fopen(f, "r"))==NULL) /* Open the file to scan */
    {
      fprintf (stderr, "Couldn't open file %s; %s\n", f, strerror (errno));
      exit(EXIT_FAILURE);
    }
  match_patterns(r, FH); /* Pass the pattern and the file to be scanned */
  regfree(r); /* Free the regular expression data structure */
  free(r);
  fclose(FH);
  return EXIT_SUCCESS;
}

void usage(void)
{
  printf("\n\tmygrep: A simple example to show how regular\texpressions are used in the Gnu C library.\tSee the Gnu documentation for information about\tregular expressions: http://www.gnu.org\n\tUsage: ./mygrep -f <filename> -p <pattern>\n\n");
}  

int main(int argc, char **argv)
{
  int c;
  char *filename=NULL;
  char *pattern=NULL;
  extern char *optarg;
  extern int optind, opterr, optopt;
  regex_t *regex;
  int err_no;
  
  /* Make space for the regular expression */
  regex = (regex_t *) malloc(sizeof(regex_t));
  memset(regex, 0, sizeof(regex_t));

  if(argc==1)
    {
      usage();
      return(EXIT_SUCCESS);
    }
  while((c=getopt(argc, argv, "f:p:"))!= EOF)
    {
      switch(c)
	{
	case 'f':
	  filename=optarg;
	  break;
	case 'p':
	  pattern=optarg;
	  break;
	case '?':
	  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
	  usage();
	  return EXIT_FAILURE;
	default:
	  usage();
	  return EXIT_SUCCESS;
	}
    }
  if((err_no=do_regex(regex, pattern, filename))!=EXIT_SUCCESS)
    {
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}



