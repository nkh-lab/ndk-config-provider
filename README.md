# ndk-config-provider
Android Studio example how to provide configuration from resources which are only accessible on Java
to Native (C/C++).

## Activity diagram
![Activity diagram](https://github.com/nkh-lab/ndk-config-provider/blob/master/doc/activity-diagram.png)

## Expected logcat output
For "MainActivityJNI" tag: 
```
2020-09-08 11:42:49.772 14528-14528/com.example.myapp D/MainActivityJNI: /data/user/0/com.example.myapp/files/config.json:
2020-09-08 11:42:49.772 14528-14528/com.example.myapp D/MainActivityJNI: {
2020-09-08 11:42:49.772 14528-14528/com.example.myapp D/MainActivityJNI:     "id": 1234
2020-09-08 11:42:49.772 14528-14528/com.example.myapp D/MainActivityJNI:     "name": "nkh-lab"
2020-09-08 11:42:49.772 14528-14528/com.example.myapp D/MainActivityJNI: }
```
