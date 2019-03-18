#include "archive.h"
#include <filesystem>
namespace cs
{
	cs_int archive::getOriginalSize() {
		return originalSize;
	}
	
	cs_int archive::getFinalSize()
	{
		return finalSize;
	}
	cs_int archive::getCompressionRatio() {
		return ratio;
	}
	void archive::addFile(const std::string &path)
	{
		paths.push_back(path);
	}
	void archive::addFile(const const char * path)
	{
		// Adds file
		if (path[0] != NULL) // path[0] == NULL means that the char array is empty
			paths.push_back(std::string(path));
	}
	void archive::addFolder(const std::string & path)
	{
		// Adds folder
		for (auto entry : std::filesystem::directory_iterator(path)) {
			addFile(entry.path().string());
		}
	}
	void archive::add(const std::string &path) {
		// adds file or folder both to the archive
		if (std::filesystem::is_directory(path))
			addFolder(path);
		else
			addFile(path);
	}
	void archive::do_while_compress(std::function<void()> func)
	{
		// This function takes a std::function and executes that function 
		// each time a new file is added to the archive.
		m_do_while_compress = func;
	}
}