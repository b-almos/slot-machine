#include "graphics/states/PaytableState.h"
#include "graphics/states/StateManager.h"

namespace slot::gfx {
    PaytableState::PaytableState(StateManager& sm, const AssetManager& assets, SlotMachine& logic)
        : State{ sm },
        asset_manager{ assets },
        game_logic{ logic },
        title_text{ assets.getFont("main_font"), "PAYTABLE", 80 },
        prompt_text{ assets.getFont("main_font"), "PRESS TAB TO CLOSE", 40 }
    {
        overlay.setSize({ virtual_width, virtual_height });
        overlay.setPosition({ 0.f, 0.f });
        overlay.setFillColor(sf::Color::Black);

        title_text.setFillColor(sf::Color(255, 225, 100));
        title_text.setPosition({
            (virtual_width - title_text.getLocalBounds().size.x) / 2.f,
            paytable_title_text_y
            });

        prompt_text.setFillColor(sf::Color(180, 150, 50));
        prompt_text.setPosition({
            (virtual_width - prompt_text.getLocalBounds().size.x) / 2.f,
            paytable_prompt_text_y
            });
    }

    void PaytableState::handleEvent(const sf::Event& event, sf::RenderWindow& window)
    {
        if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Tab ||
                key->code == sf::Keyboard::Key::Escape) {
                state_manager.popState();
            }
        }
    }

    void PaytableState::update(float dt) {}

    void PaytableState::render(sf::RenderWindow& window)
    {
        window.draw(overlay);
        window.draw(title_text);

        sf::Text header2(asset_manager.getFont("main_font"), "x2", 36);
        sf::Text header3(asset_manager.getFont("main_font"), "x3", 36);
        sf::Text header4(asset_manager.getFont("main_font"), "x4", 36);
        sf::Text header5(asset_manager.getFont("main_font"), "x5", 36);

        header2.setFillColor(sf::Color(180, 150, 50));
        header3.setFillColor(sf::Color(180, 150, 50));
        header4.setFillColor(sf::Color(180, 150, 50));
        header5.setFillColor(sf::Color(180, 150, 50));

        header2.setPosition({ paytable_col_x2, paytable_header_y });
        header3.setPosition({ paytable_col_x3, paytable_header_y });
        header4.setPosition({ paytable_col_x4, paytable_header_y });
        header5.setPosition({ paytable_col_x5, paytable_header_y });

        window.draw(header2);
        window.draw(header3);
        window.draw(header4);
        window.draw(header5);

        struct SymbolRow {
            Symbol symbol;
            int x2;
            int x3;
            int x4;
            int x5;
        };

        std::array<SymbolRow, 8> rows = { {
            {Symbol::Seven,      0,  20,  200, 1000},
            {Symbol::Grapes,     0,  10,  40,  100},
            {Symbol::Watermelon, 0,  10,  40,  100},
            {Symbol::Bell,       0,  8,   20,  80},
            {Symbol::Plum,       0,  4,   10,  40},
            {Symbol::Orange,     0,  4,   10,  40},
            {Symbol::Lemon,      0,  4,   10,  40},
            {Symbol::Cherry,     1,  4,   10,  40}
        } };

        for (int i = 0; i < symbol_count; ++i) {
            float y = paytable_start_y + i * paytable_row_height;

            std::string key = symbolToTextureKey(rows[i].symbol);
            sf::Sprite sprite(asset_manager.getTexture(key));
            float scale = paytable_sprite_size / static_cast<float>(asset_manager.getTexture(key).getSize().x);
            sprite.setScale({ scale, scale });
            sprite.setPosition({ paytable_sprite_x, y });
            window.draw(sprite);

            int current_bet = game_logic.getCurrentBet();
            auto drawValue = [&](int multiplier, float x) {
                int payout = multiplier * current_bet;
                std::string str = multiplier > 0 ? std::to_string(payout) : "-";
                sf::Text text(asset_manager.getFont("main_font"), str, 36);
                text.setFillColor(multiplier > 0 ? sf::Color(255, 225, 100) : sf::Color(100, 100, 100));
                text.setPosition({ x, y + paytable_text_offset_y });
                window.draw(text);
                };

            drawValue(rows[i].x2, paytable_col_x2);
            drawValue(rows[i].x3, paytable_col_x3);
            drawValue(rows[i].x4, paytable_col_x4);
            drawValue(rows[i].x5, paytable_col_x5);
        }

        window.draw(prompt_text);
    }
}