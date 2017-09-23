#include <my_global.h>
#include <mysql.h>

void finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

int Persons(int argc, char **argv)
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if (mysql_real_connect(con, argv[1], argv[2], argv[3],
		"information", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}

	if (mysql_query(con, "DROP TABLE IF EXISTS Persons")) {
		finish_with_error(con);
	}

	if (mysql_query(con, "CREATE TABLE Persons(AcctNum INT ,Name TEXT, Address TEXT,Balance INT)")) {
		finish_with_error(con);
	}

	if (mysql_query(con, "INSERT INTO Persons VALUES(1,'xiaohong','jiana',22)")) {
		finish_with_error(con);
	}

	if (mysql_query(con, "INSERT INTO Persons VALUES(2,'xiaoming','jinan',11)")) {
		finish_with_error(con);
	}

	if (mysql_query(con, "INSERT INTO Persons VALUES(3,'Skoda','jinan',22)")) {
		finish_with_error(con);
	}

	if (mysql_query(con, "INSERT INTO Persons VALUES(4,'Volvo','jinan',33)")) {
		finish_with_error(con);
	}

	mysql_close(con);
	exit(0);
}