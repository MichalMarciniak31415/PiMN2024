#pragma once


class Box {
    float a{}, b{}, c{};

public:
    Box(float _a, float _b, float _c);

    float area();

    float volume();
};
