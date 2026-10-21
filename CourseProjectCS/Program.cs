using CourseProjectCS.Cards;
using CourseProjectCS.Entities;
using System.Runtime.CompilerServices;

namespace CourseProjectCS {
    internal class Program {
        static void Main(string[] args) {
            Console.WriteLine("===== Демонстрация игрового сценария =====\n");
            Console.WriteLine("=== Агрегация и композиция ===");

            var card1 = new Card("Кара", "Наносит 42 урона", CardType.Attack, 3, 42);
            var card2 = new Card("Исцеление", "Восстанавливает 10 здоровья", CardType.Skill, 2, 10);

            {
                var player = new Player(80, 3, 100);

                player.AddCardToDeck(card1);
                player.AddCardToDeck(card2);

                player.PrepareForCombat();

                Console.WriteLine("Состояние игрока после подготовки к бою");
                Console.WriteLine(player);

                player.DrawCard();
                player.DrawCard();

                Console.WriteLine("Состояние игрока после добора карт");
                Console.WriteLine(player);

                bool isPlayed = player.PlayCard(0);
                Console.WriteLine(isPlayed ? "Успешно" : "Ошибка");
                Console.WriteLine($"Оставшаяся мана: {player.CurrentMana}");

                Console.WriteLine("Состояние игрока после попытки розыгрыша первой карты");
                Console.WriteLine(player);

                isPlayed = player.PlayCard(0);
                Console.WriteLine(isPlayed ? "Успешно" : "Ошибка");
                Console.WriteLine($"Оставшаяся мана: {player.CurrentMana}");

                Console.WriteLine("Состояние игрока после попытки розыгрыша второй карты");
                Console.WriteLine(player);
            }

            Console.WriteLine("=== Проверка агрегации ===");
            Console.WriteLine(card1);
            Console.WriteLine(card2);

            Console.WriteLine("===== Ссылки и копии =====\n");

            var secondCard1 = card1;

            Console.WriteLine("Улучшаем карту через вторую ссылку");
            secondCard1.Upgrade();

            Console.WriteLine("Вторая ссылка");
            Console.WriteLine(secondCard1);

            Console.WriteLine("Первая ссылка");
            Console.WriteLine(card1);

            Console.WriteLine($"Равны ли ссылки? {ReferenceEquals(secondCard1, card1)}");

            Console.WriteLine("=== Копирование структуры ===");

            var stats = new DemoStats() { Health = 100 };

            var statsCopy = stats;

            statsCopy.Health -= 20;

            Console.WriteLine($"Характеристики копии: {statsCopy.Health}");
            Console.WriteLine($"Характеристики оригинала: {stats.Health}");

            Console.WriteLine("===== Освобождение ресурса без деструктора =====\n");

            using (var resource = new DemoResource("Лог боя")) {
                resource.Write("Запись результата сражения");
                Console.WriteLine("Выходим из using");
            }

            Console.WriteLine("После блока using");

            Console.WriteLine("===== Работа сборщика мусора =====");

            var watcher = CreateTemporaryCard();

            GC.Collect();
            GC.WaitForPendingFinalizers();

            Console.WriteLine($"Объект доступен после сборки мусора? {watcher.TryGetTarget(out _)}");
        }

        [MethodImpl(MethodImplOptions.NoInlining)]
            static WeakReference<Card> CreateTemporaryCard() {
                var temp = new Card("Вспышка маны", "Получите 1 ману", CardType.Skill, 0, 1);
                return new WeakReference<Card>(temp);
            }
        }
}
