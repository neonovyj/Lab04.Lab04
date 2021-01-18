// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <analizers.h>
#include <broker.h>

#include <cash_file.hpp>
#include <iostream>

std::string lastdate(const std::vector<financial_file> &files) {
  std::string res;
  for (const auto &file : files) {
    res = std::max(res, file.date());
  }
  return res;
}

void print_files(const std::vector<broker> &brokers) {
  for (auto const &broker : brokers) {
    for (auto const &broker_file : broker.files()) {
      std::cout << broker.name() << " " << broker_file.name() << std::endl;
    }
  }
}

void short_print_files(const std::vector<broker> &brokers) {
  for (auto const &broker : brokers) {
    for (auto const &account : broker.accounts()) {
      std::vector<financial_file> this_account_files;
      for (auto const &file : broker.files()) {
        if (file.account() == account) this_account_files.push_back(file);
      }
      std::cout << "broker:" << broker.name() << " account:" << account
                << " files:" << this_account_files.size()
                << " lastdate:" << lastdate(this_account_files) << std::endl;
    }
  }
}

int main(int argc, char *argv[]) {
  std::string directory;
  if (argc == 1) {
    directory = ".";
  } else {
    directory = argv[1];
  }
  directory = "../misc/ftp";

  std::vector<broker> brokers = analyse_all(directory);
  print_files(brokers);
  short_print_files(brokers);
  return 0;
}
