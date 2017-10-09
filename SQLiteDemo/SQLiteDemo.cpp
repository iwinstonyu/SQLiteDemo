// SQLiteDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <thread>

using namespace std;

// 阻塞型调用
// 每一行数据都会调用一次callback
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	cout << "callback: " << this_thread::get_id() << endl;
	Sleep(10000);
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main()
{
	sqlite3* db;
	char* pszErr = NULL;
	char* sql;
	int rc;

	cout << "Main thread: " << this_thread::get_id() << endl;

	rc = sqlite3_open("test.db", &db);
	if (rc) {
		cout << "fail open test.db" << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return 1;
	}

	cout << "succ open test.db" << endl;

	// 创建表
// 	sql = "create table role_list(id int primary key not null, nickname varchar(50) not null);";
// 	rc = sqlite3_exec(db, sql, callback, 0, &pszErr);
// 	if (rc != SQLITE_OK) {
// 		cout << "SQL error: " << pszErr;
// 		sqlite3_free(pszErr);
// 	}
// 	else {
// 		cout << "succ create table role_list" << endl;
// 	}

	// 查询数据
	sql = "select * from role_list;";
	rc = sqlite3_exec(db, sql, callback, 0, &pszErr);
	if (rc != SQLITE_OK) {
		cout << "SQL error: " << pszErr;
		sqlite3_free(pszErr);
	}
	else {
		cout << "succ select from role_list" << endl;
	}

	// 删除数据
	sql = "delete from role_list where id = 1;";
	rc = sqlite3_exec(db, sql, callback, 0, &pszErr);
	if (rc != SQLITE_OK) {
		cout << "SQL error: " << pszErr;
		sqlite3_free(pszErr);
	}
	else {
		cout << "succ delete from role_list" << endl;
	}

	// 查询数据
	sql = "select * from role_list;";
	rc = sqlite3_exec(db, sql, callback, 0, &pszErr);
	if (rc != SQLITE_OK) {
		cout << "SQL error: " << pszErr;
		sqlite3_free(pszErr);
	}
	else {
		cout << "succ select from role_list" << endl;
	}

	sqlite3_close(db);

	system("pause");
    return 0;
}

