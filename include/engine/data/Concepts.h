#pragma once

#include <concepts>

template<typename T>
concept DataSource = requires(T dataSource)
{
	{ dataSource.hasNext() } -> std::convertible_to<bool>;
	{ dataSource.next() };
};