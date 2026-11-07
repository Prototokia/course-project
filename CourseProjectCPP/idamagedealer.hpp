#pragma once
#include "itarget.hpp"

namespace combat
{

class IDamageDealer
{
public:
	virtual ~IDamageDealer() = default;

	virtual void DealDamage(ITarget& target) = 0;
};

}

