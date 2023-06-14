#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <cctype>
#include <locale>

bool isValidWord(const std::wstring& word) {
    // Перевірка, чи слово має правильну довжину
    if (word.length() < 1 || word.length() > 20)
        return false;

    // Перевірка, чи кожен символ є буквою
    for (wchar_t c : word) {
        if (std::iswalpha(c) == 0)
            return false;
    }

    return true;
}

void printMenu() {
    std::wcout << L"Меню користувача:" << std::endl;
    std::wcout << L"1. Введіть слово" << std::endl;
    std::wcout << L"2. Виконати сортування" << std::endl;
    std::wcout << L"3. Вихід" << std::endl;
    std::wcout << L"Ваш вибір: ";
}

int main() {
    std::wstring word;
    bool isWordEntered = false;
    bool isSorted = false;

    // Налаштування локалі для української мови
    std::locale::global(std::locale(""));

    while (true) {
        printMenu();

        int choice;
        std::wcin >> choice;

        // Перевірка на некоректне значення користувача
        if (std::wcin.fail()) {
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
            std::wcout << L"Некоректне значення. Спробуйте ще раз." << std::endl;
            continue;
        }

        switch (choice) {
            case 1:
                std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n'); // Очищення буфера перед getline
                std::wcout << L"Введіть слово: ";
                std::getline(std::wcin, word);

                if (!isValidWord(word)) {
                    std::wcout << L"Невірний формат слова. Слово повинно містити від 1 до 20 символів, українські або латинські літери." << std::endl;
                    continue;
                }

                // Перетворення всіх символів у слові на нижній регістр
                std::transform(word.begin(), word.end(), word.begin(), [](wchar_t c) { return std::towlower(c); });

                isWordEntered = true;
                isSorted = false;
                break;
            case 2:
                if (!isWordEntered) {
                    std::wcout << L"Спочатку введіть слово." << std::endl;
                    continue;
                }

                if (!isSorted) {
                    // Сортування символів у слові
                    std::sort(word.begin(), word.end());
                    isSorted = true;
                }

                std::wcout << L"Результат: " << word << std::endl;
                break;
            case 3:
                return 0;
            default:
                std::wcout << L"Невірний вибір. Спробуйте ще раз." << std::endl;
                break;
        }
    }

    return 0;
}
