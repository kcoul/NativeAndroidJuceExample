package com.acme;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

import com.acme.nativeandroidjucesample.R;

public class NativeAndroidJuceActivity extends Activity
{
    //==============================================================================
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mainlayout);

        // call the native C++ class constructor
        constructNativeClass();
    }

    @Override
    protected void onDestroy()
    {
        // call the native C++ class destructor
        destroyNativeClass();
        super.onDestroy();
    }

    // called by NativeAndroidJuceActivity.cpp
    public void addToLog(String message)
    {
        EditText editText = (EditText) findViewById(R.id.juceOutput);

        editText.setText(message + "\n" + editText.getText());
    }

    // called by mainlayout.xml and implemented in NativeAndroidJuceActivity.cpp
    public native void timerButtonClicked(View sender);

    public void addJuceComponentButtonClicked(View sender)
    {
        addRemoveJuceComponent(findViewById(R.id.juceStage));
    }

    //==============================================================================
    private native void constructNativeClass();
    private native void destroyNativeClass();
    private native void addRemoveJuceComponent(View container);

    private long cppCounterpartInstance;
};
