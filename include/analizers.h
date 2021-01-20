// Copyright 2020 ivan <ikhonyak@gmail.com>

#ifndef TEMPLATE_ANALIZERS_H
#define TEMPLATE_ANALIZERS_H
//тут содержатся функции, анализирующие брокера
#include <broker.h>
#include <boost/filesystem.hpp>//подключаем нашу библиотеку
#include <string>
#include <vector>
//за правую часть считаем левую, чтобы было короче и удобнее
using pathB = boost::filesystem::path; //объект бустовый, позволяющий работать с путем к какому-нибудь файлу как с объектом
using iteratorB = boost::filesystem::directory_iterator; //бустовый итератор. итератор - некая обертка над каждым элементом массива, позволяет работать с ним удобнее.читаем массив имен файлов в директории и по массиву имен итерируем
using entryB = boost::filesystem::directory_entry;//бустовая обертка над каждой входной точкой(папка, файл... все, что является файловой системой)
broker analyse_one(const std::string &path);//эта функция анализирует одну директорию(одного брокера), возращаем одного брокера
std::vector<broker> analyse_all(const std::string &path);//анализирует всех брокеров в директории, предает путь, где хранятся брокеры, возврашщаем массив брокеров

#endif  // TEMPLATE_ANALIZERS_H
