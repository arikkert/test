#include <stdio.h>
#include <sys/stat.h>

// ============================================================================
// Functions
// ============================================================================

// functions return 1 if true 

int testfile(char *file, unsigned type)
{
	int returnvalue;

	struct stat buf;
	if (lstat (file, &buf) == 0)
	{
		// its a file, test if a synlink
		returnvalue = (( buf.st_mode & S_IFMT) == type);
	}
	else
	{
		// its not even a file
		returnvalue = 0;
	}	
	return returnvalue;
}

int isregular(char *file)	{ return testfile(file, S_IFREG); }
int issymlink(char *file)	{ return testfile(file, S_IFLNK); }
int isdir(char *file)		{ return testfile(file, S_IFDIR); }
