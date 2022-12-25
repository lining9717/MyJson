#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myjson.h"

static int g_MainRet = 0;
static int g_TestCount = 0;
static int g_TestPassed = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                                                          \
    do                                                                                                            \
    {                                                                                                             \
        g_TestCount++;                                                                                            \
        if (equality)                                                                                             \
            g_TestPassed++;                                                                                       \
        else                                                                                                      \
        {                                                                                                         \
            fprintf(stderr, "%s:%d: expect: " format " actual:" format "\n", __FILE__, __LINE__, expect, actual); \
            g_MainRet = 1;                                                                                        \
        }                                                                                                         \
    } while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect == actual), expect, actual, "%.17g")

#define TEST_ERROR(error, json)                     \
    do                                              \
    {                                               \
        JsonValue jv;                               \
        jv.type = JSON_FALSE;                       \
        EXPECT_EQ_INT(error, JsonParse(&jv, json)); \
        EXPECT_EQ_INT(JSON_NULL, JsonGetType(&jv)); \
    } while (0);

#define TEST_NUMBER(expect, json)                           \
    do                                                      \
    {                                                       \
        JsonValue jv;                                       \
        EXPECT_EQ_INT(JSON_PARSE_OK, JsonParse(&jv, json)); \
        EXPECT_EQ_INT(JSON_NUMBER, JsonGetType(&jv));       \
        EXPECT_EQ_DOUBLE(expect, JsonGetNumber(&jv));       \
    } while (0)

static void TestParseNull()
{
    JsonValue jv;
    jv.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_OK, JsonParse(&jv, "null"));
    EXPECT_EQ_INT(JSON_NULL, JsonGetType(&jv));
}

static void TestParseFalse()
{
    JsonValue jv;
    jv.type = JSON_TRUE;
    EXPECT_EQ_INT(JSON_PARSE_OK, JsonParse(&jv, "false"));
    EXPECT_EQ_INT(JSON_FALSE, JsonGetType(&jv));
}

static void TestParseTrue()
{
    JsonValue jv;
    jv.type = JSON_FALSE;
    EXPECT_EQ_INT(JSON_PARSE_OK, JsonParse(&jv, "true"));
    EXPECT_EQ_INT(JSON_TRUE, JsonGetType(&jv));
}

static void TestParseExpectValue()
{
    TEST_ERROR(JSON_PARSE_EXPECT_VALUE, "");
    TEST_ERROR(JSON_PARSE_EXPECT_VALUE, " ");
}

static void TestParseInvalidValue()
{
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "nul");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "?");

    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "+0");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "+1");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "INF");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "inf");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "NAN");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "nan");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "e");
    TEST_ERROR(JSON_PARSE_INVALID_VALUE, "E");
}

static void TestParseRootNotSingular()
{
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "null          x");
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "truesad");
}

static void TestParseNumber()
{
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    TEST_NUMBER(0.0, "1e-10000"); /* must underflow */
}

static void TestParse()
{
    TestParseNull();
    TestParseFalse();
    TestParseTrue();
    TestParseExpectValue();
    TestParseInvalidValue();
    TestParseRootNotSingular();
    TestParseNumber();
}

int main(int argc, char const *argv[])
{
    TestParse();
    printf("%d/%d (%3.2f%%) passed\n", g_TestPassed, g_TestCount, g_TestPassed * 100.0 / g_TestCount);
    return g_MainRet;
}
