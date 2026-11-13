#pragma once
#include <cstdint>

namespace entities
{

class IHealingPolicy
{
public:
	virtual ~IHealingPolicy() noexcept = default;

	virtual std::int32_t CalculateNewHealth(std::int32_t currentHealth, std::int32_t maxHealth, std::int32_t healAmount) const = 0;
};

}