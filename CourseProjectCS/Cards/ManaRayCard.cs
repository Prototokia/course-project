using CourseProjectCS.Combat;
using CourseProjectCS.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal sealed class ManaRayCard : BaseCard, IDamageDealer {
        private const int UpgradeValue = 3;
        public ManaRayCard(string name, string textAbility, int cost, int value) : base(name, textAbility, CardType.Attack, cost, value) { }
        public ManaRayCard(ManaRayCard other) : base(other) { }
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
            return new ManaRayCard(this);
        }

        public override string Describe() {
            return base.Describe() + $"\nЗначение улучшения: {UpgradeValue}";
        }

        public void DealDamage(ITarget target) {
            target.TakeDamage(Value);
        }

        public new string GetKind() {
            return "ManaRayCard";
        }
    }
}
