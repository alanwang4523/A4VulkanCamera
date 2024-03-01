package com.alanwang4523.a4vulkancamera.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.alanwang4523.a4vulkancamera.R;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    // Used to load the 'a4vulkancamera' library on application startup.
    static {
        System.loadLibrary("a4vulkancamera");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btnVulkanCamera).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnVulkanCamera:
//                TriangleDemoActivity.launchActivity(MainActivity.this);
                startActivity(new Intent(MainActivity.this, VulkanCameraActivity.class));
                break;
        }
    }

    /**
     * A native method that is implemented by the 'a4vulkancamera' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}