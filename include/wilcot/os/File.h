/**
 * @author Ivan Udovin
 * @license MIT
 */

#ifndef HEADER_wilcot_os_File
#define HEADER_wilcot_os_File

#include <wilcot/Object.h>

#include <wilcot/os/Path.h>

#include <vector>

namespace wilcot { namespace os {

class File : public Object {
public:
	enum Type {
		TYPE_FILE,
		TYPE_DIRECTORY
	};

	File();

	File(const Path& path);

	const Type& getType() const;

	const Path& getPath() const;

	Path getName() const;

	std::vector<File> list() const;

	File getParent() const;

	bool create(Type type = TYPE_FILE) const;

	bool createRecursive(Type type = TYPE_FILE) const;

	bool exists() const;

	bool isFile() const;

	bool isDirectory() const;

	bool canRead() const;

	bool canWrite() const;

	bool canExecute() const;

	static File create(const Path& path, Type type = TYPE_FILE);

	static File createRecursive(const Path& path, Type type = TYPE_FILE);

private:
	Path path_;
};

}}

#endif // HEADER_wilcot_os_File