// Copyright 2020 ivan <ikhonyak@gmail.com>

#ifndef TEMPLATE_ANALIZERS_H
#define TEMPLATE_ANALIZERS_H

#include <broker.h>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

using pathB = boost::filesystem::path;
using iteratorB = boost::filesystem::directory_iterator;
using entryB = boost::filesystem::directory_entry;
broker analyse_one(const std::string &path);
std::vector<broker> analyse_all(const std::string &path);

#endif  // TEMPLATE_ANALIZERS_H
