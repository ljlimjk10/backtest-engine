#pragma once

#include "Concepts.h"
#include "Bar.h"


template<typename Source>
requires DataSource<Source>
class BarFeed {
public:
	explicit BarFeed(Source source)
		: source_(source)
	{};

	bool hasNext() { return source_.hasNext(); };

	Bar next() { return source_.next(); };

private:
	Source source_;
};
