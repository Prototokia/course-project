using System;
using System.Collections.Generic;
using System.Text;

namespace CourseProjectCS.Combat {
    internal interface IDamageDealer {
        void DealDamage(ITarget target);
    }
}
