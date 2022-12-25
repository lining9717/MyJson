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

#define TEST_ERROR(error, json)                     \
    do                                              \
    {                                               \
        JsonValue jv;                               \
        jv.type = JSON_FALSE;                       \
        EXPECT_EQ_INT(error, JsonParse(&jv, json)); \
        EXPECT_EQ_INT(JSON_NULL, JsonGetType(&jv)); \
    } while (0);

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
}

static void TestParseRootNotSingular()
{
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "null          x");
    TEST_ERROR(JSON_PARSE_ROOT_NOT_SINGULAR, "truesad");
}

static void TestParse()
{
    TestParseNull();
    TestParseFalse();
    TestParseTrue();
    TestParseExpectValue();
    TestParseInvalidValue();
    TestParseRootNotSingular();
}

int main(int argc, char const *argv[])
{
    TestParse();
    printf("%d/%d (%3.2f%%) passed\n", g_TestPassed, g_TestCount, g_TestPassed * 100.0 / g_TestCount);
    return 0;
}
