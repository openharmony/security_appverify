/*
 * Copyright (c) 2020-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SECURITY_APP_VERIFY_H
#define SECURITY_APP_VERIFY_H

#include <stdint.h>

#include "mbedtls/pk.h"
#include "app_centraldirectory.h"
#include "app_provision.h"
#include "app_verify_pub.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define HW_SH_VERSION_LEN  4
#define HW_SH_RESERVE_LEN  4

#define CONTENT_VERSION_LEN 4

#define SHA256_SIZE (256 / 8)

#define SHA384_SIZE (384 / 8)

#define SHA512_SIZE (512 / 8)

#define BUF_LEN  1024

#define BUF_1M (1024 * 1024)

#define MAX_PROFILE_SIZE  (1024 * 1024)

#define MAX_BLOCK_NUM  (1024)

#define NORMAL_HASH_SIZE 32

#define MAX_KEY_PAIR_SIZE 4096

#define MAX_PK_BUF (MBEDTLS_MPI_MAX_SIZE * 2 + 20)

/* BlockHead->type */
typedef enum {
    SIGNATURE_BLOCK_TYPE = 0x20000000,
    KEY_ROTATION_BLOCK_TYPE = 0x20000001,
    PROFILE_BLOCK_WITHSIGN_TYPE = 0x20000002,
    PROPERTY_BLOCK_TYPE = 0x20000003,
} BockType;

/* contentinfo tag */
typedef enum {
    DEFAULT_TAG = 0,
    HASH_TAG,                   /* total file */
    HASH_ROOT_1M_TAG = 0x80,
    HASH_ROOT_512K_TAG,
    HASH_ROOT_256K_TAG,
    HASH_ROOT_128K_TAG,
    HASH_ROOT_64K_TAG,
    HASH_ROOT_32K_TAG,
    HASH_ROOT_16K_TAG,
    HASH_ROOT_8K_TAG,
    HASH_ROOT_4K_TAG,
} SignBlockTag;

/* block head */
typedef struct {
    uint32_t type;
    uint32_t length;
    uint32_t offset;
} BlockHead;

/* sign content */
typedef struct {
    int32_t version;  /* version */
    int32_t blockNum;
    int32_t size;
    int32_t algId;
    int32_t length;
    char hash[NORMAL_HASH_SIZE];
} ContentInfo;

#define CERT_MAX_NAME_LEN 512
#define CERT_TYPE_APPGALLARY  0
#define CERT_TYPE_SYETEM      1
#define CERT_TYPE_OTHER       2
#define CERT_MAX_DEPTH        3

/* trusted app list */
typedef struct {
    int32_t  maxCertPath;
    char *name;
    char *appSignCert;
    char *profileSignCert;
    char *profileDebugSignCert;
    char *issueCA;
} TrustAppCert;

typedef struct {
    int32_t issuerLen;
    char *issuer;
    int32_t subjectLen;
    char *subject;
    mbedtls_pk_type_t pkType;
    int32_t pkLen;
    char *pkBuf;
} CertInfo;

int32_t GetAppid(ProfileProf *profile);
int32_t CalculateHash(const unsigned char *input, int32_t len, int32_t hashAlg, unsigned char *output);
int32_t GetHashUnitLen(int32_t hashAlg);
char *GetSignBlockByType(
    const SignatureInfo *signInfo, int32_t fp, int32_t blockType, int32_t *len, BlockHead *blockHead);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
