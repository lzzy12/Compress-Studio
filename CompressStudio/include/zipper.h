#pragma once
#include "Core.h"
#include "archive.h"
#include "mz_zip.h"
namespace cs {
	class CS_UTIL zipper : public archive
	{
	protected:
		friend int32_t minizip_add_progress_cb(void* handle, void* userdata, mz_zip_file* file_info, int64_t position);
	public:
		zipper();
		bool compress(const std::string& destination, const bool overwrite_if_exists,
			const std::string& password = "", int level = CS_DEFAULT_COMPRESSION);

		bool decompress(const std::string& zip_path, const std::string& destination,
			const std::string &pattern = "", const std::string &password = "");
		std::vector<std::string> listArchive(std::string path, const std::string &pattern = "*") const;
		double getProgress() const;

	};
}