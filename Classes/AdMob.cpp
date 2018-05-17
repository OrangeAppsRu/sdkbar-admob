#include "AdMob.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <sstream>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "utils/PluginUtils.h"

static void printLog(const char* str) {
    CCLOG("%s", str);
}

void register_all_admob_framework(JSContext* cx, JS::HandleObject obj) {
    printLog("register_all_admob_framework");
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "admob", &ns);

    // JS_DefineFunction(cx, ns, "init", jsb_vksdk_init, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "login", jsb_vksdk_login, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "logout", jsb_vksdk_logout, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "loggedin", jsb_vksdk_loggedin, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "users_get", jsb_vksdk_users_get, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "friends_get", jsb_vksdk_friends_get, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "wall_post", jsb_vksdk_wall_post, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    // JS_DefineFunction(cx, ns, "call_api", jsb_vksdk_call_api, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
}
