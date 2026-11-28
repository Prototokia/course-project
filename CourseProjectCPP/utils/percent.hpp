#pragma once

#include <concepts>
#include <stdexcept>

namespace utils
{
	template <typename T>
	concept Numeric = std::integral<T> || std::floating_point<T>;

	template <Numeric T>
	double Percent(T part, T whole)
	{
		if (whole == 0)
		{
			throw std::invalid_argument("Zero divison");
		}

		return (static_cast<double>(part) / static_cast<double>(whole)) * 100.0;
	}
}