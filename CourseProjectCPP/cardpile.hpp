#pragma once

#include "card.hpp"

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <random>
#include <memory>

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
	std::vector<std::weak_ptr<Card>> m_cards ;

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
	void AddCard(std::weak_ptr<Card> card);
	std::weak_ptr<Card> RemoveCardAt(std::int32_t index);
	std::weak_ptr<Card> DrawCard();

	[[nodiscard]] std::weak_ptr<Card> GetCardAt(std::int32_t index) const
	{
		if (index < 0 || static_cast<std::size_t>(index) >= m_cards.size()) return {};

		return m_cards[static_cast<std::size_t>(index)];
	}

	[[nodiscard]] std::int32_t GetCount() const
	{
		return static_cast<std::int32_t>(m_cards.size());
	}

	[[nodiscard]] std::int32_t GetCapacity() const
	{
		return static_cast<std::int32_t>(m_cards.capacity());
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