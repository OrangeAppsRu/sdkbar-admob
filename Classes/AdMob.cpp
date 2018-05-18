#include "AdMob.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <sstream>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "utils/PluginUtils.h"
#include "firebase/app.h"
#include "firebase/admob.h"
#include "firebase/admob/banner_view.h"
#include "firebase/admob/interstitial_ad.h"

static firebase::admob::AdRequest my_ad_request = {};

static void printLog(const char* str) {
    CCLOG("%s", str);
}

///////////////////////////////////////
//
//  AdMob Listeners & Utilities
//
///////////////////////////////////////

class MyBannerViewListener : public firebase::admob::BannerView::Listener {
    int cbId;
public:
    MyBannerViewListener(int callbackId): cbId(callbackId) {}

    void OnPresentationStateChanged(firebase::admob::BannerView* banner_view, firebase::admob::BannerView::PresentationState state) override {
        // This method gets called when the banner view's presentation
        // state changes.
        printLog("[AdMob] Banner state changed");
    }

    void OnBoundingBoxChanged(firebase::admob::BannerView* banner_view, firebase::admob::BoundingBox box) override {
        // This method gets called when the banner view's bounding box
        // changes.
        printLog("[AdMob] Banner size changed");
    }
};

class MyInterstitialAdListener: public firebase::admob::InterstitialAd::Listener {
    int cbId;
public:
    MyInterstitialAdListener(int callbackId): cbId(callbackId) {};

    void OnPresentationStateChanged(firebase::admob::InterstitialAd* interstitialAd, firebase::admob::InterstitialAd::PresentationState state) override {
        printLog("[AdMob] InterstitialAd state changed");
    }
};

class MyRewardedVideoListener: public firebase::admob::rewarded_video::Listener {
    int cbId;
public:
    MyRewardedVideoListener(int callbackId): cbId(callbackId) {};

    void OnRewarded(firebase::admob::rewarded_video::RewardItem item) override {
        printLog("[AdMob] On reward item");
    }

    void OnPresentationStateChanged(firebase::admob::rewarded_video::PresentationState state) override {
        printLog("[AdMob] InterstitialAd state changed");
    }
};

firebase::admob::AdParent getAdParent() {
    // Returns the Android Activity.
    return cocos2d::JniHelper::getActivity();
}

///////////////////////////////////////
//
//  JS API
//
///////////////////////////////////////

static bool jsb_admob_show_banner(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_admob_show_banner");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 1) {
        // banner id, callback, this
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(2), args.get(1));
        bool ok = true;
        std::string bannerId;
        JS::RootedValue arg0Val(cx, args.get(0));
        ok &= jsval_to_std_string(cx, arg0Val, &bannerId);

        firebase::admob::AdSize ad_size;
        ad_size.ad_size_type = firebase::admob::kAdSizeStandard;
        ad_size.width = 320;
        ad_size.height = 50;
        firebase::admob::BannerView* banner_view;
        banner_view = new firebase::admob::BannerView();
        banner_view->Initialize(getAdParent(), bannerId.c_str(), ad_size);
        banner_view->SetListener(new MyBannerViewListener(cb->callbackId));
        banner_view->LoadAd(my_ad_request);
        rec.rval().set(JSVAL_TRUE);
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_admob_show_interstitial(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_admob_show_interstitial");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 1) {
        // banner id, callback, this
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(2), args.get(1));
        bool ok = true;
        std::string bannerId;
        JS::RootedValue arg0Val(cx, args.get(0));
        ok &= jsval_to_std_string(cx, arg0Val, &bannerId);

        firebase::admob::InterstitialAd* interstitial_ad;
        interstitial_ad = new firebase::admob::InterstitialAd();
        interstitial_ad->Initialize(getAdParent(), bannerId.c_str());
        interstitial_ad->SetListener(new MyInterstitialAdListener(cb->callbackId));
        interstitial_ad->LoadAd(my_ad_request);
        rec.rval().set(JSVAL_TRUE);
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

static bool jsb_admob_show_rewarded(JSContext *cx, uint32_t argc, jsval *vp)
{
    printLog("jsb_admob_show_rewarded");
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    JS::CallReceiver rec = JS::CallReceiverFromVp(vp);
    if(argc == 1) {
        // banner id, callback, this
        CallbackFrame *cb = new CallbackFrame(cx, obj, args.get(2), args.get(1));
        bool ok = true;
        std::string bannerId;
        JS::RootedValue arg0Val(cx, args.get(0));
        ok &= jsval_to_std_string(cx, arg0Val, &bannerId);

        firebase::admob::rewarded_video::LoadAd(bannerId.c_str(), my_ad_request);
        firebase::admob::rewarded_video::SetListener(new MyRewardedVideoListener(cb->callbackId));
        rec.rval().set(JSVAL_TRUE);
        return true;
    } else {
        JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
}

void register_all_admob_framework(JSContext* cx, JS::HandleObject obj) {

    printLog("[AdMob] Init plugin");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Initialize Firebase for Android.
    firebase::App* app = firebase::App::Create(firebase::AppOptions(), cocos2d::JniHelper::getEnv(), cocos2d::JniHelper::getActivity());
    // Initialize AdMob.
    firebase::admob::Initialize(*app, "ca-app-pub-8085014911314432~4835892581");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // Initialize Firebase for iOS.
    firebase::App* app = firebase::App::Create(firebase::AppOptions());
    // Initialize AdMob.
    firebase::admob::Initialize(*app, "INSERT_YOUR_ADMOB_IOS_APP_ID");
#endif
    // Initialize AdMob.
    firebase::admob::Initialize(*app);
    firebase::admob::rewarded_video::Initialize();

    printLog("[AdMob] register js interface");
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "admob", &ns);

    JS_DefineFunction(cx, ns, "show_banner", jsb_admob_show_banner, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "show_interstitial", jsb_admob_show_interstitial, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ns, "show_rewarded", jsb_admob_show_rewarded, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
