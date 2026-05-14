#include "doc_lib.h"
#include <cassert>

static void removeFile(const std::string& name) {
    std::remove(name.c_str());
}

int main() {
    // Тест 1: создание
    removeFile("test.txt");
    assert(createDocument("test.txt"));
    assert(documentExists("test.txt"));

    // Тест 2: запись и чтение
    assert(writeDocument("test.txt", "Hello"));
    assert(readDocument("test.txt") == "Hello");

    // Тест 3: удаление
    assert(deleteDocument("test.txt"));
    assert(!documentExists("test.txt"));

    removeFile("test.txt");
    std::cout << "Все успешно" << std::endl;
    return 0;
}