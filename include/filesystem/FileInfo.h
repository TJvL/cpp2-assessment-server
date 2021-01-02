#ifndef CPP2SERVER_FILEINFO_H
#define CPP2SERVER_FILEINFO_H

#include "FileType.h"

namespace cpp2 {
    struct FileInfo {
    public:
        FileInfo(const std::string& fileName, const unsigned long fileSize, const std::time_t& lastModified, const FileType fileType)
                : fileName(fileName), fileSize(fileSize), fileType(fileType), lastModified(lastModified) {}

        virtual ~FileInfo() = default;

        std::string toString() const {
            std::stringstream stringStream;
            stringStream << getFileTypeCharacter() << '|'
                         << fileName << '|'
                         << lastModified << '|'
                         << fileSize;
            return stringStream.str();
        }

        char getFileTypeCharacter() const {
            switch (fileType) {
                case FILE:
                    return 'F';
                case DIRECTORY:
                    return 'D';
                case OTHER:
                default:
                    return '*';
            }
        }

        const std::string fileName;
        const unsigned long fileSize;
        const FileType fileType;
        const std::time_t lastModified;
    };
}

#endif //CPP2SERVER_FILEINFO_H
