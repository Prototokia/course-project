// CourseProjectCPP.cpp: определяет точку входа для приложения.
//
#include "CourseProjectCPP.h"

int main()
{
	std::cout << "========== Inheritance Demo ==========" << "\n";

	entities::Player player{ 100, 10, 0 };

	auto drawSource1 = std::make_shared<cards::Card>("Card 1", "Temporary draw source", cards::Card::CardType::eSkill, 0, 0);

	auto drawSource2 = std::make_shared<cards::Card>("Card 2", "Temporary draw source", cards::Card::CardType::eSkill, 0, 0);

	player.AddCardToDeck(drawSource1);
	player.AddCardToDeck(drawSource2);
	
	player.PrepareForCombat();

	{
		std::cout << "\n===== 1. Creating cards =====\n";

		std::unique_ptr<cards::BaseCard> cardArray[] =
		{
			std::make_unique<cards::ManaRayCard>(),
			std::make_unique<cards::BarrierCard>(),
			std::make_unique<cards::MagicIntuitionCard>()
		};

		std::cout << "\n===== 2. Describe =====\n";

		for (const auto& card : cardArray)
		{
			std::cout << card->Describe() << "\n\n";
		}

		std::cout << "\n===== 3. String operations =====\n";

		StringOperationsDemo(*cardArray[0]);

		std::cout << "\n===== 4. This demonstration =====\n";

		cards::CardReceiver receiver;

		cardArray[1]->SendTo(receiver);

		std::cout << "\n===== 5. Upgrade =====\n";

		for (auto& card : cardArray)
		{
			card->Upgrade();
		}

		std::cout << "\n===== 6. Updated descriptions =====\n";

		for (const auto& card : cardArray)
		{
			std::cout << card->Describe() << "\n\n";
		}

		std::cout << "\n===== 7. Play cards =====\n";

		for (const auto& card : cardArray)
		{
			card->Play(player);
		}

		std::cout << "\nRemaining mana: " << player.GetCurrentMana() << '\n';

		std::cout << "\n===== 8. Cloning =====\n";

		std::unique_ptr<cards::BaseCard> clonedCards[] =
		{
			cardArray[0]->Clone(),
			cardArray[1]->Clone(),
			cardArray[2]->Clone()
		};

		for (const auto& card : clonedCards)
		{
			std::cout << card->Describe() << "\n\n";
		}

		std::cout << "\n===== 9. Static members =====\n";

		std::cout << "Created BaseCard objects: " << cards::BaseCard::GetCreatedCount() << '\n';

		std::cout << "\n===== 10. Virtual destructor =====\n";

		cardArray[0].reset();

		std::cout << "\nLeaving card array scope...\n";
	}

	std::cout << "\n========== Constructors Demo ==========\n";

	{
		cards::ManaRayCard original{ 2 };

		cards::ManaRayCard copied{ original };

		cards::ManaRayCard moved{ std::move(copied) };

		cards::ManaRayCard assigned;

		assigned = original;
		assigned = std::move(moved);
		assigned = assigned;     
	}

	std::cout << "\n========== Shallow copy ==========\n";
	{
		cards::ManaRayCard original;

		original.ShareMetadata()->flavorText = "A powerful beam of mana";

		auto shallowCopy = original.ShareMetadata();

		std::cout << "Original: " << original.ShareMetadata()->flavorText << '\n';

		std::cout << "Shallow copy: " << shallowCopy->flavorText << '\n';

		std::cout << "Shared pointers count: " << shallowCopy.use_count() << '\n';

		shallowCopy->flavorText = "Changed through shallow copy";

		std::cout << "\nAfter modification:\n";

		std::cout << "Original: " << original.ShareMetadata()->flavorText << '\n';

		std::cout << "Shallow copy: " << shallowCopy->flavorText << '\n';
	}
	std::cout << "\n========== Deep copy ==========\n";
	{
		cards::ManaRayCard original;

		original.ShareMetadata()->flavorText = "Original metadata";

		std::unique_ptr<cards::BaseCard> deepCopy = original.Clone();

		std::cout << "Original: " << original.ShareMetadata()->flavorText << '\n';

		std::cout << "Deep copy: " << deepCopy->ShareMetadata()->flavorText << '\n';

		deepCopy->ShareMetadata()->flavorText = "Changed through deep copy";

		std::cout << "\nAfter modification:\n";

		std::cout << "Original: " << original.ShareMetadata()->flavorText << '\n';

		std::cout << "Deep copy: " << deepCopy->ShareMetadata()->flavorText << '\n';
	}
	return 0;
}

void StringOperationsDemo(const cards::BaseCard& card)
{
	std::string name{ card.GetName() };

	std::cout << "1. Concatenation\n";

	std::string label = "Selected card " + name;
	std::cout << label << "\n";

	std::cout << "2. Substring find\n";

	std::size_t position = name.find("Ray");

	if (position != std::string::npos)
	{
		std::cout << "3. Substring extraction\n";

		std::string substring = name.substr(position, 3);
		std::cout << "Found substring: " << substring << "\n";
	}

	std::cout << "4. String comparison\n";

	if (name == "Mana Ray")
	{
		std::cout << "This is Mana Ray!\n";
	}
}
