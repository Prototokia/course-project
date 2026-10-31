#include "basecard.hpp"
#include "player.hpp"

#include <iostream>
#include <utility>

namespace cards
{

BaseCard::BaseCard()
{
	m_createdCount++;
    std::cout << "[BaseCard] default-constructed: " << m_name << '\n';
}

BaseCard::BaseCard(std::string_view name, std::string_view textAbility, CardType cardType, std::int32_t cost, std::int32_t value)
	: m_name{ name }
	, m_textAbility{ textAbility }
	, m_cardType{ cardType }
	, m_manaCost{ cost }
	, m_value{ value }
{
	m_createdCount++;
    std::cout << "[BaseCard] constructed: " << m_name << '\n';
}

BaseCard::BaseCard(const BaseCard& other)
    : m_name{ other.m_name }
    , m_textAbility{ other.m_textAbility }
    , m_cardType{ other.m_cardType }
    , m_manaCost{ other.m_manaCost }
    , m_value{ other.m_value }
    , m_isUpgraded{ other.m_isUpgraded }
{
    m_createdCount++;
    std::cout << "[BaseCard] copy-constructed: " << m_name << '\n';
}

BaseCard::BaseCard(BaseCard&& other) noexcept
    : m_name{ std::move(other.m_name) }
    , m_textAbility{ std::move(other.m_textAbility) }
    , m_cardType{ other.m_cardType }
    , m_manaCost{ other.m_manaCost }
    , m_value{ other.m_value }
    , m_isUpgraded{ other.m_isUpgraded }
{
    m_createdCount++;
    std::cout << "[BaseCard] move-constructed: " << m_name << '\n';
}

BaseCard& BaseCard::operator=(const BaseCard& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_name = other.m_name;
    m_textAbility = other.m_textAbility;
    m_cardType = other.m_cardType;
    m_manaCost = other.m_manaCost;
    m_value = other.m_value;
    m_isUpgraded = other.m_isUpgraded;

    return *this;
}

BaseCard& BaseCard::operator=(BaseCard&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    m_name = std::move(other.m_name);
    m_textAbility = std::move(other.m_textAbility);
    m_cardType = other.m_cardType;
    m_manaCost = other.m_manaCost;
    m_value = other.m_value;
    m_isUpgraded = other.m_isUpgraded;

    return *this;
}

BaseCard::~BaseCard()
{
    std::cout << "[BaseCard] destroyed: " << m_name << '\n';
}

bool BaseCard::Play(entities::Player& player)
{
    const auto currentMana = player.GetCurrentMana();

    if (currentMana < m_manaCost)
    {
        std::cout << "Not enough mana to play card\n";
        return false;
    }
    
    player.SetCurrentMana(currentMana - m_manaCost);

    if (!ApplyEffect(player)) {
        player.SetCurrentMana(currentMana);

        std::cout << "The card effect could not be applied.\n";
        return false;
    }

    

    std::cout << "The card " << m_name << " has been played. Remaining mana: " << player.GetCurrentMana();

    return true;
}

bool BaseCard::Upgrade()
{
    if (m_isUpgraded)
    {
        std::cout << "The card has already been upgraded.\n";
        return false;
    }

    if (!ApplyUpgrade())
    {
        std::cout << "The card could not be upgraded.\n";
        return false;
    }

    m_isUpgraded = true;

    return true;
}

std::string BaseCard::Header() const
{
    return m_name + " [mana cost: " + std::to_string(m_manaCost) + "]";
}

std::string BaseCard::Describe() const
{
    return Header() 
        + "\nAbility: " + m_textAbility 
        + "\nType: " + std::to_string(static_cast<int>(m_cardType)) 
        + "\nValue: "  + std::to_string(m_value) 
        + "\nUpgraded: " + (m_isUpgraded ? "yes" : "no");
}

}