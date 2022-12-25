#include "myjson.h"
#include <stdlib.h>
#include <assert.h>

#define EXPECT(c, ch)               \
    do                              \
    {                               \
        assert((*c->json) == (ch)); \
        c->json++;                  \
    } while (0)

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

static int JsonParseNull(JsonContext *c, JsonValue *jv)
{
    EXPECT(c, 'n');
    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return JSON_PARSE_INVALID_VALUE;
    c->json += 3;
    jv->type = JSON_NULL;
    return JsonParseRootSingluar(c, jv);
}

static int JsonParseTrue(JsonContext *c, JsonValue *jv)
{
    EXPECT(c, 't');
    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e')
        return JSON_PARSE_INVALID_VALUE;
    c->json += 3;
    jv->type = JSON_TRUE;
    return JsonParseRootSingluar(c, jv);
}

static int JsonParseFalse(JsonContext *c, JsonValue *jv)
{
    EXPECT(c, 'f');
    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e')
        return JSON_PARSE_INVALID_VALUE;
    c->json += 4;
    jv->type = JSON_FALSE;
    return JsonParseRootSingluar(c, jv);
}

static int JsonPareValue(JsonContext *c, JsonValue *jv)
{
    int ret = JSON_PARSE_INVALID_VALUE;
    switch (*c->json)
    {
    case 'n':
        ret = JsonParseNull(c, jv);
        break;
    case 't':
        ret = JsonParseTrue(c, jv);
        break;
    case 'f':
        ret = JsonParseFalse(c, jv);
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
