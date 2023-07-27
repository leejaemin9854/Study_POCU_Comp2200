#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "user.h"
#include "data_store.h"

static int check_file(const char* file_name)
{
	FILE* fp = fopen(file_name, "rb");

	if (fp == NULL) {
		return 0;
	}

	fclose(fp);
	return 1;
}

static int record_log(const char* str)
{
	char* open_type = check_file(LOG_FILE_NAME) == 0 ? "wb" : "ab";

	FILE* fp = fopen(LOG_FILE_NAME, open_type);

	fputs(str, fp);

	fclose(fp);
	return 0;
}

user_t* get_user_by_id_or_null(user_t** users_or_null, unsigned int id)
{
	if (users_or_null == NULL) {
		return NULL;
	}

	//int length = _msize(users_or_null) / sizeof(user_t*) - 1;
	int length = 0;
	while (users_or_null[length] != NULL) {
		length++;
	}

	for (int i = 0; i < length; i++) {

		if (users_or_null[i]->id == id) {
			return users_or_null[i];
		}

	}

	return NULL;

}


user_t* get_user_by_username_or_null(user_t** users_or_null, const char* username)
{
	if (users_or_null == NULL) {
		return NULL;
	}

	//int length = _msize(users_or_null) / sizeof(user_t*) - 1;
	int length = 0;
	while (users_or_null[length] != NULL) {
		length++;
	}

	for (int i = 0; i < length; i++) {

		if (strcmp(users_or_null[i]->username, username) == 0) {
			return users_or_null[i];
		}

	}

	return NULL;

}


int update_email(user_t** users_or_null, unsigned int id, const char* email)
{
	if (users_or_null == NULL) {
		return FALSE;
	}

	//int length = _msize(users_or_null) / sizeof(user_t*) - 1;
	int length = 0;
	while (users_or_null[length] != NULL) {
		length++;
	}

	for (int i = 0; i < length; i++) {
		
		if (users_or_null[i]->id == id) {
			
			char log_record[BUFFER_SIZE];

			if (!RELEASE_MOD) {

				sprintf(log_record, "TRACE: User %d updated email from \"%s\" to \"%s\"", users_or_null[i]->id, users_or_null[i]->email, email);

			}
			else {

				sprintf(log_record, "TRACE: User %d updated email from", users_or_null[i]->id);

				char str_email[2][sizeof(users_or_null[i]->email) / sizeof(char)];
				str_email[0][0] = '\0';
				str_email[1][0] = '\0';


				//Pre-modification email--
				int len = 0;
				while (users_or_null[i]->email[len] != '@') {
					len++;
				}

				if (len < 3) {
					strncat(str_email[0], users_or_null[i]->email, len - 1);
					strncat(str_email[0], "*", 1);

					strcat(str_email[0], &users_or_null[i]->email[len]);

				}
				else {
					strncat(str_email[0], users_or_null[i]->email, 1);
					strncat(str_email[0], "**************************************************", len - 2);

					strcat(str_email[0], &users_or_null[i]->email[len - 1]);

				}

				//Email after modification--
				len = 0;
				while (email[len] != '@') {
					len++;
				}

				if (len < 3) {

					strncat(str_email[1], email, len - 1);
					strncat(str_email[1], "*", 1);

					strcat(str_email[1], &email[len]);

				}
				else {

					strncat(str_email[1], email, 1);

					strncat(str_email[1], "**************************************************", len - 2);

					strcat(str_email[1], &email[len - 1]);

				}

				sprintf(log_record, "%s \"%s\" to \"%s\"", log_record, str_email[0], str_email[1]);

			}
			strcat(log_record, "\n");

			record_log(log_record);

			users_or_null[i]->email[0] = '\0';
			strncat(users_or_null[i]->email, email, sizeof(users_or_null[i]->email) / sizeof(char) - 1);


			return TRUE;
		}

	}
	
	return FALSE;
}

int update_password(user_t** users_or_null, unsigned int id, const char* password)
{
	if (users_or_null == NULL) {
		return FALSE;
	}

	//int length = _msize(users_or_null) / sizeof(user_t*) - 1;
	int length = 0;
	while (users_or_null[length] != NULL) {
		length++;
	}

	for (int i = 0; i < length; i++) {

		if (users_or_null[i]->id == id) {

			char log_record[BUFFER_SIZE];
			if (!RELEASE_MOD) {
				sprintf(log_record, "TRACE: User %d updated password from \"%s\" to \"%s\"", users_or_null[i]->id, users_or_null[i]->password, password);
			}
			else {

				sprintf(log_record, "TRACE: User %d updated password from", users_or_null[i]->id);

				char str_password[2][sizeof(users_or_null[i]->password) / sizeof(char)];
				str_password[0][0] = '\0';
				str_password[1][0] = '\0';

				int len = strlen(users_or_null[i]->password);
				
				if (len < 3) {
					strncat(str_password[0], users_or_null[i]->password, len - 1);
					strncat(str_password[0], "*", 1);

				}
				else {
					strncat(str_password[0], users_or_null[i]->password, 1);
					strncat(str_password[0], "**************************************************", len - 2);
					strcat(str_password[0], &users_or_null[i]->password[len - 1]);

				}


				len = strlen(password);

				if (len < 3) {
					strncat(str_password[1], password, len - 1);
					strncat(str_password[1], "*", 1);

				}
				else {
					strncat(str_password[1], password, 1);
					strncat(str_password[1], "**************************************************", len - 2);
					strcat(str_password[1], &password[len - 1]);

				}

				sprintf(log_record, "%s \"%s\" to \"%s\"", log_record, str_password[0], str_password[1]);
			}

			strcat(log_record, "\n");

			record_log(log_record);


			users_or_null[i]->password[0] = '\0';
			strncat(users_or_null[i]->password, password, sizeof(users_or_null[i]->password) / sizeof(char) - 1);

			return TRUE;
		}

	}

	return FALSE;
}



