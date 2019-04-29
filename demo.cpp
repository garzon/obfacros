#include "obfacros.hpp"

// test for IF/IF_ELSE
size_t test_case_1(int a, int b) { 
	size_t ret = 0;
	FUNCTION_START(ret)
		#define SET_RET_FLAG(bit) ret |= (1 << bit)
		IF_ELSE(b == 1,
			SET_RET_FLAG(1);
		) ELSE (
			SET_RET_FLAG(2);
			IF(a == 1, SET_RET_FLAG(3));
			SET_RET_FLAG(4);
		);
		SET_RET_FLAG(0);
		#undef SET_RET_FLAG
	FUNCTION_END;
	return ret;
}

// test for BLOCK && WHILE
std::string test_case_2(int a) { 
	std::string ret;
	int b;
	FUNCTION_START(ret)
		WHILE(a > 0,
			BLOCK(b = 0);
			WHILE(b < a,
				BLOCK(ret += '*');
				BLOCK(b++);
			);
			BLOCK(ret += '\n');
			BLOCK(a--);
		);
	FUNCTION_END;
	return ret;
}

// test for FOR(BLOCK and _WHILE used)
std::string test_case_3(int a) { 
	std::string ret;
	int b;
	FUNCTION_START(ret)
		FOR(, a > 0, a--,
			FOR(b = 0, b < a, b++,
				IF_ELSE(a%2, ret += '*')
				ELSE(ret += '#');
			);
			ret += '\n';
		);
	FUNCTION_END;
	return ret;
}

std::string test_case_prime_numbers(int n) { 
	std::string ret = "2 ";
	int c, count, i = 3;
	FUNCTION_START(ret)
		FOR(count = 2, count <= n, ,
			FOR(c = 2, c <= i - 1, c++,
				IF(i%c == 0, goto for_break);
			);
for_break:
			IF(c == i,
				BLOCK(ret += std::to_string(i));
				BLOCK(ret += ' ');
				BLOCK(count++);
			);
			i++;
		);
	FUNCTION_END;
	return ret;
}

int main() {
	std::cout << test_case_1(0, 0) << " = " << 21 << std::endl;
	std::cout << test_case_1(0, 1) << " = " << 3 << std::endl;
	std::cout << test_case_1(1, 0) << " = " << 29 << std::endl;
	std::cout << test_case_1(1, 1) << " = " << 3 << std::endl;
	std::cout << test_case_2(5) << std::endl;
	std::cout << test_case_3(5) << std::endl;
	std::cout << test_case_prime_numbers(10) << std::endl;
}