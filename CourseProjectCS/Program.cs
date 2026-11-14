using CourseProjectCS.Cards;
using CourseProjectCS.Combat;
using CourseProjectCS.Entities;
using CourseProjectCS.Exceptions;
using CourseProjectCS.Policies;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using CardCollection = System.Collections.Generic.List<CourseProjectCS.Cards.BaseCard>;

namespace CourseProjectCS {
    internal class Program {
        static void Main(string[] args) {
            Console.WriteLine("===== Демонстрация полиморфизма =====");

            Console.WriteLine("===== Раннее и позднее связывание =====");

            ManaRayCard bindingCard = new ManaRayCard("Проверка связывания", "Наносит урон", 1, 5);

            BaseCard baseReference = bindingCard;

            Console.WriteLine($"Через ManaRayCard: {bindingCard.GetKind()}");
            Console.WriteLine($"Через BaseCard: {baseReference.GetKind()}");

            Console.WriteLine(baseReference.Describe());

            Console.WriteLine("===== Интерфейсы и проверка типов =====");

            Player combatPlayer = new Player(100, 10, 20);

            BaseCard attackCard = new ManaRayCard("Луч маны", "Наносит 5 урона", 1, 5);

            BaseCard defensiveCard = new BarrierCard("Барьер", "Дает 5 защиты", 1, 5);

            Console.WriteLine($"Луч маны реализует IDamageDealer: {attackCard is IDamageDealer}");

            Console.WriteLine($"Барьер реализует IDamageDealer: {defensiveCard is IDamageDealer}");

            ITarget target = combatPlayer;

            TryDealDamage(attackCard, target);
            TryDealDamage(defensiveCard, target);

            Console.WriteLine($"Здоровье игрока: {combatPlayer.CurrentHealth}");

            Console.WriteLine("===== Конфигурирование =====");

            Player healingPlayer = new Player(100, 10, 0);

            healingPlayer.TakeDamage(40);

            healingPlayer.HealingPolicy = new StandardHealingPolicy();
            healingPlayer.Heal(10);

            Console.WriteLine($"Здоровье после обычного лечения: {healingPlayer.CurrentHealth}");

            healingPlayer.TakeDamage(40);

            healingPlayer.HealingPolicy = new EnhancedHealingPolicy();
            healingPlayer.Heal(10);

            Console.WriteLine($"Здоровье после усиленного лечения: {healingPlayer.CurrentHealth}");

            Console.WriteLine("===== Исключения =====");

            try {
                combatPlayer.TakeDamage(-10);
            }
            catch (InvalidAmountException ex) {
                Console.WriteLine($"Ошибка игрового правила: {ex.Message}");
            }
            finally {
                Console.WriteLine("Проверка урона завершена");
            }

            BaseCard upgradeCard = new ManaRayCard("Улучшаемая карта","Наносит урон", 1, 5);

            try {
                Console.WriteLine($"Первое улучшение: {upgradeCard.Upgrade()}");

                upgradeCard.Upgrade();
            }
            catch (CardAlreadyUpgradedException ex) {
                Console.WriteLine($"Ошибка игрового правила: {ex.Message}");
            }
            finally {
                Console.WriteLine("Проверка улучшения завершена");
            }

            Console.WriteLine("===== Сортировка карт и IComparable =====");

            CardCollection sortableCards = new CardCollection {
                new BarrierCard("Барьер", "Защита", 1, 5),
                new FireballCard("Огненный шар", "Урон", 2, 10),
                new MagicIntuitionCard("Магическая интуиция", "Добор", 2, 1),
                new ManaRayCard("Атака", "Урон", 1, 5)
            };

            sortableCards.Sort();

            foreach (var card in sortableCards) {
                Console.WriteLine(card.Name);
            }

            Console.WriteLine("===== Освобождение ресурса =====");

            using (var stream = new MemoryStream()) {
                using (var writer = new StreamWriter(stream, leaveOpen: true)) {
                    writer.WriteLine(attackCard.Describe());
                }

                stream.Position = 0;

                using (var reader = new StreamReader(stream, leaveOpen: true)) {
                    Console.WriteLine(reader.ReadToEnd());
                }
            }
        }

        private static void TryDealDamage(BaseCard card, ITarget target) {
            var damageDealer = card as IDamageDealer;

            if (damageDealer == null) {
                Console.WriteLine($"Карта {card.Name} не может наносить урон");

                return;
            }

            damageDealer.DealDamage(target);

            Console.WriteLine($"Карта {card.Name} нанесла урон");
        } 
    }
}
