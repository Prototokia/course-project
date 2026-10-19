// CourseProjectCPP.cpp: определяет точку входа для приложения.
//
#include "CourseProjectCPP.h"

int main()
{
	std::cout << "=== Smart Pointers Demonstration ===\n";
	std::cout << "\n=== 5.1. unique_ptr ===\n";

	{
		std::cout << "Local scope\n";

		auto uniqueCard = std::make_unique<cards::Card>("Mana blaze", "Gain 1 mana", cards::Card::CardType::eSkill, 0, 1);

		std::cout << "Original pointer owns: " << uniqueCard->GetName() << "\n";

		auto transferedCard = std::move(uniqueCard);

		std::cout << "Original pointer is: " << (uniqueCard ? "not null" : "null") << "\n";

		std::cout << "New owner owns: " << transferedCard->GetName() << "\n";

		std::cout << "Leaving local scope...\n";
	}

	std::cout << "\n=== 5.2. shared_ptr ===\n";

	auto sharedCard = std::make_shared<cards::Card>("Fireball", "Deals 12 damage", cards::Card::CardType::eAttack, 1, 12);

	std::cout << "Initial use_count: " << sharedCard.use_count() << "\n";

	{
		auto sharedCopy = sharedCard;

		std::cout << "After copying use_count: " << sharedCard.use_count() << "\n";

		std::cout << "Copy accesses card: " << sharedCopy->GetName() << "\n";

		std::cout << "Leaving local scope...\n";
	}

	std::cout << "After sharedCopy destruction use_count: " << sharedCard.use_count() << "\n";

	std::cout << "Resetting the last shared_ptr...\n";
	sharedCard.reset();

	std::cout << "use_count after reset: " << sharedCard.use_count() << "\n";
	
	std::cout << "\n=== 5.3. weak_ptr ===\n";

	std::weak_ptr<cards::Card> weakCard;

	{
		auto strongOwner = std::make_shared<cards::Card>("Ice bolt", "Deals 10 damage", cards::Card::CardType::eAttack, 1, 10);

		weakCard = strongOwner;

		std::cout << "Created weak_ptr. Object expired: " << (weakCard.expired() ? "yes" : "no") << "\n";

		std::cout << "use_count after creating weak_ptr: " << strongOwner.use_count() << "\n";

		{
			auto lockedCard = weakCard.lock();

			std::cout << "lock() succeeded. Card name: " << lockedCard->GetName() << "\n";

			std::cout << "use_count while locked: " << strongOwner.use_count() << "\n";

			std::cout << "Leaving lockedCard scope...\n";
		}

		std::cout << "use_count after lock scope: " << strongOwner.use_count() << "\n";
		
		std::cout << "Leaving strong owner's scope...\n";
	}

	std::cout << "After owner destruction, object expired: " << (weakCard.expired() ? "yes" : "no") << "\n";

	if (auto lockedCard = weakCard.lock())
	{
		std::cout << "Card is still available: " << lockedCard->GetName() << "\n";
	}
	else
	{
		std::cout << "lock() returned an empty pointer. The Card object no longer exists.\n";
	}
	return 0;
}
