#include <jni.h>

#include <string.h>
#include <stdlib.h>

#include <android/log.h>

#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "MOBI-O-TRON-TURBO", fmt, ##__VA_ARGS__)

void Java_com_lockotron_mobi_1o_1tron_MainActivity_test(JNIEnv* env, jobject thiz)
{
    LOG("TEST SUCCESSFUL!!!%d", 1);
}