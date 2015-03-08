#include <vector>
#include <string>
using namespace std;

#include <boost/lexical_cast.hpp>

#define _ED_CONNECTOR_DEFINED_
#include "connector.h"
boost::asio::io_service io;
connector singletone_connector(io);

#include "example_module.h"
#include <thread>

int func(vector<string> &args)
{
  if (args.size() == 0)
    return -1;
  int port = 30000; // boost::lexical_cast<int>(args[1]);

  singletone_connector.Connect("localhost", port);
  example_module a;

  a.Subscribe();
  a.Emit();

  while (_DEBUG)
  {
    io.run();
    std::this_thread::sleep_for(10ms);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  vector<string> arguments;
  for (auto i = 0; i < argc; i++)
    arguments.push_back(argv[i]);
  return func(arguments);
}