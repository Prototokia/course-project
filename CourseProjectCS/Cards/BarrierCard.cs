using CourseProjectCS.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal sealed class BarrierCard : BaseCard {
        private const int UpgradeValue = 2;
        public BarrierCard(string name, string textAbility, int cost, int value) : base(name, textAbility, CardType.Skill, cost, value) { }
        public BarrierCard(BarrierCard other) : base(other) { }

        protected override bool ApplyEffect(Player player) {
            if (player == null) return false;


            Console.WriteLine($"Карта {Name} дает {Value} защиты");

            return true;
        }

        protected override bool ApplyUpgrade() {
            Value += UpgradeValue;

            TextAbility = TextAbility.Replace('5', '7');

            Console.WriteLine($"[BarrierCard] защита увеличена до {Value}");

            return true;
        }

        public override BaseCard Clone() {
            return new BarrierCard(this);
        }

        public override string Describe() {
            return Header() + $"\nСпособность {TextAbility}\nЗначение {Value}\nУлучшена {IsUpgraded}";
        }
    }
}
