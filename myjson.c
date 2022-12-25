#include "myjson.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h> /* errno, ERANGE */
#include <math.h>  /* HUGE_VAL */

#define EXPECT(c, ch)               \
    do                              \
    {                               \
        assert((*c->json) == (ch)); \
        c->json++;                  \
    } while (0)

#define JSON_PARSE_LEN 8

#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')

typedef struct
{
    const char *json;
} JsonContext;

static int CheckDoubleNumber(const char *num)
{
    if (*num == '-')
        ++num;

    if (!ISDIGIT(*num))
        return JSON_PARSE_INVALID_VALUE;

    if (*num == '0')
        ++num;
    else
    {
        while (ISDIGIT(*num))
        {
            ++num;
        }
    }

    if (*num == '\0')
        return JSON_PARSE_OK;

    if (*num == '.')
    {
        ++num;
        if (!ISDIGIT(*num))
            return JSON_PARSE_INVALID_VALUE;
        while (ISDIGIT(*num))
        {
            ++num;
        }
        if (*num == '\0')
            return JSON_PARSE_OK;
    }

    if (*num != 'e' && *num != 'E')
        return JSON_PARSE_INVALID_VALUE;

    ++num;
    if (*num != '-' && *num != '+' && !ISDIGIT(*num))
        return JSON_PARSE_INVALID_VALUE;

    if (*num == '-' || *num == '+')
        ++num;

    if (!ISDIGIT(*num))
        return JSON_PARSE_INVALID_VALUE;

    while (ISDIGIT(*num))
    {
        ++num;
    }

    if (*num != '\0')
        return JSON_PARSE_ROOT_NOT_SINGULAR;
    return JSON_PARSE_OK;
}

static void JsonParseWhitespace(JsonContext *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\n' || *p == '\t' || *p == '\r')
        ++p;
    c->json = p;
}

static int JsonParseRootSingluar(JsonContext *c, JsonValue *jv)
{
    JsonParseWhitespace(c);
    if (*c->json != '\0')
    {
        jv->type = JSON_NULL;
        return JSON_PARSE_ROOT_NOT_SINGULAR;
    }
    return JSON_PARSE_OK;
}

static int JsonParseLiteral(JsonContext *c, JsonValue *jv, const char *text)
{
    int textLen = strlen(text);
    for (int i = 0; i < textLen; ++i)
    {
        if (c->json[i] == '\0' || c->json[i] != text[i])
        {
            return JSON_PARSE_INVALID_VALUE;
        }
    }
    c->json += textLen;

    const char *resultCondicates[JSON_PARSE_LEN] = {"null", "false", "true"};
    for (int i = 0; i < (sizeof(resultCondicates) / sizeof(resultCondicates[0])); ++i)
    {
        if (strcmp(resultCondicates[i], text) == 0)
        {
            jv->type = (JsonType)i;
            break;
        }
    }
    return JsonParseRootSingluar(c, jv);
}

static int JsonParseNumber(JsonContext *c, JsonValue *jv)
{
    int ret = CheckDoubleNumber(c->json);
    if (ret != JSON_PARSE_OK)
        return ret;

    errno = 0;
    jv->number = strtod(c->json, NULL);
    if (errno == ERANGE && (jv->number == HUGE_VAL || jv->number == -HUGE_VAL))
        return JSON_PARSE_NUMBER_TOO_BIG;

    jv->type = JSON_NUMBER;
    return JSON_PARSE_OK;
}

static int JsonParseValue(JsonContext *c, JsonValue *jv)
{
    int ret = JSON_PARSE_INVALID_VALUE;
    switch (*c->json)
    {
    case 'n':
        ret = JsonParseLiteral(c, jv, "null");
        break;
    case 't':
        ret = JsonParseLiteral(c, jv, "true");
        break;
    case 'f':
        ret = JsonParseLiteral(c, jv, "false");
        break;
    case '\0':
        ret = JSON_PARSE_EXPECT_VALUE;
        break;
    default:
        ret = JsonParseNumber(c, jv);
        break;
    }

    return ret;
}

int JsonParse(JsonValue *jv, const char *json)
{
    assert(jv != NULL);
    JsonContext c;
    c.json = json;
    jv->type = JSON_NULL;
    JsonParseWhitespace(&c);
    return JsonParseValue(&c, jv);
}

JsonType JsonGetType(const JsonValue *jv)
{
    assert(jv != NULL);
    return jv->type;
}

double JsonGetNumber(const JsonValue *jv)
{
    assert(jv != NULL && jv->type == JSON_NUMBER);
    return jv->number;
}
