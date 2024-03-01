package com.alanwang4523.a4vulkancamera.render;

import android.content.res.AssetManager;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class VKVideoRenderer implements SurfaceHolder.Callback {

    static {
        System.loadLibrary("a4vulkancamera");
    }

    private long mNativeContext;
    private AssetManager assetManager;
    private int filterType = 0;

    public VKVideoRenderer() {
        nativeCreate();
    }

    public void init(SurfaceView surface, AssetManager manager) {
        surface.getHolder().addCallback(this);
        assetManager = manager;
    }

    public void drawVideoFrame(byte[] data, int width, int height, int rotation) {
        nativeDraw(data, width, height, rotation);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        nativeInit(holder.getSurface(), width, height,assetManager);
        setFilterType(filterType);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        nativeDestroy();
    }


    public void setFilterType(int filterType){
        this.filterType = filterType;
        nativeSetFilterType(filterType);
    }

    public void updateFilterValue(int progress){
        nativeSetProgress(progress);
    }

    ////////// native method
    native void nativeCreate();
    native void nativeDestroy();
    native void nativeInit(Surface surface, int width, int height, AssetManager assetManager);
    native void nativeDraw(byte[] data, int width, int height, int rotation);
    native void nativeSetFilterType(int filterType);
    native void nativeSetProgress(int params);
}

