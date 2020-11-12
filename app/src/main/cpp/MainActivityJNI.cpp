#include <android/log.h>
#include <fstream>
#include <jni.h>
#include <string>
#include <unistd.h>

namespace {
const char* TAG = "MainActivityJNI";

std::string getConfigDirPathFromJava(JNIEnv* env, jobject obj);
void readConfigFile(std::string filePath);
} // namespace

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapp_MainActivity_stringFromJNI(JNIEnv* env, jobject obj)
{
    readConfigFile(getConfigDirPathFromJava(env, obj) + "/config.json");

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

namespace {
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

    LOGD("%s:", filePath.c_str());

    while (std::getline(ifs, line))
    {
        LOGD("%s", line.c_str());
    }
}
} // namespace