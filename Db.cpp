#include"Db.h"

MYSQL* mysql = NULL;
MYSQL_RES* res;
MYSQL_ROW row;

/// <summary>
/// 数据库连接初始化
/// </summary>
/// <returns></returns>
int Db_link() {
	//初始化数据库
	mysql = mysql_init(mysql);
	if (mysql == NULL) {
		printf("mysql_init error!\n");
		return 0;
	}

	//连接到数据库
	mysql = mysql_real_connect(mysql, "localhost", "root", "Abc12345", "GenTableProject", 3306, NULL, 0);
	if (mysql == NULL) {
		printf("mysql_real_connect error!\n");
		return 0;
	}
	else
		return 1;
}

/// <summary>
/// 账号密码校验
/// </summary>
/// <param name="id">账号为6位长度</param>
/// <param name="key">密码为6位长度</param>
/// <returns>账号密码匹配返回1，失败返回0，有账号密码不对返回3，没有账号返回2</returns>
int Db_query_account(char* id,char* key) {
	char querylog[] = "select * from Projects where Name='000000'";
	strncpy(strchr(querylog, '0'), id, 6);
	
	int t= mysql_real_query(mysql, querylog, (unsigned int)strlen(querylog));
	if (t) {
		printf("Error making query:%s\n", mysql_error(mysql));
		return 0;
	}
	res = mysql_store_result(mysql);
	if (mysql_num_rows(res) > 0) {	//判断如果有至少1条记录
		while (row = mysql_fetch_row(res)) {	//循环处理每个记录
			if (strcmp(row[2], key) == 0) { //如果密码一致
				mysql_free_result(res);
				return 1;
			}
			else { //如果密码不一致
				mysql_free_result(res);
				return 3;
			}
			
		}
	}
	else {	//没有记录，说明没有匹配到有效项目ID
		mysql_free_result(res);
		return 2;
	}
	
}