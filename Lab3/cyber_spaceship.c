#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    const char* longest_start_pos = cab_start_location;

    const char* p_start_pos = cab_start_location;
    size_t longest_safty_location_length = 0;
    int p_space_length = 0;

    int p_space_cluster = 0;

    unsigned int i;
    unsigned int j;

    unsigned int p_pos;
    unsigned int cluster_spos;
	

    if (cab_length == 0) {
        out_longest_safe_area_length = 0;
        return NULL;
    }

    for (i = 0; i < cab_length; i++) {

        p_space_cluster = 0;
        for (j = 0; j < cluster_count; j++) {

            p_pos = (unsigned int)&cab_start_location[i];
            cluster_spos = (unsigned int)cluster_start_locations[j];
            if (p_pos >= cluster_spos && p_pos < cluster_spos + cluster_lengths[j]) {
                p_space_cluster++;
            }

        }
        if (p_space_cluster % 2 == 0) {
            if (p_space_length == 0) {
                p_start_pos = &cab_start_location[i];
            }

            p_space_length++;
        } else {
            if (p_space_length >= longest_safty_location_length) {
                longest_safty_location_length = p_space_length;
                longest_start_pos = p_start_pos;

            }
            p_space_length = 0;

        }
		
    }
    if (p_space_length >= longest_safty_location_length) {
        longest_safty_location_length = p_space_length;
        longest_start_pos = p_start_pos;
    }

	

    *out_longest_safe_area_length = longest_safty_location_length;
    return longest_start_pos;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    double result = 0;
    int safty_time = 0;
    int dangrous_time = 0;

    const char* p_start_pos = cab_start_location;
    int p_space_length = 0;

    int p_space_cluster;

    unsigned int i;
    unsigned int j;

    unsigned int p_pos;
    unsigned int cluster_spos;


    if (cab_length == 0) {
        return 0;
    }

    for (i = 0; i < cab_length; i++) {

        p_space_cluster = 0;
        for (j = 0; j < cluster_count; j++) {

            p_pos = (unsigned int)&cab_start_location[i];
            cluster_spos = (unsigned int)cluster_start_locations[j];
            if (p_pos >= cluster_spos && p_pos < cluster_spos + cluster_lengths[j]) {
                p_space_cluster++;
            }

        }
        if (p_space_cluster % 2 == 0) {
            safty_time++;
        }
        else {
            dangrous_time++;
        }

    }
    result = ((float)safty_time / 10 + (float)dangrous_time / 5) + 0.5f;

    return (int)result;
}

