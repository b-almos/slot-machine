#include "graphics/views/HUD.h"

namespace slot::gfx {
	HUD::HUD(const AssetManager& assets)
		: balance_label{ assets.getFont("main_font"), "BALANCE", 32 },
		balance_value{ assets.getFont("main_font"), "0", 48 },
		bet_label{ assets.getFont("main_font"), "BET", 32 },
		bet_value{ assets.getFont("main_font"), "0", 48 },
		win_label{ assets.getFont("main_font"), "WIN", 32 },
		win_value{ assets.getFont("main_font"), "0", 48 }
	{
        sf::Color label_color(180, 150, 50);
        sf::Color value_color(255, 225, 100);

        balance_label.setFillColor(label_color);
        balance_value.setFillColor(value_color);
        bet_label.setFillColor(label_color);
        bet_value.setFillColor(value_color);
        win_label.setFillColor(label_color);
        win_value.setFillColor(value_color);

        balance_label.setPosition({ hud_balance_x, hud_label_y });
        balance_value.setPosition({ hud_balance_x, hud_value_y });
        bet_label.setPosition({ hud_bet_x, hud_label_y });
        bet_value.setPosition({ hud_bet_x, hud_value_y });
        win_label.setPosition({ hud_win_x, hud_label_y });
        win_value.setPosition({ hud_win_x, hud_value_y });
	}


    void HUD::update(int balance, int current_bet, int last_win)
    {
        balance_value.setString(std::to_string(balance));
        bet_value.setString(std::to_string(current_bet));
        win_value.setString(std::to_string(last_win));
    }

    void HUD::draw(sf::RenderWindow& window)
    {
        window.draw(balance_label);
        window.draw(balance_value);
        window.draw(bet_label);
        window.draw(bet_value);
        window.draw(win_label);
        window.draw(win_value);
    }
}