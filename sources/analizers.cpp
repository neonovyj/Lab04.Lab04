// Copyright 2020 ivan <ikhonyak@gmail.com>
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
    i = std::find_if(i, text.end(), not_separator);
    auto j = std::find_if(i, text.end(), is_separator);
    ret.push_back(std::string(i, j));
    i = j;
  }
  return ret;
}

void processing_filename(const std::string &filename,
                         std::vector<cash_file> &files,
                         std::set<std::string> &accounts) {
  auto filename_tokens = split_string(filename);
  if (filename_tokens.size() != 3) return;

  auto type = filename_tokens[0];
  auto account = filename_tokens[1];
  auto date = filename_tokens[2];

  if (type != "balance") return;
  if (account.length() != 8) return;
  if (date.length() != 8) return;

  files.push_back(cash_file(filename, date, account));
  accounts.insert(account);
}

broker analyse_one(const std::string &path) {
  std::string name;
  std::vector<cash_file> files;
  std::set<std::string> accounts;

  const pathB broker_directory{path};
  if (!boost::filesystem::is_directory(broker_directory))
    throw std::runtime_error(
        "argument must be path to broker directory, not file");

  name = broker_directory.filename().stem().string();
  for (const auto &entry : iteratorB{broker_directory}) {
    if (boost::filesystem::is_directory(entry) ||
        !entry.path().stem().extension().empty() ||
        entry.path().extension().string() != ".txt")
      continue;
    processing_filename(entry.path().filename().stem().string(), files,
                        accounts);
  }
  return broker(name, files, accounts);
}
//НИЖЕ Есть массив брокеров, каждую папку мы отдаем analyse one, //анализирует всех, проходит по папкам и каждую папку анализирует как отдельного брокера. проходим по каждой папке и там применяем функцию analyse one/
std::vector<broker> analyse_all(const std::string &path) { //передается путь в виде строки
  const pathB brokers_directory{path}; //объект бустовый, позволяющий работать с путем к какому-нибудь файлу как с объектом. Переданную сюда строку мы преобразуем в boost::filesystem::path. В качестве параметра конструктора мы передаем путь (path). теперь brokers_directory- объект пути к папке, где хранятся папки остальных брокеров.
  std::vector<broker> result; //массив брокеров. Вначале пустой
  for (const auto &entry : iteratorB{brokers_directory}) {//Этим циклом мы проходимся по папкам с брокерами
    broker brok = analyse_one(entry.path().string()); //анализируем брокера
    if (!brok.files().empty() && !brok.accounts().empty())//Проверка, чтобы за брокеров не считались папки, в которых ничего нет
      result.push_back(brok);//сохраняем его в массив, а массив потом возвращаем
  }
  return result;
}
