#include <jni.h>

#include <string.h>
#include <stdlib.h>

#include <android/log.h>

#include "src/statistics.c"

#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "MOBI-O-TRON-TURBO", fmt, ##__VA_ARGS__)

int Java_com_lockotron_mobi_1o_1tron_util_Statistics_00024Native_mostFrequentUser(JNIEnv *env, jobject instance, jintArray userIds_)
{
    jint *userIds = (*env)->GetIntArrayElements(env, userIds_, NULL);

    int result = getMode(userIds, (*env)->GetArrayLength(env, userIds_));
    LOG("Called C function with return %d", result);

    (*env)->ReleaseIntArrayElements(env, userIds_, userIds, 0);

    return result;
}