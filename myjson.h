#ifndef MYJSON_H_
#define MYJSON_H_

typedef enum
{
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JOSN_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

typedef struct
{
    JsonType type;
    double number;
} JsonValue;

enum
{
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR,
    JSON_PARSE_NUMBER_TOO_BIG
};

int JsonParse(JsonValue *jv, const char *json);

JsonType JsonGetType(const JsonValue *jv);

double JsonGetNumber(const JsonValue *jv);

#endif