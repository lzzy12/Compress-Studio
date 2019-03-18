#pragma once
#include "Core.h"
#include "archive.h"
namespace cs {
	class CS_UTIL zipper : public archive
	{
	public:
		zipper();
		bool compress(const std::string& destination, const bool overwrite_if_exists, const std::string& password = "", int level = CS_DEFAULT_COMPRESSION);
		bool decompress();
		std::string getCurrFile();
	};
}