using CourseProjectCS.Entities;
using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Linq;

namespace CourseProjectCS.Cards {
    internal class FireballCard : BaseCard {
        private const int UpgradeValue = 8;
        public FireballCard(string name, string textAbility, int cost, int value) : base(name, textAbility, CardType.Attack, cost, value) { }
        public FireballCard(FireballCard other) : base(other) { }
        protected override bool ApplyEffect(Player player) {
            if (player == null) return false;

            Console.WriteLine($"Карта {Name} наносит {Value} урона");

            return true;
        }
        protected override bool ApplyUpgrade() {
            Value += UpgradeValue;

            TextAbility = TextAbility.Replace('5', '8');

            Console.WriteLine($"[ManaRayCard] урон увеличен до {Value}");

            return true;
        }
        public override BaseCard Clone() {
            return new FireballCard(this);
        }

        public override string Describe() {
            return base.Describe() + $"\nЗначение улучшения: {UpgradeValue}";
        }

    }
}
}
