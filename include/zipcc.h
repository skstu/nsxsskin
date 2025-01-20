#if !defined(__8ED16D1D_54AA_4335_9DA0_01ABFC3C3244__)
#define __8ED16D1D_54AA_4335_9DA0_01ABFC3C3244__

#include <stl.h>

class Zipcc final {
public:
	Zipcc() {}
	~Zipcc() = delete;
public:
	static bool IsZipCompress(const std::string& buffer);
	static bool zipCompress(const std::string& src, std::string& dst);
	static bool zipUnCompress(const std::string& src, const size_t& nraw, std::string& dst);
	static bool gzipCompress(const std::string& src, std::string& dst, int level = -1);
	static bool gzipUnCompress(const std::string& src, std::string& dst);

	typedef bool(*tfzipUnCompressProgressCb)(size_t total, size_t current,void* route);
	typedef bool(*tfzipUnCompressCb)(const std::u16string& path, const std::string& buffer, void* route);
	//static bool zipCompressFile(const std::string& inputFile,const std::string& outputFile);
	static bool zipCompressDirectory(const std::u16string& inputDirpath, const std::u16string& outputZipfile);
	static bool zipUnCompress(const std::u16string& inputZipFile, const std::u16string& outputUnzipPath);
	static bool zipUnCompress(const std::u16string& inputZipFile, const std::u16string& outputUnzipPath, const tfzipUnCompressProgressCb&);
	static bool zipUnCompress(const std::u16string& inputZipFile, const tfzipUnCompressCb& uncompress_cb, void* route = nullptr);

	typedef std::map<std::string, std::vector<unsigned char>> bit7zoutmap;
	static bool bit7zUnCompress(
		const std::string& f7za,
		const std::string& inBuffer, bit7zoutmap& outBuffer, const tfzipUnCompressProgressCb& progress_cb,void* route);
	static bool bit7zUnCompress(
		const std::string& f7za,
		const std::string& inBuffer,
		const std::string& outPath,
		const tfzipUnCompressProgressCb& progress_cb, void* route
	);
};

/// /*_ Memade®（新生™） _**/
/// /*_ Tue, 17 Sep 2024 14:10:56 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif///__8ED16D1D_54AA_4335_9DA0_01ABFC3C3244__
