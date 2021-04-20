# ndk-config-provider
Android Studio example how to provide configuration from assets (app/src/main/assets) or resources (app/src/main/res/raw) to Native (C/C++) code.

## How it works
### Assets
It performs via [NDK Asset API](https://developer.android.com/ndk/reference/group/asset)

### Raw Resorces
To access config file hosted in resorces from native code, you need to do some workarounds:
1. Copy the resource file to the local app storage.
2. Provide the path to stored file to native via JNI or via Environment Variable.

The following diagram shows this:

![Activity diagram](https://github.com/nkh-lab/ndk-config-provider/blob/master/doc/activity-diagram.png)

## Expected logcat output
For "MainActivityJNI" tag: 

Getting path to configuration folder via calling JNI method from Java (```GET_PATH_VIA_ENV_VAR``` is not defined):
```
2021-04-20 12:39:41.115 26129-26129/com.example.myapp D/MainActivityJNI: asset_config.json:
    {
        "id": 1234,
        "name": "asset_config"
    }
2021-04-20 12:39:41.115 26129-26129/com.example.myapp D/MainActivityJNI: Get config path via JNI
2021-04-20 12:39:41.115 26129-26129/com.example.myapp D/MainActivityJNI: /data/user/0/com.example.myapp/files/res_raw_config.json:
    {
        "id": 5678,
        "name": "res_raw_config"
    }
```
Getting path to configuration folder via setting-getting Environment Variable (```GET_PATH_VIA_ENV_VAR``` is defined):
```
2021-04-20 12:41:24.515 26278-26278/com.example.myapp D/MainActivityJNI: asset_config.json:
    {
        "id": 1234,
        "name": "asset_config"
    }
2021-04-20 12:41:24.516 26278-26278/com.example.myapp D/MainActivityJNI: Get config path via Environment Variable
2021-04-20 12:41:24.516 26278-26278/com.example.myapp D/MainActivityJNI: /data/user/0/com.example.myapp/files/res_raw_config.json:
    {
        "id": 5678,
        "name": "res_raw_config"
    }
```
