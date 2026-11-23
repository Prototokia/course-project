using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Policies {
    internal interface IHealingPolicy {
        int CalculateNewHealth(int currentHealth, int maxHealth, int healAmount);
    }
}
