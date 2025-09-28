#ifndef QUERY_H
#define QUERY_H

#include <array>
#include <functional>
#include <vector>
#include <string>
#include <sstream>

///========================================================///
template <typename DatabaseTy> class Query {
public:
  template <typename TableItemTy>
  std::vector<TableItemTy> query_items_from(const std::string &key_str) {
    return static_cast<DatabaseTy *>(this)
        ->template query_items_from_impl<TableItemTy>(key_str);
  };
};

///========================================================///
template <typename T>
concept TableItemTy = requires {
    { T::get_table_name() } -> std::convertible_to<std::string>;
};

class RdbQuery : public Query<RdbQuery> {
  friend Query<RdbQuery>;
protected:
  template <typename TableItemTy>
  std::vector<TableItemTy> query_items_from_impl(const std::string &key_str) {
    std::string tableName = TableItemTy::get_table_name();

    // TODO: get value from RDB, value is csv format
    std::string items; // placeholder for csv data

    // parse csv to vector<TableItemTy>
    std::vector<TableItemTy> tableItems;
    std::istringstream iss(items);
    std::string line;
    while (std::getline(iss, line, '\n')) {
      tableItems.emplace_back(key_str.c_str(), line.c_str());
    }

    return tableItems;
  }
};

#endif
