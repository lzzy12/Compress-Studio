#pragma once
#include "Core.h"
#include "archive.h"
namespace cs {
	class CS_UTIL zipper :public archive
	{
	public:
		zipper();
		int compress(std::string& destination, const std::string& password = NULL, int level = CS_DEFAULT_COMPRESSION);
		int decompress();
	};
}