#ifndef CHARACTER_DESERIALIZER_H
#define CHARACTER_DESERIALIZER_H

#define NAME_LENGTH 64

typedef struct {

    char name[NAME_LENGTH];
    unsigned int health;
    unsigned int strength;
    unsigned int defence;

} minion_t;

typedef struct {

    unsigned int fire;
    unsigned int cold;
    unsigned int lightning;

} elemental_resistance_t;


typedef struct {

    unsigned int id;
    unsigned int lvl;
    unsigned int str;
    unsigned int dex;
    unsigned int intel;
    unsigned int def;
    unsigned int hp;
    unsigned int mp;

} character_v1_t;

typedef struct {

    char name[NAME_LENGTH];
    unsigned int level;
    unsigned int strength;
    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int health;
    unsigned int mana;

    unsigned int evasion;
    unsigned int magic_resistance;

} character_v2_t;



typedef struct {

    char name[NAME_LENGTH];
    unsigned int level;
    unsigned int health;
    unsigned int mana;
    unsigned int strength;

    unsigned int dexterity;
    unsigned int intelligence;
    unsigned int armour;
    unsigned int evasion;
    unsigned int leadership;
    unsigned int minion_count;

    elemental_resistance_t elemental_resistance;
    minion_t minions[3];

} character_v3_t;

int is_alpha(char ch);

void convert_string(unsigned int num, char* string);

unsigned int convert_unsigned_int(const char* str);

int check_version(const char* const info);

character_v1_t* convert_character_v1(const char* info, character_v1_t* character_v1);

character_v2_t* convert_character_v2(const char* info, character_v2_t* character_v2);

character_v3_t* convert_character_v3(const char* info, character_v3_t* character_v3);

int get_character(const char* filename, character_v3_t* out_character);

#endif /* CHARACTER_DESERIALIZER_H */

