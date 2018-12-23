/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/os/files.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstdio>
#include <stdexcept>

namespace wilcot { namespace os {

bool pathExists(const Path& path) {
	struct stat info;
	return stat(path, &info) == 0;
}

bool isFile(const Path& path) {
	struct stat info;
	if (stat(path, &info) != 0) {
		return false;
	}
	return (info.st_mode & S_IFDIR) == 0;
}

bool isDirectory(const Path& path) {
	struct stat info;
	if (stat(path, &info) != 0) {
		return false;
	}
	return (info.st_mode & S_IFDIR) > 0;
}

std::vector<Path> listDirectory(const Path& path) {
	if (!isDirectory(path)) {
		throw std::runtime_error("Unable to list regular file");
	}
	std::vector<Path> children;
	DIR* directory = opendir(path);
	if (directory) {
		for (;;) {
			struct dirent* entity = readdir(directory);
			if (entity == NULL) {
				break;
			}
			Path child(entity->d_name);
			if (child != Path(".") && child != Path("..")) {
				children.push_back(child);
			}
		}
		closedir(directory);
	}
	return children;
}

void createFile(const Path& path) {
	int fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		throw std::runtime_error("Unable to create file");
	}
	close(fd);
}

void createDirectory(const Path& path) {
	if (mkdir(path, 0777) != 0) {
		throw std::runtime_error("Unable to create directory");
	}
}

void createDirectories(const Path& path) {
	Path parent(path.getParent());
	if (!pathExists(parent)) {
		createDirectories(parent);
	}
	if (!pathExists(path)) {
		createDirectory(path);
	} else if (!isDirectory(path)) {
		throw std::runtime_error("Unable to create directory");
	}
}

void removeFile(const Path& path) {
	if (!isFile(path)) {
		throw std::runtime_error("File does not exists");
	}
	if (remove(path) < 0) {
		throw std::runtime_error("Failed to remove file");
	}
}

void removeDirectory(const Path& path) {
	if (!isDirectory(path)) {
		throw std::runtime_error("Directory does not exists");
	}
	if (remove(path) < 0) {
		throw std::runtime_error("Failed to remove directory");
	}
}

void recursiveRemoveDirectory(const Path& path) {
	if (!isDirectory(path)) {
		throw std::runtime_error("Directory does not exists");
	}
	std::vector<Path> children(listDirectory(path));
	for (std::size_t i = 0; i < children.size(); i++) {
		Path childPath(path / children[i]);
		if (isFile(childPath)) {
			removeFile(childPath);
		}
		if (isDirectory(childPath)) {
			recursiveRemoveDirectory(childPath);
		}
	}
	removeDirectory(path);
}

}}
