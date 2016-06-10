#include "config.h"

#define CONFIG_ERR "<libco:config:error> "

/* 
* libco.config
* '#' is comment which will be ingored.
* each line has the format:
*   key_str=value_str
*/ 


/* 
* config parser function
* Return -1 if failed, otherwise return 0.
*/ 
typedef int (*cfg_fn)(char *val_str);

struct cfg_parser {
    cfg_fn fn;
    char *key_str;
};

/* 
* log subsys related 
*/
int config_log_enable = 1;
char *config_log_file = "libco.log";
int config_log_level = 1;
int config_log_delete = 0;


enum cfg_index {
    CFG_LOG_LEVEL = 0,
    CFG_LOG_FILE,
};

static int set_log_file(char *val_str)
{
    config_log_file = val_str;
    return 0;
}

static int set_log_level(char *val_str)
{

    return 0;   
}

static struct cfg_parser parsers {
    {set_log_file, "log_file"},
    {set_log_level, "log_level"}
};

#define KEY_VALUE_LEN 32
static char key[KEY_VALUE_LEN];
static char value[KEY_VALUE_LEN];

static inline is_special(char ch)
{
    return (ch==' ' || ch=='=');
}

static int strim_special_head(char *str)
{
    int idx = 0;
    
    while (is_special(str[idx]))
        ++idx;

    return idx;
}

static int strim_blanck_head(char *str)
{
    int idx = 0;
    
    while (str[idx] == ' ')
        ++idx;

    return idx;
}

static int validate_line(char *str)
{
    int nr_equal = 0;
    
    while (*str) {
        if (*str++ == '=')
            ++nr_equal;
    }

    return (nr_equal==1 ? 0 : -1);
}

static int decode_string(char *line)
{
    int i, idx;

    if (-1 == validate_line(line)) {
        printf(CONFIG_ERR"%s syntax wrong:\n\t%s\n",
                __func__, line);
        return -1;
    }    

    i = strim_special_head(line);

    for (idx=0; line[i]; ++idx, ++i) {
        if (is_special(line[i])) {
            key[idx] = 0;
            if (line[i] == ' ')
                i += strim_blanck_head(line+i);
            break;
        }

        key[idx] = line[i];
    }

    if (line[i++] != '=') {
        printf(CONFIG_ERR"%s syntax wrong:\n\t%s\n",
                __func__, line);
        return -1;
    }

    strim_blanck_head(line+i);
    // TODO



    return 0;
}





