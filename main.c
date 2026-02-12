#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

void remove_leading_zeros(char* num)
{
    int len = strlen(num), position = 0;
    while (position < len - 1 && num[position] == '0') position++;
    if (position > 0) memmove(num, num + position, len - position + 1);
}

int compare_strings(const char* first, const char* second)
{
    int first_len = strlen(first), second_len = strlen(second);
    return (first_len != second_len) ? first_len - second_len : strcmp(first, second);
}

char* add_strings(const char* first, const char* second)
{
    int first_len = strlen(first), second_len = strlen(second);
    int max_len = ((first_len > second_len) ? first_len : second_len) + 2;
    char* res = (char*)malloc(max_len);
    res[max_len - 1] = '\0';

    int carry = 0, idx = max_len - 2;
    for (int i = first_len - 1, j = second_len - 1; i >= 0 || j>=0 || carry; i--, j--, idx--)
    {
        int digit1 = (i >= 0) ? first[i] - '0' : 0;
        int digit2 = (j >= 0) ? second[j] - '0' : 0;
        int sum_digit = digit1 + digit2 + carry;
        res[idx] = (sum_digit % 10) + '0';
        carry = sum_digit / 10;
    }

    memmove(res, res + idx + 1, max_len - idx - 1);
    remove_leading_zeros(res);
    return res;
}

char* subtract_strings(const char* first, const char* second)
{
    int first_len = strlen(first), max_len = first_len + 1;
    char* res = (char*)malloc(max_len);
    res[max_len - 1] = '\0';

    int borrow = 0, idx = max_len - 2;
    for (int i = first_len - 1, j = strlen(second) - 1; i >= 0; i--, j--, idx--)
    {
        int digit1 = first[i] - '0' - borrow;
        int digit2 = (j >= 0) ? second[j] - '0' : 0;
        borrow = (digit1 < digit2) ? (digit1 += 10, 1) : 0;
        res[idx] = (digit1 - digit2) + '0';
    }

    remove_leading_zeros(res);
    if (res[0] == '\0')
    {
        res[0] = '0'; res[1] = '\0';
    }

    return res;
}

char* multiply_strings(const char* first, const char* second)
{
    if (first[0] == '0' || second[0] == '0')
    {
        char* zero_result = (char*)malloc(2);
        strcpy(zero_result, "0");
        return zero_result;
    }

    int first_len = strlen(first), second_len = strlen(second), result_len = first_len + second_len;
    int* temp = (int*)calloc(result_len, sizeof(int));

    for (int i = first_len - 1; i >= 0; i--)
        for (int j = second_len - 1; j >= 0; j--)
        {
            int product = (first[i] - '0') * (second[j] - '0');
            int sum = temp[i + j + 1] + product;
            temp[i + j + 1] = sum % 10;
            temp[i + j] += sum / 10;
        }

    char* res = (char*)malloc(result_len + 1);
    int idx = 0, result_idx = 0;
    while (idx < result_len && temp[idx] == 0) idx++;
    for (; idx < result_len; idx++)  res[result_idx++] = temp[idx] + '0';

    res[result_idx] = '\0';
    free(temp);
    if (result_idx == 0)
    {
        free(res); char* zero_result = (char*)malloc(2);
        strcpy(zero_result, "0"); return zero_result;
    }
    return res;
}

char* divide_strings(const char* dividend, const char* divisor)
{
    if (divisor[0] == '0')
    {
        printf("Error: division by zero!\n"); return NULL;
    }

    if (compare_strings(dividend, divisor) < 0)
    {
        printf("The divisible is less than the divisor.\n"); return NULL;
    }

    int dividend_len = strlen(dividend);
    char* quotient = (char*)malloc(dividend_len + 1);
    char* cur_remainder = (char*)malloc(strlen(divisor) + 2);
    char digit_str[2] = { 0 };

    strcpy(cur_remainder, "");
    int quotient_idx = 0;

    for (int i = 0; i < dividend_len; i++)
    {
        int cl = strlen(cur_remainder);
        cur_remainder[cl] = dividend[i];
        cur_remainder[cl + 1] = '\0';
        remove_leading_zeros(cur_remainder);

        if (compare_strings(cur_remainder, divisor) < 0)
        {
            quotient[quotient_idx++] = '0'; continue;
        }

        int digit;
        for (digit = 1; digit <= 9; digit++)
        {
            sprintf(digit_str, "%d", digit);
            char* temp = multiply_strings(divisor, digit_str);
            if (compare_strings(temp, cur_remainder) > 0)
            {
                free(temp); digit--; break;
            }
            free(temp);
        }

        if (digit == 10) digit = 9;

        quotient[quotient_idx++] = digit + '0';
        digit_str[0] = digit + '0';
        char* product = multiply_strings(divisor, digit_str);
        char* new_remainder = subtract_strings(cur_remainder, product);
        strcpy(cur_remainder, new_remainder);
        free(product);
        free(new_remainder);
    }

    quotient[quotient_idx] = '\0';
    remove_leading_zeros(quotient);
    free(cur_remainder);
    return quotient;
}

char* add_with_sign(const char* first, const char* second)
{
    int is_first_negative = first[0] == '-';
    int is_second_negative = second[0] == '-';

    const char* first_num = (is_first_negative) ? first + 1 : first;
    const char* second_num = (is_second_negative) ? second + 1 : second;

    if (!is_first_negative && !is_second_negative) return add_strings(first_num, second_num);
    if (is_first_negative && is_second_negative)
    {
        char* sum = add_strings(first_num, second_num);
        char* negative_res = (char*)malloc(strlen(sum) + 2);
        sprintf(negative_res, "-%s", sum);
        free(sum);
        return negative_res;
    }

    int cmp = compare_strings(first_num, second_num);
    if (cmp == 0)
    {
        char* zero_result = (char*)malloc(2);
        strcpy(zero_result, "0");
        return zero_result;
    }

    char* result = (cmp > 0) ? subtract_strings(first_num, second_num) : subtract_strings(second_num, first_num);
    if ((is_first_negative && !is_second_negative && cmp > 0) || (!is_first_negative && is_second_negative && cmp < 0))
    {
        char* negative_res = (char*)malloc(strlen(result) + 2);
        sprintf(negative_res, "-%s", result);
        free(result);
        result = negative_res;
    }
    return result;
}
char* subtract_with_sign(const char* first, const char* second)
{
    int is_first_negative = first[0] == '-';
    int is_second_negative = second[0] == '-';
    const char* first_num = (is_first_negative) ? first + 1 : first, * second_num = (is_second_negative) ? second + 1 : second;

    if (!is_first_negative && is_second_negative) return add_strings(first_num, second_num);
    if (is_first_negative && !is_second_negative)
    {
        char* sum = add_strings(first_num, second_num);
        char* negative_res = (char*)malloc(strlen(sum) + 2);
        sprintf(negative_res, "-%s", sum);
        free(sum);
        return negative_res;
    }

    int cmp = compare_strings(first_num, second_num);
    if (cmp == 0)
    {
        char* zero_result = (char*)malloc(2);
        strcpy(zero_result, "0");
        return zero_result;
    }

    char* result = ((!is_first_negative && !is_second_negative && cmp > 0)
        || (is_first_negative && is_second_negative && cmp < 0)) ? subtract_strings(first_num, second_num) : subtract_strings(second_num, first_num);

    if ((!is_first_negative && !is_second_negative && cmp < 0) || (is_first_negative && is_second_negative && cmp > 0))
    {
        char* negative_res = (char*)malloc(strlen(result) + 2);
        sprintf(negative_res, "-%s", result);
        free(result); return negative_res;
    }
    return result;
}

char* multiply_with_sign(const char* first, const char* second)
{
    int is_first_negative = first[0] == '-';
    int is_second_negative = second[0] == '-';
    const char* first_num = (is_first_negative) ? first + 1 : first, * second_num = (is_second_negative) ? second + 1 : second;

    char* product = multiply_strings(first_num, second_num);
    if ((is_first_negative != is_second_negative) && strcmp(product, "0") != 0)
    {
        char* negative_res = (char*)malloc(strlen(product) + 2);
        sprintf(negative_res, "-%s", product);
        free(product);
        return negative_res;
    }
    return product;
}

int is_valid_num(const char* num)
{
    if (strlen(num) == 0) return 0;
    int start_idx = 0;
    if (num[0] == '-')
    {
        if (strlen(num) == 1) return 0; // Только минус без цифр
        start_idx = 1;
    }

    for (int i = start_idx; num[i]; i++) if (!isdigit(num[i])) return 0;

    return 1;
}

int main()
{
    char num1[MAX_LEN], num2[MAX_LEN];
    int choice;

    printf("Long Integer Calculator\n\n");
    printf("First number: "); scanf("%s", num1);
    if (!is_valid_num(num1))
    {
        printf("Error!\n"); return 0;
    }

    printf("Second number: "); scanf("%s", num2);
    if (!is_valid_num(num2))
    {
        printf("Error!\n"); return 0;
    }

    printf("\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exit\nChoice: ");
    scanf("%d", &choice);
    if (choice == 5)
    {
        printf("Exitn"); return 0;
    }

    char* result = NULL;
    switch (choice)
    {
    case 1: result = add_with_sign(num1, num2); break;
    case 2: result = subtract_with_sign(num1, num2); break;
    case 3: result = multiply_with_sign(num1, num2); break;
    case 4:
    {
        int is_first_negative = num1[0] == '-';
        int is_second_negative = num2[0] == '-';
        result = divide_strings(is_first_negative ? num1 + 1 : num1, is_second_negative ? num2 + 1 : num2);
        if (result && (is_first_negative != is_second_negative) && strcmp(result, "0") != 0)
        {
            char* negative_res = (char*)malloc(strlen(result) + 2);
            sprintf(negative_res, "-%s", result);
            free(result);
            result = negative_res;
        }
        break;
    }
    default: printf("Wrong choice\n"); return 0;
    }

    if (result)
    {
        printf("\nResult: %s\n", result);
        free(result);
    }

    return 0;
}


