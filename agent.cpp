#include "agent.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

agent::agent(const agent_type type, const double x, const double y)
    : m_type{type}, m_x{x}, m_y{y}{}

std::ostream& operator<<(std::ostream& os, const agent& a) noexcept
{
  //TODO: actually save the tile and agents
  os << a.m_type << ' ' << a.m_x << ' ' << a.m_y;
  return os;
}

std::istream& operator>>(std::istream& is, agent& a)
{
  //TODO: actually save the tile and agents
  is >> a.m_type >> a.m_x >> a.m_y;
  return is;
}

bool operator==(const agent& lhs, const agent& rhs) noexcept{
    if (!(lhs.m_type == rhs.m_type))
        return false;
    if (!(lhs.m_x == rhs.m_x))
        return false;
    if (!(lhs.m_y == rhs.m_y))
        return false;

    return true;
}

void agent::move()
{
  if (m_type == agent_type::cow ||
      m_type == agent_type::fish ||
      m_type == agent_type::crocodile) {
    m_x += 0.1 * (-1 + (std::rand() % 3));
    m_y += 0.1 * (-1 + (std::rand() % 3));
  }
  if (m_type == agent_type::crocodile) {
    m_x += 0.1 * (-1 + (std::rand() % 3));
    m_y += 0.1 * (-1 + (std::rand() % 3));
  }
}

void test_agent() //!OCLINT testing functions may be long
{
  // A default agent has coordinate (0,0)
  {
    const agent a(agent_type::cow);
    assert(a.get_x() == 0.0);
    assert(a.get_y() == 0.0);
  }
  // A agent has the right coordinats
  {
    const double x{12.34};
    const double y{56.78};
    const agent a(agent_type::cow, x, y);
    assert(a.get_x() == x);
    assert(a.get_y() == y);
  }
  // A cow moves
  {
    std::srand(314);
    const double x{12.34};
    const double y{56.78};
    agent a(agent_type::cow, x, y);
    a.move();
    assert(a.get_x() != x || a.get_y() != y);
  }
  // A crocodile moves
  {
    std::srand(314);
    const double x{12.34};
    const double y{56.78};
    agent a(agent_type::crocodile, x, y);
    for (int i = 0; i != 10; ++i) a.move(); //To make surer x or y is changed
    assert(a.get_x() != x || a.get_y() != y);
  }

  // A fish moves
  {
    const double x{12.34};
    const double y{56.78};
    agent a(agent_type::fish, x, y);
    a.move();
    assert(a.get_x() != x || a.get_y() != y);
  }
  // Grass does not move
  {
    const double x{12.34};
    const double y{56.78};
    agent a(agent_type::grass, x, y);
    a.move();
    assert(a.get_x() == x && a.get_y() == y);
  }
}

