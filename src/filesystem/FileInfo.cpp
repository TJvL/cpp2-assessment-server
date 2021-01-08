#include <ctime>
#include <utility>
#include <vector>
#include <sstream>
#include "../../include/filesystem/FileInfo.h"

namespace cpp2 {

    FileInfo::FileInfo(std::string  fileName, const unsigned long fileSize, const std::time_t lastModified, const FileType fileType)
            : fileName(std::move(fileName)), fileSize(fileSize), fileType(fileType), lastModified(lastModified) {}

    std::string FileInfo::toString() const {
        std::vector<char> buffer(20);
        std::strftime(buffer.data(), 20, "%Y-%m-%d %H:%M:%S", std::localtime(&lastModified));
        std::stringstream stringStream;
        stringStream << getFileTypeCharacter() << '|'
                     << fileName << '|'
                     << buffer.data() << '|'
                     << fileSize;
        return stringStream.str();
    }

    char FileInfo::getFileTypeCharacter() const {
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
}
