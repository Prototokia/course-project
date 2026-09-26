#include "cardpile.hpp"

namespace cards
{

CardPile::CardPile(CardPileType cardPileType, std::uint32_t capacity)
	: m_type{ cardPileType }
	, m_capacity{ capacity > 0 ? capacity : 1 }
	{
	  m_cards = new Card*[m_capacity];
	}

void CardPile::AddCard(Card* card)
{
	if (card == nullptr)
	{
		std::cout << "Cannot add null card.\n";

		return;
	}

	if (m_count == m_capacity)
	{
		std::uint32_t newCapacity = m_capacity * 2;
		Card** newCards = new Card*[newCapacity];

		for (int i = 0; i < m_count; i++)
		{
			newCards[i] = m_cards[i];
		}

		delete[] m_cards;
		m_cards = newCards;
		m_capacity = newCapacity;
	}

	m_cards[m_count] = card;

	m_count++;
}

Card* CardPile::DrawCard()
{
	if (m_count == 0)
	{
		std::cout << "The card pile is empty.\n";

		return nullptr;
	}

	m_count--;

	Card* drawCard = m_cards[m_count];

	m_cards[m_count] = nullptr;

	return drawCard;
}

void CardPile::Shuffle()
{
	if (m_count < 2)
	{
		std::cout << "Not enough cards to shuffle.\n";
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(m_cards, m_cards + m_count, gen);
}

CardPile::~CardPile()
{
	delete[] m_cards;

	std::cout << "CardPile destroyed.\n";
}

}