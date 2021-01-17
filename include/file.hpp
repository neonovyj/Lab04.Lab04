// Copyright 2020 ivan <ikhonyak@gmail.com>

#ifndef INCLUDE_FILE_HPP_
#define INCLUDE_FILE_HPP_
#include <string>

class financial_file {  //название класса переименовать!
 public:
  financial_file() = default;
  financial_file(const std::string &name, const std::string &date,
                 const std::string &account);

  std::string name() const;
  std::string date() const;
  std::string account() const;

 private:
  std::string _name;
  std::string _date;
  std::string _account;
};

#endif  // INCLUDE_FILE_HPP_
