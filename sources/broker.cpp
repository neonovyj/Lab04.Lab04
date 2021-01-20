// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <broker.h>
broker::broker(const std::string& name,
               const std::vector<cash_file>& files,
               const std::set<std::string>& accounts)
    : _name(name), _files(files), _accounts(accounts) {}//список инициализации, чтобы не писать _name=name...(имя поля(значение))

std::string broker::name() const { return _name; }//метод name просто возвращает _name

std::vector<cash_file> broker::files() const { return _files; }//возвращают соответсующие имени зачеения,тк поля приватные и мы не можем к ним обратиться
std::set<std::string> broker::accounts() const { return _accounts; }//
