using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Policies {
    internal class EnhancedHealingPolicy : IHealingPolicy {
        private const int EnhancedFactor = 2;
        public int CalculateNewHealth(int currentHealth, int maxHealth, int healAmount) {
            return Math.Min(currentHealth + EnhancedFactor * healAmount, maxHealth);
        }
    }
}
