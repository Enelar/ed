#include <vector>
#include <string>
using namespace std;

#include "ctrler.h"

#include <boost/lexical_cast.hpp>

int func(vector<string> &args)
{
  if (args.size() == 0)
    return -1;
  int port = 30000; // boost::lexical_cast<int>(args[1]);
  boost::asio::io_service io;
  ctrler a(io, port);
  return 0;
}

int main(int argc, char *argv[])
{
  vector<string> arguments;
  for (auto i = 0; i < argc; i++)
    arguments.push_back(argv[i]);
  return func(arguments);
}