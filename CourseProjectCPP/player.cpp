#include "player.hpp"

namespace entities
{

Player::Player(std::int32_t health, std::int32_t mana, std::int32_t coins)
	: m_maxHealth{ health }
	, m_maxMana{ mana }
	, m_coins{ coins }
{
	m_currentHealth = m_maxHealth;
	m_currentMana = m_maxMana;
}

void Player::TakeDamage(std::uint32_t damageAmount)
{
	if (m_currentHealth - damageAmount < 0)
	{
		m_currentHealth = 0;
	}
	else
	{
		m_currentHealth -= damageAmount;
	}
}

void Player::Heal(std::uint32_t healAmount)
{
	if (m_currentHealth + healAmount > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
	else
	{
		m_currentHealth += healAmount;
	}
}

bool Player::DrawCard()
{
	if (m_draw.GetCount() == 0)
	{
		if (m_discard.GetCount() == 0)
		{
			std::cout << "Both draw and discard piles are empty! Cannot draw.\n";

			return false;
		}

		while (m_discard.GetCount() > 0)
		{
			cards::Card* recycledCard = m_discard.DrawCard();
			m_draw.AddCard(recycledCard);
		}

		m_draw.Shuffle();
	}

	if (m_hand.GetCount() >= MAX_HAND_SIZE)
	{
		std::cout << "Hand is full.\n";

		return false;
	}

	cards::Card* drawnCard = m_draw.DrawCard();
	m_hand.AddCard(drawnCard);

	return true;
}

bool Player::PlayCard(std::uint32_t cardIndex)
{
	if (cardIndex >= m_hand.GetCount())
	{
		std::count << "Invalid card index.\n";

		return false;
	}

	cards::Card* cardToPlay = m_hand.GetCardAt(cardIndex);

	if (!cardToPlay->Play(m_currentMana))
	{
		return false;
	}

	m_hand.RemoveCardAt(cardIndex);
	m_discard.AddCard(cardToPlay);

	return true;
}

Player::~Player()
{
	std::cout << "Player destroyed.\n";
}

}