/*
 SPDX-License-Identifier: AGPL-3.0-or-later

 Copyright (C) 2025 - 2026 emexlab

 This file is part of Nyxian.

 Nyxian is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Nyxian is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Affero General Public License for more details.

 You should have received a copy of the GNU Affero General Public License
 along with Nyxian. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef NXBOOTSTRAP_H
#define NXBOOTSTRAP_H

#import <Foundation/Foundation.h>

#define NXBOOTSTRAP_NEWEST_VERSION  25
#define NXBOOTSTRAP_CSTEP           (double)(1.0 / NXBOOTSTRAP_NEWEST_VERSION)

/*
 * MARK: bundled SDK knobs
 *
 * everything about the SDK we ship lives here. bumping emexDE to a
 * newer iOS SDK should only mean touching this block plus
 * NXBOOTSTRAP_NEWEST_VERSION above (so already bootstrapped installs
 * re-download the SDK instead of keeping the stale one around).
 *
 * NXSDK_VERSION           the marketing version of the SDK we ship.
 * NXSDK_NAME              the on disk SDK bundle name, apple style.
 * NXSDK_ARCHIVE_URL       where the SDK bundle gets pulled from.
 * NXSDK_TARGET_TRIPLE     triple used when there is no project to ask,
 *                         i.e. the read only editor. per project builds
 *                         build their own triple from the projects
 *                         deployment target instead.
 * NXSDK_COMPAT_VERSIONS   older SDK versions we keep symlinks around for
 *                         so projects and caches that recorded an older
 *                         sysroot path keep resolving.
 *
 * TODO: iPhoneOS27.0.sdk.zip is not hosted yet, the bootstrap will fail
 *       its download step until it is uploaded to nyxian.app/bootstrap.
 */
#define NXSDK_VERSION               @"27.0"
#define NXSDK_NAME                  (@"iPhoneOS" NXSDK_VERSION @".sdk")
#define NXSDK_ARCHIVE_URL           (@"https://nyxian.app/bootstrap/" @"iPhoneOS" NXSDK_VERSION @".sdk" @".zip")
#define NXSDK_TARGET_TRIPLE         (@"apple-arm64-ios" NXSDK_VERSION)
#define NXSDK_COMPAT_VERSIONS       (@[@"26.2", @"26.4", @"26.4.1", @"26.5"])

@interface NXBootstrap : NSObject

/*
 * NXSDK_VERSION exposed to swift, macros dont cross the bridge.
 */
@property (class, nonatomic, readonly, strong, nonnull) NSString *sdkVersion;

@property (nonatomic, readonly, strong, nonnull) NSURL *rootURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *sdkURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *includeURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *projectsURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *cacheURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *bootstrapPlistURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *swiftURL;
@property (nonatomic, readonly, strong, nonnull) NSURL *swiftModuleCacheURL;

@property (atomic, readonly) UInt64 version;
@property (atomic, readonly) BOOL isInstalled;

- (instancetype _Nonnull)init;
+ (instancetype _Nonnull)shared;

- (void)bootstrap;

- (NSString  * _Nullable)relativeToBootstrapWithAbsolutePath:( NSString  * _Nonnull)path;
- (void)clearURL:(NSURL * _Nonnull)url;

- (void)waitTillDone;
- (BOOL)isNewest;

@end

#endif /* NXBOOTSTRAP_H */
