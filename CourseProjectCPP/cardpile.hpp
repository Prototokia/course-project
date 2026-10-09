#pragma once

#include "card.hpp"

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <random>

namespace cards
{

class CardPile
{
public:
	enum class CardPileType
	{
		eNone,
		eDeck,
		eHand,
		eDiscard,
		eDraw,
	};
private:
	static constexpr auto BASE_COUNT = 0;
	static constexpr auto BASE_CAPACITY = 0;

	Card** m_cards{ nullptr };

	std::int32_t m_count{ BASE_COUNT };
	std::int32_t m_capacity{ BASE_CAPACITY };

	CardPileType m_type{ CardPileType::eNone };

public:
	CardPile(CardPileType cardPileType, std::int32_t capacity);

	CardPile()                           = delete;
	CardPile(const CardPile&)            = delete;
	CardPile(CardPile&&)                 = delete;
	CardPile& operator=(const CardPile&) = delete;
	CardPile& operator=(CardPile&&)      = delete;
	~CardPile();

	void Shuffle();
	void AddCard(Card* card);
	Card* RemoveCardAt(std::int32_t index);
	Card* DrawCard();

	[[nodiscard]] Card* GetCardAt(std::int32_t index) const
	{
		if (index < 0 || index >= m_count) return nullptr;
		return m_cards[index];
	}

	[[nodiscard]] std::int32_t GetCount() const
	{
		return m_count;
	}

	[[nodiscard]] std::int32_t GetCapacity() const
	{
		return m_capacity;
	}

	[[nodiscard]] CardPileType GetCardPileType() const
	{
		return m_type;
	}

	void SetCardPileType(CardPileType cardPileType)
	{
		m_type = cardPileType;
	}
};

} // namespace cards