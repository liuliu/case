#ifndef _GUARD_case_h_
#define _GUARD_case_h_

#include <stdio.h>
#include <stdint.h>

/* the following 9 lines to generate unique name was taken from Catch: https://github.com/philsquared/Catch
 * here is the licence:
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. */
#ifndef INTERNAL_CATCH_UNIQUE_NAME_LINE2
#define INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line ) name##line
#endif
#ifndef INTERNAL_CATCH_UNIQUE_NAME_LINE
#define INTERNAL_CATCH_UNIQUE_NAME_LINE( name, line ) INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line )
#endif
#ifndef INTERNAL_CATCH_UNIQUE_NAME
#define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __LINE__ )
#endif

typedef void (*case_f)(char*, int*);

typedef struct {
	uint64_t sig_head;
	case_f driver;
	char* name;
	uint64_t sig_tail;
} case_t;

#define TEST_CASE(desc) \
static void __attribute__((used)) INTERNAL_CATCH_UNIQUE_NAME(__test_case_driver__) (char* __case_name__, int* __case_result__); \
static case_t INTERNAL_CATCH_UNIQUE_NAME(__test_case_ctx__) __attribute__((used)) = { .driver = INTERNAL_CATCH_UNIQUE_NAME(__test_case_driver__), .sig_head = 0x883253372849284B, .name = desc, .sig_tail = 0x883253372849284B }; \
static void INTERNAL_CATCH_UNIQUE_NAME(__test_case_driver__) (char* __case_name__, int* __case_result__) 

#define ABORT_CASE (*__case_result__) = -1; return;

#define REQUIRE(a, err, ...) { \
if (!(a)) \
{ \
	printf("\n\t\033[0;31mREQUIRE\033[0;0m: %s:%d: %s is not true, " err, __FILE__, __LINE__, #a, ##__VA_ARGS__); \
	ABORT_CASE; \
} }

#define REQUIRE_EQ(a, b, err, ...) { \
if ((a) != (b)) \
{ \
	printf("\n\t\033[0;31mREQUIRE_EQ\033[0;0m: %s:%d: %s(%lg) != %s(%lg), " err, __FILE__, __LINE__, #a, (double)(a), #b, (double)(b), ##__VA_ARGS__); \
	ABORT_CASE; \
} }

#define REQUIRE_ARRAY_EQ(type, a, b, len, err, ...) { \
int __case_i__; \
for (__case_i__ = 0; __case_i__ < (len); __case_i__++) \
	if (((type*)(a))[__case_i__] != ((type*)(b))[__case_i__]) \
	{ \
		printf("\n\t\033[0;31mREQUIRE_ARRAY_EQ\033[0;0m: %s:%d: %s[%d](%lg) != %s[%d](%lg), " err, __FILE__, __LINE__, #a, __case_i__, (double)((type*)(a))[__case_i__], #b, __case_i__, (double)((type*)(b))[__case_i__], ##__VA_ARGS__); \
		ABORT_CASE; \
	} }

#define REQUIRE_EQ_WITH_TOLERANCE(a, b, t, err, ...) { \
if ((double)((a) - (b)) > (t) || (double)((a) - (b)) < -(t)) \
{ \
	printf("\n\t\033[0;31mREQUIRE_EQ_WITH_TOLERANCE\033[0;0m: %s:%d: %s(%lg) != %s(%lg) | +-%lg, " err, __FILE__, __LINE__, #a, (double)(a), #b, (double)(b), (double)(t), ##__VA_ARGS__); \
	ABORT_CASE; \
} }

#define REQUIRE_ARRAY_EQ_WITH_TOLERANCE(type, a, b, len, t, err, ...) { \
int __case_i__; \
for (__case_i__ = 0; __case_i__ < (len); __case_i__++) \
	if ((double)(((type*)(a))[__case_i__] - ((type*)(b))[__case_i__]) > (t) || (double)(((type*)(a))[__case_i__] - ((type*)(b))[__case_i__]) < -(t)) \
	{ \
		printf("\n\t\033[0;31mREQUIRE_ARRAY_EQ_WITH_TOLERANCE\033[0;0m: %s:%d: %s[%d](%lg) != %s[%d](%lg) | +-%lg, " err, __FILE__, __LINE__, #a, __case_i__, (double)((type*)(a))[__case_i__], #b, __case_i__, (double)((type*)(b))[__case_i__], (double)(t), ##__VA_ARGS__); \
		ABORT_CASE; \
	} }

#define REQUIRE_NOT_EQ(a, b, err, ...) { \
if ((a) == (b)) \
{ \
	printf("\n\t\033[0;31mREQUIRE_NOT_EQ\033[0;0m: %s:%d: %s(%lg) == %s(%lg), " err, __FILE__, __LINE__, #a, (double)(a), #b, (double)(b), ##__VA_ARGS__); \
	ABORT_CASE; \
} }

#define REQUIRE_ARRAY_NOT_EQ(type, a, b, len, err, ...) { \
int __case_i__; \
for (__case_i__ = 0; __case_i__ < (len); __case_i__++) \
	if (((type*)(a))[__case_i__] == ((type*)(b))[__case_i__]) \
	{ \
		printf("\n\t\033[0;31mREQUIRE_ARRAY_NOT_EQ\033[0;0m: %s:%d: %s[%d](%lg) == %s[%d](%lg), " err, __FILE__, __LINE__, #a, __case_i__, (double)((type*)(a))[__case_i__], #b, __case_i__, (double)((type*)(b))[__case_i__], ##__VA_ARGS__); \
		ABORT_CASE; \
	} }

#define REQUIRE_NOT_EQ_WITH_TOLERANCE(a, b, t, err, ...) { \
if ((double)((a) - (b)) <= (t) && (double)((a) - (b)) >= -(t)) \
{ \
	printf("\n\t\033[0;31mREQUIRE_NOT_EQ_WITH_TLERANCE\033[0;0m: %s:%d: %s(%lg) == %s(%lg) | +-%lg, " err, __FILE__, __LINE__, #a, (double)(a), #b, (double)(b), (double)(t), ##__VA_ARGS__); \
	ABORT_CASE; \
} }

#define REQUIRE_ARRAY_NOT_EQ_WITH_TOLERANCE(type, a, b, len, t, err, ...) { \
int __case_i__; \
for (__case_i__ = 0; __case_i__ < (len); __case_i__++) \
	if ((double)(((type*)(a))[__case_i__] - ((type*)(b))[__case_i__]) <= (t) && (double)(((type*)(a))[__case_i__] - ((type*)(b))[__case_i__]) >= -(t)) \
	{ \
		printf("\n\t\033[0;31mREQUIRE_ARRAY_NOT_EQ_WITH_TOLERANCE\033[0;0m: %s:%d: %s[%d](%lg) == %s[%d](%lg) | +-%lg, " err, __FILE__, __LINE__, #a, __case_i__, (double)((type*)(a))[__case_i__], #b, __case_i__, (double)((type*)(b))[__case_i__], (double)(t), ##__VA_ARGS__); \
		ABORT_CASE; \
	} }

#endif
