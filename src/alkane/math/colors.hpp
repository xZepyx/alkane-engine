#pragma once


struct Color {
    float r;
    float g;
    float b;
    float a;
};

namespace Colors {

    // Uses normalized floats (0-1)

    inline constexpr Color LightGray {200.0f/255.0f, 200.0f/255.0f, 200.0f/255.0f, 1.0f};
    inline constexpr Color Gray      {130.0f/255.0f, 130.0f/255.0f, 130.0f/255.0f, 1.0f};
    inline constexpr Color DarkGray  { 80.0f/255.0f,  80.0f/255.0f,  80.0f/255.0f, 1.0f};

    inline constexpr Color Yellow    {253.0f/255.0f, 249.0f/255.0f,   0.0f/255.0f, 1.0f};
    inline constexpr Color Gold      {255.0f/255.0f, 203.0f/255.0f,   0.0f/255.0f, 1.0f};
    inline constexpr Color Orange    {255.0f/255.0f, 161.0f/255.0f,   0.0f/255.0f, 1.0f};

    inline constexpr Color Pink      {255.0f/255.0f, 109.0f/255.0f, 194.0f/255.0f, 1.0f};
    inline constexpr Color Red       {230.0f/255.0f,  41.0f/255.0f,  55.0f/255.0f, 1.0f};
    inline constexpr Color Maroon    {190.0f/255.0f,  33.0f/255.0f,  55.0f/255.0f, 1.0f};

    inline constexpr Color Green     {  0.0f/255.0f, 228.0f/255.0f,  48.0f/255.0f, 1.0f};
    inline constexpr Color Lime      {  0.0f/255.0f, 158.0f/255.0f,  47.0f/255.0f, 1.0f};
    inline constexpr Color DarkGreen {  0.0f/255.0f, 117.0f/255.0f,  44.0f/255.0f, 1.0f};

    inline constexpr Color SkyBlue   {102.0f/255.0f, 191.0f/255.0f, 255.0f/255.0f, 1.0f};
    inline constexpr Color Blue      {  0.0f/255.0f, 121.0f/255.0f, 241.0f/255.0f, 1.0f};
    inline constexpr Color DarkBlue  {  0.0f/255.0f,  82.0f/255.0f, 172.0f/255.0f, 1.0f};

    inline constexpr Color Purple    {200.0f/255.0f, 122.0f/255.0f, 255.0f/255.0f, 1.0f};
    inline constexpr Color Violet    {135.0f/255.0f,  60.0f/255.0f, 190.0f/255.0f, 1.0f};
    inline constexpr Color DarkPurple{112.0f/255.0f,  31.0f/255.0f, 126.0f/255.0f, 1.0f};

    inline constexpr Color Beige     {211.0f/255.0f, 176.0f/255.0f, 131.0f/255.0f, 1.0f};
    inline constexpr Color Brown     {127.0f/255.0f, 106.0f/255.0f,  79.0f/255.0f, 1.0f};
    inline constexpr Color DarkBrown { 76.0f/255.0f,  63.0f/255.0f,  47.0f/255.0f, 1.0f};

    inline constexpr Color White     {1.0f, 1.0f, 1.0f, 1.0f};
    inline constexpr Color Black     {0.0f, 0.0f, 0.0f, 1.0f};
    inline constexpr Color Blank     {0.0f, 0.0f, 0.0f, 0.0f};
    inline constexpr Color Magenta   {1.0f, 0.0f, 1.0f, 1.0f};
}