#ifndef _WHCBOR_TYPES_H
#define _WHCBOR_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "cn-cbor/cn-cbor.h""
#include "cbor.h"

typedef struct _whcbor_map_t {
    cn_cbor *command;
    cn_cbor *subcommand;
}whcbor_map_t;


typedef struct _whcbor_connect_t  {
    struct _whcbor_map_t    head;
    cn_cbor                 *pair;  /**< Command and Response pair */
}whcbor_connect_t;

typedef enum _e_whcbor_cmd {
    WHCBOR_CMD_SCP                      = 0x01,     /**< Secure Connection Protocol command */
    WHCBOR_CMD_BIO                                  /**< Secure Biometric command */
}e_whcbor_cmd;

typedef enum _e_whcbor_scp_subcmd {
    WHCBOR_SCP_SUBCMD_CONNECT           = 0x01,
    WHCBOR_SCP_SUBCMD_RECONNECT
}e_whcbor_scp_subcmd;

typedef enum _e_whcbor_bio_subcmd {
    WHCBOR_BIO_SUBCMD_ENROLLBEGIN       = 0x01,
    WHCBOR_BIO_SUBCMD_ENROLLCOMMIT,
    WHCBOR_BIO_SUBCMD_IDENTIFY
}e_whcbor_bio_subcmd;



// Error define
#define WHCBOR_RET_DONE                     false
#define WHCBOR_RET_FAIL                     -true

#endif

