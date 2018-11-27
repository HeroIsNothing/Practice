#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " src_file dst_file" << endl;
		return -1;
	}

	const char *pSrc = argv[1];
	const char *pDst = argv[2];

	int nfdSrc, nfdDst;
	if ( (nfdSrc = open(pSrc, O_RDONLY)) == -1)
	{
		perror("Open src file failed");
		return -1;
	}

	struct stat stSrc;
	if (fstat(nfdSrc, &stSrc) == -1)
	{
		perror("fstat() failed");
		close(nfdSrc);
		return -1;
	}
	
	// unlink(pDst);

	if ((nfdDst = open(pDst, O_CREAT | O_WRONLY | O_TRUNC, stSrc.st_mode)) == -1)
	{
		perror("Open dest file failed");
		close(nfdSrc);
		return -1;
	}

	fchmod(nfdDst, stSrc.st_mode);

	char chBuf[1024];
	ssize_t cnt = 0;
	while ((cnt = read(nfdSrc, chBuf, sizeof(chBuf))) > 0)
	{
		write(nfdDst, chBuf, cnt);
	}

	close(nfdSrc);
	close(nfdDst);
}
