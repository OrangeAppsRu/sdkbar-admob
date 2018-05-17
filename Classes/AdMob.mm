#import <Foundation/Foundation.h>
#import "AdMob.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#import <StoreKit/StoreKit.h>

static void printLog(const char* str) {
    CCLOG("%s", str);
}

void register_all_admob_framework(JSContext* cx, JS::HandleObject obj) {
    printLog("register_all_admob_framework");
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "admob", &ns);
}
