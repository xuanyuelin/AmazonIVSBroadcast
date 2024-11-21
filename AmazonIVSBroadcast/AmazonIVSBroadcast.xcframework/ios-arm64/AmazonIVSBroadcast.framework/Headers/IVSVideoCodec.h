//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>

NS_ASSUME_NONNULL_BEGIN

/// Constants to identify codec names used by the IVS Broadcast SDK.
typedef NSString *IVSVideoCodecName NS_TYPED_ENUM;

/// "H264", also known as AVC.
IVS_EXPORT IVSVideoCodecName const IVSVideoCodecNameH264 NS_SWIFT_NAME(IVSVideoCodecName.h264);
/// "H265", also known as HEVC.
IVS_EXPORT IVSVideoCodecName const IVSVideoCodecNameH265 NS_SWIFT_NAME(IVSVideoCodecName.h265);

/// A description of the capabilities of an AV device that is usable by the
/// Broadcast SDK.
IVS_EXPORT
@interface IVSVideoCodec : NSObject

IVS_INIT_UNAVAILABLE

/// The codec MIME subtype. Valid types are listed in:
/// https://www.iana.org/assignments/media-types/media-types.xhtml
@property (nonatomic, strong, readonly) IVSVideoCodecName name;

@end

NS_ASSUME_NONNULL_END
