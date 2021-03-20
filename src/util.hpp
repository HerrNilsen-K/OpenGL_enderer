//
// Created by karl on 19.03.21.
//

#ifndef OPENGL_RENDERER_UTIL_HPP
#define OPENGL_RENDERER_UTIL_HPP

static inline constexpr double map(double value,
                  double start1, double stop1,
                  double start2, double stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}


static inline constexpr float map(float value,
                            float start1, float stop1,
                            float start2, float stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

#endif //OPENGL_RENDERER_UTIL_HPP
