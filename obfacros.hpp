// written in C++14 by garzon

#include <unordered_map>
#include <string>
#include <iostream>
#include <queue>
#include <stack>

// a marker for useless(obfuscating) code, w. or w/o. code inside will not affect the logic
#define _USELESS_CODE(...) __VA_ARGS__
// #define _USELESS_CODE(...)

_USELESS_CODE(
	constexpr uint64_t myXorConst = 0x78abda5f;
	constexpr uint64_t myOffsetConst = 0x57419f8e;

	template<uint64_t n>
	struct ConstInt {
		static constexpr uint64_t encoder() {
			constexpr uint64_t i = n + myOffsetConst;
			return i ^ myXorConst;
		}
		static constexpr uint64_t encoded = encoder();
	};

	inline uint64_t ConstInt_decoder(const uint64_t n) {
		return (n^myXorConst)-myOffsetConst;
	}
)

#define _OBF_CONST(c) _USELESS_CODE(ConstInt_decoder) ( _USELESS_CODE(ConstInt<) c _USELESS_CODE(>::encoded) )

#define _GOTO_EXECUTE_FSM _USELESS_CODE(if (!__is_executing)) goto *__goto_labels[__exec_fsm_id]
#define _GOTO_BLOCK(id) __next_state_id.push(id); _GOTO_EXECUTE_FSM
#define _STATE(id) st_ ## id
#define _FUNCTION_START(dummy, id, retVal) { auto &__retVal = (retVal); std::stack<uint64_t> __next_state_id; uint64_t __else_block = 0, __is_executing = dummy & 0, __exec_fsm_id; std::unordered_map<uint64_t, void *> __goto_labels; void *__nxt_ptr; constexpr uint64_t __fsm_entry_id = id; __goto_labels[id] = &&_STATE(id); if (__is_executing) { _STATE(id):
#define FUNCTION_START(retVal)    _FUNCTION_START(__COUNTER__, __COUNTER__, retVal)
#define _FUNCTION_END(id, id2) goto *__goto_labels[0]; } __exec_fsm_id = id; __goto_labels[id]=&&_STATE(id); __goto_labels[0]=&&_STATE(id2); goto *__goto_labels[__fsm_entry_id]; _STATE(id): __nxt_ptr = __goto_labels[__next_state_id.top()]; __next_state_id.pop(); goto *__nxt_ptr; _STATE(id2):; }
#define FUNCTION_END      _FUNCTION_END(__COUNTER__, __COUNTER__)
#define RETURN(...)       __retVal = (__VA_ARGS__); goto *__goto_labels[0]
#define _MAKE_BLOCK_WITH_OID(oid, id, id2, ...) _GOTO_BLOCK(id2); } __goto_labels[oid] = &&_STATE(id); __goto_labels[_OBF_CONST(id2)] = &&_STATE(id2); if (__is_executing) { _STATE(id): __VA_ARGS__; } if (__is_executing) { _STATE(id2): 
#define _MAKE_BLOCK(id, id2, ...) _MAKE_BLOCK_WITH_OID(id, id, id2, __VA_ARGS__)
#define _BLOCK_WITH_NAME(id, name, ...) _GOTO_BLOCK(id); } __goto_labels[_OBF_CONST(id)] = &&_STATE(name); if (__is_executing) { _STATE(name): __VA_ARGS__;
#define _BLOCK(id, ...) _BLOCK_WITH_NAME(id, id, __VA_ARGS__)
#define BLOCK(...) _BLOCK(__COUNTER__, __VA_ARGS__)
//#define BLOCK_WITH_NAME(name, ...) _BLOCK_WITH_NAME(__COUNTER__, name, __VA_ARGS__) BLOCK();
#define MAKE_BLOCK_WITH_NAME(name, ...) _MAKE_BLOCK_WITH_OID(__COUNTER__, name, __COUNTER__, __VA_ARGS__; _GOTO_EXECUTE_FSM)
#define _INCLUDE_BLOCK(name, id1) __next_state_id.push(id1); goto name; _BLOCK_WITH_NAME(id1, id1, )
#define INCLUDE_BLOCK(name) _INCLUDE_BLOCK(_STATE(name), __COUNTER__)
//#define INCLUDE_BLOCK_POINTER(block_ptr) _INCLUDE_BLOCK(*(block_ptr), __COUNTER__)
#define GET_BLOCK_POINTER(name) (&&_STATE(name))

#define _IF(expr, id, id2, id3, id4, ...) _MAKE_BLOCK(id, id2, __VA_ARGS__; _GOTO_BLOCK(id3)) _GOTO_BLOCK(id4); _MAKE_BLOCK(id4, id3, uint64_t __tmp = id3; if (expr) { __tmp -= 2; static_assert(id3 - 2 == id, "IF block id not match"); } _GOTO_BLOCK(__tmp))
#define IF(expr, ...) _IF(expr, __COUNTER__, __COUNTER__, __COUNTER__, __COUNTER__, __VA_ARGS__)
	
#define _WHILE(expr, id, id2, id3, id4, ...) _MAKE_BLOCK(id, id2, __VA_ARGS__; _GOTO_BLOCK(id3)) _GOTO_BLOCK(id3); _MAKE_BLOCK(id3, id4, uint64_t __tmp = id4; if (expr) { __tmp -= 3; static_assert(id4 - 3 == id, "WHILE block id not match"); } _GOTO_BLOCK(__tmp))
#define WHILE(expr, ...) _WHILE(expr, __COUNTER__, __COUNTER__, __COUNTER__, __COUNTER__, __VA_ARGS__)
#define FOR(init, cond, end, ...) BLOCK(init); _WHILE(cond, __COUNTER__, __COUNTER__, __COUNTER__, __COUNTER__, __VA_ARGS__; end)

#define _IF_ELSE(expr, id, id2, id3, id4, id5, ...) _MAKE_BLOCK(id, id2, __VA_ARGS__; _GOTO_BLOCK(id3)) _GOTO_BLOCK(id4); _MAKE_BLOCK(id4, id3, uint64_t __tmp = id5; if (expr) { __tmp -= 4; } static_assert(id5 - 4 == id, "IF_ELSE block id not match"); _GOTO_BLOCK(__tmp); _USELESS_CODE(__else_block+=2;) } _USELESS_CODE(else) { __else_block = id5 )
#define IF_ELSE(expr, ...) _IF_ELSE(expr, __COUNTER__, __COUNTER__, __COUNTER__, __COUNTER__, __COUNTER__, __VA_ARGS__)

#define _ELSE(id5__STATE_id_str, id6, ...) _MAKE_BLOCK_WITH_OID(__else_block, id5__STATE_id_str, id6, __VA_ARGS__; _GOTO_BLOCK(id6))
#define ELSE(...) _ELSE(__COUNTER__, __COUNTER__, __VA_ARGS__)

#define ELIF(expr, ...) ELSE(IF(expr, __VA_ARGS__))
#define _ELIF_ELSE(expr, id, id2, id3, ...) _MAKE_BLOCK_WITH_OID(__else_block, id, id2, IF_ELSE(expr, __VA_ARGS__; _GOTO_BLOCK(id2)) ELSE (_GOTO_BLOCK(id3)); _USELESS_CODE(__else_block++;) } _USELESS_CODE(else) { __else_block = id3 )
#define ELIF_ELSE(expr, ...) _ELIF_ELSE(expr, __COUNTER__, __COUNTER__, __COUNTER__, __VA_ARGS__)

// magic ends ----------------------------------------