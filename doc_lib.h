#ifndef DOC_LIB_H
#define DOC_LIB_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

extern const  std::string FILE_NAME;

struct Document {
    std::string name;
    std::string content;
    bool exists;
};
// Основные функции библиотеки
std::vector<Document> loadDocuments();                     // прочитать все документы из файла-списка
void saveDocuments(const std::vector<Document>& docs);     // сохранить список в файл
bool createDocument(const std::string& filename);          // создать файл на диске
bool deleteDocument(const std::string& filename);          // удалить файл
std::string readDocument(const std::string& filename);          // прочитать содержимое
bool writeDocument(const std::string& filename, const std::string& content); // записать
bool documentExists(const std::string& filename);          // проверка существования

// Интерфейсные функции меню
void runUI();
int mainMenu();
int subMenu();
std::string askFilename();
int getNumber(int min, int max);

#endif