//
// Created by shanhai on 2020/4/13.
//

#ifndef CPPREDIS_SERVER_H
#define CPPREDIS_SERVER_H

// 尝试用枚举代替宏
/* 错误代码 */
typedef enum {
    REDIS_OK = 0,
    REDIS_ERR = -1
} REDIS_STATE;

/* 静态服务配置 */
typedef enum {
    REDIS_SERVER_PORT = 6379,   //默认端口
    REDIS_MAX_IDLE_TIME = 60 * 5,//最大闲置时间
    REDIS_IO_BUF_LEN  = 1024,//IO缓冲大小
    REDIS_LOAD_BUF_LEN = 1024,//读缓冲大小
    REDIS_STATIC_ARGS = 8,//TODO ？？
    REDIS_DEFAULT_DB_NUM = 16,//默认数据库分片数量
    REDIS_CONFIG_LINE_MAX = 1024, //TODO ??
    REDIS_MAX_SYNC_TIME = 60,//TODO 单位是什么？
    REDIS_EXPIRE_LOOKUPS_PER_CRON = 10,//TODO 每查看10次过期一次？
    REDIS_MAX_WRITE_PER_EVENT = 1024*64,//TODO 每个事件最大写 缓冲？
    REDIS_REQUEST_MAX_SIZE = 1024*1024*256,//最大字节数量
    REDIS_SHARED_INTEGERS = 10000,
    REDIS_REPLY_CHUNK_BYTES = 5*1500,//5（TODO 官方注释是tcp packet，但这不准确，packet是IP层的）*（1500， 1个MTU的大小，MTU---以太网数据帧的数据部分Payload的大小），单位字节
    REDIS_MAX_LOG_MSG_LEN = 1024,
    REDIS_SLOWLOG_LOG_SLOWER_THAN = 10000,//  TODO SLOWLOG 是什么？
    REDIS_SLOWLOG_MAX_LEN = 64
} REDIS_SERVER_CONFIG;

//Hash table 参数 TODO 最小容量   ？？
#define REDIS_HT_MINFILL    10

/**
 * 命令
 */
//TODO 拒绝oom？
#define REDIS_CMD_DENYOOM   4
//TODO 强制复制吗？
#define REDIS_CMD_FORCE_REPLICATION 8

/**
 * 对象类型
 */
typedef enum {
    REDIS_STRING = 0,
    REDIS_LIST = 1,
    REDIS_SET = 2,
    REDIS_ZSET = 3,
    REDIS_HASH = 4,
    REDIS_VMPOINTER = 8
}REDIS_TYPE;

/* 对象编码，关于不同数据类型的安全编码问题， */
typedef enum{
    REDIS_ENCODING_RAW = 0,
    REDIS_ENCODING_INT = 1,
    REDIS_ENCODING_HT = 2,
    REDIS_ENCODING_ZIPMAP = 3,
    REDIS_ENCODING_LINKEDLIST = 4,
    REDIS_ENCODING_ZIPLIST = 5,
    REDIS_ENCODING_INTSET = 6,
    REDIS_ENCODING_SKIPLIST = 7,
}REDIS_TYPE_ENCODING;

/* TODO 对象类型仅仅用来dump到物理磁盘??*/
#define REDIS_EXPIRETIME    253
#define REDIS_SELECTDB      254
#define REDIS_EOF           255










#endif //CPPREDIS_SERVER_H
