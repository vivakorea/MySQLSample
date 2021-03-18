#pragma once
#define LONG_STRING	 30
#define NUMBER_MAX   14
#define MSG_MAX  2000
typedef struct {
	char REQ_TIME[LONG_STRING];
	char SND_NUM[NUMBER_MAX];
	char RECV_NUM[NUMBER_MAX];
	char SEND_MSG[MSG_MAX];
	char GROUP_ID[4];
	char SMS_TYPE;
	char PRIORITY;
	char RESERVED_TIME[LONG_STRING];
	char URL[80];
	char STATUS;
	int  TRY_COUNT;
	char REQ_USER[50];
	char END_DATE[LONG_STRING];
	char reserved1[32];
	char reserved2[32];
	char reserved3[32];
} stSMSInfo;