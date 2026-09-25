#include "card.hpp"

namespace cards
{

Card::Card(std::string_view name, std::string_view textAbility, CardType cardType, std::uint8_t manaCost, std::uint32_t value)
	: m_name{ name }
	, m_textAbility{ textAbility }
	, m_cardType{ cardType }
	, m_manaCost{ manaCost }
	, m_value{ value }
{}

bool Card::Play(int& playerMana)
{
	if (playerMana < m_manaCost) 
	{
		std::cout << "Not enough mana to play the card.\n";

		return false;
	}

	playerMana -= m_manaCost;

	std::cout << "The card " << m_name << "has been played. " << "Remaining mana: " << playerMana << std::endl;

	return true;
}

bool Card::Upgrade()
{
	if (m_isUpgraded)
	{
		std::cout << "The card has already been upgraded.\n";

		return false;
	}

	m_isUpgraded = true;
	m_value += 5;

	return true;
}

Card::~Card()
{
	std::cout << "Card " << m_name << " destroyed.\n";
}

} // namespace cards