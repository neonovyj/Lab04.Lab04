// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <analizers.h>
#include <broker.h>

#include <algorithm>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
//is_separator not_separator объявлены в качестве вспомогательных функций. inline - слово, говорящее компилятору, что эту функцию надо не вызывать, а подставлять ее текст. Если компилятор решит, что так выгоднее с точки зрения производительности
inline bool is_separator(char c) { return c == '_'; }//функция, которая вернет тру, если символ является разделителем
inline bool not_separator(char c) { return !is_separator(c); }//функция, которая вохвращает тру, если текщий символ не является разделителм
std::vector<std::string> split_string(const std::string &text) { //функция, которая по нужному разделителю разбивает строки на подстроки
  std::vector<std::string> ret; //у нас есть массив строк. Выполняет список подстрок
  for (auto i = text.cbegin(); i != text.cend();) { //проходим по строке итерируя ее специальными итераторами, которые у нее есть
    i = std::find_if(i, text.end(), not_separator); //find if в некотором множестве ищет такой элемент, для которого будет выполняться такое условие. будет искать такой символ, для которого not_separator будет тру(найдет символ, который не является разделителем)
    auto j = std::find_if(i, text.end(), is_separator); //i, j -итераторы строки
    ret.push_back(std::string(i, j)); //std::string-создаем строку из итераторов, которые мы нашли
    i = j;
  }
  return ret;
}
//ниже обрабатываем имя. Распарсивает имя, вытаскивает его номер и вставила в множество аккаунтов. Делается множество, чтобы каждый элемент был уникален
void processing_filename(const std::string &filename,//первым аргументом принимает имя. полное имя файла
                         std::vector<cash_file> &files,//ссылка на массив финансовых файлов
                         std::set<std::string> &accounts) {//ссылка на множество аккаунтов
  auto filename_tokens = split_string(filename);//std vector string (auto сам выводит тип, но мы знаем, что split_string возвращает вектор строк)
  if (filename_tokens.size() != 3) return; //если элементов файла не три, то файл игнорируется
//Разбиваем имя аккаунта на 3 элемента, потом проверяем на валидность(нужен ли нам этот файл)
  auto type = filename_tokens[0];//std string
  auto account = filename_tokens[1];//std string
  auto date = filename_tokens[2];//std string

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
