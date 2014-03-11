//-----------------------------//
// file system operation, such as mkdir/ls/getpath.etc
//-----------------------------//
#ifndef FILE_SYS_H__
#define FILE_SYS_H__

#include <string>
#include <vector>
#include <sys/types.h>

class FileSys
{
public:

    int MakeDir(const char *pPath, mode_t iMode);

    int GetPath(const char *pFullName, std::string &strPath);

    int Ls(const char *pPath, const char *pFilterString, std::vector<std::string> &vecResult);

    int SaveFile(const char *pPath, const char *pContent, unsigned iSize);

	int StrtoK(char* str, const char* sep);

	int StrtoKCPP(char* str, const char* sep);
};

#endif  //FILE_SYS_H__
