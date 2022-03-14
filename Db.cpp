#include"Db.h"

MYSQL* mysql = NULL;
MYSQL_RES* res;
MYSQL_ROW row;

/// <summary>
/// ���ݿ����ӳ�ʼ��
/// </summary>
/// <returns></returns>
int Db_link() {
	//��ʼ�����ݿ�
	mysql = mysql_init(mysql);
	if (mysql == NULL) {
		printf("mysql_init error!\n");
		return 0;
	}

	//���ӵ����ݿ�
	mysql = mysql_real_connect(mysql, "localhost", "root", "Abc12345", "GenTableProject", 3306, NULL, 0);
	if (mysql == NULL) {
		printf("mysql_real_connect error!\n");
		return 0;
	}
	else
		return 1;
}

/// <summary>
/// �˺�����У��
/// </summary>
/// <param name="id">�˺�Ϊ6λ����</param>
/// <param name="key">����Ϊ6λ����</param>
/// <returns>�˺�����ƥ�䷵��1��ʧ�ܷ���0�����˺����벻�Է���3��û���˺ŷ���2</returns>
int Db_query_account(char* id,char* key) {
	char querylog[] = "select * from Projects where Name='000000'";
	strncpy(strchr(querylog, '0'), id, 6);
	
	int t= mysql_real_query(mysql, querylog, (unsigned int)strlen(querylog));
	if (t) {
		printf("Error making query:%s\n", mysql_error(mysql));
		return 0;
	}
	res = mysql_store_result(mysql);
	if (mysql_num_rows(res) > 0) {	//�ж����������1����¼
		while (row = mysql_fetch_row(res)) {	//ѭ������ÿ����¼
			if (strcmp(row[2], key) == 0) { //�������һ��
				mysql_free_result(res);
				return 1;
			}
			else { //������벻һ��
				mysql_free_result(res);
				return 3;
			}
			
		}
	}
	else {	//û�м�¼��˵��û��ƥ�䵽��Ч��ĿID
		mysql_free_result(res);
		return 2;
	}
	
}