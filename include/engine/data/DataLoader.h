#pragma once

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string>

class DataLoader
{
public:
	DataLoader(const std::string& path)
	{
		fd_ = open(path.c_str(), O_RDONLY);
		if (fd_ < 0) throw std::runtime_error("failed to open file");

		struct stat st;
		fstat(fd_, &st);
		length_ = st.st_size;

		data_ = mmap(nullptr, length_, PROT_READ, MAP_PRIVATE, fd_, 0);
		if (data_ == MAP_FAILED) throw std::runtime_error("mmap failed");
	}

	~DataLoader()
	{
		munmap(data_, length_);
		if (fd_ >= 0) close(fd_);
	}

	const char* begin() const
	{
		return static_cast<const char*>(data_);
	}

	const char* end() const
	{
		return static_cast<const char*>(data_)+length_;
	}

private:
	int fd_ = -1;
	size_t length_ = 0;
	void* data_ = nullptr;
};
