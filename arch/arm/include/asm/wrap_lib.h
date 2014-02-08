#ifndef ASM_WRAP_LIB_H
#define ASM_WRAP_LIB_H

/*
 * the wrapper assembly adds 13 registers to the stack which will be
 * reported by the unwind/backtrace functions
 */
#define WRAPPER_STACK_SZ (13 * 4)

#define REG_LR_IDX 12

#endif
