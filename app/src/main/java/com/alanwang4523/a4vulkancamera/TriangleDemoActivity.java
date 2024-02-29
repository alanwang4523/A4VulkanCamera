package com.alanwang4523.a4vulkancamera;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

import com.google.androidgamesdk.GameActivity;

public class TriangleDemoActivity extends GameActivity {

    public static void launchActivity(Context context) {
        Intent intent = new Intent(context, TriangleDemoActivity.class);
        context.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }
}