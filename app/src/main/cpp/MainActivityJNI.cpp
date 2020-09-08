#include <fstream>
#include <jni.h>
#include <string>
#include <unistd.h>

#include "android/log.h"

#define LOG_TAG "MainActivityJNI"

std::string getConfigDirPathFromJava(JNIEnv* env, jobject obj);
void readConfigFile(std::string filePath);

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapp_MainActivity_stringFromJNI(JNIEnv* env, jobject obj)
{
    readConfigFile(getConfigDirPathFromJava(env, obj) + "/config.json");

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

std::string getConfigDirPathFromJava(JNIEnv* env, jobject obj)
{
    jclass clazz = env->GetObjectClass(obj); // or env->FindClass("com/example/myapp/MainActivity");
    jmethodID method = env->GetMethodID(clazz, "getConfigDirPath", "()Ljava/lang/String;");
    jobject ret = env->CallObjectMethod(obj, method);

    jstring jConfigDirPath = (jstring)ret;

    return std::string(env->GetStringUTFChars(jConfigDirPath, nullptr));
}

void readConfigFile(std::string filePath)
{
    std::ifstream ifs(filePath);
    std::string line;

    (void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s:", filePath.c_str());

    while (std::getline(ifs, line))
    {
        (void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s", line.c_str());
    }
}
