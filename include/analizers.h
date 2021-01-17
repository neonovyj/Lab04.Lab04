//
// Created by ivan on 17.01.2021.
//

#ifndef TEMPLATE_ANALIZERS_H
#define TEMPLATE_ANALIZERS_H

#include <boost/filesystem.hpp>
#include <broker.h>
#include <string>
#include <vector>

using d_path = boost::filesystem::path;
using d_iter = boost::filesystem::directory_iterator;
using d_entry = boost::filesystem::directory_entry;

broker analyse_one(const std::string &path);

std::vector<broker> analyse_all(const std::string &path);

#endif  // TEMPLATE_ANALIZERS_H
