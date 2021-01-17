// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <string>

class financial_file { //название класса переименовать!
 public:
  financial_file() = default;
  financial_file(std::string name, std::string date);

  std::string name() const;
  std::string date() const;


 private:
  std::string _name;
  std::string _date;
};
#endif // INCLUDE_HEADER_HPP_
