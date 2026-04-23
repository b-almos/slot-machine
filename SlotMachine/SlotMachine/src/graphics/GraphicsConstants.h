#pragma once

namespace slot::gfx {

    constexpr float virtual_width = 1920.f;
    constexpr float virtual_height = 1080.f;

    constexpr float top_bar_height = 70.f;

    constexpr float symbol_size = 240.f;
    constexpr float reel_gap = 10.f;

    constexpr float grid_width = 5.f * symbol_size + 4.f * reel_gap;
    constexpr float grid_height = 3.f * symbol_size;
    constexpr float grid_origin_x = (virtual_width - grid_width) / 2.f;
    constexpr float grid_origin_y = 130.f;

    constexpr float frame_padding = 10.f;
    constexpr float frame_x = grid_origin_x - frame_padding;
    constexpr float frame_y = grid_origin_y - frame_padding;
    constexpr float frame_width = grid_width + 2.f * frame_padding;
    constexpr float frame_height = grid_height + 2.f * frame_padding;

    constexpr float hud_y = 850.f;
    constexpr float hud_height = virtual_height - hud_y;

    constexpr float message_y = 820.f;

    constexpr float hud_label_y = 870.f;
    constexpr float hud_value_y = 920.f;
    constexpr unsigned int hud_label_size = 30;
    constexpr unsigned int hud_value_size = 46;
    constexpr float hud_balance_x = 200.f;
    constexpr float hud_bet_x = 960.f;
    constexpr float hud_win_x = 1720.f;

    constexpr float spin_speed = 20.f;
    constexpr float stop_duration = 0.6f;
    constexpr float spin_base_time = 0.8f;
    constexpr float reel_stagger = 0.3f;

    constexpr float menu_title_text_y = 300.f;
    constexpr float menu_prompt_text_y = 600.f;

    constexpr float paytable_title_text_y = 30.f;
    constexpr float paytable_prompt_text_y = 1000.f;
    constexpr float paytable_header_y = 130.f;
    constexpr float paytable_start_y = 180.f;
    constexpr float paytable_row_height = 95.f;
    constexpr float paytable_sprite_size = 80.f;
    constexpr float paytable_text_offset_y = 25.f;

    constexpr float paytable_sprite_col = 100.f;
    constexpr float paytable_name_col = 150.f;
    constexpr float paytable_value_col = 200.f;

    constexpr float paytable_width = paytable_sprite_col + paytable_name_col + 4.f * paytable_value_col;
    constexpr float paytable_origin_x = (virtual_width - paytable_width) / 2.f;

    constexpr float paytable_sprite_x = paytable_origin_x;
    constexpr float paytable_name_x = paytable_sprite_x + paytable_sprite_col;
    constexpr float paytable_col_x2 = paytable_name_x + paytable_name_col;
    constexpr float paytable_col_x3 = paytable_col_x2 + paytable_value_col;
    constexpr float paytable_col_x4 = paytable_col_x3 + paytable_value_col;
    constexpr float paytable_col_x5 = paytable_col_x4 + paytable_value_col;
    constexpr float paytable_right_edge = paytable_col_x5 + paytable_value_col;

}