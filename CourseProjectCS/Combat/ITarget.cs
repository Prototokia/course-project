using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Combat {
    internal interface ITarget {
        void TakeDamage(int damageAmount);
    }
}
