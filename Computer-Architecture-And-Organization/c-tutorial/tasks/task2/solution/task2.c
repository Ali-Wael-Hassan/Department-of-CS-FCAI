#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static unsigned long int_magnitude(int value) {
    if (value < 0)
        return (unsigned long)(-(value + 1)) + 1UL;
    return (unsigned long)value;
}

static int parse_integer(const char *text, int *out) {
    const char *p;
    unsigned long value;
    unsigned long limit;
    unsigned long digit;
    int sign;

    if (text == NULL || out == NULL || *text == '\0')
        return 0;

    p = text;
    sign = 1;
    if (*p == '+' || *p == '-') {
        if (*p == '-')
            sign = -1;
        ++p;
    }

    if (*p == '\0')
        return 0;

    if (sign < 0)
        limit = (unsigned long)INT_MAX + 1UL;
    else
        limit = (unsigned long)INT_MAX;

    value = 0UL;
    while (*p != '\0') {
        if (*p < '0' || *p > '9')
            return 0;

        digit = (unsigned long)(*p - '0');
        if (value > (limit - digit) / 10UL)
            return 0;

        value = value * 10UL + digit;
        ++p;
    }

    if (sign < 0) {
        if (value == (unsigned long)INT_MAX + 1UL)
            *out = INT_MIN;
        else
            *out = -(int)value;
    } else {
        *out = (int)value;
    }

    return 1;
}

static int is_operator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%';
}

static int checked_multiply(int left, int right, int *result) {
    unsigned long left_magnitude;
    unsigned long right_magnitude;
    unsigned long limit;
    unsigned long product;
    int negative;

    left_magnitude = int_magnitude(left);
    right_magnitude = int_magnitude(right);
    negative = (left < 0 && right > 0) || (left > 0 && right < 0);

    if (negative)
        limit = (unsigned long)INT_MAX + 1UL;
    else
        limit = (unsigned long)INT_MAX;

    if (left_magnitude != 0UL && right_magnitude > limit / left_magnitude)
        return 0;

    product = left_magnitude * right_magnitude;
    if (negative) {
        if (product == limit)
            *result = INT_MIN;
        else
            *result = -(int)product;
    } else {
        *result = (int)product;
    }

    return 1;
}

static int apply_operator(int left, int right, char op, int *result) {
    int valid;

    valid = 0;
    switch (op) {
    case '+':
        if (right > 0 && left > INT_MAX - right)
            break;
        if (right < 0 && left < INT_MIN - right)
            break;
        *result = left + right;
        valid = 1;
        break;
    case '-':
        if (right < 0 && left > INT_MAX + right)
            break;
        if (right > 0 && left < INT_MIN + right)
            break;
        *result = left - right;
        valid = 1;
        break;
    case '*':
        valid = checked_multiply(left, right, result);
        break;
    case '/':
        if (right == 0 || (left == INT_MIN && right == -1))
            break;
        *result = left / right;
        valid = 1;
        break;
    case '%':
        if (right == 0 || (left == INT_MIN && right == -1))
            break;
        *result = left % right;
        valid = 1;
        break;
    default:
        break;
    }

    return valid;
}

static void print_usage(const char *program) {
    if (program == NULL)
        program = "duckcalc";
    fprintf(stderr, "usage: %s <left> <operator> <right>\n", program);
}

int main(int argc, char *argv[]) {
    int left;
    int right;
    int result;
    char op;

    if (argc != 4) {
        print_usage(argv[0]);
        return 1;
    }

    if (!parse_integer(argv[1], &left) || !parse_integer(argv[3], &right)) {
        fprintf(stderr, "invalid integer\n");
        return 1;
    }

    if (argv[2] == NULL || argv[2][0] == '\0' || argv[2][1] != '\0' ||
        !is_operator(argv[2][0])) {
        fprintf(stderr, "operator must be one of: + - * / %%\n");
        return 1;
    }

    op = argv[2][0];
    if ((op == '/' || op == '%') && right == 0) {
        fprintf(stderr, "division by zero\n");
        return 1;
    }

    if (!apply_operator(left, right, op, &result)) {
        fprintf(stderr, "result out of range\n");
        return 1;
    }

    printf("ans = %d\n", result);
    return 0;
}