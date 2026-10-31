#pragma once

#include "basecard.hpp"

namespace cards
{

class BarrierCard final : public BaseCard
{
public:
	BarrierCard();
	explicit BarrierCard(std::int32_t manaCost);

	BarrierCard(const BarrierCard& other);
	BarrierCard(BarrierCard&& other) noexcept;

	BarrierCard& operator=(const BarrierCard& other);
	BarrierCard& operator=(BarrierCard&& other) noexcept;

	~BarrierCard() override;

	std::unique_ptr<BaseCard> Clone() const override;
	std::string Describe() const override;

private:
	bool ApplyEffect(entities::Player& player) override;
	bool ApplyUpgrade() override;
};
}