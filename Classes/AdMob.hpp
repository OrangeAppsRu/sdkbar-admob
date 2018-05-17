#ifndef AdMob_h
#define AdMob_h

#include "base/ccConfig.h"
#include "jsapi.h"
#include "jsfriendapi.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

void register_all_admob_framework(JSContext* cx, JS::HandleObject obj);

#endif /* AdMob_h */
