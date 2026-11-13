#pragma once
#include "ihealingpolicy.hpp"

namespace entities
{

class StandardHealingPolicy : public IHealingPolicy
{
public:
	~StandardHealingPolicy() noexcept override = default;

	std::int32_t CalculateNewHealth(std::int32_t currentHealth, std::int32_t maxHealth, std::int32_t healAmount) const override;
};

}