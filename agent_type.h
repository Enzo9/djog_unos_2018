#ifndef AGENT_TYPE_H
#define AGENT_TYPE_H

#include <iosfwd>
#include <vector>

/// The type a tile can be
enum class agent_type { none,bacterium, cow, grass, fish, crocodile };

/// Get all the agent types in a std::vector
std::vector<agent_type> collect_all_agent_types();

///Tests the agent_type
void test_agent_type();

std::ostream& operator<<(std::ostream& os, const agent_type a) noexcept;
std::istream& operator>>(std::istream& is, agent_type& a) noexcept;

#endif // TILE_TYPE_H
