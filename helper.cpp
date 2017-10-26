#include "helper.h"

#include <cassert>
#include <iostream>
#include <QFile>
#include <vector>

void create_fonts()
{
  std::vector<std::string> v;
  v.push_back("Fonts/arial.ttf");
  for (const std::string s: v)
  {
    QFile f((":/fonts/" + s).c_str());
    const std::string filename{extract_base(s)};
    f.copy(s.c_str());

    if(!QFile::exists(filename.c_str()))
    {
      std::cerr << "file " << s << " not created\n";
    }
    assert(QFile::exists(filename.c_str()));
  }
}

void create_resources()
{
  create_fonts();
  create_sprites();
}

void create_sprites()
{
  std::vector<std::string> file_names;
  file_names.push_back("Sprites/Bush.png");
  file_names.push_back("Sprites/CandlePicture_redhood.png");
  file_names.push_back("Sprites/CandlePicture_redhood2.png");
  file_names.push_back("Sprites/CandlePicture_wolf.png");
  file_names.push_back("Sprites/CandlePicture_wolf2.png");
  file_names.push_back("Sprites/deadgrandmother_winner_screen.png");
  file_names.push_back("Sprites/DoubleTree.png");
  file_names.push_back("Sprites/Grandmother.png");
  file_names.push_back("Sprites/Grass.png");
  file_names.push_back("Sprites/GrassBush.png");
  file_names.push_back("Sprites/GrassTree.png");
  file_names.push_back("Sprites/Hunter.png");
  file_names.push_back("Sprites/RRH_winner_screen.png");
  file_names.push_back("Sprites/tilemap.png");
  file_names.push_back("Sprites/Tree.png");
  file_names.push_back("Sprites/Wolf_winner_screen.png");

  for (const std::string s: file_names)
  {
    QFile f((std::string(":/sprites/") + s).c_str());
    const std::string filename{extract_base(s)};
    f.copy(filename.c_str());
    if(!QFile::exists(filename.c_str()))
    {
      std::cerr << "file " << s << " not created\n";
    }

    assert(QFile::exists(filename.c_str()));
  }
}

std::string extract_base(const std::string& s)
{
  const auto from = s.find_last_of('/');
  if (from == std::string::npos) return s;
  return s.substr(from + 1, s.size() - 1);
}
