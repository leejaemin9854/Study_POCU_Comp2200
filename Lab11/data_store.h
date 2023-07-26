#ifndef DATA_STORE_H
#define DATA_STORE_H

#include "user.h"

#define TRUE (1)
#define FALSE (0)

#define BUFFER_SIZE (1024)

#define RELEASE_MOD (0)



#ifdef RELEASE

#undef RELEASE_MOD
#define RELEASE_MOD (1)

#endif // !RELEASE



#define LOG_FILE_NAME ("log.txt")

static int check_file(const char* file_name);

static int record_log(const char* str);

user_t* get_user_by_id_or_null(user_t** users_or_null, unsigned int id);

user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username);

int update_email(user_t** users_or_null, unsigned int id, const char* email);

int update_password(user_t** users_or_null, unsigned int id, const char* password);


#endif
