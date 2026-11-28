#pragma once

#include "exceptions/gameruleexceptions.hpp"

#include <iostream>
#include <cstdint>
#include <compare>

namespace entities
{

class Coins
{
private:
	static constexpr auto BASE_AMOUNT = 0;

	std::int32_t m_amount{BASE_AMOUNT};

public:
	Coins() = default;

	explicit Coins(std::int32_t amount);

	~Coins() noexcept = default;

	Coins& operator+=(const Coins& other);
	
	friend Coins operator+(Coins left, const Coins& right)
	{
		left += right;
		return left;
	}

	auto operator<=>(const Coins& other) const = default;

	[[nodiscard]] std::int32_t GetAmount() const
	{
		return m_amount;
	}
};

}