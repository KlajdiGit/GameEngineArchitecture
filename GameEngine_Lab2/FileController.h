#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "StandardIncludes.h"

class FileController : public Singleton<FileController>
{
public:
	//Constructors/Destructors
	FileController();
	virtual ~FileController();

	//Accessors
	bool GetFilereadDone() { return !m_thread.joinable(); }
	bool GetFileReadSuccess() { return m_readSuccess; }

	//Methods
	string GetCurDirectory();
	int GetFileSize(string _filePath);
	bool ReadFile(string _filePath, unsigned char* _buffer, unsigned int _bufferSize);
	void ReadFileAsync(string _filePath, unsigned char* _buffer, unsigned int _bufferSize);

private:
	FILE* m_handle;
	thread m_thread;
	bool m_readSuccess;
};

#endif //FILE_CONTROLLER_H 