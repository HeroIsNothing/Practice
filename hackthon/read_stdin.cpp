#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned char u_char;
typedef unsigned short u_short;

int main(int argc, char *argv[])
{
	u_char ch;
	vector<u_char> header;
	bool bData = false;

	while(read(0, &ch, 1) > 0)
	{
		//write(1, &ch, 1);

		if(ch >= '0' && ch <= '9')
			ch -= '0';
		else if(ch >= 'a' && ch <= 'z')
			ch = ch - 'a' + 10;
		else
			continue;

		if(ch == 0xf)
		{
			int sz = header.size();
			if(sz == 0)
				printf("\n");

			if(sz == 1)
			{
				bData = true;
				header.clear();
			}	
			else
			{
				bData = false;
				header.push_back(ch);
			}
			continue;	
		}
			
		if(!bData)
			continue;
		printf("%d ", (u_short)ch);	
	}
	
	return 0;
}
