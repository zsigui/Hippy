/*!
 * iOS SDK
 *
 * Tencent is pleased to support the open source community by making
 * Hippy available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import <UIKit/UIKit.h>
#import "HippyBridge.h"
#import "HippyViewManager.h"
#import "HippyInvalidating.h"
#import "HippyBridgeModule.h"
#import "HippyCustomTouchHandlerProtocol.h"

@class HippyShadowView;
@class HippyUIManager;
@class HippyViewManager;
@class HippyComponentMap;
@protocol HippyImageProviderProtocol;

NS_ASSUME_NONNULL_BEGIN

/**
 * Posted whenever a new root view is registered with HippyUIManager. The userInfo property
 * will contain a HippyUIManagerRootViewKey with the registered root view.
 */
HIPPY_EXTERN NSString *const HippyUIManagerDidRegisterRootViewNotification;

/**
 * Posted whenever a root view is removed from the HippyUIManager. The userInfo property
 * will contain a HippyUIManagerRootViewKey with the removed root view.
 */
HIPPY_EXTERN NSString *const HippyUIManagerDidRemoveRootViewNotification;

/**
 * Key for the root view in the above notifications
 */
HIPPY_EXTERN NSString *const HippyUIManagerRootViewKey;

/**
 * Key for the root view's HippyTag in the above notifications
 */
HIPPY_EXTERN NSString *const HippyUIManagerRootViewTagKey;

/**
 * Posted whenever endBatch is called
 */
HIPPY_EXTERN NSString *const HippyUIManagerDidEndBatchNotification;

/**
 * This notification can be sent when the font is registered or modified on the native side
 * and hippy needs to be refreshed.
 *
 * `notification.object` can carry rootTag to filter the RootView that needs to be refreshed.
 *  Default value nil indicating that a refresh is required.
 */
HIPPY_EXTERN NSString *const HippyFontChangeTriggerNotification;



/// The HippyUIManager responsible for updating the view hierarchy.
@interface HippyUIManager : NSObject <HippyInvalidating>

/// HippyBridge instance
@property (weak, readonly) HippyBridge *bridge;

/// View Registry of all nodes
@property (nonatomic, readonly) HippyComponentMap *viewRegistry;

/// Specify whether UI hierarchy will be created instantly.
/// When setting YES, UI hierarchy will not be created automatically,
/// default is NO.
@property (nonatomic, assign) BOOL uiCreationLazilyEnabled;

/// Multiplier for fontSize of Text and TextView component.
///
/// The default value is nil, which means the multiplier is 1.0.
/// Use `HippyFontChangeTriggerNotification` to update and reload all text components.
@property (nonatomic, strong, nullable, readonly) NSNumber *globalFontSizeMultiplier;

/// Init method
/// - Parameter bridge: HippyBridge
- (instancetype)initWithBridge:(HippyBridge *)bridge NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Set hippyBridge for UIManager
/// - Parameter bridge: HippyBridge instance
- (void)setBridge:(HippyBridge * _Nullable)bridge;

/// Get all rootView
- (NSArray<__kindof UIView *> *)rootViews;

/// Get rootView with given tag
/// Note: this is root's contentView, 
/// NOT the HippyRootView instance!
- (UIView *)rootContentViewForTag:(NSNumber *)rootTag;

/// Gets the view associated with a hippyTag.
/// - Parameters:
///   - hippyTag: NSNumber
///   - rootTag: NSNumber
- (UIView *)viewForHippyTag:(NSNumber *)hippyTag onRootTag:(NSNumber *)rootTag;

/// Get the shadow view associated with a hippyTag
/// - Parameters:
///   - hippyTag: NSNumber
///   - rootTag: NSNumber
- (HippyShadowView *)shadowViewForHippyTag:(NSNumber *)hippyTag onRootTag:(NSNumber *)rootTag;

/// Update the frame of a root view. This might be in response to a screen rotation
/// or some other layout event outside of the Hippy-managed view hierarchy.
/// - Parameters:
///   - frame: new frame
///   - view: target view
- (void)setFrame:(CGRect)frame forRootView:(UIView *)view;

/// Update the frame of a view. This might be in response to a screen rotation
/// or some other layout event outside of the Hippy-managed view hierarchy.
/// - Parameters:
///   - frame: new frame
///   - view: target view
- (void)setFrame:(CGRect)frame forView:(UIView *)view;

/// Schedule a block to be executed on the UI thread. Useful if you need to execute
/// view logic after all currently queued view updates have completed.
/// - Parameter block: block to be executed on main thread
- (void)addUIBlock:(HippyViewManagerUIBlock)block;

/// In some cases we might want to trigger layout from native side.
/// Hippy won't be aware of this, so we need to make sure it happens.
/// - Parameter tag: root tag
- (void)setNeedsLayoutForRootNodeTag:(NSNumber *)tag;

/// Update view with props
- (void)updateView:(NSNumber *)componentTag onRootTag:(NSNumber *)rootTag props:(NSDictionary *)pros;


/**
 * Manully create views recursively from shadowView
 *
 * @param shadowView HippyShadowView corresponding to UIView
 * @return view created by HippyShadowView
 */
- (UIView *)createViewForShadowListItem:(HippyShadowView *)shadowView;

/// Register extra components
/// @param extraComponents extra components classes
- (void)registerExtraComponent:(NSArray<Class> *)extraComponents;

/// Clear all resources
- (void)invalidate;

@end


#pragma mark - HippyBridge (HippyUIManager)

/**
 * This category makes the current HippyUIManager instance available via the
 * HippyBridge, which is useful for HippyBridgeModules or HippyViewManagers that
 * need to access the HippyUIManager.
 */
@interface HippyBridge (HippyUIManager)

/// The current HippyUIManager instance
@property (nonatomic, strong) HippyUIManager *uiManager;

/// A custom touch handler for gesture special processing
/// You can use it when you need to modify Hippy's default gesture handling logic
@property (nonatomic, strong, readonly) id<HippyCustomTouchHandlerProtocol> customTouchHandler;

@end

NS_ASSUME_NONNULL_END
