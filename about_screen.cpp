#include "about_screen.h"
//#include "Text.hpp"
//#include <SFML/Graphics.hpp>
#include <QFile>
#include <cassert>

about_screen::about_screen(

//{
    //window(sf::VideoMode(800, 600), "About")
    const int window_width,
   const int window_height
) : aboutwindow(
      sf::VideoMode(
        static_cast<unsigned int>(window_width),
        static_cast<unsigned int>(window_height)
      ),
      "About"
   )
{
  //Haha done everything already :-)
  //Re-create font
  {
    QFile f(":/nature_zen/resources/OpenSans.ttf");
    f.copy("OpenSans.ttf");
    assert(QFile::exists("OpenSans.ttf"));
  }
}

void about_screen::closeabout()
{
  aboutwindow.close();
}

void about_screen::displayabout()
{
  while (aboutwindow.isOpen())
  {
    sf::Event event;
    while (aboutwindow.pollEvent(event))
    {
        //Haha!
    }

    sf::Font font;
    assert(QFile::exists("OpenSans.ttf"));
    font.loadFromFile("OpenSans.ttf");
    aboutwindow.clear(sf::Color::White);//Clear the window with black color
    about_screen::abouttext.setFont(font);
    about_screen::abouttext.setString("This game was developed by...\r\nIt is about..");
    about_screen::abouttext.setCharacterSize(24); // in pixels, not points!

    // set the color
    about_screen::abouttext.setFillColor(sf::Color::Black);


    aboutwindow.draw(about_screen::abouttext);
    aboutwindow.display();
    if (event.type == sf::Event::Closed)
    about_screen::aboutwindow.close();
  }
}

//}


//void about_screen::display()
