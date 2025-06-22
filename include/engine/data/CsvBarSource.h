#pragma once

#include <string>

#include "Bar.h"
#include <string_view>
#include <__charconv/from_chars_integral.h>

class CsvBarSource
{
public:
	explicit CsvBarSource(const char* current, const char* end)
		: current_(current)
		, end_(end)
	{};

	CsvBarSource(CsvBarSource&& other) noexcept
		: current_{other.current_}
		, end_{other.end_}
		, nextBar_{other.nextBar_}
	{
		other.current_ = nullptr;
		other.end_ = nullptr;
	}

	CsvBarSource(const CsvBarSource& other) = delete;

	CsvBarSource& operator=(CsvBarSource&& other) noexcept
	{
		if (this != &other)
		{
			current_ = other.current_;
			end_ = other.end_;
			nextBar_ = other.nextBar_;
			other.current_ = nullptr;
			other.end_ = nullptr;
		}

		return *this;
	}

	CsvBarSource& operator=(const CsvBarSource& other) = delete;

	bool hasNext()
	{
		if (current_ >= end_) return false;
		const char* lineStart = current_;
		while (current_ < end_ && *current_ != '\n') ++current_;
		std::string_view line(lineStart, current_-lineStart);
		if (current_ < end_) ++current_;

		nextBar_ = parseLine(line);
		return true;

	};

	const Bar& next() const { return nextBar_; }

private:
	const char* current_;
	const char* end_;
	Bar nextBar_;

	template <typename T>
	T parseVal(std::string_view sv)
	{
		T val;
		auto [ptr, ec] = std::from_chars(sv.data(), sv.data()+sv.size(), val);
		if (ec != std::errc()) {
			throw std::runtime_error("parseVal: failed to parse");
		}
		return val;
	}

	Bar parseLine(std::string_view line)
	{
		Bar bar;
		size_t start = 0, end=0;

		auto next = [&]() -> std::string_view
		{
			end = line.find(',', start);
			std::string_view token = line.substr(start, end-start);
			start = end+1;
			return token;
		};

		bar.timestamp = parseVal<uint64_t>(next());
		bar.open      = parseVal<double>(next());
		bar.high      = parseVal<double>(next());
		bar.low       = parseVal<double>(next());
		bar.close     = parseVal<double>(next());
		bar.volume    = parseVal<double>(next());
		return bar;
	}

};
