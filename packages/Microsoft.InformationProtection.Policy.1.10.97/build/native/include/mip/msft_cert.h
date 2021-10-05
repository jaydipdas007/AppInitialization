/*
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief Exposes MSFT SSL public cert
 * 
 * @file msft_cert.h
 */

#ifndef API_MIP_MSFT_CERT_H_
#define API_MIP_MSFT_CERT_H_

#include <string>
#include <vector>

#include "mip/mip_export.h"
#include "mip/mip_namespace.h"

MIP_NAMESPACE_BEGIN

/**
 * @brief Get PEM-encoded MSFT cert used by RMS service
 * 
 * @return PEM-encoded MSFT cert
 * 
 * @note The RMS service currently uses a cert that is not globally trusted by default on all platforms. If an
 *       application overrides HttpDelegate for protection operations on a non-Windows platform, that HttpDelegate
 *       must treat this as a trusted cert during SSL authentication. The RMS service may eventually migrate to an
 *       existing MSFT cert that is already trusted by default on all platforms, so it equally important to not expect
 *       the server cert to be pinned to any particular cert.
 */
MIP_API const std::string& __CDECL GetMsftCertPEM();

/**
 * @brief Get binary MSFT cert used by RMS service
 * 
 * @return Binary MSFT cert
 * 
 * @note The RMS service currently uses a cert that is not globally trusted by default on all platforms. If an
 *       application overrides HttpDelegate for protection operations on a non-Windows platform, that HttpDelegate
 *       must treat this as a trusted cert during SSL authentication. The RMS service may eventually migrate to an
 *       existing MSFT cert that is already trusted by default on all platforms, so it equally important to not expect
 *       the server cert to be pinned to any particular cert.
 */
MIP_API const std::vector<uint8_t>& __CDECL GetMsftCert();

MIP_NAMESPACE_END

#endif // API_MIP_MSFT_CERT_H_
