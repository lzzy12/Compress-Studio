#pragma once
#include "Core.h"
#include <vector>
#include <string>
#include <functional>
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
		std::function<void()> m_do_while_compress;
		std::string currFile;
	public:
		virtual bool compress(const std::string &destination, const bool overwrite_if_exists, const std::string& password = "", int level = CS_DEFAULT_COMPRESSION) = 0;
		virtual bool decompress() = 0;
		cs_int getOriginalSize();
		cs_int getFinalSize();
		cs_int getCompressionRatio();
		void addFile(const std::string& path);
		void addFile(const char* path);
		void addFolder(const std::string &path);
		void add(const std::string &path);
		void do_while_compress(std::function<void()> func);
		virtual std::string getCurrFile() = 0;
	};

}