#include "functionkno.h"
#include <sys/stat.h>
#include <iostream>

bool isFileExists_stat(std::string& name) {
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}
void existfunc(){
    std::string filename = "/dev/video*";
    bool ret = isFileExists_stat(filename);
    if (ret)
    {
        std::cout << "文件存在" << std::endl;
    }
    else
    {
        std::cout << "文件不存在" << std::endl;
    }
}

FunctionKno::FunctionKno(QObject *parent)
    : QObject{parent}
{

}
