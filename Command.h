/*
 * command.h
 *
 *  Created on: 2021/08/31
 *      Author: ando
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

namespace AndoLab{

class Command{
private:
  std::vector <std::string> splitted_string;

public:
  Command(std::string, const char delimiter);

  double get_d(const int i){ return std::stod( splitted_string.at(i) ); }
  int get_i(const int i){ return std::stoi( splitted_string.at(i) ); }
};

}

#endif /* COMMAND_H_ */
