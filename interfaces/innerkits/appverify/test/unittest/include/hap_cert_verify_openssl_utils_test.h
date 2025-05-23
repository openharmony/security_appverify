/*
 * Copyright (C) 2021-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HAP_CERT_VERIFY_OPENSSL_UTILS_TEST_H
#define HAP_CERT_VERIFY_OPENSSL_UTILS_TEST_H

#include <cstdint>
#include <string>

#include "common/hap_byte_buffer.h"

#include "test_const.h"

namespace OHOS {
namespace Security {
namespace Verify {
bool Base64StringDecode(const std::string& base64String, HapByteBuffer& output);
}
}
}
int32_t GetCertInfo001(void);
int32_t CertVerify001(void);
int32_t Base64NotUrlSafeCertTest001(void);
int32_t GetX509CrlFromDerBufferTest001(void);
int32_t GetCertsChainTest001(void);
int32_t GetIssuerAndSubjectTest001(void);
int32_t GetSerialNumberFromX509Test001(void);
int32_t VerifyCertChainPeriodOfValidityTest001(void);
int32_t VerifyCrlTest001(void);
int32_t CompareX509CertTest001(void);
int32_t WriteX509CrlToStreamTest001(void);
int32_t PrivateFuncInvalidInputTest001(void);
int32_t GetPublickeyBase64Test001(void);
int32_t GetOrganizationFromPemCertTest001(void);
#endif // HAP_CERT_VERIFY_OPENSSL_UTILS_TEST_H
