#include "array.h"
#include <limits.h>

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t cnt = 0;

    for (; cnt < element_count; cnt++) {
        if (numbers[cnt] == INT_MIN) {
            return -1;
        }

        if (numbers[cnt] == num) {
            return cnt;
        }

    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t cnt = 0;
    int result = -1;
    for (; cnt < element_count; cnt++) {
        if (numbers[cnt] == INT_MIN) {
            return -1;
        }

        if (numbers[cnt] == num) {
            result = (int)cnt;
        }

    }

    return result;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    int maxNum = 0;
    int index = -1;

    size_t cnt = 0;

    if (element_count <= 0) {
        return index;
    }

    index = 0;
    maxNum = numbers[index];

    for (; cnt < element_count; cnt++) {
        if (numbers[cnt] == INT_MIN) {
            return -1;
        }

        if (maxNum < numbers[cnt]) {
            maxNum = numbers[cnt];
            index = cnt;
        }

    }

    return index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    int minNum = 0;
    int index = -1;

    size_t cnt = 0;

    if (element_count <= 0) {
        return index;
    }

    index = 0;
    minNum = numbers[index];

    for (; cnt < element_count; cnt++) {
        if (numbers[cnt] == INT_MIN) {
            return -1;
        }

        if (minNum > numbers[cnt]) {
            minNum = numbers[cnt];
            index = cnt;
        }

    }

    return index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    int result = 0;
    size_t cnt = 0;

    if (element_count <= 0) {
        return result;
    }

    for (; cnt < element_count; cnt++) {
        if (numbers[cnt] <= 0) {
            return result;
        }

    }

    result = 1;
    return result;

}

int has_even(const int numbers[], const size_t element_count)
{
    int result = 0;
    size_t cnt = 0;

    if (element_count <= 0) {
        return result;
    }

    for (; cnt < element_count; cnt++) {
        if (numbers[cnt] % 2 == 0) {
            result = 1;
            return result;
        }
    }

    return result;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t cnt;

    if (element_count == 0 && pos == 0) {
        numbers[0] = num;
        return 1;
    }
	
    if (element_count <= 0 || pos > element_count) {
        return 0;
    }

    for (cnt = element_count; cnt > pos; cnt--) {
        numbers[cnt] = numbers[cnt - 1];
    }

    numbers[pos] = num;

    return 1;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t cnt;

    if (element_count <= 0 || index >= element_count) {
        return 0;
    }

    for (cnt = index; cnt < element_count - 1; cnt++) {
        numbers[cnt] = numbers[cnt + 1];
    }

    numbers[element_count - 1] = INT_MIN;

    return 1;
}
