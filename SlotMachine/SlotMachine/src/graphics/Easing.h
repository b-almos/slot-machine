#pragma once

namespace slot::gfx {
    inline float easeOutBack(float t)
    {
        const float c1 = 1.70158f;
        const float c3 = c1 + 1.f;
        return 1.f + c3 * std::pow(t - 1.f, 3) + c1 * std::pow(t - 1.f, 2);
    }
}