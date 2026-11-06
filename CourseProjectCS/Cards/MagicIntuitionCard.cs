using CourseProjectCS.Entities;
using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Cards {
    internal sealed class MagicIntuitionCard : BaseCard {
        private const int UpgradeCostValue = 1;
        private const int UpgradeDrawValue = 1;
        public MagicIntuitionCard(string name, string textAbility, int cost, int value) : base(name, textAbility, CardType.Talent, cost, value) { }
        public MagicIntuitionCard(MagicIntuitionCard other) : base(other) { }

        protected override bool ApplyEffect(Player player) {
            int drawnCards = 0;

            for (int i = 0; i < Value; i++) {
                if (!player.DrawCard()) {
                    break;
                }

                drawnCards++;
            }

            if (drawnCards == 0) {
                Console.WriteLine("[MagicIntuitionCard] нет доступных карт");

                return false;
            }

            Console.WriteLine($"[MagicIntuitionCard] добрано карт: {drawnCards}");

            return true;
        }

        protected override bool ApplyUpgrade() {
            Value += UpgradeDrawValue;
            Cost -= UpgradeCostValue;

            TextAbility = $"Немедленно доберите {Value} карт";

            return true;
        }

        public override BaseCard Clone() {
            return new MagicIntuitionCard(this);
        }

        public override string Describe() {
            return base.Describe();
        }
    }
}
