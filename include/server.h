//
// Created by shanhai on 2020/4/13.
//

#ifndef CPPREDIS_SERVER_H
#define CPPREDIS_SERVER_H

// 用枚举代替宏
/* 错误代码 */
typedef enum {
    REDIS_OK = 0,
    REDIS_ERR = -1
} REDIS_STATE;

/* 静态服务配置 */
#define CONFIG_DEFAULT_HZ  10//每秒钟 执行后台人物的频率，例如清除过期key
#define CONFIG_MIN_HZ    1
#define CONFIG_MAX_HZ    500
#define CONFIG_DEFAULT_SERVER_PORT    6379   //默认端口
#define CONFIG_DEFAULT_TCP_BACKLOG    511//

#define CONFIG_DEFAULT_CLIENT_TIMEOUT    0
#define CONFIG_DEFAULT_DB_NUM    16//默认数据库分片数量
#define CONFIG_MAX_LINE    1024 //TODO ??
#define CRON_DBS_PER_CALL    16 //TODO ?
#define NET_MAX_WRITES_PER_EVENT    1024*64//TODO 每个事件最大写 缓冲？
#define PROTO_SHARED_SELECT_CMDS    10// TODO ?
#define OBJ_SHARED_INTEGERS    10000 //todo ?
#define OBJ_SHARED_BULKHDR_LEN    32 //todo
#define LOG_MAX_LEN    1024,//默认系统日志的最大长度

#define AOF_REWRITE_PERC    100 //todo
#define AOF_REWRITE_MIN_SIZE    64*1024*1024
#define AOF_REWRITE_ITEMS_PER_CMD    64
#define CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN    10000
#define CONFIG_DEFAULT_SLOWLOG_MAX_LEN    128
#define CONFIG_DEFAULT_MAX_CLIENTS    10000
#define CONFIG_AUTHPASS_MAX_LEN    512
#define CONFIG_DEFAULT_SLAVE_PRIORITY    100    //todo 默认从节点的优先
#define CONFIG_DEFAULT_REPL_TIMEOUT    60
#define CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD    10
#define CONFIG_RUN_ID_SIZE    40
#define RDB_EOF_MARK_SIZE    40
#define CONFIG_DEFAULT_REPL_BACKLOG_SIZE    1024*1024    // 1mb
#define CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT    60*60    // 1h
#define CONFIG_REPL_BACKLOG_MIN_SIZE    1024*16    //16kb
#define CONFIG_BGSAVE_RETRY_DELAY    5     //5 seconds
#define CONFIG_DEFAULT_PID_FILE      "/var/run/redis.pid"
#define CONFIG_SYSLOG_IDENT     "redis"
#define CONFIG_DEFAULT_CLUSTER_CONFIG_FILE  "nodes.conf"

#define CONFIG_DEFAULT_DAEMONIZE    0
#define CONFIG_DEFAULT_UNIX_SOCKET_PERM    0
#define CONFIG_DEFAULT_TCP_KEEPALIVE    300
#define CONFIG_DEFAULT_PROTECTED_MODE    1
#define CONFIG_DEFAULT_LOGFILE      ""
#define CONFIG_DEFAULT_SYSLOG_ENABLED       0
#define CONFIG_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR  1
#define CONFIG_DEFAULT_RDB_COMPRESSION      1
#define CONFIG_DEFAULT_RDB_CHECKSUM         1
#define CONFIG_DEFAULT_RDB_FILENAME         "dump.rdb"
#define CONFIG_DEFAULT_REPL_DISKLESS_SYNC   0
#define CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY 5
#define CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA   1
#define CONFIG_DEFAULT_SLAVE_READ_ONLY          1
#define CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP    NULL
#define CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT  0
#define CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY 0
#define CONFIG_DEFAULT_MAXMEMORY    0
#define CONFIG_DEFAULT_MAXMEMORY_SAMPLES    0
#define CONFIG_DEFAULT_AOF_FILENAME "appendonly.aof"    /* 追加写，可以保持比较高的性能 */
#define CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE  0   /* aof首先写入缓冲区，然后根据FSYNC配置策略刷入磁盘（always/per sec/no） */
#define CONFIG_DEFAULT_AOF_LOAD_TRUNCATED   1
#define CONFIG_DEFAULT_ACTIVE_REHASHING     1
#define CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC    1
#define CONFIG_DEFAULT_MIN_SLAVES_TO_WTITE  0
#define CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG   10
#define NET_IP_STR_LEN      46  /* IPV4地址长度为16个字节，这里46是支持IPV6的长度 */
#define NET_PEER_ID_LEN     (NET_IP_STR_LEN+32)        /* ip+port*/
#define CONFIG_BINDADDR_MAX     16
#define CONFIG_MIN_RESERVED_FDS     32
#define CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD    0
#define ACTIVE_EXPIRE_CYCLE_LOOKUPS_PER_LOOP    20  /* 每个循环中，lookup的次数*/
#define ACTIVE_EXPIRE_CYCLE_FAST_DURATION       1000    //毫秒
#define ACTIVE_EXPIRE_CYCLE_SLOW_TIME_PERC      25
#define ACTIVE_EXPIRE_CYCLE_SLOW                0
#define ACTIVE_EXPIRE_CYCLE_FAST                1

// todo 指标跟踪
#define STATS_METRIC_SAMPLES                    16
#define STATS_METRIC_COMMAND                    0
#define STATS_METRIC_NET_INPUT                  1
#define STATS_METRIC_NET_OUTPUT                 2
#define STATS_METRIC_COUNT                      3

// 协议/IO相关定义
#define PROTO_MAX_QUERYBUF_LEN                  (1024*1024*1024)  /* 1GM最大队列缓冲*/
#define PROTO_IOBUF_LEN                         (1024*16) /* 常规的IO缓冲大小*/
#define PROTO_REPLY_CHUNK_BYTES                 (16*1024) /* IO写缓冲*/
//TODO 缓存行 读？  内联读？
#define PROTO_INLINE_MAX_SIZE               (1024*64)
#define PROTO_MBULK_BIG_ARG                 (1024*32)
//todo 为什么是21？一个long占4字节，32位
#define LONG_STR_SIZE                           21  /* long->str 所需字节数（+'\0'） */
#define AOF_AUTOSYNC_BYTES                      (1024*1024*32)  /* 每32MB同步刷入磁盘*/

/**
 * 配置eventloop所能挂载的事件（或称文件描述符）数量， = 服务的最大客户端数量+预定文件描述符数量
 * 预定FDs默认为32，todo 为什么要补到128
 */
#define CONFIG_FDSET_INCR                       (CONFIG_MIN_RESERVED_FDS+96)
#define HASHTABLE_MIN_FILL                      10


/**
 * 命令标记，全部采用十进制为2的幂的数字
 */
#define CMD_WRITE           1
#define CMD_READONLY        2
#define CMD_DENYOOM         4
#define CMD_NOT_USED_1      8
#define CMD_ADMIN           16
#define CMD_PUBSUB          32
#define CMD_NOSCRIPT        64
#define CMD_RANDOM          128
#define CMD_SORT_FOR_SCRIPT 256
#define CMD_LOADING         512
#define CMD_STALE           1024
#define CMD_SKIP_MONITOR    2048
#define CMD_ASKING          4096
#define CMD_FAST            8192

/**
 * 对象类型
 */
typedef enum {
    OBJ_STRING = 0,
    OBJ_LIST = 1,
    OBJ_SET = 2,
    OBJ_ZSET = 3,
    OBJ_HASH = 4,
}OBJ_TYPE;

/* 对象编码，关于不同数据类型的安全编码问题， */
typedef enum{
    OBJ_ENCODING_RAW = 0,//原始类型
    OBJ_ENCODING_INT = 1,
    OBJ_ENCODING_HT = 2,
    OBJ_ENCODING_ZIPMAP = 3,
    OBJ_ENCODING_LINKEDLIST = 4,
    OBJ_ENCODING_ZIPLIST = 5,
    OBJ_ENCODING_INTSET = 6,
    OBJ_ENCODING_SKIPLIST = 7,
    OBJ_ENCODING_EMBSTR =   8,
    OBJ_ENCODING_QUICKLIST = 9

}OBJ_TYPE_ENCODING;
/**
 * 2MSB-----the Most Significant 2 Bits of the first byte
 * 00|00 0000:2MSB==00，则该数据为该字节的后6位
 * 01|00 0000 00000000: 2MSB==01，代表该数据为16位，即后6位+1个8位完整字节
 * 10|00 0000:【32位整数】2MSB==10，后面跟一个32位的整数
 * 11|00 0000: 后面跟随特殊编码的对象。后6位为特殊对象的编码，于RDB_ENC_* 定义
 */
#define RDB_6BITLEN         0
#define RDB_14BITLEN        1
#define RDB_32BITLEN        2
#define RDB_ENCVAL          3
#define RDB_LENERR          UINT_MAX

/** 当一个字符串对象保存到磁盘时，如果前两位bit被置位，
 * 代表该字符串对象需要特殊处理，通过
 */
#define RDB_ENC_INT         0   //8位有符号int
#define RDB_ENC_INT16       1   //16位。。。
#define RDB_ENC_INT32       2   //32位。。。
#define RDB_ENC_LZF         3   // 使用FASTLZ压缩的string

/* AOF states */
#define AOF_OFF             0
#define AOF_ON              1
#define AOF_WAIT_REWRITE    3 /* 等待重写？？*/

/*  客户端标识*/
#define CLIENT_SLAVE        (1<<0)  /* 客户端是一个从服务器*/
#define CLIENT_MASTER       (1<<1)  /* 客户端是一个主服务器*/
#define CLIENT_MONITOR      (1<<2)  /* 客户端是一个从服务器的监视器*/
#define CLIENT_MULTI        (1<<3)  /* 混合模式*/
#define CLIENT_BLOCKED      (1<<4)  /* 处于一个阻塞操作的等待阶段*/
#define CLIENT_DIRTY_CAS    (1<<5)  /* key被修改了，cas操作失败*/
#define CLIENT_CLOSE_AFTER_REPLY    (1<<6) /* 复写，完成后自动关闭*/
#define CLIENT_UNBLOCKED    (1<<7)  /* 非阻塞的，保存于服务端的非阻塞客户端中*/
#define CLIENT_LUA          (1<<8)  /* 使用lua的，非连接的客户端*/
#define CLIENT_ASKING       (1<<9)  /* 正在发布询问命令*/
#define CLIENT_CLOSE_ASAP   (1<<10)  /* 尽快关闭客户端*/
#define CLIENT_UNIX_SOCKET  (1<<11) /* 客户端通过Unix socket 连接*/
#define CLIENT_DIRTY_EXEC   (1<<12) /* EXEC操作将会失败*/
#define CLIENT_MASTER_FORCE_REPLY   (1<<13) /* 即便是master也要排队应答*/
#define CLIENT_FORCE_AOF    (1<<14) /* 强制当前命令的AOF传播？*/
#define CLIENT_FORCE_REPL   (1<<15) /* 强制复制当前命令*/
#define CLIENT_PRE_PSYNC    (1<<16) /* ？？*/
#define CLIENT_READONLY     (1<<17) /* 集群客户端处于只读状态*/
#define CLIENT_PUBSUB       (1<<18) /* 客户端处于发布/订阅模式*/
#define CLIENT_PREVENT_AOF_PROP (1<<19) /* 不传播到AOF*/
#define CLIENT_PREVENT_REPL_PROP    (1<<20) /* 不传播到从节点*/
#define CLIENT_PREVENT_PRO  (CLIENT_PREVENT_AOF_PROP|CLIENT_PREVENT_REPL_PROP)
#define CLIENT_PENDING_WRITE    (1<<21)
#define CLIENT_REPLY_OFF        (1<<22) /* 不发送答复到客户端*/
#define CLIENT_REPLY_SKIP_NEXT  (1<<23) /* 为客户端下一个命令设置跳过答复*/
#define CLIENT_REPLY_SKIP       (1<<24) /* 不发送该答复*/
#define CLIENT_LUA_DEBUG        (1<<25) /* 在DEBUG模式下执行lua脚本*/
#define CLIENT_LUA_DEBUG_SYNC   (1<<26) /* 同步执行，不使用fork()*/

/**客户端阻塞类型（btype 字段）
 * 如果客户端的阻塞标识位被置位
 */
#define BLOCKED_NONE            0   /* 非阻塞模式，标识位未置位*/
#define BLOCKED_LIST            1   /* BLPOP & co ？？*/
#define BLOCKED_WAIT            2   /* 等待同步拷贝*/

/**客户端请求类型
 */
#define PROTO_REQ_INLINE        1   /* inline协议（老协议）请求*/
#define PROTO_REQ_MULTIBULK     2   /* multibulk协议查询*/

/** 客户端限制种类
 */
#define CLIENT_TYPE_NORMAL      0   /* 常规请求-应答 + 监视器*/
#define CLIENT_TYPE_SLAVE       1   /* 从节点*/
#define CLIENT_TYPE_PUBSUB      2   /* 客户端订阅到 发布/订阅 频道*/
#define CLIENT_TYPE_MASTER      3   /* 主节点*/
#define CLIENT_TYPE_OBUF_COUNT  3   /* 要暴露到输出缓冲配置的客户端数量。进前三种 0/1/2*/

/** 从节点拷贝状态，为从节点配置server.repl_state 来记忆将要做的事
 */
#define REPL_STATE_NONE         0   /* 没有活跃的拷贝*/
#define REPL_STATE_CONNECT      1   /* 必须连接到主节点*/
#define REPL_STATE_CONNECTING    2   /* 正在连接到主节点*/


/**
 * 这里需要了解主从模式的相关信息
 * replication模式是主从模式下的、从节点拷贝主节点数据的模式。
 * 关于replication的相关信息只需要从节点配置，如从节点需要配置主节点的ip+端口
 *
 */
/* 握手状态， 必须有序   */
#define REPL_STATE_RECEIVE_PONG     3   /* 发送PING，等待PONG的答复*/
#define REPL_STATE_SEND_AUTH        4   /* 发送Auth信息到主节点（如果master开启了权限验证的话）*/
#define REPL_STATE_RECEIVE_AUTH     5   /* 等待主节点的auth的答复*/
#define REPL_STATE_SEND_PORT        6   /* 发送拷贝配置 监听端口*/
#define REPL_STATE_RECEIVE_PORT     7   /* 等待拷贝配置答复*/
#define REPL_STATE_SEND_IP          8   /* 发送拷贝配置的ip地址*/
#define REPL_STATE_RECEIVE_IP       9   /* 等待接受拷贝配置的ip地址*/
#define REPL_STATE_SEND_CAPA        10  /* 等待拷贝配置验证*/
#define REPL_STATE_RECEIVE_CAPA     11  /* 等待拷贝配置应答*/
/** 扩展 PSYNC命令，全量：PSYNC ？ -1
 *  增量： PSYNC runid offset */
#define REPL_STATE_SEND_PSYNC       12  /* 发送PSYNC同步命令，支持全量同步（从节点初次同步）、增量同步（从节点短线重连，靠offset定位命令的偏移量）*/
#define REPL_STATE_RECEIVE_PSYNC    13  /* 等待PSYNC应答*/
/* 握手结束*/

/**从节点的状态
 *
 */
#define SLAVE_STATE_WAIT_BGSAVE_START   6   /* 需创建一个新的rdb文件*/
#define SLAVE_STATE_WAIT_BGSAVE_END     7   /* 等待rdb文件创建完成*/
#define SLAVE_STATE_SEND_BULK           8   /* 发送rdb文件到从节点*/
#define SLAVE_STATE_ONLINE              9   /* RDB文件传输已完成，正在发送更新*/

/**从节点的能力 */
#define SLAVE_CAPA_NONE             0
#define SLAVE_CAPA_EOF              (1<<0) /* 可以解析RDB文件流的结束符号*/

/** 同步读超时--从节点一侧 todo 时间单位？//*/
#define CONFIG_REPL_SYNCIO_TIMEOUT      5

/* List 相关配置*/
#define LIST_HEAD       0
#define LIST_TAIL       1
/** Sort操作*/
#define SORT_OP_GET     0
/** Log等级*/
#define LL_DEBUG        0
#define LL_VERBOSE      1
#define LL_NOTICE       2
#define LL_WARNING      3
#define LL_RAW          (1<<10)
#define CONFIG_DEFAULT_VERBOSITY    LL_NOTICE

/** 监管选项*/
#define SUPERVISION_NONE    0
#define SUPERVISION_AUTODETECT  1
#define SUPERVISION_SYSTEMD     2
#define SUPERVISION_UPSTART     3

/** 反警告宏？？*/
#define UNUSED(V)   ((void) V)

#define ZSKIPLIST_MAXLEVEL      32  //跳表的层级最大32级
#define ZSKIPLIST_P             0.25

/* AOF的定义*/
#define AOF_FSYNC_NO        0   /* 默认关闭*/
#define AOF_FSYNC_ALWAYS    1   /* 每个写命令都刷到aof文件，可用性最高，性能也最差*/
#define AOF_FSYNC_EVERYSEC  2   /* 每秒将缓冲数据刷一次disk, 默认该选项*/
#define CONFIG_DEFAULT_AOF_FSYNC AOF_FSYNC_EVERYSEC

/** Zip-List 压缩列表结构相关定义*/
#define OBJ_HASH_MAX_ZIPLIST_ENTRIES        512
#define OBJ_HASH_MAX_ZIPLIST_VAUE           64
#define OBJ_SET_MAX_INTSET_ENTRIES          512
#define OBJ_ZSET_MAX_ZIPLIST_ENTRIES        128
#define OBJ_ZSET_MAX_ZIPLIST_VALUE          64


/** List 默认配置*/
#define OBJ_LIST_MAX_ZIPLIST_SIZE       -2
#define OBJ_LIST_COMPRESS_DEPTH         0

/** HyperLogLog （一种高性能的去重统计的算法）*/
#define CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES     3000

/** Sets 集合操作码*/
#define SET_OP_UNION        0
#define SET_OP_DIFF         1
#define SET_OP_INTER        2

/** 内存策略*/
#define MAXMEMORY_VOLATILE_LRU      0
#define MAXMEMORY_VOLATILE_TTL      1
#define MAXMEMORY_VOLATILE_RANDOM   2
#define MAXMEMORY_ALLKEYS_LRU       3
#define MAXMEMORY_ALLKEYS_RANDOM    4
#define MAXMEMORY_NO_EVICTION       5
#define CONFIG_DEFAULT_MAXMEMORY_POLICY MAXMEMORY_NO_EVICTION

/** 脚本*/
#define LUA_SCRIPT_TIME_LIMIT       5000 //毫秒

/** 测试*/
#define UNIT_SECONDS            0
#define UNIT_MILLISECONDS       1

/** 关机标志符*/
#define SHUTDOWN_NOFLAGS        0
#define SHUTDOWN_SAVE           1   /* 在关闭时强制保存（阻塞save），即使没有设置保存点*/
#define SHUTDOWN_NOSAVE         2

#define CMD_CALL_NONE           0
#define CMD_CALL_SLOWLOG        (1<<0)
#define CMD_CALL_STATS          (1<<1)
#define CMD_CALL_PROPAGATE_AOF  (1<<2)
#define CMD_CALL_PROPAGATE_REPL (1<<3)
#define CMD_CALL_PROPAGATE      (CMD_CALL_PROPAGTE_AOF|CMD_CALL_PROPAGATE_REPL)

/** 命令传播标识符，查看propagate() 函数*/
#define PROPAGATE_NONE          0
#define PROPAGATE_AOF           1
#define PROPAGATE_REPL          2

/** RDB 活跃子节点保存类型？*/
#define RDB_CHILD_TYPE_NONE     0
#define RDB_CHILD_TYPE_DISK     1   /* RDB写入磁盘*/
#define RDB_CHILD_TYPE_SOCKET   2   /* RDB通过socket写入（传输）从节点*/


/** Key空间 变化 通知类型，每个分类都和一个用来配置的字符相关*/
#define NOTIFY_KEYSPACE         (1<<0)  /* K */
#define NOTIFY_KEYEVENT         (1<<1)  /* E */
#define NOTIFY_GENERIC          (1<<2)  /* g */
#define NOTIFY_STRING           (1<<3)  /* $ */
#define NOTIFY_LIST             (1<<4)  /* l */
#define NOTIFY_SET              (1<<5)  /* s */
#define NOTIFY_HASH             (1<<6)  /* h */
#define NOTIFY_ZSET             (1<<7)  /* z */
#define NOTIFY_EXPIRED          (1<<8)  /* x */
#define NOTIFY_EVICTED          (1<<9)  /* e */
#define NOTIFY_ALL         (NOTIFY_GENERIC | NOTIFY_STRING | NOTIFY_LIST | NOTIFY_SET | NOTIFY_HASH | NOTIFY_ZSET | NOTIFY_EXPIRED | NOTIFY_EVICTED)  /*  */

/** 获取首个绑定的地址或NULL*/
#define NET_FIRST_BIND_ADDR     (server.bindaddr_count ? server.bindaddr[0] : NULL)

/** 使用如下宏，可以在serverCron() 中运行代码
 */
#define run_with_period(_ms_) if ((_ms_ <= 1000/server.hz) || !(server.cronloops%((_ms_)/(1000/server.hz))))

/** 打印异常栈的assert宏*/
#define serverAssertWithInfo(_c,_o,_e)((_e)?(void)0:(_serverAssertWithInfo(_c,_o,#_e,__FILE__,__LINE__),_exit(1)))
#define serverAssert(_e) ((_e)?(void)0:(_serverAssert(#_e,__FILE__,__LINE__),_exist(1)))
#define serverPanic(_e) _serverPanic(#_e, __FILE__,__LINE__),_exit(1)

/** 日期类型
 * 一个redis Object类型，可以存放string/list/set*/
#define LRU_BITS    24
#define LRU_CLOCK_MAX       ((1<<LRU_BITS)-1)
#define LRU_CLOCK_RESOLUTION    1000
typedef struct redisObject {
    unsigned type:4;
    unsigned encoding:4;
    unsigned lru:LRU_BITS;  /* lru 时间（相对于server.lruclock）*/
    int refcount;//引用计数
    void* ptr;// todo 谁的指针？
} robj;

/** 宏， 用来获得当前LRU clock的宏
 *  如果当前方案比我们刷新时钟的频率低，返回预先计算的值，否则需要采用系统调用
 */
#define LRU_CLOCK()     ((1000/server.hz <= LRU_CLOCK_RESOLUTION) ? server.lruclock: getLRUClock())

/** 用来初始化一个在栈上分配的Redis Object的宏
 * 注意，这个宏在靠近结构体定义的地方被使用，以确保
 * 我们将会更新它，当结构体改变时。从而避免bug的产生
 */
#define initStaticStringObject(_var, _ptr) do { \
    _var.refcoun = 1;\
    _var.type = OBJ_STRING;\
    _var.encoding = OBJ_ENCODING_RAW; \
    _var.ptr = _ptr;\
}while(0)

/** 为了提升LRU近似值的质量？我们使用keys的集合，通过调用freeMemoryIfNeeded() 作为驱逐者的候选人*/









#endif //CPPREDIS_SERVER_H
