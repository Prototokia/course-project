#include "manaraycard.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace cards
{

ManaRayCard::ManaRayCard()
	: ManaRayCard{ 1 }
{
	std::cout << "[ManaRayCard] default-constructed\n";
}

ManaRayCard::ManaRayCard(std::int32_t manaCost)
	: BaseCard{ "Mana Ray", "Deals 5 damage", CardType::eAttack, manaCost, 5 }
{
	std::cout << "[ManaRayCard] constructed\n";
}

ManaRayCard::ManaRayCard(const ManaRayCard& other)
	: BaseCard{ other }
{
	std::cout << "[ManaRayCard] copy-constructed\n";
}

ManaRayCard::ManaRayCard(ManaRayCard&& other) noexcept
	: BaseCard{ std::move(other) }
{
	std::cout << "[ManaRayCard] move-constructed\n";
}

ManaRayCard& ManaRayCard::operator=(const ManaRayCard& other)
{
	if (this == &other)
	{
		return *this;
	}

	BaseCard::operator=(other);

	return *this;
}

ManaRayCard& ManaRayCard::operator=(ManaRayCard&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	BaseCard::operator=(std::move(other));

	return *this;
}

ManaRayCard::~ManaRayCard()
{
	std::cout << "[ManaRayCard] destroyed\n";
}

bool ManaRayCard::ApplyEffect(entities::Player& player)
{
	std::cout << "[ManaRayCard] deals " << GetValue() << " damage to the target.\n";

	return true;
}

bool ManaRayCard::ApplyUpgrade()
{
	const auto newDamage = GetValue() + 3;

	SetValue(newDamage);

	const std::string ability = "Deals " + std::to_string(newDamage) + " damage";

	SetTextAbility(ability);

	std::cout << "[ManaRayCard] attack increased to " << GetValue() << '\n';

	return true;
}

std::unique_ptr<BaseCard> ManaRayCard::Clone() const
{
	return std::make_unique<ManaRayCard>(*this);
}

std::string ManaRayCard::Describe() const
{
	return BaseCard::Describe()
		+ "\nEffect: Deals "
		+ std::to_string(GetValue())
		+ " damage.";
}

}