#include "archive.h"
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
	void archive::addFile(const char * path)
	{
		if (path[0] != NULL) // path[0] == NULL means that the char array is empty
			paths.push_back(std::string(path));
	}
	std::string archive::getFileName()
	{
		return fileName;
	}
}