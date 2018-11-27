#ifndef FILE_IMPL_CLIB_H_20180615
#define FILE_IMPL_CLIB_H_20180615

#include "file.h"

class CFileImplClib : public CFile
{
public:
	CFileImplClib(const string &strFileName);
	~CFileImplClib();

	virtual bool open(int open_flag = RDONLY);
	virtual void close();
	virtual bool truncate();
	virtual bool exist();
	virtual bool is_folder(const string &strPath);

	virtual long get_size();
	virtual long get_offset();
	virtual mode_t get_mode();
	virtual string get_modestr();
	virtual string get_modestr(mode_t mode);

	virtual bool write(const void *buf, size_t cnt);
	virtual ssize_t read(void *buf, size_t cnt);
	virtual bool seek(off_t offset);
	virtual ssize_t pread(void *buf, size_t cnt, off_t pos);
	virtual bool pwrite(const void *buf, size_t cnt, off_t pos) ;

private:
	FILE * m_pFile;
};

#endif
