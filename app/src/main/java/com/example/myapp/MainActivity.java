package com.example.myapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    private static final String ConfigFileName = "config.json";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("MainActivityJNI");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initNativeConfig();

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }

    private boolean existsInFilesDir(String fileName) {
        File file = new File(getFilesDir(), fileName);

        if(file.exists()) return true;

        return false;
    }

    private void initNativeConfig() {
        if (existsInFilesDir(ConfigFileName)) {
            Log.d(TAG, "Config file: " + ConfigFileName + " already exists in " + getFilesDir().toString());
        }
        else {
            copyFileFromResToFilesDir(R.raw.config, ConfigFileName);
            Log.d(TAG, "Config file: " + ConfigFileName + " copied to " + getFilesDir().toString());
        }
    }

    private void copyFileFromResToFilesDir(int fromResId, String toFile) {
        InputStream is =  getResources().openRawResource(fromResId);
        byte[] buffer = new byte[4096];
        try
        {
            FileOutputStream fos = openFileOutput(toFile, Context.MODE_PRIVATE);

            int bytes_read;
            while ((bytes_read = is.read(buffer)) != -1)
                fos.write(buffer, 0, bytes_read);

            fos.close();
            is.close();
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public String getConfigDirPath()
    {
        return getFilesDir().toString();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}

