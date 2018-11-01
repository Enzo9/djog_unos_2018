#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include <iosfwd>
#include "SFML/Graphics.hpp"
#include "agent_type.h"

using namespace sf;

/// Logic of an agent; something that moves on the tiles
class agent {
public:
  /// Constructor
  /// @param x the x-coordinat of the top-left corner of the agent
  /// @param y the y-coordinat of the top-left corner of the agent
  /// @param type the type the tile
  agent(const agent_type type, const double x = 0, const double y = 0,
        const Texture texture = Texture());

  /// The type the tile
  agent_type get_type() const noexcept { return m_type; }

  /// The x-coordinat of the top-left corner of the agent
  double get_x() const noexcept { return m_x; }

  /// The y-coordinat of the top-left corner of the agent
  double get_y() const noexcept { return m_y; }

  double get_width() const noexcept { return m_sprite.getTexture()->getSize().x; }

  double get_height() const noexcept { return m_sprite.getTexture()->getSize().y; }

  Sprite getSprite();

  Texture getTexure();

  // TODO Add below functions to the cpp file

  /// Check if the agent wants to move to position
  bool checkout(double x, double y);

  /// Make the agent move (movement depends on agent type and surroundings)
  void action();

  bool can_eat(agent &a);
  bool run_away(agent &a);

  ///Make the agent move
  void move();

private:
  /// The type the tile
  agent_type m_type;

  /// The x-coordinat of the top-left corner of the agent
  double m_x;

  /// The y-coordinat of the top-left corner of the agent
  double m_y;

  // The sprite
  Sprite m_sprite;

  // The texture
  Texture m_texture;

  //A rare exception to use a friend
  friend std::ostream& operator<<(std::ostream& os, const agent& a);
  friend std::istream& operator>>(std::istream& is, agent& a);
};

std::ostream& operator<<(std::ostream& os, const agent& a);

std::istream& operator>>(std::istream& is, agent& a);

/// Test the tile class
void test_agent();

#endif // TILE_H
