#ifndef RECORDER_H
#define RECORDER_H

#include <string>
#include <vector>
#include <iterator>

class Recorder {
public:
    using names_type = std::vector<std::string>;
    using names_size_type = names_type::size_type;
    using count_type = std::vector<std::size_t>;
    using count_size_type = count_type::size_type;
    using counts_type = std::vector<count_type>;
    using counts_size_type = counts_type::size_type;

    // 根据索引获取名字
    std::string name(names_size_type index) const;
    // 获取所有名字
    names_type const& names() const;
    // 根据索引获取种类
    std::string specie(names_size_type index) const;
    // 获取所有种类
    names_type const& species() const;
    // 查找名字是否存在
    bool find_name(std::string const& name) const;
    // 查找种类是否存在
    bool find_specie(std::string const& specie) const;
    // 获取名字的索引
    names_size_type name_index(std::string const& name) const;
    // 获取种类的索引
    names_size_type specie_index(std::string const& specie) const;
    // 根据名字获取计数
    count_type by_name(std::string const& name) const;
    // 根据种类获取计数
    count_type by_specie(std::string const& specie) const;
    // 同时根据名字和种类获取计数
    std::size_t& by_name_specie(std::string const& name,
                                std::string const& specie);
    // 增加名字
    void add_name(std::string const& name);
    // 增加种类
    void add_specie(std::string const& specie);
    // 删除名字
    void remove_name(std::string const& name);
    void remove_name(names_size_type const index);
    // 删除种类
    void remove_specie(std::string const& specie);
    void remove_specie(names_size_type const index);
    // 导出
    void export_data(std::ostream_iterator<std::string>) const;
private:
    names_type __names;
    names_type __species;
    counts_type __counts;
};

#endif // RECORDER_H
