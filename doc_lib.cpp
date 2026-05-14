#include "doc_lib.h"

#include "doc_lib.h"
#include <vector>

const std::string FILE_NAME = "documents.txt";


std::vector<Document> loadDocuments() {
    std::vector<Document> docs;
    std::ifstream file(FILE_NAME);
    if (!file.is_open()) {
        std::cout << "Файл-список не найден, создайте новый документ через меню." << std::endl;
        return docs;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, statusStr;
        std::getline(ss, name, ';');
        std::getline(ss, statusStr, ';');

        if (!name.empty()) {
            Document doc;
            doc.name = name;
            doc.exists = documentExists(name);
            doc.content = doc.exists ? readDocument(name) : "";
            docs.push_back(doc);
        }
    }
    file.close();
    return docs;
}

void saveDocuments(const std::vector<Document>&docs) {
    std::ofstream file(FILE_NAME);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла-списка для записи." << std::endl;
        return;
    }

    for (size_t i = 0; i < docs.size(); i++) {
        file << docs[i].name << ";" << (docs[i].exists ? "1" : "0") << std::endl;
    }
    file.close();
}

bool documentExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool createDocument(const std::string& filename) {
    if (documentExists(filename)) return false;
    std::ofstream file(filename);
    return file.good();
}

bool deleteDocument(const std::string& filename) {
    return remove(filename.c_str()) == 0;
}

std::string readDocument(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool writeDocument(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file) return false;
    file << content;
    return true;
}


int getNumber(int min, int max) {
    int value;
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            return min - 1;  
        }

        std::stringstream ss(line);
        if (ss >> value && (value >= min && value <= max)) {
       
            char extra;
            if (!(ss >> extra)) {
                std::cin.clear();
                return value;
            }
        }
        std::cout << "Ошибка! Введите число от " << min << " до " << max << "." << std::endl;
        std::cin.clear();
    }
}

std::string askFilename() {
    std::string filename;
    std::cout << "Введите имя файла (без пробелов): ";
    std::cin >> filename;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return filename;
}

int mainMenu() {
    std::cout << "\nГлавное меню:" << std::endl;
    std::cout << "1. Выбрать документ (редактирование)" << std::endl;
    std::cout << "2. Создать документ" << std::endl;
    std::cout << "3. Прочитать документ" << std::endl;
    std::cout << "4. Заполнить документ (если пустой)" << std::endl;
    std::cout << "5. Выйти" << std::endl;
    return getNumber(1, 5);
}

int subMenu() {
    std::cout << "\nПодменю:" << std::endl;
    std::cout << "1. Редактировать" << std::endl;
    std::cout << "2. Удалить документ" << std::endl;
    std::cout << "3. Выйти" << std::endl;
    return getNumber(1, 3);
}

void runUI() {
    while (true) {
        int opt = mainMenu();
        if (opt == 5) {
            std::cout << "Работа завершена." << std::endl;
            break;
        }

        std::string filename = askFilename();
        if (filename.empty()) {
            std::cout << "Имя файла не может быть пустым." << std::endl;
            continue;
        }

        bool fileExists = documentExists(filename);

        switch (opt) {
        case 1: // выбрать и редактировать
            if (!fileExists) {
                std::cout << "Файл не существует." << std::endl;
                break;
            }
            {
                int sub = subMenu();
                if (sub == 1) {
                    std::string content = readDocument(filename);
                    std::cout << "Текущее содержимое:" << std::endl << content << std::endl;
                    std::cout


                        << "Введите новый текст (до Enter): ";
                    std::string newText;
                    std::getline(std::cin, newText);
                    if (writeDocument(filename, newText))
                        std::cout << "Файл обновлён." << std::endl;
                    else
                        std::cout << "Ошибка записи." << std::endl;
                }
                else if (sub == 2) {
                    if (deleteDocument(filename))
                        std::cout << "Файл удалён." << std::endl;
                    else
                        std::cout << "Не удалось удалить файл." << std::endl;
                }
               
            }
            break;

        case 2: // создать
            if (fileExists) {
                std::cout << "Файл уже существует." << std::endl;
            }
            else {
                if (createDocument(filename))
                    std::cout << "Документ создан." << std::endl;
                else
                    std::cout << "Не удалось создать файл." << std::endl;
            }
            break;

        case 3: // прочитать
            if (!fileExists) {
                std::cout << "Файл не существует." << std::endl;
            }
            else {
                std::cout << "Содержимое:" << std::endl << readDocument(filename) << std::endl;
            }
            break;

        case 4: // заполнить если пустой
            if (!fileExists) {
                std::cout << "Файл не существует." << std::endl;
            }
            else {
                std::string content = readDocument(filename);
                if (content.empty()) {
                    std::cout << "Введите текст: ";
                    std::string newContent;
                    std::getline(std::cin, newContent);
                    if (writeDocument(filename, newContent))
                        std::cout << "Файл заполнен." << std::endl;
                    else
                        std::cout << "Ошибка записи." << std::endl;
                }
                else {
                    std::cout << "Документ уже заполнен." << std::endl;
                }
            }
            break;
        }
    }
}