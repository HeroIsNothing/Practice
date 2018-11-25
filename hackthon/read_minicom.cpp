#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned char u_char;
enum STATUS { UNKNOWN, CHECKING, DATA };
#define START_CHR				'f'
#define DATA_LEN				(8 * 2)
#define GAS_CONCENTRATION_HIGH	4
#define GAS_CONCENTRATION_LOW	5
bool g_debug = false;

bool ignore(u_char ch)
{
	if(ch >= '0' && ch <= '9')
		return false;
	else if(ch >= 'a' && ch <= 'z')
		return false;
	else
		return true;
}

bool read_byte(u_char &ch)
{
	while(1)
	{
		if(read(STDIN_FILENO, &ch, 1) <= 0)
			return false;

		if(ignore(ch))
			continue;

		return true;
	}
}

// ch = 'f' will return 15
short HexChrToNum(u_char ch)
{
	if(ch >= '0' && ch <= '9')
		return ch - '0';
	else if(ch >= 'a' && ch <= 'z')
		return ch - 'a' + 10;
	else if(ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 10;
	else
		return 0;
}

/*
  buf = 'ff' will return
  f*16+f = 15*16+15 = 255
*/
long HexStrToNum(u_char buf[], int len)
{
	if(len != 2)
		return 0;
	return HexChrToNum(buf[0]) * 16 + HexChrToNum(buf[1]);
}

bool data_is_valid(const vector<u_char> &buf)
{
	if(buf.size() != DATA_LEN)
		return false;

	static const char *pGasName = "1704";
	static const char *pMaxUom  = "07d0";
	for(int i=0; i<4; ++i)
	{
		if(pGasName[i] != buf[i])
			return false;
		if(pMaxUom[i] != buf[10+i])
			return false;
	}

	return true;
}

void parse_data(const vector<u_char> &buf)
{
	if(!data_is_valid(buf))
		return;

	u_char gas_high[2];
	u_char gas_low[2];

	int  offset = (GAS_CONCENTRATION_HIGH-1) * 2;

	gas_high[0] = buf[offset];
	gas_high[1] = buf[++offset];
	gas_low[0]  = buf[++offset];
	gas_low[1]  = buf[++offset];

	long val_high = HexStrToNum(gas_high, 2);
	long val_low  = HexStrToNum(gas_low,  2);

	if(g_debug)
	{
		cout << '[';
		for(int i=0; i<buf.size(); ++i)
			cout << buf[i];
		cout << '\t';
		cout << gas_high[0] << gas_high[1] << ' ';
		cout << gas_low[0]  << gas_low[1];
		cout << ']' << '\t';
	}

	cout << val_high * 256 + val_low << " ug/m^3" <<  endl;
}

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		if(string(argv[1]) == string("-d"))
			g_debug = true;
	}

	u_char ch;
	vector<u_char> buf;
	STATUS status = UNKNOWN;

	while(read_byte(ch))
	{
		// 1. Read until meeting double START_CHR
		if(status == UNKNOWN)
		{
			if(ch != START_CHR)
			{
				continue;
			}
			else
			{
				status = CHECKING;
				continue;
			}
		}

		if(status == CHECKING)
		{
			if(ch != START_CHR)
			{
				status = UNKNOWN;
				continue;
			}
			else
			{
				status = DATA;
			}
		}

		// 2. Read data (status == DATA)
		int nlen = DATA_LEN;
		buf.clear();
		while(nlen-- > 0 && read_byte(ch))
		{
			buf.push_back(ch);
		}

		parse_data(buf);

		status = UNKNOWN;
	}
	
	return 0;
}
