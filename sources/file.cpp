// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <file.hpp>
financial_file::financial_file(const std::string& name, const std::string& date,
                               const std::string& account)
    : _name(name), _date(date), _account(account) {}

std::string financial_file::name() const { return _name + ".txt"; }

std::string financial_file::date() const { return _date; }

std::string financial_file::account() const { return _account; }
