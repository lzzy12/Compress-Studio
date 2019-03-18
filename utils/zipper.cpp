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
				int in = path.rfind("\\");
				if (in == -1)
					in = path.rfind("/");
				std::string rootDir = path.substr(0, in);
				m_do_while_compress();
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

	bool zipper::decompress() {
		return CS_OK;
	}
	std::string zipper::getCurrFile()
	{
		return currFile;
	}
}