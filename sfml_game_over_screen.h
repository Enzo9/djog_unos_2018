#ifndef SFML_GAME_OVER_SCREEN_H
#define SFML_GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

class sfml_game_over_screen {
public:
  sfml_game_over_screen(const int window_width = 1000, const int window_height = 600);
  void close();
  void exec();
  sf::RenderWindow aboutwindow;
  sf::Text _text;
};

#endif // SFML_GAME_OVER_SCREEN_H
