#pragma once

// references:
// http://www.gnu.org/software/tar/manual/html_node/Standard.html

// this struct is padded to 512 byte so you can read directly one block into it
struct tar_header
{                              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
  char z_padding[12];           /* 500 */
};

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

#ifdef WIN32
#define access _access
#endif

const int TAR_BLOCK_SIZE = 512;

enum class IfFileExists
{
	FAIL,
	REPLACE,
	SKIP
};

class UntarStream
{
public:
	UntarStream(std::istream &stream);
	~UntarStream();

	void ExtractAllTo(const std::string path, IfFileExists onFileExists = IfFileExists::FAIL);
private:
	istream &input;
	tar_header header;
	std::string destPath;
	IfFileExists ifFileExists = IfFileExists::FAIL;
	
private:
	bool ReadHeader();
	void ExtractFile();	

protected:
	virtual ostream* CreateOutputStream(const char* fileName);
	virtual bool CreateOutputDirectory(const char* dirName);
	virtual void CloseOutputStream(ostream &strm);
	virtual bool FileExists(const char* fileName);
};


enum class untar_exception_source
{
	GENERIC,
	READ,
	WRITE,
};

class untar_exception : public exception
{
public:
	untar_exception();
	untar_exception(untar_exception_source es);
	untar_exception(untar_exception_source es, int error_no);
	virtual ~untar_exception() noexcept {}

	const char* what() const throw() { return msg.c_str(); }

private:
	string msg;
	untar_exception_source src = untar_exception_source::GENERIC;
	int error_no;

	void init();
};
