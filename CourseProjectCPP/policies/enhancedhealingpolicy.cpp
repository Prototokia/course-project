#include "enhancedhealingpolicy.hpp"
#include <algorithm>

namespace entities
{

std::int32_t EnhancedHealingPolicy::CalculateNewHealth(std::int32_t currentHealth, std::int32_t maxHealth, std::int32_t healAmount) const
{
	return std::min(currentHealth + ENHANCED_FACTOR * healAmount, maxHealth);
}

}