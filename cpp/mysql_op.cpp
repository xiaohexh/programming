#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void close_mysql(MYSQL* conn, MYSQL_RES* result)
{
	mysql_free_result(result);
	mysql_close(conn);
	mysql_library_end();
}

int main()
{
	MYSQL*		conn;
	MYSQL_RES*	result;
	MYSQL_ROW	row;	
	unsigned long* lens;

	const std::string sql_name("umonitor2");
	const std::string table_name("my_contacts");

	conn = mysql_init(NULL);
	mysql_real_connect(conn, "127.0.0.1", "root", "root000", "mysql", 3306, NULL, 0);

	// change db
	mysql_select_db(conn, sql_name.c_str());

	// insert record into db
	std::stringstream ssql;
	std::string name("Tom");
	int age = 20;
	std::string location("Tokyo");
	int prof_id = 3;
	std::string interest("reading");

	ssql << "insert into " << table_name << "(name, age, location, prof_id, interests) values ('"
		<< name << "', " << age << ", '" << location << "', " << prof_id << ", '" << interest << "')";
	int ret = mysql_real_query(conn, ssql.str().c_str(), ssql.str().size());
	if (ret != 0)
	{
		std::cout << "insert sql sentence executed failed\n";
	}

	// select record from db
	std::string sql = "select * from my_contacts";
	//mysql_query(conn, sql);
	mysql_real_query(conn, sql.c_str(), sql.size());

	result = mysql_store_result(conn);
	if (result == NULL)
	{
		std::cout << mysql_errno(conn) << ":" << mysql_error(conn) << std::endl;
		close_mysql(conn, result);
	}

	unsigned field_count = mysql_field_count(conn);
	int rows = mysql_num_rows(result);
	printf("rows:%d\n", rows);

	for (int i = 0; i < rows; ++i)
	{
		row = mysql_fetch_row(result);
		for (int j = 0; j < mysql_num_fields(result); ++j)
			printf("%s ", row[j]);
		printf("\n");
	}

	unsigned long long affected_rows = mysql_affected_rows(conn);
	std::cout << "affected rows:" << affected_rows << std::endl;

	close_mysql(conn, result);

	return 0;
}
