
// Always include the header of the unit first
#include "id.h"
#include "game.h"
#include <cassert>
#include <fstream>
#include <cstdio>
#include <QFile>

game::game(const std::vector<tile>& tiles)
  : m_tiles{tiles},
    m_score{0}
{

}

void game::add_tiles(std::vector<tile> ts)
{
  for (tile& t : ts)
  {
    m_tiles.push_back(t);
  }
}

std::vector<tile_type> collect_tile_types(const game& g) noexcept
{
  std::vector<tile_type> types;
  for (const tile& t: g.get_tiles())
  {
    types.push_back(t.get_type());
  }
  return types;
}

int count_n_tiles(const game& g) noexcept
{
  return g.get_tiles().size();
}

void game::delete_tiles(std::vector<tile> ts)
{
  for (tile& t : ts)
  {
    auto here = std::find_if(
      std::begin(m_tiles),
      std::end(m_tiles),
      [t](const tile& u)
      {
        return u.get_id() == t.get_id();
      }
    );
    std::swap(*here, m_tiles.back());
    m_tiles.pop_back();
  }
}

void game::process_events()
{
  //Merge tiles
  //(I use indices here, so it is more beginner-friendly)
  //(one day, we'll use iterators)
  bool done = false;
  while (!done)
  {
    done = true;
    const int n = count_n_tiles(*this);
    for (int i = 0; i != n; ++i)
    {
      tile& focal_tile = m_tiles[i];
      // j is the next tile in the vector
      for (int j = i + 1; j < n; ++j)
      {
        const tile& other_tile = m_tiles[j];
        if (have_same_position(focal_tile, other_tile))
        {
          const tile_type merged_type = get_merge_type(
            focal_tile.get_type(),
            other_tile.get_type()
          );
          //focal tile becomes merged type
          focal_tile.set_type(merged_type);
          //other tile is swapped to the back, then deleted
          m_tiles[j] = m_tiles.back();
          m_tiles.pop_back();
          //Redo
          done = false;
        }
      }
    }
  }


  //Process the events happening on the tiles
  for (auto& tile: m_tiles)
  {
    tile.process_events();
  }
  ++m_n_tick;
}

void test_game() //!OCLINT a testing function may be long
{
  // A game starts with one or more tiles
  {
    const game g;
    assert(!g.get_tiles().empty());
  }

  // A game starts with a score of zero
  {
    const game g;
    assert(g.get_score() == 0);
  }

//#define FIX_ISSUE_91_GAME_TRACKS_THE_NUMBER_OF_TICKS
#ifdef FIX_ISSUE_91_GAME_TRACKS_THE_NUMBER_OF_TICKS
  // A game starts with a zero number of game cycles
  {
    const game g;
    assert(g.get_n_ticks() == 0);
  }
  // Number of game cycles is increased each time all events are processed
  {
    game g;
    g.process_events();
    assert(g.get_n_ticks() == 1);
  }
#endif // FIX_ISSUE_91_GAME_TRACKS_THE_NUMBER_OF_TICKS

  // A game can be saved
  {
    const game g;
    const std::string filename{"tmp.sav"};
    if (QFile::exists(filename.c_str()))
    {
      std::remove(filename.c_str());
    }
    assert(!QFile::exists(filename.c_str()));
    save(g, filename);
    assert(QFile::exists(filename.c_str()));
  }
  #ifdef FIX_ISSUE_RAFAYEL
  // A game can be loaded
  {
    const game g;
    const std::string filename{"tmp.sav"};
    if (QFile::exists(filename.c_str()))
    {
      std::remove(filename.c_str());
    }
    assert(!QFile::exists(filename.c_str()));
    save(g, filename);
    assert(QFile::exists(filename.c_str()));
    const game h = load(filename);
    assert(g == h);
  }
  #endif // FIX_ISSUE_RAFAYEL
  {
    // Create a game with two grassland blocks on top of each other
    // +====+====+    +----+----+
    // || grass || -> |mountains|
    // +====+====+    +----+----+
    const std::vector<tile> tiles
    {
      //   x    y    z   w    h    type                  ID
      tile(1, 1, 1, 2, 1, tile_type::grassland, new_id()),
      tile(1, 1, 1, 2, 1, tile_type::grassland, new_id())
    };

    game g(tiles);
    assert(count_n_tiles(g) == 2);
    assert(collect_tile_types(g)[0] == tile_type::grassland);
    assert(collect_tile_types(g)[1] == tile_type::grassland);
    g.process_events();
    assert(count_n_tiles(g) == 1);
    assert(collect_tile_types(g)[0] == tile_type::mountains);

  }
}

game load(const std::string &filename) {
  std::ifstream f(filename);
  game g;
  f >> g;
  return g;
}

void save(const game &g, const std::string &filename) {
  std::ofstream f(filename);
  f << g;
}

std::ostream& operator<<(std::ostream& os, const game& g)
{
  //TODO: actually save the tile and agents
  os << g.m_n_tick << ' ' << g.m_score << ' '
     << g.m_tiles.size();

  for (int i=0; i < static_cast<int>(g.m_tiles.size()); i++){
      os << ' ' <<g.m_tiles[i];
  }

  os << ' ';

  return os;
}

std::istream& operator>>(std::istream& is, game& g)
{
  //TODO: actually save the tile and agents
  is >> g.m_n_tick >> g.m_score;
  int n_tiles = 0;
  is >> n_tiles;
  //TODO: the line below is a stub
  for (int i=0; i!=n_tiles; ++i)
  {
      tile t(1, 1, 1, 1, 1, tile_type::grassland, new_id());
      is >> t;
      g.m_tiles.emplace_back(t);
  }
  return is;
}

bool operator==(const game& lhs, const game& rhs) noexcept
{
  if (lhs.m_n_tick != rhs.m_n_tick)
      return false;
  if (lhs.m_score != rhs.m_score)
      return false;
  if (lhs.m_tiles != rhs.m_tiles)
      return false;

  return true;
}
