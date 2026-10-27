#include <fstream>
#include <iostream>
#include "html.h"
#include "tree.h"

int main() {
    std::ofstream fout("output.html");
    if(!fout.is_open()) {
        std::cout<<"ошибка открытия файла"<<std::endl;
        return 1;
        }
    utils::html::f1(fout);
    utils::tree::Tree a;
    int choice, x;
    while (1) {
        std::cout<<"1 - добавить элемент"<<std::endl;
        std::cout<<"2 - удалить элемент"<<std::endl;
        std::cout<<"3 - поиск элемента"<<std::endl;
        std::cout<<"4 - выход из программы"<<std::endl;
        std::cin>>choice;
    switch (choice) {
    case 1:
        std::cout<<"введите значение элемента для добавления: ";
        std::cin>>x;
        if (a.add(x,fout)) std::cout<<"элемент добавлен"<<std::endl;
        else std::cout<<"ошибка при добавлении"<<std::endl;
        break;
    case 2:
        std::cout<<"введите значение элемента для удаления: ";
        std::cin>>x;
        if (a.del(x,fout)) std::cout<<"элемент удалён"<<std::endl;
        else std::cout<<"элемент не найден"<<std::endl;
        break;
            case 3:
                std::cout<<"введите значение элемента для поиска: ";
                std::cin>>x;
                if (a.search(x)) std::cout<<"элемент найден"<<std::endl;
                else std::cout<<"элемент не найден"<<std::endl;
                break;
    case 4:
        utils::html::f3(fout);
        fout.close();
        return 0;
    default:
        std::cout<<"введите число от 1 до 4"<<std::endl;
    }
}
utils::html::f3(fout);
return 0;
}
