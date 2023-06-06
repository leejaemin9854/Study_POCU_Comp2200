#include "character_deserializer.h"
#define BUFFER_SIZE 1024

#include <string.h>

int isalpha(char ch)
{
    return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122);
}


unsigned int convert_unsigned_int(const char* str)
{
    unsigned int result=0;

    while(*str != 0) {
        result = result*10u + *str-48u;
        str++;
    }

    return result;
}



int version_check(const char* info)
{
    int result=0;

    while(*info==' ' || *info=='_' || isalpha(*info)) {
        info++;
    }

    if((*info)==':') {

        result=1;

    } else if((*info)==',') {

        result=2;

    } else if((*info)=='|') {

        result=3;

    }


    return result;
}

character_v1_t convert_character_v1(const char* info)
{
    character_v1_t result;

    char member_name[8][64]={0, };
    int member_value[8]={0, };

    unsigned int i;
    size_t index=0;

    for(i=0; i<8; i++) {

        index=0;
        while(info[index++]!=':');

        strncpy(member_name[i], info, index-1);

        while(info[index]>=48 && info[index]<=57) {
            member_value[i] = member_value[i]*10 + info[index]-48;
            index++;

        }
        info=&info[++index];
        
    }

    for(i=0; i<8; i++) {
        if(strncmp(member_name[i], "lvl", 3)==0) {
            result.lvl=member_value[i];

        } else if(strncmp(member_name[i], "intel", 5)==0) {
            result.intel=member_value[i];

        } else if(strncmp(member_name[i], "str", 3)==0) {
            result.str=member_value[i];

        } else if(strncmp(member_name[i], "dex", 3)==0) {
            result.dex=member_value[i];

        } else if(strncmp(member_name[i], "def", 3)==0) {
            result.def=member_value[i];

        } else if(strncmp(member_name[i], "id", 2)==0) {
            result.id=member_value[i];

        } else if(strncmp(member_name[i], "hp", 2)==0) {
            result.hp=member_value[i];

        } else if(strncmp(member_name[i], "mp", 2)==0) {
            result.mp=member_value[i];

        }
    }


    return result;
}


character_v2_t convert_character_v2(const char* info)
{
    character_v2_t result;
    unsigned int member_value[9]={0, };

    unsigned int i;
    size_t index=0;

    while(*info++!='\n');

    index=0;
    while(info[index++]!=',');
    strncpy(result.name, info, index-1);

    info=&info[index];

    for(i=0; i<9; i++) {

        index=0;
        while(info[index]>=48 && info[index]<=57) {
            member_value[i] = member_value[i]*10 + info[index]-48;
            index++;
        }

        info=&info[++index];
    }

    index=0;
    result.level=member_value[index++];
    result.strength=member_value[index++];
    result.dexterity=member_value[index++];
    result.intelligence=member_value[index++];
    result.armour=member_value[index++];
    result.evasion=member_value[index++];
    result.magic_resistance=member_value[index++];
    result.health=member_value[index++];
    result.mana=member_value[index];

    return result;
}



int get_character(const char* filename, character_v3_t* out_character)
{
    


    return 0;
}

