#pragma once
#include "itarget.hpp"

namespace combat
{

class IDamageDealer
{
public:
	virtual ~IDamageDealer() noexcept = default;

	virtual void DealDamage(ITarget& target) = 0;
};

}

