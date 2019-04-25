#include "archive.h"
#ifdef LEGACY_CXX
#include <experimental/filesystem>
namespace n_fs = ::std::experimental::filesystem;
#else
#include <filesystem>
namespace n_fs = ::std::filesystem;
#endif


namespace cs
{
	archive::archive() : 
		originalSize(0), 
		finalSize(0),
		progress(0)
	{
	}

	double archive::getOriginalSize() const
	{
		return originalSize;
	}
	
	double archive::getFinalSize()const
	{
		return finalSize;
	}
	cs_int archive::getCompressionRatio() {
		// Not implemented yet. Return CS_OK for now
		return CS_OK;
	}
	void archive::addFile(const char * path)
	{
		// Adds file
		if (path[0] != '\0') // path[0] == '\0' means that the char array is empty
			paths.push_back(std::string(path));
	}	
	
	void archive::addFile(const std::string &path)
	{
		paths.push_back(path);
	}
	
	void archive::setOriginalSize(std::string path)
	{
			if (!n_fs::is_directory(path))
			{
				originalSize += n_fs::file_size(path);
			}
			else
			{
				for(auto entry: n_fs::directory_iterator(path))
					setOriginalSize(entry.path().string());
			}
	}
	void archive::addFolder(const std::string& path)
	{
		// Adds folder
		for (const auto& entry : n_fs::directory_iterator(path)) {
				addFile(entry.path().string());
				setOriginalSize(entry.path().string());
		}
	}
	void archive::add(const std::string &path) {
		// adds file or folder both to the archive
		if (n_fs::is_directory(path))
			addFolder(path);
		else
			addFile(path);
	}
	std::string archive::getCurrFile() const
	{	// Returns file currently being added or extracted to/from the archive
		return currFile;
	}
	void cs::archive::setWhileCompressJob(std::function<void()> func)
	{
		// Sets a job which is to be done before adding any file to the archive
		m_do_while_compress = func;
	}
}
