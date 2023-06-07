#include "character_deserializer.h"
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1024

int is_alpha(char ch)
{
    return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122);
}

void convert_string(unsigned int num, char* const string)
{
    char ch;
    unsigned int i;
    unsigned int index = 0;

    while (num > 0) {

        ch = num % 10 + 48;
        string[index++] = ch;
        
        num /= 10;
    }

    for (i = 0; i < index / 2; i++) {
        ch = string[i];
        string[i] = string[index - i - 1];
        string[index - i - 1] = ch;
    }
    string[index] = '\0';

}


unsigned int convert_unsigned_int(const char* str)
{
    unsigned int result = 0;

    while (*str != 0) {
        result = result * 10u + *str - 48u;
        str++;
    }

    return result;
}



int version_check(const char* info)
{
    int result = 0;

    while (*info == ' ' || *info == '_' || is_alpha(*info)) {
        info++;
    }

    if ((*info) == ':') {

        result = 1;

    }
    else if ((*info) == ',') {

        result = 2;

    }
    else if ((*info) == '|') {

        result = 3;

    }


    return result;
}

character_v1_t* convert_character_v1(const char* info, character_v1_t* const character_v1)
{
    unsigned int i;
    size_t index = 0;

    char member_name[8][64] = { 0, };
    int member_value[8] = { 0, };

    for (i = 0; i < 8; i++) {

        index = 0;
        while (info[index++] != ':');

        strncpy(member_name[i], info, index - 1);

        while (info[index] >= 48 && info[index] <= 57) {
            member_value[i] = member_value[i] * 10 + info[index] - 48;
            index++;

        }
        info = &info[++index];
        
    }

    for (i = 0; i < 8; i++) {
        if (strncmp(member_name[i], "lvl", 3) == 0) {
            character_v1->lvl = member_value[i];

        } else if (strncmp(member_name[i], "intel", 5) == 0) {
            character_v1->intel=member_value[i];

        } else if (strncmp(member_name[i], "str", 3) == 0) {
            character_v1->str=member_value[i];

        } else if (strncmp(member_name[i], "dex", 3) == 0) {
            character_v1->dex=member_value[i];

        } else if (strncmp(member_name[i], "def", 3) == 0) {
            character_v1->def=member_value[i];

        } else if (strncmp(member_name[i], "id", 2) == 0) {
            character_v1->id=member_value[i];

        } else if (strncmp(member_name[i], "hp", 2) == 0) {
            character_v1->hp=member_value[i];

        } else if (strncmp(member_name[i], "mp", 2) == 0) {
            character_v1->mp=member_value[i];

        }
    }


    return character_v1;
}


character_v2_t* convert_character_v2(const char* info, character_v2_t* character_v2)
{
    unsigned int i;
    size_t index = 0;
    size_t length;

    unsigned int member_value[9] = { 0, };

    while (*info++ != '\n');

    index = 0;
    while (info[index] != ',') {
        index++;
    }
    length = index;
    if (length > 50) {
        length = 50;
    }

    strncpy(character_v2->name, info, length);
    character_v2->name[length] = '\0';

    info = &info[++index];

    for (i = 0; i < 9; i++) {

        index = 0;
        while (info[index] >= 48 && info[index] <= 57) {
            member_value[i] = member_value[i] * 10 + info[index] - 48;
            index++;
        }

        info = &info[++index];
    }

    index = 0;
    character_v2->level = member_value[index++];
    character_v2->strength = member_value[index++];
    character_v2->dexterity = member_value[index++];
    character_v2->intelligence = member_value[index++];
    character_v2->armour = member_value[index++];
    character_v2->evasion = member_value[index++];
    character_v2->magic_resistance = member_value[index++];
    character_v2->health = member_value[index++];
    character_v2->mana = member_value[index];

    return character_v2;
}


character_v3_t* convert_character_v3(const char* info, character_v3_t* character_v3)
{
    character_v3_t* result = character_v3;

    unsigned int i;
    size_t index;
    size_t length;

    unsigned int member_value[13]={0, };

    result = character_v3;


    while (*info++ != '\n');

    index = 0;
    while (info[index] != ' ' && info[index] != '|') {
        index++;
    }

    length = index;
    if (length > 50) {
        length = 50;
    }

    strncpy(character_v3->name, info, length);
    character_v3->name[length] = '\0';

    while (info[index++] != '|');
    info = &info[index];

    for (i = 0; i < 13; i++) {

        index = 0;
        while (info[index] < 48 || info[index]>57) {
            index++;
        }
        info = &info[index];

        index = 0;
        while (info[index] >= 48 && info[index] <= 57) {
            member_value[i] = member_value[i] * 10 + info[index] - 48;
            index++;

        }
        info = &info[index];
    }

    index = 0;
    character_v3->level = member_value[index++];
    character_v3->health = member_value[index++];
    character_v3->mana = member_value[index++];
    character_v3->strength = member_value[index++];
    character_v3->dexterity = member_value[index++];
    character_v3->intelligence = member_value[index++];
    character_v3->armour = member_value[index++];
    character_v3->evasion = member_value[index++];

    character_v3->elemental_resistance.fire = member_value[index++];
    character_v3->elemental_resistance.cold = member_value[index++];
    character_v3->elemental_resistance.lightning = member_value[index++];


    character_v3->leadership = member_value[index++];
    character_v3->minion_count = member_value[index++];

    if (character_v3->minion_count > 0) {

        while (*info++ != 'n');

        while (*info++ != '\n');

        for (i = 0; i < character_v3->minion_count; i++) {

            /* Name Copy */
            index = 0;
            while (info[index] != ' ' && info[index] != '|') {
                index++;
            }
            length = index;
            if (length > 50) {
                length = 50;
            }
            strncpy(character_v3->minions[i].name, info, length);
            character_v3->minions[i].name[length] = '\0';

            info = &info[index];
            
            /* Health Copy */
            index = 0;
            while (info[index] < 48 || info[index] >57) {
                index++;
            }

            info = &info[index];

            index = 0;
            character_v3->minions[i].health = 0;
            while (info[index] >= 48 && info[index] <= 57) {
                character_v3->minions[i].health = character_v3->minions[i].health * 10 + info[index] - 48;
                index++;
            }
            info = &info[index];

            index = 0;
            while (info[index] < 48 || info[index]>57) {
                index++;
            }

            info = &info[index];


            /* Strength Copy */
            index = 0;
            character_v3->minions[i].strength = 0;
            while (info[index] >= 48 && info[index] <= 57) {
                character_v3->minions[i].strength = character_v3->minions[i].strength * 10 + info[index] - 48;
                index++;
            }
            info = &info[index];

            index=0;
            while (info[index] < 48 || info[index]>57) {
                index++;
            }
            info = &info[index];


            /* Defence Copy */
            index = 0;
            character_v3->minions[i].defence = 0;
            while (info[index] >= 48 && info[index] <= 57) {
                character_v3->minions[i].defence = character_v3->minions[i].defence * 10 + info[index] - 48;
                index++;
            }
            info = &info[index];

            index = 0;
            while (info[index] != '\n' && info[index] != 0) {
                index++;
            }
            info = &info[++index];
        }

    }

    return result;
}


int get_character(const char* filename, character_v3_t* out_character)
{
    int version = 0;
    char buffer[BUFFER_SIZE] = { 0, };
    unsigned int i;

    character_v1_t character_v1;
    character_v2_t character_v2;
    character_v3_t character_v3;

    FILE* stream;
    stream = fopen(filename, "rb");
    fread(buffer, sizeof(buffer), 1, stream);
    fclose(stream);

    version = version_check(buffer);


    if (version == 1) {
        convert_character_v1(buffer, &character_v1);

        strcpy(character_v2.name, "player_");
        convert_string(character_v1.id, &character_v2.name[7]);


        character_v2.level = character_v1.lvl;
        character_v2.strength = character_v1.str;
        character_v2.dexterity = character_v1.dex;
        character_v2.intelligence = character_v1.intel;
        character_v2.armour = character_v1.def;
        character_v2.health = character_v1.hp;
        character_v2.mana = character_v1.mp;

        character_v2.evasion = character_v2.dexterity / 2;
        character_v2.magic_resistance = character_v2.armour / 4;

        goto after_convert_v2;

    }

    if (version == 2) {

        convert_character_v2(buffer, &character_v2);

    after_convert_v2:
        strcpy(character_v3.name, character_v2.name);
        character_v3.level = character_v2.level;
        character_v3.health = character_v2.health;
        character_v3.mana = character_v2.mana;
        character_v3.strength = character_v2.strength;

        character_v3.dexterity = character_v2.dexterity;
        character_v3.intelligence = character_v2.intelligence;
        character_v3.armour = character_v2.armour;
        character_v3.evasion = character_v2.evasion;

        character_v3.leadership = character_v2.level / 10;
        character_v3.minion_count = 0;

        character_v3.elemental_resistance.fire = character_v2.magic_resistance / 3;
        character_v3.elemental_resistance.cold = character_v2.magic_resistance / 3;
        character_v3.elemental_resistance.lightning = character_v2.magic_resistance / 3;

        goto after_convert_v3;

    }

    if (version == 3) {

        convert_character_v3(buffer, &character_v3);
    }

after_convert_v3:


    strcpy(out_character->name, character_v3.name);

    out_character->level = character_v3.level;
    out_character->health = character_v3.health;
    out_character->mana = character_v3.mana;
    out_character->strength = character_v3.strength;

    out_character->dexterity = character_v3.dexterity;
    out_character->intelligence = character_v3.intelligence;
    out_character->armour = character_v3.armour;
    out_character->evasion = character_v3.evasion;
    out_character->leadership = character_v3.leadership;
    out_character->minion_count = character_v3.minion_count;

    out_character->elemental_resistance.fire = character_v3.elemental_resistance.fire;
    out_character->elemental_resistance.cold = character_v3.elemental_resistance.cold;
    out_character->elemental_resistance.lightning = character_v3.elemental_resistance.lightning;

    for (i = 0; i < character_v3.minion_count; i++) {
        strcpy(out_character->minions[i].name, character_v3.minions[i].name);

        out_character->minions[i].health = character_v3.minions[i].health;
        out_character->minions[i].strength = character_v3.minions[i].strength;
        out_character->minions[i].defence = character_v3.minions[i].defence;
    }


    return version;
}

