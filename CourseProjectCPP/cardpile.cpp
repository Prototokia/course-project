#include "cardpile.hpp"

namespace cards
{

CardPile::CardPile(CardPileType cardPileType, std::int32_t capacity)
	: m_type{ cardPileType }
{
	m_cards.reserve(static_cast<std::size_t>(capacity > 0 ? capacity : 1));
}

void CardPile::AddCard(std::weak_ptr<Card> card)
{
	if (card.expired()) {
		std::cout << "Cannot add null or expired card\n";

		return;
	}

	m_cards.push_back(std::move(card));
}

std::weak_ptr<Card> CardPile::RemoveCardAt(std::int32_t index)
{
	if (index < 0 || static_cast<std::size_t>(index) >= m_cards.size()) return {};

	auto removedCard = std::move(m_cards[static_cast<std::size_t>(index)]);

	m_cards.erase(m_cards.begin() + index);

	return removedCard;
}

std::weak_ptr<Card> CardPile::DrawCard()
{
	if (m_cards.empty())
	{
		std::cout << "The card pile is empty.\n";

		return {};
	}

	auto drawCard = std::move(m_cards.back());

	m_cards.pop_back();

	return drawCard;
}

void CardPile::Shuffle()
{
	if (m_cards.size() < 2)
	{
		std::cout << "Not enough cards to shuffle.\n";
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(m_cards.begin(), m_cards.end(), gen);
}

CardPile::~CardPile()
{
	std::cout << "CardPile destroyed.\n";
}

} // namespace cards