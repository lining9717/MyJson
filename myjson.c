#include "myjson.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define EXPECT(c, ch)               \
    do                              \
    {                               \
        assert((*c->json) == (ch)); \
        c->json++;                  \
    } while (0)

#define JSON_PARSE_LEN 8

typedef struct
{
    const char *json;
} JsonContext;

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

static int JsonPareValue(JsonContext *c, JsonValue *jv)
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
    return JsonPareValue(&c, jv);
}

JsonType JsonGetType(const JsonValue *jv)
{
    assert(jv != NULL);
    return jv->type;
}
