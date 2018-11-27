#include "stdafx.h"
#include "file_impl_clib.h"

CFileImplClib::CFileImplClib(const string &strFileName)
	: CFile(strFileName)
	, m_pFile(NULL)
{
}

CFileImplClib::~CFileImplClib()
{
	close();
}

bool CFileImplClib::open(int open_flag/* = RDONLY*/)
{
	close();

	switch (open_flag)
	{
	case RDONLY:
		m_pFile = fopen(m_strFileName.c_str(), "rb");
		break;
	case WRONLY:
		m_pFile = fopen(m_strFileName.c_str(), "wb");
		break;
	case RDWR:
		m_pFile = fopen(m_strFileName.c_str(), "rb+");
		break;
	case CREATE:
		m_pFile = fopen(m_strFileName.c_str(), "wb+");
		break;
	default:
		return false;
	}
	return m_pFile == NULL ? false : true;
}

void CFileImplClib::close()
{
	if (m_pFile != NULL)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}

bool CFileImplClib::truncate()
{
	int fd = fileno(m_pFile);
	return ftruncate(fd, 0);
}

bool CFileImplClib::exist()
{
	struct stat buf;
	if (0 == stat(m_strFileName.c_str(), &buf))
		return true;
	return false;
}

bool CFileImplClib::is_folder(const string &strPath)
{
	struct stat buf;
	if (0 == stat(strPath.c_str(), &buf))
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
		{
			return true;
		}
	}
	return false;
}

long CFileImplClib::get_size()
{
	struct stat buf;
	int fd = fileno(m_pFile);
	if (0 == fstat(fd, &buf))
		return buf.st_size;
	return 0;
}

long CFileImplClib::get_offset()
{
	return ftell(m_pFile);
}

mode_t CFileImplClib::get_mode()
{
	struct stat buf;
	int fd = fileno(m_pFile);
	if (0 == fstat(fd, &buf))
		return buf.st_mode;
	return 0;
}

string CFileImplClib::get_modestr()
{
	return get_modestr(get_mode());
}

string CFileImplClib::get_modestr(mode_t mode)
{
	string strMode = "-rwxrwxrwx";
	const int len = strMode.length();
	mode_t mask;
	for (int i = 0; i < len; ++i)
	{
		mask = 1 << i;
		if ((mode & mask) == 0)
		{
			strMode[len - i - 1] = '-';
		}
	}
	return strMode;
}

bool CFileImplClib::write(const void *buf, size_t cnt)
{
	if (cnt == fwrite(buf, sizeof(char), cnt, m_pFile))
		return true;
	return false;
}

ssize_t CFileImplClib::read(void *buf, size_t cnt)
{
	size_t read = fread(buf, sizeof(char), cnt, m_pFile);
	if (read == cnt)
	{
		return read;
	}
	else
	{
		if (feof(m_pFile))
			return read;
		else
			return -1;
	}
}

bool CFileImplClib::seek(off_t offset)
{
	if (-1 == fseek(m_pFile, offset, SEEK_SET))
	{
		cout << "offset: " << offset << endl;
		perror("fseek() failed");
		return false;
	}
	return true;
}

ssize_t CFileImplClib::pread(void *buf, size_t cnt, off_t pos)
{	
	long off_old = get_offset();
	if (seek(pos))
	{
		ssize_t bytes = this->read(buf, cnt);
		seek(off_old);
		return bytes;
	}
	else
	{
		return -1;
	}
}

bool CFileImplClib::pwrite(const void *buf, size_t cnt, off_t pos)
{
	long off_old = get_offset();
	if (seek(pos))
	{
		bool bRet = this->write(buf, cnt);
		return bRet & seek(off_old);
	}
	else
	{
		return false;
	}
}
