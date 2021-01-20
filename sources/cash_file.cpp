// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <cash_file.hpp>
cash_file::cash_file(const std::string& name, const std::string& date,
                               const std::string& account)
    : _name(name), _date(date), _account(account) {}

std::string cash_file::name() const { return _name + ".txt"; }//тут name не имя брокера, а имя файла

std::string cash_file::date() const { return _date; }

std::string cash_file::account() const { return _account; }
