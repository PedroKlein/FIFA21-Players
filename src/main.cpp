#include <iostream>
#include "UI/ui.h"
#include "Database/database.h"

int main(int argc, char const *argv[])
{
  Database database;

  UI ui(database);

  ui.Run();

  return 0;
}
