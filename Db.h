#ifndef _DB_H_
#define _DB_H_

#include<mysql/mysql.h>
#include<stdio.h>
#include<string.h>
int Db_link();
int Db_query_account(char* id, char* key);
void Net_send(char* sendbuff);
#endif
