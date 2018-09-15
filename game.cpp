#include <game.h>

game::game(const std::vector<std::string>& args)
  : sfml_game_object(800, 600),
    m_n_displayed_max{extract_n_displayed_max(args)}

{

}

int game::exec()
{
    sfml_game_object.init();
    while (sfml_game_object.m_window.isOpen())
    {
      fixed_update();
      process_input();
      process_events();
      update();
      sfml_game_object.display();
    }

    return 0;
}

void game::update(){
    sf::RectangleShape shape(sf::Vector2f(400, 200));
      shape.setPosition(200, 200);
      shape.setFillColor(sf::Color(0, 255, 0));
      shape.setOutlineThickness(10);
      shape.setOutlineColor(sf::Color(0, 100, 0));
    sfml_game_object.add_shape(shape);
}

void game::process_events()
{
  //Close if frames are limited
  if (m_n_displayed_max > 0 && m_n_displayed == m_n_displayed_max)
  {
    sfml_game_object.m_window.close();
  }
}

void game::process_input()
{
  // check all the window's events that were triggered since the last iteration of the loop
  sf::Event event;
  while (sfml_game_object.m_window.pollEvent(event))
  {
      switch (event.type) {
          case sf::Event::Closed:
              sfml_game_object.m_window.close();
              break;

          case sf::Event::KeyPressed:
              //Coming Soon
              break;

          default:
              //Do nothing by default
              break;
      }
  }
}

int extract_n_displayed_max(const std::vector<std::string>& /* args */)
{
  //STUB
  return 100;
}
