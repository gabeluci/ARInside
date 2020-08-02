#include "stdafx.h"
#include "UntarStream.h"
#include "../FileSystemUtil.h"
#include "../ARApi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UntarStream::UntarStream(std::istream &stream)
: input(stream)
{
	ARZeroMemory(&header);
}

UntarStream::~UntarStream()
{
}

void UntarStream::ExtractAllTo(const std::string path, IfFileExists onFileExists)
{
	ifFileExists = onFileExists;
	destPath = path;
	/*
	 * 1) Read Header
	 * 2) Check Type
	 * 3a) Create Directory
	 * 3b) Extract File
	 * Loop Next Header
	 */
	while (ReadHeader())
	{
		switch (header.typeflag)
		{
		case DIRTYPE:
			{
				string dirName = FileSystemUtil::CombinePath(destPath, header.name);
				if (!this->CreateOutputDirectory(dirName.c_str()))
				{
					if (errno != EEXIST || (ifFileExists != SKIP && ifFileExists != REPLACE))
					{
						throw untar_exception();
					}
				}
			}
			break;
		case REGTYPE:
		case AREGTYPE:
			//cout << "File: " << header.name << endl;
			ExtractFile();
			break;
		}

	}
}

bool UntarStream::ReadHeader()
{
	input.read(reinterpret_cast<char*>(&header), sizeof(tar_header));
	
	if (input.fail())
	{
		throw untar_exception(untar_exception::READ, 0);
		return false;
	}

	if ((header.typeflag == REGTYPE || header.typeflag == AREGTYPE) && header.name[0] == 0)
	{
		// this is the end of the tar
		return false;
	}

	return true;
}

bool UntarStream::FileExists(const char* fileName)
{
	return (access(fileName, 0) != -1);
}

ostream* UntarStream::CreateOutputStream(const char* fileName)
{
	return new ofstream(fileName, ios_base::out | ios_base::binary);
}

void UntarStream::CloseOutputStream(std::ostream &strm)
{
	reinterpret_cast<ofstream&>(strm).close();
}

bool UntarStream::CreateOutputDirectory(const char* dirName)
{
#ifdef WIN32		
	return (_mkdir(dirName) == 0);
#else
	return (mkdir(dirName, S_IRWXU|S_IRWXG|S_IRWXO) == 0);
#endif
}

void UntarStream::ExtractFile()
{
	string fileName = FileSystemUtil::CombinePath(destPath, header.name);

	if (FileExists(fileName.c_str()))
	{
		if (ifFileExists == FAIL)
		{
			throw untar_exception(untar_exception::WRITE, EEXIST);
		}
		if (ifFileExists == SKIP)
		{
			return;
		}
	}

	auto_ptr<ostream> output(CreateOutputStream(fileName.c_str()));
	if (output->bad())
	{
		throw untar_exception(untar_exception::WRITE);
		return;
	}

	char buffer[TAR_BLOCK_SIZE];
	char* size_end = &header.size[12];
	long size = strtol(header.size, &size_end, 8);
	long rest = size;
	long bytesread = 0;
	while (rest > 0)
	{
		input.read(buffer, TAR_BLOCK_SIZE); // always read in 512 byte blocks. the end of a file is always padded to 512 byte using \0
		if (input.fail())
		{
			throw untar_exception(untar_exception::READ);
			return;
		}
		
		output->write(buffer, (TAR_BLOCK_SIZE < rest ? TAR_BLOCK_SIZE : rest));
		if (output->fail())
		{
			throw untar_exception(untar_exception::WRITE);
			return;
		}

		if (rest > TAR_BLOCK_SIZE)
		{
			bytesread += TAR_BLOCK_SIZE;
			rest -= TAR_BLOCK_SIZE;
		}
		else
		{
			bytesread += rest;
			rest = 0;
		}
	}
	CloseOutputStream(*output);
}

untar_exception::untar_exception()
{
 src = GENERIC; 
 error_no = errno;
 init();
}

untar_exception::untar_exception(error_source es)
{
	src = es; 
	error_no = errno;
	init();
}

untar_exception::untar_exception(error_source es, int error_num)
{
	src = es; 
	error_no = error_num;
	init();
}

void untar_exception::init()
{
	stringstream strm;
	switch (src)
	{
	case READ:
		strm << "reading source file failed";
		break;
	case WRITE:
		strm << "writing destination file failed";
		break;
	default:
		strm << "generic untar exception";
		break;
	}

	if (error_no > 0)
	{
		strm << ": code=" << error_no << ", " << strerror(error_no);
	}

	msg = strm.str();
}
