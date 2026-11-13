#pragma once

#include "basecard.hpp"
#include "itarget.hpp"
#include "idamagedealer.hpp"

namespace cards
{

class ManaRayCard final : public BaseCard, public combat::IDamageDealer
{
public:
	ManaRayCard();
	explicit ManaRayCard(std::int32_t manaCost);

	ManaRayCard(const ManaRayCard& other);
	ManaRayCard(ManaRayCard&& other) noexcept;

	ManaRayCard& operator=(const ManaRayCard& other);
	ManaRayCard& operator=(ManaRayCard&& other) noexcept;

	~ManaRayCard() noexcept override;

	std::unique_ptr<BaseCard> Clone() const override;
	std::string Describe() const override;

	void DealDamage(combat::ITarget& target) override;

private:
	bool ApplyEffect(entities::Player& player) override;
	bool ApplyUpgrade() override;
};

}