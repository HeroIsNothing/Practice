#ifndef FILE_DATABASE_H_20180612_H
#define FILE_DATABASE_H_20180612_H

#include "noncopyable.h"
class CFile;
class CFileDB : public noncopyable
{
public:
	CFileDB(const string &strDBFileName);
	~CFileDB();

	bool Open();
	bool Create(int nCapacity);

	void List();
	void Insert(const string &strFileName);
	void Extract(int slot, const string &strPath);
	void ExtractAll(const string &strPath);

private:
	bool OpenDB();
	void CloseDB();

	bool IsFileFormatted();
	
	struct Metadata;
	bool GetMetadata(long slot, Metadata &mdata);
	bool WriteMetadata(long slot, const Metadata &mdata);
	bool WriteSlotCnt(long val);
	bool WriteSlotUsed(long val);

	void SeekToBegin();
	void SeekToMetadata(long slot);
	void SeekToFiledata(long slot);
	void SeekToEnd();

	void DoExtract(int slot, const string &strPath);

private:
	CFile * m_pFile;
	/*
	Database file structure:

	| magic_nr   | slot_cnt    | slot_used |
	| metadata_1 | metadata_2  |...|
	| file_data_1| file_data_2 |...|
	*/

	static const long m_magic_nr = 19860513L;
	long m_slot_cnt;
	long m_slot_used;
	static const int  m_offset_metadata = 3 * sizeof(long);

	static const long filename_len = 255;
	struct Metadata
	{
		long	offset;
		long	filesize;
		char	filename[filename_len];
		mode_t	filemode;
	};
};

#endif
