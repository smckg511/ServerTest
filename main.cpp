#include<stdio.h>
#include"Net.h"
#include"Db.h"

int main() {

	int num=0,db_res=0;
	char* readbuff;

	//�������ݿ�
	if (Db_link())	printf("Db_link success\n");
	//��������ʼ��
	if (Net_init()) printf("Net_init success\n");
	//�����������
	if (Net_listen()) printf("Net_listen create\n");

	while (1) {
		//����ֱ���пͻ�������
		if (Net_accept()) {
			printf("Net_accept success\n");
			//��ȡ��Ϣ
			readbuff = Net_recv(&num);

			if (num > 0) {
				switch (readbuff[0]) {
				case 1: //ϵͳ��¼��Ϣ
					printf("type=1 num=%d,readbuff:%s\n", num, readbuff+1);
					char readId[7], readKey[7];
					strncpy(readId, readbuff + 1, 6);
					readId[6] = '\0';
					strncpy(readKey, readbuff + 7, 6);
					readKey[6] = '\0';
					printf("%s,%s\n", readId, readKey);
					db_res = Db_query_account(readId, readKey);
					if (db_res == 1) Net_send("account success");
					else if (db_res == 2) Net_send("no account id");
					else if (db_res == 3) Net_send("key wrong");
					break;
				default:
					printf("��Ч��Ϣ\n");
					break;
				}
			}
			Net_connect_close();
		}
	}
	return 1;
}




