/* ============================================================================
# Create
# name  : Andre Rikkert de Koe          date:	apr 2011
# descr : filefind
#	  This is a demo of programming in the C language.
#	  Its part of a project to implement a program to create a directory
#	  tree similar to the output of the Unix find program.
# EUID  : Any user who has read access to all the files being searched for. 
# run   : interactive
#
# Changes
# name  :                               date:
# descr : short description
#
============================================================================ */

#include <string.h>

#include <stdio.h>
#include <libgen.h>
#include "checkfiles.h"
#include <unistd.h> // getcwd


#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include <errno.h>

//define PATH_MAX 255

// ============================================================================
// Functions
// ============================================================================

void Usage(char *progname, char *mesg)
{
	printf("Usage: %s directory\n" ,progname);
	printf("%s\n", mesg);
}

// http://www.ibm.com/developerworks/aix/library/au-unix-readdir.html

void traverse(char *directory)
{
	char curdir[PATH_MAX];
	char curdir2[PATH_MAX]; 

	getcwd(curdir, PATH_MAX);
	chdir(directory);
	getcwd(curdir2, PATH_MAX);

	DIR *dir = NULL;
	struct dirent entry;
	struct dirent *entryPtr = NULL;
	int retval = 0;
	char pathName[PATH_MAX + 1];
	char pfile[PATH_MAX + 1];

	/* Open the given directory, if you can. */  
	dir = opendir(curdir2);
	if (dir == NULL)
	{
		printf( "Error opening %s: %s", directory, strerror( errno ) );
	}
	retval = readdir_r( dir, &entry, &entryPtr );
	while( entryPtr != NULL )
	{
		struct stat entryInfo;
        
		if( ( ! strncmp( entry.d_name, ".",  PATH_MAX ) == 0 ) && 
	    	    ( ! strncmp( entry.d_name, "..", PATH_MAX ) == 0 ) )
		{
			sprintf(pfile,"%s/%s", curdir2, entry.d_name);
			if (isdir(entry.d_name) && ! issymlink(entry.d_name))
			{
				printf("%s\n", pfile);
				traverse(entry.d_name);
			}
			else
			{
				if ((isregular(entry.d_name)) || issymlink(entry.d_name))
					printf("%s\n", pfile);
				else
					printf("WARRNING: Could not process file %s\n", entry.d_name);
			}	
		}
		retval = readdir_r( dir, &entry, &entryPtr );
	}
	chdir(curdir);
}

void start_traverse(char *directory)
{
	printf("%s\n", directory);
	traverse(directory);
}

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char *argv[])
{
	char *progname = argv[0];
	char *directory;
	char mesg[80];

	progname = basename(progname);
	if (argc == 2)
	{
		directory = argv[1];
		if (isdir(directory))
		{
			start_traverse(directory);
		}
		else
		{
			sprintf(mesg, "ERROR: No directory %s found", directory);
			Usage(progname, mesg);
		}
	}
	else
	{
		Usage(progname, "ERROR : 1 argument expected");
	}
}
