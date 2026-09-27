#pragma once

#include "cardpile.hpp"

#include <iostream>
#include <cstdint>

namespace entities
{

class Player
{
public:

private:
	static constexpr auto BASE_HEALTH = 0;
	static constexpr auto BASE_MANA = 0;
	static constexpr auto BASE_COINS = 0;
	static constexpr auto BASE_CAPACITY = 1;
	static constexpr auto MAX_HAND_SIZE = 10;

	std::int32_t m_maxHealth{ BASE_HEALTH };
	std::int32_t m_currentHealth{ BASE_HEALTH };
	std::int32_t m_maxMana{ BASE_MANA };
	std::int32_t m_currentMana{ BASE_MANA };
	std::int32_t m_coins{ BASE_COINS };

	cards::CardPile m_deck{ cards::CardPile(cards::CardPile::CardPileType::eDeck, BASE_CAPACITY) };
	cards::CardPile m_hand{ cards::CardPile(cards::CardPile::CardPileType::eHand, BASE_CAPACITY) };
	cards::CardPile m_discard{ cards::CardPile(cards::CardPile::CardPileType::eDiscard, BASE_CAPACITY) };
	cards::CardPile m_draw{ cards::CardPile(cards::CardPile::CardPileType::eDraw, BASE_CAPACITY) };

public:
	Player(std::int32_t health, std::int32_t mana, std::int32_t coins);

	Player()                         = delete;
	Player(const Player&)            = delete;
	Player(Player&&)                 = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&)      = delete;
	~Player();

	void TakeDamage(std::int32_t damageAmount);
	void Heal(std::int32_t healAmount);
	bool DrawCard();
	bool PlayCard(std::uint32_t cardIndex);

	[[nodiscard]] std::int32_t GetMaxHealth() const
	{
		return m_maxHealth;
	}

	[[nodiscard]] std::int32_t GetCurrentHealth() const
	{
		return m_currentHealth;
	}

	[[nodiscard]] std::int32_t GetMaxMana() const
	{
		return m_maxMana;
	}

	[[nodiscard]] std::int32_t GetCurrentMana() const
	{
		return m_currentMana;
	}

	[[nodiscard]] std::int32_t GetCoins() const
	{
		return m_coins;
	}

	void SetMaxHealth(std::int32_t maxHealth)
	{
		m_maxHealth = maxHealth;
	}

	void SetCurrentHealth(std::int32_t health)
	{
		m_currentHealth = health;
	}

	void SetMaxMana(std::int32_t maxMana)
	{
		m_maxMana = maxMana;
	}

	void SetCurrentMana(std::int32_t mana)
	{
		m_currentMana = mana;
	}

	void SetCoins(std::int32_t amount)
	{
		m_coins = amount;
	}
};

} // namespace entities
