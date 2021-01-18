// Copyright 2020 ivan <ikhonyak@gmail.com>

#ifndef INCLUDE_FILE_HPP_
#define INCLUDE_FILE_HPP_
#include <string>

class cash_file {//объявляем наш класс
 public:
  cash_file() = default; //конструктор по умолчанию
  cash_file(const std::string &name, const std::string &date, //определяем конструктор от параметров(имя и дата)
                 const std::string &account); //имя передается, сохранить его, чтобы представлять, возвращать, выводить...
//Дата тк в задании говорится, что нужно сохранять дату
  std::string name() const;//вернет строку имени. Конст означает, что метод не меняет полей класса
  std::string date() const;//
  std::string account() const;

 private:
  std::string _name;//эти поля неизменны из за конст
  std::string _date;
  std::string _account;
};

#endif  // INCLUDE_FILE_HPP_
