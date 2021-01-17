// Copyright 2020 ivan <ikhonyak@gmail.com>

#ifndef TEMPLATE_BROKER_H
#define TEMPLATE_BROKER_H

#include <file.hpp>
#include <set>  //контейнер, каждый элемент которого уникален
#include <string>
#include <vector>

class broker {
 public:
  broker() = default;
  broker(const std::string &name,
         const std::vector<financial_file> &files,  //название файла поменять
         const std::set<std::string> &accounts);

  std::string name() const;
  std::vector<financial_file> files() const;
  std::set<std::string> accounts() const;

 private:
  std::string _name;
  std::vector<financial_file> _files;
  std::set<std::string> _accounts;
};

#endif  // TEMPLATE_BROKER_H
