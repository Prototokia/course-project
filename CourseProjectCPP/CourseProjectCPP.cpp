// CourseProjectCPP.cpp: определяет точку входа для приложения.
//
#include "CourseProjectCPP.h"

int main()
{
	cards::Card* dynamicCard = nullptr;

	{
		cards::Card staticCard{ "Mana Ray", "Deals 6 damage", cards::Card::CardType::eAttack, 1, 6 };

		dynamicCard = new cards::Card("Barrier", "Gain 5 block", cards::Card::CardType::eSkill, 1, 5);
	}

	std::cout << dynamicCard->GetValue() << "\n";
	dynamicCard->Upgrade();
	std::cout << dynamicCard->GetValue() << "\n";

	delete dynamicCard;
	dynamicCard = nullptr;

	std::cout << "\n\n";

	cards::Card* cardArray = new cards::Card[2]
	{
		cards::Card("Mana Blaze", "Gain 1 mana", cards::Card::CardType::eSkill, 0, 1),
		cards::Card("Death Ray", "Deals 18 damage to all enemies", cards::Card::CardType::eAttack, 2, 18)
	};

	delete[] cardArray;
	cardArray = nullptr;

	cards::Card** cardPtrArray = new cards::Card*[2]
	{
		new cards::Card("Plague", "Inflict 3 vulnerable and 3 weakness to all enemies", cards::Card::CardType::eSkill, 2, 3),
		new cards::Card("Carapace", "Ignore next incoming damage once", cards::Card::CardType::eSkill, 2, 1)
	};

	delete cardPtrArray[0];
	cardPtrArray[0] = nullptr;

	cardPtrArray[0] = new cards::Card("Ice bolt", "Deals 10 damage, inflicts freeze", cards::Card::CardType::eAttack, 1, 10);

	for (std::int32_t i = 0; i < 2; i++) 
	{
		delete cardPtrArray[i];
		cardPtrArray[i] = nullptr;
	}

	delete[] cardPtrArray;
	cardPtrArray = nullptr;

	std::cout << "\n\n";

	cards::Card* card1 = new cards::Card("Judjement", "Deals 42 damage", cards::Card::CardType::eAttack, 3, 42);
	cards::Card* card2 = new cards::Card("Heal", "Heals 10 hp", cards::Card::CardType::eSkill, 2, 10);

	{
		entities::Player player{ 80, 3, 100 };

		player.AddCardToDeck(card1);
		player.AddCardToDeck(card2);

		player.PrepareForCombat();

		player.DrawCard();
		player.DrawCard();

		std::cout << "Round 1. Valid action\n";
		bool isPlayed = player.PlayCard(0);

		std::cout << ((isPlayed) ? "Success\n" : "Error\n");

		std::cout << "Current mana: " << player.GetCurrentMana() << "\n";

		std::cout << "Round 2. Invalid action\n";
		isPlayed = player.PlayCard(0);

		std::cout << ((isPlayed) ? "Success\n" : "Error\n");
		std::cout << "Current mana: " << player.GetCurrentMana() << "\n";
	}
	std::cout << "\n\n";

	std::cout << "First aggregated card: " << card1->GetName() << "\n";
	std::cout << "Second aggregated card: " << card2->GetName() << "\n";

	delete card1;
	card1 = nullptr;

	delete card2;
	card2 = nullptr;

	return 0;
}
