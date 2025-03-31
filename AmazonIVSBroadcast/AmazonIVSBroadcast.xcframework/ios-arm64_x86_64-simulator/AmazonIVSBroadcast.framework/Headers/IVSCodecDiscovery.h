//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>

@class IVSVideoCodec;
@class IVSVideoConfiguration;

NS_ASSUME_NONNULL_BEGIN

IVS_EXPORT
/// A codec result returned by `IVSCodecDiscovery`.
NS_SWIFT_NAME(IVSCodecDiscovery.Result)
@interface IVSCodecDiscoveryResult : NSObject

/// The name of the video codec that this result is related to.
/// This can be matched with `IVSVideoCodecNames`.
@property (nonatomic, readonly) NSString *videoCodecName;

/// The validated `IVSVideoConfiguration` that this codec is known to work with. This may differ
/// from the configuration provided to the `IVSCodecDiscovery` session if there are known compatibility
/// issues, such as lack of B-frame support or limited bitrate/keyframe interval ranges.
/// This will be `nil` if the codec associated with `videoCodecName` is not available for use on this
/// device for the requested channel or configuration.
///
/// - Warning: This configuration object will be locked, meaning attempting to change any properties
///            (except `usesAutoBitrate`, `autoBitrateProfile`, and `enableTransparency`) will result in an error or no-op.
@property (nonatomic, readonly, nullable) IVSVideoConfiguration *configuration;

/// This will be `nil` if `videoCodec` can be used on this device for the requested channel,
/// otherwise this will provide a description of why the `IVSVideoCodec` is not available.
@property (nonatomic, readonly, nullable) NSError *error;

@end

IVS_EXPORT
/// The interaction point for discovering codecs for use with the Broadcast and Stage SDKs.
@interface IVSCodecDiscovery : NSObject

/// Gather all codecs that are supported by the SDK for RTMP Broadcast.
/// Each codec will be associated with either an `IVSVideoConfiguration` if
/// the codec is supported, or an `NSError` if the codec is not supported.
/// Codec availability depends on the `IVSVideoConfiguration` provided, your
/// AWS Customer ID, and the available encoders on your device. Regardless of
/// if a codec is supported, a `IVSCodecDiscoveryResult` will be returned for it.
///
/// Certain encoders will support some dimensions but not others, so it is required
/// that an `IVSVideoConfiguration` is provided to this API. A codec will be considered
/// incompatible if the dimensions or frame rate isn't supported. Things like B-frame
/// support, keyframe interval, and bitrate may be changed to provide compatibility,
/// and those changes will be reflected in the `configuration` property of each `IVSCodecDiscoveryResult`.
///
/// H.264 will always be returned with a configuration identical to the configuration provided.
/// All other codecs are subject to configuration changes.
///
/// In order to use the discovered codec, the `IVSVideoConfiguration` on the
/// `IVSCodecDiscoveryResult` *must* be used, you can not manually assign a non H.264 codec
/// to an `IVSVideoConfiguration` instance. If you only plan on using H.264, it is not necessary
/// to use this API, the default `IVSVideoConfiguration` initializer will use H.264 by default.
///
/// - Note: This API will perform short encoding sessions to guarantee compatibility with
/// non-H.264 codecs. To ensure these encodes can complete by the deadline, this API should
/// be invoked when the device is not using an excessive amount of CPU. Calling this API under
/// heavy CPU load may result in codecs that would otherwise be compatible being returned as not
/// compatible.
///
/// - Warning: This API is in beta and may change in the future.
///
/// - Parameters:
///   - customerID: The AWS Customer ID associated with the IVS channel being streamed to.
///   - videoConfiguration: An `IVSVideoConfiguration` to test encoders against.
///   - resultsCallback: A callback that will provide an array of results for all IVS supported codecs. This will always be invoked asynchronously on the main queue.
- (void)gatherAvailableCodecsForCustomerID:(NSString *)customerID
                        videoConfiguration:(IVSVideoConfiguration *)videoConfiguration
                           resultsCallback:(void (^)(NSArray<IVSCodecDiscoveryResult *> *))resultsCallback;

@end

NS_ASSUME_NONNULL_END
