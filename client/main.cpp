#include <vector>
#include <string>
using namespace std;

#include <boost/lexical_cast.hpp>

#define _ED_CONNECTOR_DEFINED_
#include "connector.h"
static boost::asio::io_service io;
connector singletone_connector(io);

int func(vector<string> &args)
{
  if (args.size() == 0)
    return -1;
  int port = boost::lexical_cast<int>(args[0]);
  return 0;
}

int main(int argc, char *argv[])
{
  vector<string> arguments;
  for (auto i = 0; i < argc; i++)
    arguments.push_back(argv[i]);
  return func(arguments);
}