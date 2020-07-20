#include <sstream>
#include <algorithm>
#include "recorder.h"

std::string Recorder::name(names_size_type index) const
{
    return __names[index];
}

Recorder::names_type const& Recorder::names() const
{
    return __names;
}

std::string Recorder::specie(names_size_type index) const
{
    return __species[index];
}

Recorder::names_type const& Recorder::species() const
{
    return __species;
}

bool Recorder::find_name(std::string const& name) const
{
  return std::find(__names.cbegin(), __names.cend(), name) != __names.cend();
}

bool Recorder::find_specie(const std::string &specie) const
{
  return std::find(__species.cbegin(), __species.cend(), specie) != __species.cend();
}

Recorder::names_size_type Recorder::name_index(std::string const& name) const
{
    return std::find(__names.cbegin(), __names.cend(), name) - __names.cbegin();
}

Recorder::names_size_type Recorder::specie_index(std::string const& specie) const
{
  return std::find(__species.cbegin(), __species.cend(), specie) - __species.cbegin();
}

Recorder::count_type Recorder::by_name(std::string const& name) const
{
    names_size_type i = name_index(name);
    return i == __names.size()? count_type(__species.size()): __counts[i];
}

Recorder::count_type Recorder::by_specie(const std::string &specie) const
{
    names_size_type index = specie_index(specie);
    if (index == __species.size()) {
        return count_type(__names.size());
    }

    count_type ret;
    for (auto const& count : __counts) {
      ret.push_back(count[index]);
    }
    return ret;
}

std::size_t& Recorder::by_name_specie(const std::string &name, const std::string &specie)
{
    names_size_type in = name_index(name);
    names_size_type is = specie_index(specie);
    return __counts[in][is];
}

void Recorder::add_name(const std::string &name)
{
    __names.push_back(name);
    __counts.emplace_back(__species.size());
}

void Recorder::add_specie(const std::string &specie)
{
    __species.push_back(specie);
    for (auto& count : __counts) {
        count.emplace_back(0);
    }
}

void Recorder::remove_name(const names_size_type index)
{
    auto i = __names.begin() + index;
    __names.erase(i);
    auto j = __counts.begin() + index;
    __counts.erase(j);
}

void Recorder::remove_name(const std::string &name)
{
    names_size_type index = name_index(name);
    remove_name(index);
}

void Recorder::remove_specie(const names_size_type index)
{
    auto i = __species.begin() + index;
    __species.erase(i);
    count_type::iterator j;
    for (auto& count : __counts) {
        j = count.begin() + index;
        count.erase(j);
    }
}

void Recorder::remove_specie(const std::string &specie)
{
    names_size_type index = specie_index(specie);
    remove_specie(index);
}

void Recorder::export_data(std::ostream_iterator<std::string> iter) const
{
  iter++ = "Words";
  for (auto const& specie : __species) {
      iter++ = "\t" + specie;
  }

  for (count_size_type i = 0; i < __names.size(); ++i) {
      iter++ = "\n";
      iter++ = __names[i];
      for (count_size_type j = 0; j < __species.size(); ++j) {
          iter++ = "\t" + std::to_string(__counts[i][j]);
      }
  }
}
