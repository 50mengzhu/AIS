#include "readDB.h"

int ReadDB::get_ship_length(std::string MMSI)
{
    int         length;
    MYSQL*      conn;
    MYSQL_RES*  res;
    MYSQL_ROW   row;

    conn = mysql_init((MYSQL*)0);

    if (!mysql_real_connect(conn, server, user, pass, dbname, 3306, NULL, 0))
        std::cout << mysql_error(conn) << std::endl;
    else
        std::cout << "Connect..." << std::endl;

    std::string sql = "select Length from ";
    sql += tabName;
    sql += " where MMSI = ";
    sql += MMSI;

    const char* query = sql.c_str();

    if (mysql_query(conn, query))
        std::cout << mysql_error(conn) << std::endl;
    else
    {
        std::cout << "Query made..." << std::endl;

        res = mysql_use_result(conn);

        if (res)
        {
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                for (int t = 0; t < mysql_num_fields(res); ++ t)
                {
                    length = atoi(row[t]);
                }
            }
        }
        mysql_free_result(res);
    }

    mysql_close(conn);

    return length;
}

double ReadDB::std_ship_coe(int length)
{  
    double coe = 0.0;
    if (length <= 0)
        coe = 0.0;
    else if (length < 30)
        coe = 0.3;
    else if (length < 50)
        coe = 0.5;
    else if (length < 90)
        coe = 1.0;
    else if (length < 180)
        coe = 2.1;
    else 
        coe = 3.5;

    return coe; 
}