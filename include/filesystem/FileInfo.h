#ifndef CPP2SERVER_FILEINFO_H
#define CPP2SERVER_FILEINFO_H

#include <string>
#include "FileType.h"

namespace cpp2 {
    class FileInfo {
    public:
        FileInfo(std::string fileName, const unsigned long fileSize, const std::time_t lastModified, const FileType fileType);

        std::string toString() const;

        char getFileTypeCharacter() const;
    private:
        std::string fileName;
        unsigned long fileSize;
        FileType fileType;
        std::time_t lastModified;
    };
}

#endif //CPP2SERVER_FILEINFO_H
