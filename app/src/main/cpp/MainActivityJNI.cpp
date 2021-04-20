#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <fstream>
#include <jni.h>
#include <sstream>
#include <string>
#include <unistd.h>

namespace {
constexpr char* TAG = "MainActivityJNI";
constexpr char* RES_RAW_CONFIG_PATH_ENV_VAR = "RES_RAW_CONFIG_PATH";
constexpr char* RES_RAW_CONFIG_FILE_NAME = "res_raw_config.json";
constexpr char* ASSET_CONFIG_FILE_NAME = "asset_config.json";

jobject getAssetManagerFromJava(JNIEnv* env, jobject obj);
void readConfigFromAsset(JNIEnv* env, jobject obj);
#ifdef GET_PATH_VIA_ENV_VAR
void readConfigFromResRaw();
#else
void readConfigFromResRaw(JNIEnv* env, jobject obj);
std::string getResRawConfigDirFromJava(JNIEnv* env, jobject obj);
#endif

std::string readFile(std::string filePath);

} // namespace

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))

// entry point to native code
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapp_MainActivity_stringFromJNI(JNIEnv* env, jobject obj)
{
    readConfigFromAsset(env, obj);

#ifdef GET_PATH_VIA_ENV_VAR
    readConfigFromResRaw();
#else
    readConfigFromResRaw(env, obj);
#endif

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

namespace {

void readConfigFromAsset(JNIEnv* env, jobject obj)
{
    jobject jam = getAssetManagerFromJava(env, obj);
    if (jam)
    {
        AAssetManager* am = AAssetManager_fromJava(env, jam);
        if (am)
        {
            AAsset* assetFile = AAssetManager_open(am, ASSET_CONFIG_FILE_NAME, AASSET_MODE_BUFFER);

            const void* buf = AAsset_getBuffer(assetFile);

            LOGD("%s:\n%s", ASSET_CONFIG_FILE_NAME, static_cast<const char*>(buf));
        }
    }
}

#ifdef GET_PATH_VIA_ENV_VAR
void readConfigFromResRaw()
{
    LOGD("Get config path via Environment Variable");
    std::string configPath = getenv(RES_RAW_CONFIG_PATH_ENV_VAR);

    LOGD(
        "%s/%s:\n%s",
        configPath.c_str(),
        RES_RAW_CONFIG_FILE_NAME,
        readFile(configPath + "/" + RES_RAW_CONFIG_FILE_NAME).c_str());
}
#else
void readConfigFromResRaw(JNIEnv* env, jobject obj)
{
    LOGD("Get config path via JNI");
    std::string configPath = getResRawConfigDirFromJava(env, obj);

    LOGD(
        "%s/%s:\n%s",
        configPath.c_str(),
        RES_RAW_CONFIG_FILE_NAME,
        readFile(configPath + "/" + RES_RAW_CONFIG_FILE_NAME).c_str());
}

std::string getResRawConfigDirFromJava(JNIEnv* env, jobject obj)
{
    jclass clazz = env->GetObjectClass(obj); // or env->FindClass("com/example/myapp/MainActivity");
    jmethodID method = env->GetMethodID(clazz, "getResRawConfigDir", "()Ljava/lang/String;");
    jobject ret = env->CallObjectMethod(obj, method);

    jstring jConfigDirPath = (jstring)ret;

    return std::string(env->GetStringUTFChars(jConfigDirPath, nullptr));
}
#endif

jobject getAssetManagerFromJava(JNIEnv* env, jobject obj)
{
    jclass clazz = env->GetObjectClass(obj); // or env->FindClass("com/example/myapp/MainActivity");
    jmethodID method =
        env->GetMethodID(clazz, "getAssetManager", "()Landroid/content/res/AssetManager;");
    jobject ret = env->CallObjectMethod(obj, method);

    return ret;
}

std::string readFile(std::string filePath)
{
    std::ifstream ifs(filePath);
    std::stringstream ss;

    ss << ifs.rdbuf();

    return ss.str();
}

} // namespace
