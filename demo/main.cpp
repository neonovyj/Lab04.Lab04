// Copyright 2020 ivan <ikhonyak@gmail.com>
#include <analizers.h>
#include <broker.h>

#include <cash_file.hpp>
#include <iostream>
//код, который работает с нашей библиотекой. Анализируем директории(перебираем файлы, парсим их названия)
std::string lastdate(const std::vector<cash_file> &files) { //ищет самую позднюю дату
  std::string res;
  for (const auto &file : files) {
    res = std::max(res, file.date());//max определен в заголовочном файле <алгоритма> и используется для определения наибольшего из переданных ему чисел.
  }
  return res;
}

void print_files(const std::vector<broker> &brokers) { //Перебираем брокеров. для каждого брокера в цикле выводим его файлы
  for (auto const &broker : brokers) {
    for (auto const &broker_file : broker.files()) {
      std::cout << broker.name() << " " << broker_file.name() << std::endl;
    }
  }
}
//ниже вывод который в конце
void short_print_files(const std::vector<broker> &brokers) {//если у брокера несколько аккаунтов, то повторяем вывод с другим аккаунтом
  for (auto const &broker : brokers) {//перебираем брокеров
    for (auto const &account : broker.accounts()) {//перебираем аккаунты каждого брокера
      std::vector<cash_file> this_account_files;//вектор с файлами
      for (auto const &file : broker.files()) {//перебираем файлы
        if (file.account() == account) this_account_files.push_back(file);//записываем кол-во файлов
      }
      std::cout << "broker:" << broker.name() << " account:" << account
                << " files:" << this_account_files.size()
                << " lastdate:" << lastdate(this_account_files) << std::endl;
    }
  }
}

int main(int argc, char *argv[]) {//argc argv - аргументы командной строки(argcount argvalue)
  std::string directory;
  if (argc == 1) { //1 потому что первый аргумент- название самой программы
    directory = ".";//если не передается никакого аргумета, то в качестве него передается то, что ниже(директория, в которой находимся)
  } else {
    directory = argv[1];//иначе мы берем второй аргумент
  }
  directory = "../misc/ftp";

  std::vector<broker> brokers = analyse_all(directory);//получаем список всех брокеров
  print_files(brokers); //передаем их фунции для вывода
  short_print_files(brokers);
  return 0;
}
