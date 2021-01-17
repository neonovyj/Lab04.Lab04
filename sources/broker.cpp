// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <broker.h>
broker::broker(const std::string& name,
               const std::vector<financial_file>& files,
               const std::set<std::string>& accounts)
    : _name(name), _files(files), _accounts(accounts) {}

std::string broker::name() const { return _name; }

std::vector<financial_file> broker::files() const { return _files; }
std::set<std::string> broker::accounts() const { return _accounts; }
