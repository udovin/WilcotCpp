/**
 * @author Ivan Udovin
 * @license MIT
 */

#include <wilcot/os/File.h>

#include <stdexcept>

namespace wilcot { namespace os {

File::File() : path_() {}

File::File(const Path& path) : path_(path) {}

const File::Type& File::getType() const {
	throw std::runtime_error("File does not exists");
}

const Path& File::getPath() const {
	return path_;
}

Path File::getName() const {
	return Path();
}

std::vector<File> File::list() const {
	return std::vector<File>();
}

File File::getParent() const {
	return File();
}

bool File::create(File::Type type) const {
	if (exists()) {
		return getType() == type;
	}

	return false;
}

bool File::createRecursive(File::Type type) const {
	if (exists()) {
		return getType() == type;
	}

	File parent(getParent());

	if (!parent.exists()) {
		if (!parent.createRecursive(TYPE_DIRECTORY)) {
			return false;
		}
	}

	return create(type);
}

bool File::exists() const {
	return false;
}

bool File::isFile() const {
	return false;
}

bool File::isDirectory() const {
	return false;
}

bool File::canRead() const {
	return false;
}

bool File::canWrite() const {
	return false;
}

bool File::canExecute() const {
	return false;
}

File File::create(const Path& path, File::Type type) {
	File file(path);

	if (!file.create(type)) {
		throw std::runtime_error("Unable to create file");
	}

	return file;
}

File File::createRecursive(const Path& path, File::Type type) {
	File file(path);

	if (!file.createRecursive(type)) {
		throw std::runtime_error("Unable to create file");
	}

	return file;
}

}}
