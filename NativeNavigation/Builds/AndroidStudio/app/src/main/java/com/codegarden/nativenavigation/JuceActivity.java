package com.codegarden.nativenavigation;

import androidx.drawerlayout.widget.DrawerLayout;
import androidx.appcompat.widget.Toolbar;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;

import android.view.*;
import android.util.Log;
import java.lang.reflect.Type;
import java.util.List;
import java.util.ArrayList;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import androidx.appcompat.app.AppCompatActivity;

public class JuceActivity extends AppCompatActivity
{
    private List<Message> messages;
    private String drawerTitle = "Messages";
    private StringBuilder messageTitle;
    private DrawerLayout drawerLayout;

    @Override
    protected void onCreate (Bundle savedInstanceState)
    {
        super.onCreate (savedInstanceState);

        constructNativeClass();

        setContentView(R.layout.main_activity);

        final Toolbar toolbar = (Toolbar) findViewById(R.id.detail_toolbar);
        messageTitle = new StringBuilder();
        messageTitle.append("JUCE/Android View Interop");
        toolbar.setTitle(messageTitle);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);

        fab.setOnClickListener(view -> Snackbar.make(view,
                        "This will disappear in just a moment...",
                        Snackbar.LENGTH_LONG)
                .setAction("Action", null).show());

        RecyclerView recyclerView = (RecyclerView)findViewById(R.id.left_drawer);
        LinearLayoutManager llm = new LinearLayoutManager(this);
        recyclerView.setLayoutManager(llm);

        drawerLayout = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawerLayout, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close)
        {
            public void onDrawerClosed(View view) {
                toolbar.setTitle(messageTitle);
            }

            public void onDrawerOpened(View drawerView) {
                toolbar.setTitle(drawerTitle);
            }
        };
        drawerLayout.addDrawerListener(toggle);
        toggle.syncState();

        initialiseData();

        MessageListAdapter adapter = new MessageListAdapter(this, messages, messageTitle, drawerLayout);
        recyclerView.setAdapter(adapter);
    }

    public void addJuceComponentButtonClicked(View sender)
    {
        addRemoveJuceComponent(findViewById(R.id.juceStage));
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
    }

    @Override
    public void onConfigurationChanged (Configuration cfg)
    {
        super.onConfigurationChanged (cfg);
    }

    private void initialiseData() {
        Gson gson = new Gson();
        messages = new ArrayList<>();

        Type collectionType = new TypeToken<List<Message>>(){}.getType();
        String json = getJsonData();
        Log.d("JSON", json);
        messages = gson.fromJson(json, collectionType);
    }

    public String getJsonData()
    {
        return getJsonString();
    }

    private long cppCounterpartInstance;
    private native void constructNativeClass();
    private native void destroyNativeClass();

    private native void addRemoveJuceComponent(View container);

    private native void methodANativeClass();
    private native void methodBNativeClass();

    private native void appNewIntent (Intent intent);
    private native void appOnResume ();

    private native String getJsonString();
    public native void setMessage (String message);
}

