package com.alanwang4523.a4vulkancamera;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'a4vulkancamera' library on application startup.
    static {
        System.loadLibrary("a4vulkancamera");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btnTriangleDemo).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnTriangleDemo:
                TriangleDemoActivity.launchActivity(MainActivity.this);
                break;
        }
    }

    /**
     * A native method that is implemented by the 'a4vulkancamera' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}