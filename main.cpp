#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "html.h"
#include "tree.h"

namespace opt = boost::program_options;
int main(int argc, char** argv) {
        opt::options_description desc("Параметры");
        std::string output_name;
        std::vector<int> values;
        desc.add_options()
                ("output,o", opt::value<std::string>(&output_name)->default_value("output.html"), "имя выходного html-файла")
                ("values,v", opt::value<std::vector<int>>(&values)->multitoken(), "элементы, которые сразу добавляются в дерево")
                ("help,h", "вывести справку")
        ;
        opt::variables_map vm;
        try {
                opt::store(opt::parse_command_line(argc,argv,desc),vm);
                if(vm.count("help")) {
                        std::cout<<desc<<std::endl;
                        return 0;
                        }
                std::ifstream config("tree.cfg");
                if(config.is_open()) opt::store(opt::parse_config_file(config,desc),vm);
                opt::notify(vm);
        } catch (std::exception& e) {
                std::cout<<e.what()<<std::endl;
                return 1;
        }
        std::ofstream fout(output_name);
        if(!fout.is_open()) {
                std::cout<<"ошибка открытия файла"<<std::endl;
                return 1;
                }
        utils::html::f1(fout);
        utils::tree::Tree<int> a;
        for(int v : values) a.add(v,fout);
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
