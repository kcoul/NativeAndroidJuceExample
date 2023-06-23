/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2018 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   To use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#define JUCE_CORE_INCLUDE_JNI_HELPERS 1
#include "../JuceLibraryCode/JuceHeader.h"

// the C++ counterpart class to the java class with the same name
class NativeAndroidJuceActivity  : private Timer
{
public:
    NativeAndroidJuceActivity (jobject javaObject)
    {
        auto* env = getEnv();

        javaCounterpartInstance = env->NewWeakGlobalRef(javaObject);
        env->SetLongField (javaObject, NativeAndroidJuceActivityJavaClass.cppCounterpartInstance,
                           reinterpret_cast<jlong> (this));

        juceComponent.setVisible (true);

        // initialise the JUCE message manager!
        MessageManager::getInstance();
    }

    ~NativeAndroidJuceActivity()
    {
        auto* env = getEnv();

        {
            LocalRef<jobject> javaThis (env->NewLocalRef (javaCounterpartInstance));

            if (javaThis != nullptr)
                env->SetLongField (javaThis.get(), NativeAndroidJuceActivityJavaClass.cppCounterpartInstance, 0);
        }

        env->DeleteWeakGlobalRef(javaCounterpartInstance);
    }

    void timerButtonClicked (jobject /*senderView*/)
    {
        if (isTimerRunning())
            stopTimer();
        else
            startTimer(1000);
    }

    void addRemoveJuceComponent (jobject containerView)
    {
        if (juceComponent.getPeer() != nullptr)
            juceComponent.removeFromDesktop();
        else
            juceComponent.addToDesktop(0, containerView);
    }

private:
    void timerCallback() override
    {
        auto* env = getEnv();

        LocalRef<jobject> javaThis (env->NewLocalRef (javaCounterpartInstance));

        if (javaThis != nullptr)
        {
            env->CallVoidMethod (javaThis.get(), NativeAndroidJuceActivityJavaClass.addToLog,
                                 javaString (String ("Timer callback: ") + String(counter++)).get());
        }
    }

    //==============================================================================
    #define JNI_CLASS_MEMBERS(METHOD, STATICMETHOD, FIELD, STATICFIELD, CALLBACK) \
     METHOD   (addToLog,                  "addToLog",               "(Ljava/lang/String;)V") \
     FIELD    (cppCounterpartInstance,    "cppCounterpartInstance", "J") \
     CALLBACK (constructNativeClassJni,   "constructNativeClass",   "()V") \
     CALLBACK (destroyNativeClassJni,     "destroyNativeClass",     "()V") \
     CALLBACK (timerButtonClickedJni,     "timerButtonClicked",     "(Landroid/view/View;)V") \
     CALLBACK (addRemoveJuceComponentJni, "addRemoveJuceComponent", "(Landroid/view/View;)V")

    DECLARE_JNI_CLASS (NativeAndroidJuceActivityJavaClass, "com/acme/NativeAndroidJuceActivity")
    #undef JNI_CLASS_MEMBERS

    //==============================================================================
    // simple glue wrappers to invoke the native code
    static void JNIEXPORT constructNativeClassJni (JNIEnv* env, jobject javaInstance)
    {
        initialiseJuce_GUI();
        new NativeAndroidJuceActivity (javaInstance);
    }

    static void JNIEXPORT destroyNativeClassJni (JNIEnv* env, jobject javaInstance)
    {
       if (auto* myself = getCppInstance (env, javaInstance))
           delete myself;
    }

    static void JNIEXPORT timerButtonClickedJni (JNIEnv* env, jobject javaInstance, jobject sender)
    {
        if (auto* myself = getCppInstance (env, javaInstance))
            myself->timerButtonClicked (sender);
    }

    static void JNIEXPORT addRemoveJuceComponentJni (JNIEnv* env, jobject javaInstance,
                                                     jobject viewContainer)
    {
        if (auto* myself = getCppInstance (env, javaInstance))
            myself->addRemoveJuceComponent (viewContainer);
    }

    static NativeAndroidJuceActivity* getCppInstance (JNIEnv* env, jobject javaInstance)
    {
         // always call JUCE::initialiseJUCEThread in java callbacks
        return reinterpret_cast<NativeAndroidJuceActivity*> (env->GetLongField (javaInstance,
                                                                                NativeAndroidJuceActivityJavaClass.cppCounterpartInstance));
    }

    //==============================================================================
    jweak javaCounterpartInstance = nullptr;
    int counter = 0;
    Slider juceComponent {Slider::Rotary, Slider::NoTextBox};
};

//NativeAndroidJuceActivity::NativeAndroidJuceActivityJavaClass_Class NativeAndroidJuceActivity::NativeAndroidJuceActivityJavaClass;
