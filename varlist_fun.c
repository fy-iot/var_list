#include <stdio.h>
#include <stdarg.h>



typedef enum 
{
    LOG_LEVEL_ERROR  = 0U,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
}log_info_e;
typedef struct
{   
    log_info_e log_level;  ///< LOG 等级
}log_t;

static log_t  s_logger;
int log_level_set(log_info_e level);
log_info_e log_level_get(void);

#define DEBUG
#ifdef DEBUG
#define LOG_HEAD "[ %s  %s:%d ]  "
#define LOG_W_HEAD "W"LOG_HEAD
#define LOG(fmt, ...) do{\
    printf(LOG_HEAD fmt, __FILE__,__func__, __LINE__,##__VA_ARGS__);}\
    while(0)

#define LOG_W(fmt, ...) do{\
    if(log_level_get() >= LOG_LEVEL_WARNING)\
    printf(LOG_W_HEAD fmt, __FILE__,__func__, __LINE__,##__VA_ARGS__);}\
while(0)


#else
#define LOG(fmt, ...)
#endif



int log_level_set(log_info_e level)
{
    s_logger.log_level = level;
    return 0;
}
log_info_e log_level_get(void)
{
    return s_logger.log_level;
}




int add(int num, ...)
{
    va_list pargs;
    va_start(pargs, num);
    int sum = 0;
    for(int i=num; i>0; i--)
    {
        sum += va_arg(pargs, int);
    }
    va_end(pargs);
    return sum;
}  


int my_snprintf(char *str, int size, const char *fmt, ...)
{
    int len = 0;

    va_list pargs;
    va_start(pargs, fmt);
    
    len = vsnprintf(str, size, fmt, pargs);
    va_end(pargs);
    return len;
}

int  str_parse(const char *req_args,  const char *req_expr, ... )
{
    va_list pargs;
    int req_args_num = 0;

    va_start(pargs, req_expr);
    
    req_args_num  = vsscanf(req_args, req_expr,  pargs);
    va_end(pargs);
    return req_args_num;
}


#define  BUF_SIZE 100
char buf[BUF_SIZE];
int main(void)
{
    int sum = 0;

    sum = add(3, 1, 2, 8);
    printf("sum is %d\n", sum);
    int len = my_snprintf(buf, BUF_SIZE, "this is a test %02d:%02d:%s\n", 1, 2, "hello" );
    printf("%s\n, len is %d\n", buf, len);
    int a, b;

    len = str_parse("+CE_REG:1,2\r\n", "+CE_REG:%d,%d\r\n", &a, &b);
    printf("a = %d, b = %d, len = %d\n", a, b, len);
    LOG("HELLO, WORLD\n");
    LOG_W("1+2 = %d\n", 1+2);
    log_level_set(LOG_LEVEL_INFO);
    LOG_W("1+2 = %d\n", 1+2);

}

