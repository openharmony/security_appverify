/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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

#include "util/hap_profile_verify_utils.h"

#include "common/hap_verify_log.h"
#include "init/matching_result.h"
#include "init/trusted_source_manager.h"
#include "util/hap_cert_verify_openssl_utils.h"
#include "util/hap_signing_block_utils.h"
#include "util/hap_verify_openssl_utils.h"

namespace OHOS {
namespace Security {
namespace Verify {
bool HapProfileVerifyUtils::ParseProfile(Pkcs7Context& profilePkcs7Context, const Pkcs7Context& hapPkcs7Context,
    const HapByteBuffer& pkcs7ProfileBlock, std::string& profile)
{
    if (hapPkcs7Context.matchResult.matchState == MATCH_WITH_SIGN &&
        hapPkcs7Context.matchResult.source == APP_GALLARY) {
        profile = std::string(pkcs7ProfileBlock.GetBufferPtr(), pkcs7ProfileBlock.GetCapacity());
        HAPVERIFY_LOG_DEBUG("hap include unsigned provision");
        return true;
    }
    const unsigned char* pkcs7Block = reinterpret_cast<const unsigned char*>(pkcs7ProfileBlock.GetBufferPtr());
    uint32_t pkcs7Len = static_cast<unsigned int>(pkcs7ProfileBlock.GetCapacity());
    if (!HapVerifyOpensslUtils::ParsePkcs7Package(pkcs7Block, pkcs7Len, profilePkcs7Context)) {
        HAPVERIFY_LOG_ERROR("parse pkcs7 failed");
        return false;
    }

    profile = std::string(profilePkcs7Context.content.GetBufferPtr(), profilePkcs7Context.content.GetCapacity());
    return true;
}

bool HapProfileVerifyUtils::VerifyProfile(Pkcs7Context& pkcs7Context)
{
    if (!HapVerifyOpensslUtils::GetCertChains(pkcs7Context.p7, pkcs7Context)) {
        HAPVERIFY_LOG_ERROR("GetCertChains from pkcs7 failed");
        return false;
    }

    if (!HapVerifyOpensslUtils::VerifyPkcs7(pkcs7Context)) {
        HAPVERIFY_LOG_ERROR("verify profile signature failed");
        return false;
    }

    std::string certSubject;
    std::string certIssuer;
    if (!HapCertVerifyOpensslUtils::GetSubjectFromX509(pkcs7Context.certChains[0][0], certSubject) ||
        !HapCertVerifyOpensslUtils::GetIssuerFromX509(pkcs7Context.certChains[0][0], certIssuer)) {
        HAPVERIFY_LOG_ERROR("Get info of sign cert failed");
        return false;
    }

    TrustedSourceManager& trustedSourceManager = TrustedSourceManager::GetInstance();
    pkcs7Context.matchResult = trustedSourceManager.IsTrustedSource(certSubject, certIssuer, PROFILE_BLOB,
        pkcs7Context.certChains[0].size());
    if (pkcs7Context.matchResult.matchState == DO_NOT_MATCH) {
        HAPVERIFY_LOG_ERROR("profile signature is not trusted source, subject: %{private}s, issuer: %{public}s",
            certSubject.c_str(), certIssuer.c_str());
        return false;
    }
    HAPVERIFY_LOG_DEBUG("profile subject: %{private}s, issuer: %{public}s",
        certSubject.c_str(), certIssuer.c_str());
    return true;
}
} // namespace Verify
} // namespace Security
} // namespace OHOS
