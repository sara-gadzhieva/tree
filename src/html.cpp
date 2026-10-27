#include "html.h"
#include <fstream>
namespace utils {
namespace html {

void f1(std::ofstream &fout) {
        fout<<"<!DOCTYPE html>"<<std::endl;
        fout<<"<html lang=\"ru\">"<<std::endl;
        fout<<"<head>"<<std::endl;
        fout<<"<meta charset=\"UTF-8\">"<<std::endl;
        fout<<"<title>Дерево поиска</title>"<<std::endl;
        fout<<"<script type=\"module\">"<<std::endl;
        fout<<"import mermaid from \"https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs\";"<<std::endl;
        fout<<"mermaid.initialize({ startOnLoad: true,"<<std::endl;
        fout<<"flowchart: {"<<std::endl;
        fout<<"useMaxWidth: false,"<<std::endl;
        fout<<"curve: 'linear',"<<std::endl;
        fout<<"nodeSpacing: 30,"<<std::endl;
        fout<<"rankSpacing: 30"<<std::endl;  
        fout<<"}"<<std::endl;  
        fout<<"});"<<std::endl;  
        fout<<"</script>"<<std::endl;  
        fout<<"</head>"<<std::endl;
        fout<<"<body>"<<std::endl;
        }

void f3(std::ofstream &fout) {
        fout<<"</body>"<<std::endl;  
        fout<<"</html>"<<std::endl;
        }
        
} 
} 
