//
// Created by ivan on 17.01.2021.
//

#ifndef TEMPLATE_BROKER_H
#define TEMPLATE_BROKER_H
#include <file(pere).hpp>
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::vector<financial_file>> acc_files_map; //название файла из file

class broker {
 public:
  broker() = default;
  broker(std::string name, acc_files_map files);

  std::string name() const;
  acc_files_map files() const;
  bool valid() const;

 private:
  std::string _name;
  acc_files_map _files;
};
#endif  // TEMPLATE_BROKER_H
