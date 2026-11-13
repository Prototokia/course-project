#pragma once

#include "basecard.hpp"
#include "itarget.hpp"
#include "idamagedealer.hpp"

namespace cards
{

class FireballCard final : public BaseCard, public combat::IDamageDealer
{
public:
	FireballCard();
	explicit FireballCard(std::int32_t manaCost);

	FireballCard(const FireballCard& other);
	FireballCard(FireballCard&& other) noexcept;

	FireballCard& operator=(const FireballCard& other);
	FireballCard& operator=(FireballCard&& other) noexcept;

	~FireballCard() override;

	std::unique_ptr<BaseCard> Clone() const override;
	std::string Describe() const override;

	void DealDamage(combat::ITarget& target) override;

private:
	bool ApplyEffect(entities::Player& player) override;
	bool ApplyUpgrade() override;
};

}