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

	zipper::zipper() {
		originalSize = 0;
	}
	int zipper::compress(std::string &destination, const std::string& password, int level) {
		if (level < CS_NO_COMPRESSION || level > CS_BEST_COMPRESSION)
			level = MZ_COMPRESS_LEVEL_DEFAULT;
		void *writer = NULL;
		int err;
		mz_zip_writer_create(&writer);
		if(!password.empty())
			mz_zip_writer_set_password(writer, password.c_str());
		mz_zip_writer_set_compress_level(writer, level);
		mz_zip_writer_set_compress_method(writer, MZ_COMPRESS_METHOD_DEFLATE);
		/*std::fstream fs(paths[0], std::ios::in | std::ios::binary);
		if (fs.is_open()) {
			fs.seekg(std::ios::end);
			originalSize = fs.tellg();
			fs.seekg(std::ios::beg);
		}*/
		err = mz_zip_writer_open_file(writer, destination.c_str(), originalSize, 0);
		if (err < 0) {
			std::cout << err;
			mz_zip_writer_delete(&writer);
			return err;
		}

		if (err == MZ_OK) {
			for (std::string path : paths)
			{
				//std::string fileName = path.substr(path.rfind('\\') + 1);
				err = mz_zip_writer_add_path(writer, path.c_str(), NULL, 0, 1);
				if (err < 0)
					return err;
			}
		}
		err = mz_zip_writer_close(writer);
		mz_zip_writer_delete(&writer);
		return err;
	}

	int zipper::decompress() {
		return CS_OK;
	}
}