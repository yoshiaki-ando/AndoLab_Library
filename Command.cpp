/*
 * command.cpp
 *
 *  Created on: 2021/08/31
 *      Author: ando
 */
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Command.h"

AndoLab::Command::Command(std::string str, const char delimiter){
  std::istringstream stream(str);
  std::string field;

  while(std::getline(stream, field, delimiter)){
    splitted_string.push_back(field);
  }
}


