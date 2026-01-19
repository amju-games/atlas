// * atlas * Texture atlas tool
// (c) Copyright 2026 Juliet Colman

#pragma once

#include <string>
#include <vector>

class commandline
{
public:
  using strvec = std::vector<std::string>;

  commandline(int argc, const char** argv) : 
    m_strings(argv, argv + argc) {}

  const strvec& strings() const { return m_strings; }

  bool contains(const std::string& s) const 
  { 
    return std::find(m_strings.cbegin(), m_strings.cend(), s) != m_strings.cend(); 
  }
  
private:
  strvec m_strings;
};

