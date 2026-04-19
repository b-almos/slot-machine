#pragma once

namespace slot::gfx {

    constexpr float virtual_width = 1920.f;
    constexpr float virtual_height = 1080.f;

    constexpr float top_bar_height = 70.f;

    constexpr float symbol_size = 240.f;
    constexpr float reel_gap = 10.f;

    constexpr float grid_width = 5.f * symbol_size + 4.f * reel_gap;    // 1240
    constexpr float grid_height = 3.f * symbol_size;                     // 720
    constexpr float grid_origin_x = (virtual_width - grid_width) / 2.f;  // 340
    constexpr float grid_origin_y = 130.f;

    constexpr float frame_padding = 10.f;
    constexpr float frame_x = grid_origin_x - frame_padding;
    constexpr float frame_y = grid_origin_y - frame_padding;
    constexpr float frame_width = grid_width + 2.f * frame_padding;
    constexpr float frame_height = grid_height + 2.f * frame_padding;

    constexpr float hud_y = 850.f;
    constexpr float hud_height = virtual_height - hud_y;

    constexpr float message_y = 820.f;

}