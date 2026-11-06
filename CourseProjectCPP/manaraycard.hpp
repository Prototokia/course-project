#pragma once

#include "basecard.hpp"

namespace cards
{

class ManaRayCard final : public BaseCard
{
public:
	ManaRayCard();
	explicit ManaRayCard(std::int32_t manaCost);

	ManaRayCard(const ManaRayCard& other);
	ManaRayCard(ManaRayCard&& other) noexcept;

	ManaRayCard& operator=(const ManaRayCard& other);
	ManaRayCard& operator=(ManaRayCard&& other) noexcept;

	~ManaRayCard() override;

	std::unique_ptr<BaseCard> Clone() const override;
	std::string Describe() const override;

private:
	bool ApplyEffect(entities::Player& player) override;
	bool ApplyUpgrade() override;
};

}