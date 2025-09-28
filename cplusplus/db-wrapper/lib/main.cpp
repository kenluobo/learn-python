#include "def/File.h"
#include "query.h"
#include "tables.h"

int main(int argc, char *argv[]) {
  RdbQuery rdbQuery;
  std::vector<FileTableItem> users = rdbQuery.query_items_from<FileTableItem>("123"); 
}
