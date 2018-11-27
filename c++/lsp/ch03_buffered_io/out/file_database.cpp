#include "stdafx.h"
#include "file_impl_clib.h"
#include "file_database.h"

CFileDB::CFileDB(const string &strDBFileName)
	: m_slot_cnt(0)
	, m_slot_used(0)
{
	try
	{
		m_pFile = new CFileImplClib(strDBFileName);
	}
	catch (bad_alloc)
	{
		m_pFile = NULL;
	}
}

CFileDB::~CFileDB()
{
	CloseDB();
}

bool CFileDB::Open()
{
	if (m_pFile == NULL)
	{
		cout << "Initialize database failed!" << endl;
		return false;
	}

	if (!m_pFile->exist())
	{
		cout << "Database file doesn't exist!" << endl;
		return false;
	}

	if (!OpenDB())
	{
		cout << "Open database failed!" << endl;
		return false;
	}

	if (!IsFileFormatted())
	{
		cout << "Unrecognized format, use \"-c\" option to create a new one." << endl;
		return false;
	}

	return true;
}

bool CFileDB::OpenDB()
{
	return m_pFile->open(CFile::RDWR);
}

void CFileDB::CloseDB()
{
	m_pFile->close();
}


bool CFileDB::IsFileFormatted()
{
	SeekToBegin();
	long magic_nr(-1);
	do
	{
		long file_size = m_pFile->get_size();
		if (file_size < m_offset_metadata)
			break;

		if (sizeof(magic_nr) != m_pFile->read(&magic_nr, sizeof(magic_nr)))
			break;

		if (magic_nr != m_magic_nr)
			break;

		if (sizeof(m_slot_cnt) != m_pFile->read(&m_slot_cnt, sizeof(m_slot_cnt)))
			break;

		if (sizeof(m_slot_used) != m_pFile->read(&m_slot_used, sizeof(m_slot_used)))
			break;

		long meta_size = m_slot_cnt * sizeof(Metadata);
		if (file_size < m_offset_metadata + meta_size)
			break;

		return true;
	} while (0);

	return false;
}

bool CFileDB::Create(int nCapacity)
{
	CloseDB();

	if (!m_pFile->open(CFile::CREATE))
		return false;

	bool bRet = false;
	do
	{
		long magic_nr  = m_magic_nr;
		m_slot_cnt	   = nCapacity;
		m_slot_used	   = 0;

		if (!m_pFile->write(&magic_nr, sizeof(magic_nr)))
			break;
		if (!m_pFile->write(&m_slot_cnt, sizeof(m_slot_cnt)))
			break;
		if (!m_pFile->write(&m_slot_used, sizeof(m_slot_used)))
			break;

		if (m_slot_cnt != 0)
		{
			Metadata mdata;
			mdata.offset   = 0;
			mdata.filemode = 0;
			mdata.filesize = 0;

			bool bSucc = true;
			for (int i = 0; i < m_slot_cnt; ++i)
			{
				if (!m_pFile->write(&mdata, sizeof(mdata)))
				{
					bSucc = false;
					break;
				}
			}

			if (!bSucc)
				break;
		}
		
		bRet = true;
	} while (0);


	CloseDB();
	return bRet;
}

void CFileDB::List()
{
	printf("DB Usage  : %ld/%ld\n", m_slot_used, m_slot_cnt);
	printf("DB Content:\n");
	printf("index    filemode      offset    filesize    filename\n");
	printf("-----    ----------    ------    --------    --------\n");
	for (int i = 0; i < m_slot_cnt; ++i)
	{
		Metadata mdata;
		if (GetMetadata(i, mdata))
		{
			printf("%5d    %10s    %6ld    %8ld    %s\n",
				i,
				m_pFile->get_modestr(mdata.filemode).c_str(),
				mdata.offset,
				mdata.filesize,
				mdata.filesize == 0 ? "" : mdata.filename);
		}
		else
		{
			cout << "Internal error!" << endl;
			break;
		}
	}
}

void CFileDB::Insert(const string &strFileName)
{
	if (m_slot_cnt == 0)
	{
		cout << "Use \"-c\" option to create database first!" << endl;
		return;
	}

	if (m_slot_used == m_slot_cnt)
	{
		cout << "Database is FULL!" << endl;
		return;
	}

	CFileImplClib file(strFileName);
	if(!file.open())
	{
		cout << "Can't read file - " << strFileName << endl;
		return;
	}

	SeekToEnd();

	Metadata mdata;
	mdata.offset   = m_pFile->get_offset();
	mdata.filemode = file.get_mode();
	strcpy(mdata.filename, strFileName.c_str());

	long file_size = 0;
	const size_t bufsize = 1024;
	char buf[bufsize];
	ssize_t read = 0;
	while ( (read = file.read(buf, bufsize)) > 0)
	{
		file_size += read;
		if (!m_pFile->write(buf, read))
		{
			perror("Insert file failed");
			return;
		}
	}
	mdata.filesize = file_size;

	long next_slot = m_slot_used;
	SeekToMetadata(next_slot);
	if (WriteMetadata(next_slot, mdata))
	{
		WriteSlotUsed(++m_slot_used);
	}	
}

void CFileDB::Extract(int slot, const string &strPath)
{
	if (m_slot_used == 0)
	{
		cout << "Database is EMPTY!" << endl;
		return;
	}

	if (slot >= m_slot_cnt)
	{
		cout << "Database only have " << m_slot_cnt << " slots!" << endl;
		return;
	}

	if (slot >= m_slot_used)
	{
		cout << "Slot is EMPTY! " << slot << endl;
		return;
	}

	if (!m_pFile->is_folder(strPath))
	{
		cout << "Folder doesn't exist!" << endl;
	}

	DoExtract(slot, strPath);
}

void CFileDB::ExtractAll(const string &strPath)
{
	if (m_slot_used == 0)
	{
		cout << "Database is EMPTY!" << endl;
		return;
	}

	if (!m_pFile->is_folder(strPath))
	{
		cout << "Folder doesn't exist!" << endl;
	}

	for (int i = 0; i < m_slot_used; ++i)
	{
		DoExtract(i, strPath);
	}
}

void CFileDB::DoExtract(int slot, const string &strPath)
{
	Metadata mdata;
	if (GetMetadata(slot, mdata))
	{
		string strFileName;
		if (strPath[strPath.length() - 1] == '/')
			strFileName = strPath + mdata.filename;
		else
			strFileName = strPath + "/" + mdata.filename;

		CFileImplClib file(strFileName);
		if (!file.open(CFile::CREATE))
		{
			perror("Create output file failed");
		}
		else
		{
			SeekToFiledata(slot);

			const int bufsize = 1024;
			char buf[bufsize];
			long tot_bytes = mdata.filesize;
			long read_bytes = bufsize < tot_bytes ? bufsize : tot_bytes;
			size_t real_bytes;
			while ( tot_bytes > 0 && 
					(real_bytes = m_pFile->read(buf, read_bytes)) > 0)
			{
				if (!file.write(buf, real_bytes))
				{
					perror("Write file failed");
					return;
				}
				tot_bytes -= real_bytes;
				read_bytes = bufsize < tot_bytes ? bufsize : tot_bytes;
			}
		}
	}
}

bool CFileDB::GetMetadata(long slot, Metadata &mdata)
{
	assert(slot >= 0 && slot < m_slot_cnt);

	SeekToMetadata(slot);
	return sizeof(mdata) == m_pFile->read(&mdata, sizeof(mdata));
}

bool CFileDB::WriteMetadata(long slot, const Metadata &mdata)
{
	assert(slot >= 0 && slot < m_slot_cnt);

	SeekToMetadata(slot);
	return m_pFile->write(&mdata, sizeof(mdata));
}

bool CFileDB::WriteSlotCnt(long val)
{
	off_t offset = sizeof(m_magic_nr);
	return m_pFile->pwrite(&val, sizeof(val), offset);
}

bool CFileDB::WriteSlotUsed(long val)
{
	off_t offset = sizeof(m_magic_nr) + sizeof(m_slot_cnt);
	return m_pFile->pwrite(&val, sizeof(val), offset);
}

void CFileDB::SeekToBegin()
{
	m_pFile->seek(0);
}

void CFileDB::SeekToMetadata(long slot)
{
	assert(slot >= 0 && slot < m_slot_cnt);

	off_t offset = m_offset_metadata + slot * sizeof(Metadata);
	m_pFile->seek(offset);
}

void CFileDB::SeekToFiledata(long slot)
{
	if(m_slot_used == 0 || slot == 0)
	{
		off_t offset = m_offset_metadata + m_slot_cnt * sizeof(Metadata);
		m_pFile->seek(offset);
	}
	else
	{
		long slot_prev = slot - 1;
		Metadata mdata;
		if (GetMetadata(slot_prev, mdata))
		{
			off_t offset = mdata.offset + mdata.filesize;
			m_pFile->seek(offset);
		}
	}
}

void CFileDB::SeekToEnd()
{
	SeekToFiledata(m_slot_used);
}