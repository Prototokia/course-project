// CourseProjectCPP.cpp: определяет точку входа для приложения.
//
#include "CourseProjectCPP.h"

int main()
{
	std::cout << "=== 1. Static Object in Scope and Dynamic Object ===\n";
	cards::Card* dynamicCard = nullptr;

	{
		std::cout << "--- Entering local scope ---\n";
		cards::Card staticCard{ "Mana Ray", "Deals 6 damage", cards::Card::CardType::eAttack, 1, 6 };

		std::cout << "[static card] Mana ray cost = " << staticCard.GetCost() << "\n";

		dynamicCard = new cards::Card("Barrier", "Gain 5 block", cards::Card::CardType::eSkill, 1, 5);
		std::cout << "--- Exiting local scope (staticCard will be destroyed) ---\n";
	}
	
	std::cout << "[dynamic card] " << dynamicCard->GetName() << " value = " << dynamicCard->GetValue() << "\n";
	dynamicCard->Upgrade();
	std::cout << "[dynamic card] " << dynamicCard->GetName() << "+ value = " << dynamicCard->GetValue() << "\n";
	dynamicCard->Upgrade();

	std::cout << "Destroying dynamic card\n";
	delete dynamicCard;
	dynamicCard = nullptr;

	std::cout << "\n\n";

	std::cout << "=== 2. Dynamic Array of Objects ===\n";
	cards::Card* cardArray = new cards::Card[2]
	{
		cards::Card("Mana Blaze", "Gain 1 mana", cards::Card::CardType::eSkill, 0, 1),
		cards::Card("Death Ray", "Deals 18 damage to all enemies", cards::Card::CardType::eAttack, 2, 18)
	};

	std::cout << "Destroying dynamic array of objects\n";
	delete[] cardArray;
	cardArray = nullptr;

	std::cout << "\n\n";

	std::cout << "=== 3. Array of Dynamic Objects ===\n";
	cards::Card** cardPtrArray = new cards::Card*[2]
	{
		new cards::Card("Plague", "Inflict 3 vulnerable and 3 weakness to all enemies", cards::Card::CardType::eSkill, 2, 3),
		new cards::Card("Carapace", "Ignore next incoming damage once", cards::Card::CardType::eSkill, 2, 1)
	};

	std::cout << "Replacing element at index 0\n";
	delete cardPtrArray[0];
	cardPtrArray[0] = nullptr;

	cardPtrArray[0] = new cards::Card("Ice bolt", "Deals 10 damage, inflicts freeze", cards::Card::CardType::eAttack, 1, 10);

	std::cout << "Destroying array of dynamic objects\n";
	for (std::int32_t i = 0; i < 2; i++) 
	{
		delete cardPtrArray[i];
		cardPtrArray[i] = nullptr;
	}

	delete[] cardPtrArray;
	cardPtrArray = nullptr;

	std::cout << "\n\n";

	std::cout << "=== 4. Composition and Aggregation ===\n";
	std::cout << "Creating aggregated cards\n";

	cards::Card* card1 = new cards::Card("Judjement", "Deals 42 damage", cards::Card::CardType::eAttack, 3, 42);
	cards::Card* card2 = new cards::Card("Heal", "Heals 10 hp", cards::Card::CardType::eSkill, 2, 10);

	{
		std::cout << "\n--- Entering Player local scope ---\n";
		entities::Player player{ 80, 3, 100 };

		player.AddCardToDeck(card1);
		player.AddCardToDeck(card2);

		player.PrepareForCombat();

		player.DrawCard();
		player.DrawCard();

		std::cout << "--- Round 1: Valid Action ---\n";
		bool isPlayed = player.PlayCard(0);

		std::cout << ((isPlayed) ? "Success" : "Error") << "\n";

		std::cout << "Current mana: " << player.GetCurrentMana() << "\n";

		std::cout << "--- Round 2: Invalid Action ---\n";
		isPlayed = player.PlayCard(0);

		std::cout << ((isPlayed) ? "Success" : "Error") << "\n";
		std::cout << "Current mana: " << player.GetCurrentMana() << "\n";

		std::cout << "--- Exiting Player local scope (Player and CardPiles destroyed - Composition) ---\n";
	}

	std::cout << "\n--- Checking Cards After Player Destruction - Aggregation ---\n";
	std::cout << "First aggregated card: " << card1->GetName() << "\n";
	std::cout << "Second aggregated card: " << card2->GetName() << "\n";

	std::cout << "Deleting aggregated cards\n";
	delete card1;
	card1 = nullptr;

	delete card2;
	card2 = nullptr;

	return 0;
}
