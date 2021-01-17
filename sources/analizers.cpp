//
// Created by ivan on 17.01.2021.
//
#include <analizers.h>
#include <broker.h>

#include <algorithm>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

inline bool is_separator(char c) { return c == '_'; }
inline bool not_separator(char c) { return !is_separator(c); }
std::vector<std::string> split_string(const std::string &text) {
  std::vector<std::string> ret;
  for (auto i = text.cbegin(); i != text.cend();) {
    i = std::find_if(i, text.end(),
                     not_separator);  //ищет символ, не являющийся разделителем.
                                      //Функция ищет в некотором множестве
                                      //элемент, при котором выполняется условие
    auto j = std::find_if(
        i, text.end(), is_separator);  //ищет символ, являеющийся разделителем
    ret.push_back(std::string(i, j));
    i = j;
  }
  return ret;
}

void processing_filename(const std::string &filename,
                         std::vector<financial_file> &files,
                         std::set<std::string> &accounts) {
  auto filename_tokens = split_string(filename);
  if (filename_tokens.size() != 3) return;

  auto type = filename_tokens[0];
  auto account = filename_tokens[1];
  auto date = filename_tokens[2];

  if (type != "balance") return;
  if (account.length() != 8) return;
  if (date.length() != 8) return;

  files.push_back(financial_file(filename, date, account));
  accounts.insert(account);
}

broker analyse_one(const std::string &path) {
  std::string name;
  std::vector<financial_file> files;
  std::set<std::string> accounts;

  const d_path broker_directory{path};
  if (!boost::filesystem::is_directory(broker_directory))
    throw std::runtime_error(
        "argument must be path to broker directory, not file");

  name = broker_directory.filename().stem().string();
  for (const auto &entry : d_iter{broker_directory}) {
    if (boost::filesystem::is_directory(entry) ||
        !entry.path().filename().stem().extension().string().empty() ||
        !entry.path().filename().extension().extension().string().empty() ||
        entry.path().extension().string() != ".txt")
      continue;
    processing_filename(entry.path().filename().stem().string(), files,
                        accounts);
  }
  return broker(name, files, accounts);
}

std::vector<broker> analyse_all(const std::string &path) {
  const d_path brokers_directory{path};
  std::vector<broker> result;
  for (const auto &entry : d_iter{brokers_directory}) {
    broker brok = analyse_one(entry.path().string());
    if (!brok.files().empty() && !brok.accounts().empty())
      result.push_back(brok);
  }
  return result;
}
