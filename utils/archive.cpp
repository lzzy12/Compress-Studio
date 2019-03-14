#include "archive.h"
namespace cs
{
	cs_int archive::getOriginalSize() {
		return originalSize;
	}
	cs_int archive::getCompressionRatio() {
		return ratio;
	}
	cs_int archive::getFinalSize() {
		return finalSize;
	}
}