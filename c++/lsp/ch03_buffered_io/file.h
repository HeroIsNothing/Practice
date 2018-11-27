#ifndef FILE_H_20180615
#define FILE_H_20180615

#include "noncopyable.h"

class CFile : public noncopyable
{
public:
	static const int RDONLY = 1;
	static const int WRONLY = 2;
	static const int RDWR   = 4;
	static const int CREATE = 8;

public:
	CFile(const string &strFileName) : m_strFileName(strFileName) {}
	~CFile() {}

	virtual bool open(int open_flag = RDONLY) = 0;
	virtual void close() = 0;
	virtual bool truncate() = 0;
	virtual bool exist() = 0;
	virtual bool is_folder(const string &strPath) = 0;

	virtual long get_size() = 0;
	virtual long get_offset() = 0;
	virtual mode_t get_mode() = 0;
	virtual string get_modestr() = 0;
	virtual string get_modestr(mode_t mode) = 0;

	virtual bool write(const void *buf, size_t cnt) = 0;
	virtual ssize_t read(void *buf, size_t cnt) = 0;
	virtual bool seek(off_t offset) = 0;
	virtual ssize_t pread(void *buf, size_t cnt, off_t pos) = 0;
	virtual bool pwrite(const void *buf, size_t cnt, off_t pos) = 0;

protected:
	string m_strFileName;
};

#endif
