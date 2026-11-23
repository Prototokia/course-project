using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Policies {
    internal class StandardHealingPolicy : IHealingPolicy {
        public int CalculateNewHealth(int currentHealth, int maxHealth, int healAmount) {
            return Math.Min(currentHealth + healAmount, maxHealth);
        }
    }
}
