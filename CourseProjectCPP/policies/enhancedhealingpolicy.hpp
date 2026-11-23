#pragma once
#include "ihealingpolicy.hpp"

namespace entities
{

class EnhancedHealingPolicy : public IHealingPolicy
{
private:
	static constexpr auto ENHANCED_FACTOR = 2;
public:
	~EnhancedHealingPolicy() noexcept override = default;

	std::int32_t CalculateNewHealth(std::int32_t currentHealth, std::int32_t maxHealth, std::int32_t healAmount) const override;
};

}