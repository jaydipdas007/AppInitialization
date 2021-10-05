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
 * @brief Flighting feature definition
 * 
 * @file flighting_feature_cc.h
 */

#ifndef API_MIP_FLIGHTING_FEATURE_CC_H_
#define API_MIP_FLIGHTING_FEATURE_CC_H_

/**
* @brief Defines new features by name
*/
typedef enum {
  MIP_FLIGHTING_FEATURE_SERVICE_DISCOVERY = 0,         /**< Rely on separate HTTP call to determine RMS service endpoints (default false)*/
  MIP_FLIGHTING_FEATURE_AUTH_INFO_CACHE = 1,           /**< Cache OAuth2 challenges per domain/tenant to reduce unnecessary 401 responses. Disable for apps/services that manage their own HTTP auth (default true) */
  MIP_FLIGHTING_FEATURE_LINUX_ENCRYPTED_CACHE = 2,     /**< Enable encrypted caching for Linux platforms (default false) */
  MIP_FLIGHTING_FEATURE_SINGLE_DOMAIN_NAME = 3,        /**< Enable single company name for dns lookup (e.g. https://corprights) */
  MIP_FLIGHTING_FEATURE_POLICY_AUTH = 4,               /**< Enable automatic HTTP authentication for requests sent to Policy service. Disable for apps/services that manage their own HTTP auth (default true) */
  MIP_FLIGHTING_FEATURE_URL_REDIRECT_CACHE = 5,        /**< Cache URL redirects to reduce number of HTTP operations */
  MIP_FLIGHTING_FEATURE_PRE_LICENSE = 6,               /**< Enable pre license api check */
  MIP_FLIGHTING_FEATURE_DOUBLE_KEY_PROTECTION = 7,     /**< Enable double key protection feature to use a customer key to encrypt with */
  MIP_FLIGHTING_FEATURE_VARIABLE_POLICY_TTL = 8,       /**< Enable variable policy ttl in storage */
  MIP_FLIGHTING_FEATURE_VARIABLE_TEXT_MARKING = 9,     /**< Enable variable text marking */
  MIP_FLIGHTING_FEATURE_OPTIMIZE_PDF_MEMORY = 10,      /**< Enable Optimize PDF Memory Creator in protect and unprotect PDF files */
  MIP_FLIGHTING_FEATURE_REMOVE_DELETED_LABEL_MD = 11,  /**< Enable removing delete label's meta data */
  MIP_FLIGHTING_FEATURE_ENFORCE_TLS12 = 12,            /**< Enforce TLS 1.2 for non-ADRMS HTTPS connections */
} mip_cc_flighting_feature;

#endif  // API_MIP_FLIGHTING_FEATURE_CC_H_