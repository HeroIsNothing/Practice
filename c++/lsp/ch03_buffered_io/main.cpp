#include "stdafx.h"
#include "file_database.h"

struct Option
{
	string val1;
	string val2;
	void(*pOperate)(CFileDB &fdb, const string &val1, const string &val2);
};

bool CheckOption(int argc, char *argv[], Option &opt);
void OutputUsage(char *argv[]);

void OpInitDB(CFileDB &fdb, const string &val1, const string &val2);
void OpListFile(CFileDB &fdb, const string &val1, const string &val2);
void OpInsertFile(CFileDB &fdb, const string &val1, const string &val2);
void OpExtractFile(CFileDB &fdb, const string &val1, const string &val2);
void OpExtractAllFiles(CFileDB &fdb, const string &val1, const string &val2);

int main(int argc, char *argv[])
{
	Option opt;

	if (!CheckOption(argc, argv, opt))
	{
		OutputUsage(argv);
		return -1;
	}

	CFileDB fdb("./database.dat");

	bool bSucc = true;
	if (strcmp(argv[1], "-c") != 0)	// No need to open for -c(creating database)
		bSucc = fdb.Open();
	if (bSucc)
	{
		opt.pOperate(fdb, opt.val1, opt.val2);
	}
	
}

////////////////////////////////////////////////////////////////////////////

bool CheckOption(int argc, char *argv[], Option &opt)
{
	opt.pOperate = NULL;

	if (argc == 2)
	{
		if (strcmp(argv[1], "-l") == 0)
		{
			opt.pOperate = OpListFile;
		}
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-a") == 0)
		{
			opt.pOperate = OpInsertFile;
		}
		else if (strcmp(argv[1], "-X") == 0)
		{
			opt.pOperate = OpExtractAllFiles;
		}
		else if (strcmp(argv[1], "-c") == 0)
		{
			opt.pOperate = OpInitDB;
		}

		opt.val1 = argv[2];
	}
	else if (argc == 4)
	{
		if (strcmp(argv[1], "-x") == 0)
		{
			opt.pOperate = OpExtractFile;
		}

		opt.val1 = argv[2];
		opt.val2 = argv[3];
	}

	return opt.pOperate == NULL ? false : true;
}

void OutputUsage(char *argv[])
{
	cout << "Usage: " << argv[0] << " options" << endl;
	cout << "  options: " << endl;
	cout << "    -l           : list files." << endl;
	cout << "    -a filename  : append a file." << endl;
	cout << "    -x slot path : extract a file into the path." << endl;
	cout << "    -X path      : extrace all the files into the path." << endl;
	cout << "    -c capacity  : create the database which can keep capacity files." << endl;
}

////////////////////////////////////////////////////////////////////////////

void OpListFile(CFileDB &fdb, const string &val1, const string &val2)
{
	fdb.List();
}

void OpInsertFile(CFileDB &fdb, const string &val1, const string &val2)
{
	fdb.Insert(val1);
}

void OpExtractFile(CFileDB &fdb, const string &val1, const string &val2)
{
	int slot = atoi(val1.c_str());
	fdb.Extract(slot, val2);
}

void OpExtractAllFiles(CFileDB &fdb, const string &val1, const string &val2)
{
	fdb.ExtractAll(val1);
}

void OpInitDB(CFileDB &fdb, const string &val1, const string &val2)
{
	int nCapacity = atoi(val1.c_str());
	fdb.Create(nCapacity);
}