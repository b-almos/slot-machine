#include "graphics/views/HUD.h"

namespace slot::gfx {
	HUD::HUD(const AssetManager& assets)
		: balance_label{ assets.getFont("main_font"), "BALANCE", 32 },
		balance_value{ assets.getFont("main_font"), "0", 48 },
		bet_label{ assets.getFont("main_font"), "BET", 32 },
		bet_value{ assets.getFont("main_font"), "0", 48 },
		win_label{ assets.getFont("main_font"), "WIN", 32 },
		win_value{ assets.getFont("main_font"), "0", 48 },
        spin_button{ assets.getTexture("spin_button") },
        bet_up_button{ assets.getTexture("bet_up_button") },
        bet_down_button{ assets.getTexture("bet_down_button") }
	{
        //sf::Color label_color(180, 150, 50);
        //sf::Color value_color(255, 225, 100);

        sf::Color label_color(sf::Color::White);
        sf::Color value_color(sf::Color::White);

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

        float spin_button_scale = spin_button_size / static_cast<float>(assets.getTexture("spin_button").getSize().x);
        spin_button.setScale({ spin_button_scale, spin_button_scale });
        spin_button.setPosition({ spin_button_x, spin_button_y });

        float bet_button_scale = bet_button_size / static_cast<float>(assets.getTexture("bet_up_button").getSize().x);
        bet_up_button.setScale({ bet_button_scale, bet_button_scale });
        bet_up_button.setPosition({ bet_up_button_x, bet_up_button_y });
        bet_down_button.setScale({ bet_button_scale, bet_button_scale });
        bet_down_button.setPosition({ bet_down_button_x, bet_down_button_y });
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
        window.draw(spin_button);
        window.draw(bet_up_button);
        window.draw(bet_down_button);
    }

    bool HUD::isSpinClicked(sf::Vector2f mouse_pos) const
    {
        return spin_button.getGlobalBounds().contains(mouse_pos);
    }

    bool HUD::isBetUpClicked(sf::Vector2f mouse_pos) const
    {
        return bet_up_button.getGlobalBounds().contains(mouse_pos);
    }

    bool HUD::isBetDownClicked(sf::Vector2f mouse_pos) const
    {
        return bet_down_button.getGlobalBounds().contains(mouse_pos);
    }
}