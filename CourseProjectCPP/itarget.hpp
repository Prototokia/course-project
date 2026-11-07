#pragma once
#include <cstdint>

namespace combat
{

class ITarget
{
public:
	virtual ~ITarget() = default;

	virtual void TakeDamage(std::int32_t damageAmount) = 0;
};

}
