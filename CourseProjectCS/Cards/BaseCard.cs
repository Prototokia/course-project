using System;
using System.Collections.Generic;
using System.Text;
using CourseProjectCS.Entities;

namespace CourseProjectCS.Cards {
    internal abstract class BaseCard {
        private static int _createdCount = 0;
        public static int CreatedCount {
            get { return _createdCount; }
            private set { _createdCount = value; }
        }

        private CardMetadata _metadata = new CardMetadata();
        public string FlavorText {
            get { return _metadata.FlavorText; }
            set { _metadata.FlavorText = value; }
        }
        private bool _isUpgraded;
        public string Name { get; private set; } = string.Empty;
        public string TextAbility { get; protected set; } = string.Empty;
        public CardType Type { get; private set; }
        public int Cost { get; protected set; }
        public int Value { get; protected set; }
        protected bool IsUpgraded => _isUpgraded;
        public BaseCard() {
            CreatedCount++;
            Console.WriteLine("Объект [BaseCard] создан конструктором по умолчанию");
        }
        public BaseCard(string name, string textAbility, CardType type, int cost, int value) {
            Name = name;
            TextAbility = textAbility;
            Type = type;
            Cost = cost;
            Value = value;

            CreatedCount++;

            Console.WriteLine("Объект [BaseCard] создан конструктором с параметрами");
        }
        protected BaseCard(BaseCard other) {
            if (other == null) {
                Console.WriteLine("Копия оказалась null");
            }

            Name = other!.Name;
            TextAbility = other.TextAbility;
            Type = other.Type;
            Cost = other.Cost;
            Value = other.Value;
            _isUpgraded = other._isUpgraded;
            _metadata = new CardMetadata(other._metadata);

            CreatedCount++;

            Console.WriteLine("Объект [BaseCard] создан конструктором копирования");

        }


        public bool Play(Player player) {
            if (player == null) {
                return false;
            }

            int currentMana = player.CurrentMana;

            if (currentMana < Cost) {
                Console.WriteLine("Не хватает маны на розыгрыш карты");

                return false;
            }

            if (!player.TrySpendMana(Cost)) {
                return false;
            }

            if (!ApplyEffect(player)) {
                player.GainMana(Cost);

                Console.WriteLine("Эффект карты не может быть применен");

                return false;
            }

            Console.WriteLine($"Карта {Name} была сыграна. Текущая мана: {player.CurrentMana}");
            return true;
        }

        public bool Upgrade() {
            if (_isUpgraded) {
                Console.WriteLine("Карта уже улучшена");

                return false;
            }

            if (!ApplyUpgrade()) {
                Console.WriteLine("Карта не может быть улучшена");

                return false;
            }

            _isUpgraded = true;
            return true;
        }

        public static void PrintCreatedCount() {
            Console.WriteLine($"Создано карт: {CreatedCount}");
        }

        protected abstract bool ApplyEffect(Player player);
        protected abstract bool ApplyUpgrade();
        public abstract BaseCard Clone();

        protected string Header() {
            return $"{Name} [стоимость: {Cost}]";
        }

        public virtual string Describe() {
            return Header() + $"\nСпособность: {TextAbility}" + $"\nТип: {Type}" + $"\nЗначение: {Value}" + $"\nУлучшена: {(_isUpgraded ? "да" : "нет")}";
        }

        public override bool Equals(object? obj) {
            if (ReferenceEquals(this, obj))
                return true;

            if (obj is not BaseCard other)
                return false;

            return GetType() == other.GetType() && Name == other.Name;
        }

        public override int GetHashCode() {
            return HashCode.Combine(GetType(), Name);
        }

        public BaseCard ShallowCopy() {
            CreatedCount++;
            return (BaseCard)MemberwiseClone();
        }
    }
}
