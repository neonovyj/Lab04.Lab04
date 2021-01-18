// Copyright 2020 ivan <ikhonyak@gmail.com>

#ifndef TEMPLATE_BROKER_H
#define TEMPLATE_BROKER_H

#include <cash_file.hpp>
#include <string>
#include <set>//контейнер, каждый элемент которого уникален
#include <vector>

class broker {//абстракция над папкой брокер. Выделяем сущность брокера: это объект, владеющий информацией:имя,
 public:
  broker() = default;//Дефолтный конструктор. Тк мы ничего не выполняем при создании пустого брокера.Когда вызовем метод, дефолтный конструктор вызовет дефолтные контсрукторы у всех полей, а они делают пустые контейнеры
  broker(const std::string &name, const std::vector<cash_file> &files,
         const std::set<std::string> &accounts);//мы делаем брокера и передаем в констурктор(не тут, это зачем нужно)
//аргументами,которые выше, инициализируются поля, которые приватные
  std::string name() const;//мы не можем напрямую обратиться, поэтому пишем методы
  std::vector<cash_file> files() const;
  std::set<std::string> accounts() const;

 private:
  std::string _name;//имя брокера, хранится в строке
  std::vector<cash_file> _files;//массив файлов, которым владеет брокер
  std::set<std::string> _accounts;//список аккаунтов хранится в виде строки, брокеров много, так что эти строки мы храним в массиве
};//set - контейнер, каждый элемент которого уникален, чтобы аккаунты не дублировались
#endif  // TEMPLATE_BROKER_H
