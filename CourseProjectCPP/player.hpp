#pragma once

#include "cardpile.hpp"
#include "itarget.hpp"
#include "ihealingpolicy.hpp"
#include "standardhealingpolicy.hpp"

#include <iostream>
#include <cstdint>
#include <memory>

namespace entities
{

class Player : public combat::ITarget
{

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

	cards::CardPile m_deck{ cards::CardPile::CardPileType::eDeck, BASE_CAPACITY };
	cards::CardPile m_hand{ cards::CardPile::CardPileType::eHand, BASE_CAPACITY };
	cards::CardPile m_discard{ cards::CardPile::CardPileType::eDiscard, BASE_CAPACITY };
	cards::CardPile m_draw{ cards::CardPile::CardPileType::eDraw, BASE_CAPACITY };

	std::unique_ptr<IHealingPolicy> m_healingPolicy;

public:
	Player(std::int32_t health, std::int32_t mana, std::int32_t coins);

	Player()                         = delete;
	Player(const Player&)            = delete;
	Player(Player&&)                 = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&)      = delete;
	~Player() noexcept override;

	void TakeDamage(std::int32_t damageAmount) override;
	void Heal(std::int32_t healAmount);
	bool DrawCard();
	bool PlayCard(std::int32_t cardIndex);
	void AddCardToDeck(const std::shared_ptr<cards::Card>& card);
	void PrepareForCombat();

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

	void SetHealingPolicy(std::unique_ptr<IHealingPolicy> policy)
	{
		if (!policy) return;

		m_healingPolicy = std::move(policy);
	}
};

} // namespace entities
