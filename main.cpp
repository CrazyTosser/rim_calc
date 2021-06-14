#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <climits>

int64_t rimToArab(std::string str) {
    if (str == "Z") return 0;
    int64_t res = 0;
    char cnt;
    bool d = false, l = false, v = false;
    size_t i = 0;
    while (str[i] == 'M') {
        res += 1000;
        i++;
    }
    if (str[i] == 'D') {
        d = true;
        res += 500;
        i++;
    }
    if (str[i] == 'C') {
        if (str[i + 1] == 'M') {
            res += 900;
            i += 2;
        } else if (str[i + 1] == 'D') {
            if (d) return -1;
            res += 400;
            i += 2;
        } else {
            res += 100;
            i++;
            for (cnt = 1; str[i] == 'C'; i++) {
                res += 100;
                cnt++;
            }
            if (cnt > 3) return -1;
        }
    }
    if (str[i] == 'L') {
        l = true;
        res += 50;
        i++;
    }
    if (str[i] == 'X') {
        if (str[i + 1] == 'C') {
            res += 90;
            i += 2;
        } else if (str[i + 1] == 'L') {
            if (l) return -1;
            res += 40;
            i += 2;
        } else if (str[i + 1] == 'V') {
            v = true;
            res += 15;
            i += 2;
        } else {
            res += 10;
            i++;
            for (cnt = 1; str[i] == 'X'; i++) {
                res += 10;
                cnt++;
            }
            if (cnt > 3) return -1;
        }
    }
    if (str[i] == 'V') {
        if (v) return -1;
        res += 5;
        v = true;
        i++;
    }
    if (str[i] == 'I') {
        if (str[i + 1] == 'X') {
            res += 9;
            i += 2;
        } else if (str[i + 1] == 'V') {
            if (v) return -1;
            res += 4;
            i += 2;
        } else {
            res++;
            i++;
            for (cnt = 1; str[i] == 'I'; i++) {
                res++;
                cnt++;
            }
            if (cnt > 3) return -1;
        }
    }
    if (str[i] != '\0') return -1;
    return res;
}

void printRim(int64_t num) {
    if (num == 0)
        std::cout << "Z" << std::endl;
    else {
        long long cnt = num / 1000;
        for (; cnt > 0; cnt--) {
            num -= 1000;
            std::cout << 'M';
        }
        if (num / 900 == 1) {
            num -= 900;
            std::cout << 'C';
            std::cout << 'M';
        }
        if (num / 500 == 1) {
            num -= 500;
            std::cout << 'D';
        }
        if (num / 400 == 1) {
            num -= 400;
            std::cout << 'C';
            std::cout << 'D';
        }
        for (cnt = num / 100; cnt > 0; cnt--) {
            num -= 100;
            std::cout << 'C';
        }
        if (num / 90 == 1) {
            num -= 90;
            std::cout << 'X';
            std::cout << 'C';
        }
        if (num / 50 == 1) {
            num -= 50;
            std::cout << 'L';
        }
        if (num / 40 == 1) {
            num -= 40;
            std::cout << 'X';
            std::cout << 'L';
        }
        for (cnt = num / 10; cnt > 0; cnt--) {
            num -= 10;
            std::cout << 'X';
        }
        if (num / 9 == 1) {
            num -= 9;
            std::cout << 'I';
            std::cout << 'X';
        }
        if (num / 5 == 1) {
            num -= 5;
            std::cout << 'V';
        }
        if (num / 4 == 1) {
            num -= 4;
            std::cout << 'I';
            std::cout << 'X';
        }
        for (; num > 0; num--) {
            std::cout << 'I';
        }
        std::cout << std::endl;
    }
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool is_rim(char c) {
    return c == 'I' || c == 'V' || c == 'X' || c == 'L' || c == 'C' || c == 'D' || c == 'M' || c == 'Z';
}

int priority(char op) {
    if (op < 0)
        return 4; // op == -'+' || op == -'-'
    return
            op == '+' || op == '-' ? 1 :
            op == '*' || op == '/' ? 2 :
            -1;
}

int process_op(std::vector<int64_t> &st, char op) {
    if (op < 0) {
        int l = st.back();
        st.pop_back();
        switch (-op) {
            case '+':
                st.push_back(l);
                break;
            case '-':
                st.push_back(-l);
                break;
        }
    } else {
        int64_t r = st.back();
        st.pop_back();
        int64_t l = st.back();
        st.pop_back();
        switch (op) {
            case '+':
                if ((r > 0) && l > (std::numeric_limits<int64_t>::max() - r) ||
                    (r < 0) && l < (std::numeric_limits<int64_t>::min() - r))
                    return 3;
                else
                    st.push_back(l + r);
                break;
            case '-':
                if ((r > 0 && l < std::numeric_limits<int64_t>::min() + r) ||
                    (r < 0 && l > std::numeric_limits<int64_t>::max() + r))
                    return 3;
                else
                    st.push_back(l - r);
                break;
            case '*':
                if (l > 0 ? r > 0 ? l > (std::numeric_limits<int64_t>::max() / r) : r <
                                                                                    (std::numeric_limits<int64_t>::min() /
                                                                                     l) : r > 0 ? l <
                                                                                                  (std::numeric_limits<int64_t>::min() /
                                                                                                   r) : (l != 0) && (r <
                                                                                                                     (std::numeric_limits<int64_t>::max() /
                                                                                                                      l))) {
                    return 3;
                }
                st.push_back(l * r);
                break;
            case '/':
                if (r == 0) return 2;
                if ((l == std::numeric_limits<int64_t>::min()) && (r == -1)) {
                    return 3;
                }
                st.push_back(l / r);
                break;
        }
    }
    return 0;
}

int calc(std::string &s, int64_t *res) {
    bool may_unary = true;
    std::vector<int64_t> st;
    std::vector<char> op;
    for (size_t i = 0; i < s.length(); ++i)
        if ((s[i]) != ' ')
            if (s[i] == '(') {
                op.push_back('(');
                may_unary = true;
            } else {
                if (s[i] == ')') {
                    while (op.back() != '(') {
                        int tmp = process_op(st, op.back());
                        if (tmp != 0) return tmp;
                        op.pop_back();
                    }
                    op.pop_back();
                    may_unary = false;
                } else if (is_op(s[i])) {
                    char curop = s[i];
                    if (may_unary && curop == '-') curop = -curop;
                    while (!op.empty() && priority(op.back()) >= priority(curop)) {
                        int tmp = process_op(st, op.back());
                        if (tmp != 0) return tmp;
                        op.pop_back();
                    }
                    op.push_back(curop);
                    may_unary = true;
                } else {
                    std::string operand;
                    while (i < s.length() && isalnum(s[i]))
                        operand += s[i++];
                    --i;
                    if (is_rim(operand[0]))
                        st.push_back(rimToArab(operand));
                    else
                        return 1;
                    may_unary = false;
                };
            }
    while (!op.empty())
        process_op(st, op.back()), op.pop_back();
    *res = st.back();
    return 0;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
    std::string expr;
    while (true) {
        int64_t res;
        getline(std::cin, expr);
        switch (calc(expr, &res)) {
            case 0:
                printRim(res);
                break;
            case 1:
                std::cout << "error: wrong input";
                break;
            case 2:
                std::cout << "error: zero division";
                break;
            case 3:
                std::cout << "error: overflow detected";
                break;
        }
    }
}

#pragma clang diagnostic pop
