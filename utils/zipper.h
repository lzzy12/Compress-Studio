#pragma once
#include "Core.h"
#include "archive.h"
namespace cs {
	class CS_UTIL zipper : archive
	{
	public:
		int compress();
		int decompress();
	};
}