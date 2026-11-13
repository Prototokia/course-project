#include "fireballcard.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace cards
{

FireballCard::FireballCard()
	: BaseCard{ "Fireball card", "Deals 12 damage", CardType::eAttack, 2, 12 }
{
	std::cout << "[FireballCard] default-constructed\n";
}

FireballCard::FireballCard(std::int32_t manaCost)
	: BaseCard{ "Fireball card", "Deals 12 damage", CardType::eAttack, manaCost, 12 }
{
	std::cout << "[FireballCard] constructed\n";
}

FireballCard::FireballCard(const FireballCard& other)
	: BaseCard{ other }
{
	std::cout << "[FireballCard] copy-constructed\n";
}

FireballCard::FireballCard(FireballCard&& other) noexcept
	: BaseCard{ std::move(other) }
{
	std::cout << "[FireballCard] move-constructed\n";
}

FireballCard& FireballCard::operator=(const FireballCard& other)
{
	if (this == &other)
	{
		return *this;
	}

	BaseCard::operator=(other);

	return *this;
}

FireballCard& FireballCard::operator=(FireballCard&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	BaseCard::operator=(std::move(other));

	return *this;
}

FireballCard::~FireballCard() noexcept
{
	std::cout << "[FireballCard] destroyed\n";
}

bool FireballCard::ApplyEffect(entities::Player& player)
{
	std::cout << "[FireballCard] deals " << GetValue() << " damage to the target.\n";

	return true;
}

bool FireballCard::ApplyUpgrade()
{
	const auto newDamage = GetValue() + 8;

	SetValue(newDamage);

	const std::string ability = "Deals " + std::to_string(newDamage) + " damage";

	SetTextAbility(ability);

	std::cout << "[FireballCard] attack increased to " << GetValue() << '\n';

	return true;
}

std::unique_ptr<BaseCard> FireballCard::Clone() const
{
	return std::make_unique<FireballCard>(*this);
}

std::string FireballCard::Describe() const
{
	return BaseCard::Describe()
		+ "\nEffect: Deals "
		+ std::to_string(GetValue())
		+ " damage.";
}

void FireballCard::DealDamage(combat::ITarget& target)
{
	target.TakeDamage(GetValue());
}

}