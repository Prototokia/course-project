#include "player.hpp"

namespace entities
{

Player::Player(std::int32_t health, std::int32_t mana, std::int32_t coins)
	: m_maxHealth{ health }
	, m_maxMana{ mana }
	, m_coins{ coins }
	, m_currentHealth{ health }
	, m_currentMana{ mana }
{}


void Player::TakeDamage(std::int32_t damageAmount)
{
	if (damageAmount < 0)
	{
		std::cout << "Damage amount must be positive.\n";

		return;
	}
	if (m_currentHealth - damageAmount < 0)
	{
		m_currentHealth = 0;
	}
	else
	{
		m_currentHealth -= damageAmount;
	}
}

void Player::Heal(std::int32_t healAmount)
{
	if (healAmount < 0)
	{
		std::cout << "Heal amount must be positive.\n";

		return;
	}
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
	while (true)
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
				auto recycledCard = m_discard.DrawCard();

				if (recycledCard.expired())
				{
					std::cout << "Skipping expired card reference.\n";
					continue;
				}

				m_draw.AddCard(std::move(recycledCard));
			}

			m_draw.Shuffle();
		}

		auto drawnCard = m_draw.DrawCard();

		if (drawnCard.expired())
		{
			std::cout << "Skipping expired card reference.\n";
			continue;
		}

		if (m_hand.GetCount() >= MAX_HAND_SIZE)
		{
			std::cout << "Hand is full.\n";

			m_discard.AddCard(std::move(drawnCard));
		}
		else
		{
			m_hand.AddCard(std::move(drawnCard));
		}

		return true;
	}
}

bool Player::PlayCard(std::int32_t cardIndex)
{
	if (cardIndex < 0 || cardIndex >= m_hand.GetCount())
	{
		std::cout << "Invalid card index.\n";

		return false;
	}

	auto cardToPlay = m_hand.GetCardAt(cardIndex).lock();

	if (!cardToPlay)
	{
		m_hand.RemoveCardAt(cardIndex);

		return false;
	}
	if (!cardToPlay->Play(m_currentMana))
	{
		return false;
	}

	auto played = m_hand.RemoveCardAt(cardIndex);
	m_discard.AddCard(std::move(played));

	return true;
}

void Player::AddCardToDeck(const std::shared_ptr<cards::Card>& card)
{
	if (!card)
	{
		return;
	}

	m_deck.AddCard(std::weak_ptr<cards::Card>{ card });;
}

void Player::PrepareForCombat()
{
	for (std::int32_t i = 0; i < m_deck.GetCount(); i++) 
	{
		auto card = m_deck.GetCardAt(i).lock();

		if (!card) 
		{
			continue;
		}

		m_draw.AddCard(std::weak_ptr<cards::Card>{ card });
	}
}

Player::~Player()
{
	std::cout << "Player destroyed.\n";
}

} // namespace entities