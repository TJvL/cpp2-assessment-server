#ifndef CPP2SERVER_FILESYSTEMMANAGER_H
#define CPP2SERVER_FILESYSTEMMANAGER_H

#include <filesystem>
#include <vector>
#include "../../include/filesystem/FileInfo.h"

namespace cpp2 {
    class FileSystemManager {
    public:
        FileSystemManager(const std::string &syncDirectoryName = "sync");

        virtual ~FileSystemManager() = default;

        unsigned long freeSpaceAvailable(const std::filesystem::path &relativePath) const;

        bool hasReadPermissions(const std::filesystem::path &relativePath) const;

        bool hasWritePermissions(const std::filesystem::path &relativePath) const;

        bool pathExists(const std::filesystem::path &relativePath) const;

        unsigned long fileSize(const std::filesystem::path &relativePath) const;

        void makeDirectory(const std::filesystem::path &relativePath, const std::string &directoryName) const;

        void deletePath(const std::filesystem::path &relativePath) const;

        void renamePath(const std::filesystem::path &relativePath, const std::string& newName) const;

        std::vector<FileInfo> listDirectoryInformation(const std::filesystem::path &relativePath) const;

        void writeFileFromStream(const std::filesystem::path &relativePath, std::istream &inputStream, const unsigned long readSize) const;

        std::unique_ptr<const std::istream> openReadFileStream(const std::filesystem::path &relativePath) const;

    private:
        const std::filesystem::path rootSyncPath;
    };
}

#endif //CPP2SERVER_FILESYSTEMMANAGER_H
