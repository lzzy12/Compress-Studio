#pragma once
#include "Core.h"
#include <vector>
#include <string>
namespace cs {
	class CS_UTIL archive
	{

		/* A base class which will be derived by the classes which will be
		* used to implement different de/compression algorithms
		*/
	protected:
		cs_int originalSize;
		cs_int finalSize;
		cs_int ratio;
		bool overwrite_extract;
		bool overwrite_compress;
		std::vector<std::string> paths;
		std::string fileName;
	public:
		virtual bool compress(std::string &destination, bool overwrite_if_exists = false, const std::string& password = "", int level = CS_DEFAULT_COMPRESSION) = 0;
		virtual bool decompress() = 0;
		cs_int getOriginalSize();
		cs_int getFinalSize();
		cs_int getCompressionRatio();
		void addFile(const std::string& path);
		void addFile(const char* path);
		std::string getFileName();
	};

}