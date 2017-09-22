#include "stdafx.h"
#include "SQLHelper.h"
#include <iosfwd>
#include <io.h>
std::string SQLHelper::create_table(const char* table, const char* values) {
    //mysql> insert into yw_account values(12345);
    std::stringstream str;
    str << "create table " << table << " values(" << values << ")";
    return str.str();
}

const char* SQLHelper::getSQLType(enum_field_types type) {
    switch (type) {
    case MYSQL_TYPE_DECIMAL:
        return "DECIMAL";
        break;
    case MYSQL_TYPE_TINY:
        return "TINYINT";
        break;
    case MYSQL_TYPE_SHORT:
        return "SMALLINT";
        break;
    case MYSQL_TYPE_LONG:
        return "INT";
        break;
    case MYSQL_TYPE_FLOAT:
        return "FLOAT";
        break;
    case MYSQL_TYPE_DOUBLE:
        return "DOUBLE";
        break;
    case MYSQL_TYPE_NULL:
        //return "TIMESTAMP";
        break;
    case MYSQL_TYPE_TIMESTAMP:
        return "TIMESTAMP";
        break;
    case MYSQL_TYPE_LONGLONG:
        return "BIGINT";
        break;
    case MYSQL_TYPE_INT24:
        //return "TIMESTAMP";
        break;
    case MYSQL_TYPE_DATE:
        return "DATE";
        break;
    case MYSQL_TYPE_TIME:
        return "TIME";
        break;
    case MYSQL_TYPE_DATETIME:
        return "DATETIME";
        break;
    case MYSQL_TYPE_YEAR:
        return "YEAR";
        break;
    case MYSQL_TYPE_NEWDATE:
        break;
    case MYSQL_TYPE_VARCHAR:
        return "VARCHAR";
        break;
    case MYSQL_TYPE_BIT:
        return "BIT";
        break;
    case MYSQL_TYPE_TIMESTAMP2:
        break;
    case MYSQL_TYPE_DATETIME2:
        break;
    case MYSQL_TYPE_TIME2:
        break;
    case MYSQL_TYPE_NEWDECIMAL:
        break;
    case MYSQL_TYPE_ENUM:
        return "ENUM";
        break;
    case MYSQL_TYPE_SET:
        return "SET";
        break;
    case MYSQL_TYPE_TINY_BLOB:
        return "BLOB";
        break;
    case MYSQL_TYPE_MEDIUM_BLOB:
        return "MEDIUMBLOB";
        break;
    case MYSQL_TYPE_LONG_BLOB:
        return "LONGBLOB";
        break;
    case MYSQL_TYPE_BLOB:
        return "BLOB";
        break;
    case MYSQL_TYPE_VAR_STRING:
        return "VARCHAR";
        break;
    case MYSQL_TYPE_STRING:
        return "TEXT";
        break;
    case MYSQL_TYPE_GEOMETRY:
        return "IMAGE";
        break;
    default:
        break;
    }
    throw new std::logic_error("Invalid Type");
}
