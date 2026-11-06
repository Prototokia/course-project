#include "barriercard.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace cards
{

BarrierCard::BarrierCard()
	: BaseCard{ "Barrier", "Gain 5 block", CardType::eSkill, 1, 5 }
{
	std::cout << "[BarrierCard] default-constructed\n";
}

BarrierCard::BarrierCard(std::int32_t manaCost)
	: BaseCard{ "Barrier", "Gain 5 block", CardType::eSkill, manaCost, 5 }
{
	std::cout << "[BarrierCard] constructed\n";
}

BarrierCard::BarrierCard(const BarrierCard& other)
	: BaseCard{ other }
{
	std::cout << "[BarrierCard] copy-constructed\n";
}

BarrierCard::BarrierCard(BarrierCard&& other) noexcept
	: BaseCard{ std::move(other) }
{
	std::cout << "[BarrierCard] move-constructed\n";
}

BarrierCard& BarrierCard::operator=(const BarrierCard& other)
{
	if (this == &other)
	{
		return *this;
	}

	BaseCard::operator=(other);

	return *this;
}

BarrierCard& BarrierCard::operator=(BarrierCard&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	BaseCard::operator=(std::move(other));

	return *this;
}

BarrierCard::~BarrierCard()
{
	std::cout << "[BarrierCard] destroyed\n";
}

bool BarrierCard::ApplyEffect(entities::Player& player)
{
	std::cout << "[BarrierCard] grants " << GetValue() << " block to the target.\n";

	return true;
}

bool BarrierCard::ApplyUpgrade()
{
	const auto newBlock = GetValue() + 3;

	SetValue(newBlock);

	const std::string ability = "Gain " + std::to_string(newBlock) + " block";

	SetTextAbility(ability);

	std::cout << "[BarrierCard] block increased to " << GetValue() << '\n';

	return true;
}

std::unique_ptr<BaseCard> BarrierCard::Clone() const
{
	return std::make_unique<BarrierCard>(*this);
}

std::string BarrierCard::Describe() const
{
	return Header()
		+ "\nAbility: " + std::string(GetTextAbility())
		+ "\nEffect: Grants "
		+ std::to_string(GetValue())
		+ " block.";
}

}