#include "coins.hpp"

namespace entities
{

Coins::Coins(std::int32_t amount)
	: m_amount{ amount }
{
	if (amount < 0)
	{
		throw game::InvalidAmount{ "Coins", amount };
	}
}

Coins& Coins::operator+=(const Coins& other)
{
	m_amount += other.GetAmount();
	return *this;
}

Coins operator+(Coins left, const Coins& right)
{
	left += right;
	return left;
}

std::ostream& operator<<(std::ostream& out, const Coins& coins)
{
	out << coins.m_amount << " coins";

	return out;
}

}