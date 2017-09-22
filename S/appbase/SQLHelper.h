#pragma once
#include "mysql.h"
class SQLHelper {
  public:
    static string create_table(const char* table, const char* values);
    static const char* getSQLType(enum_field_types type);
};

