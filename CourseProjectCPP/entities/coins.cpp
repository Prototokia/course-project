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

}