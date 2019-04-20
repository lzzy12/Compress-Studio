#include "zipper.h"
#include <iostream>
#include <fstream>
#include "mz.h"
#include "mz_os.h"
#include "mz_strm.h"
#include "mz_strm_buf.h"
#include "mz_strm_split.h"
#include "mz_zip.h"
#include "mz_zip_rw.h"
namespace cs {

	zipper::zipper(){
		originalSize = 0;
		overwrite_compress = false;
		overwrite_extract = false;
	}
	bool zipper::compress(const std::string &destination, const bool overwrite_if_exists, const std::string& password, int level) {
		if (level < CS_NO_COMPRESSION || level > CS_BEST_COMPRESSION)
			level = MZ_COMPRESS_LEVEL_DEFAULT;
		void *writer = NULL;
		int err;
		mz_zip_writer_create(&writer);
		if(!password.empty())
			mz_zip_writer_set_password(writer, password.c_str());
		mz_zip_writer_set_compress_level(writer, level);
		mz_zip_writer_set_compress_method(writer, MZ_COMPRESS_METHOD_DEFLATE);
		err = mz_zip_writer_open_file(writer, destination.c_str(), 0, (int) !overwrite_if_exists);
		if (err < 0) {
			std::cout << err;
			mz_zip_writer_delete(&writer);
			return !CS_OK;
		}

		if (err >= 0) {
			for (std::string path : paths)
			{
				size_t in = path.rfind("\\");
				if (in == -1)
					in = path.rfind("/");
				std::string rootDir = path.substr(0, in);
				currFile = path;
				m_do_pre_compress();
				err = mz_zip_writer_add_path(writer, path.c_str(), rootDir.c_str(), 0, 1);
				if (err < 0)
					return !CS_OK;
			}
		}
		err = mz_zip_writer_close(writer);
		mz_zip_writer_delete(&writer);
		if (err < 0)
			return !CS_OK;
		return CS_OK;
	}

	bool zipper::decompress(const std::string& zip_path, const std::string& destination, const std::string &pattern, const std::string &password) {
		void *reader = NULL;
		mz_zip_reader_create(&reader);
		if (!password.empty())
			mz_zip_reader_set_password(reader, password.c_str());
		mz_zip_reader_set_encoding(reader, 0);
		if(!pattern.empty())
			mz_zip_reader_set_pattern(reader, pattern.c_str(), 1);

		if (mz_zip_reader_open_file(reader, zip_path.c_str()) == MZ_OK) // Means everything OK
		{
			if (mz_zip_reader_save_all(reader, destination.c_str()) != MZ_OK)
				return !CS_OK;
			
			if(mz_zip_reader_close(reader) != MZ_OK)
				return !CS_OK;
			
		}
		mz_zip_reader_delete(&reader);
		return CS_OK;

	}

	std::vector<std::string> zipper::listArchive(std::string path)
	{
		std::vector<std::string> r;
		mz_zip_file* file_info = NULL;
		uint32_t ratio = 0;
		int16_t level = 0;
		int32_t err = MZ_OK;
		struct tm tmu_date;
		const char* string_method = NULL;
		char crypt = ' ';
		void* reader = NULL;
		mz_zip_reader_create(&reader);
		err = mz_zip_reader_open_file(reader, path.c_str());
		if (err != MZ_OK)
		{
			mz_zip_reader_delete(&reader);
			return std::vector<std::string>();	// return an empty vector if error occurs
		}
		err = mz_zip_reader_goto_first_entry(reader);
		if (err != MZ_OK && err != MZ_END_OF_LIST)
		{
			mz_zip_reader_delete(&reader);
			return std::vector<std::string>();
		}
		do {

			err = mz_zip_reader_entry_get_info(reader, &file_info);
			if (err != MZ_OK)
				break;
			r.push_back(file_info->filename);
			err = mz_zip_reader_goto_next_entry(reader);
		} while (err == MZ_OK);
		if (err != MZ_OK && err != MZ_END_OF_LIST)
		{
			mz_zip_reader_delete(&reader);
			return std::vector<std::string>();
		}
		return r;
	}
	
}