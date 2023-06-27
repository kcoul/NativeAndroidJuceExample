/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#define JUCE_CORE_INCLUDE_JNI_HELPERS 1

#include <JuceHeader.h>
#include "Data.h"

static String jsonData;

class MainContentComponent : public Component
{
public:
    MainContentComponent()
    {

    }

    MainContentComponent(jobject javaObject)
    {
        auto* env = getEnv();

        javaCounterpartInstance = env->NewWeakGlobalRef(javaObject);
        env->SetLongField (javaObject, NativeNavigationJuceActivityJavaClass.cppCounterpartInstance,
                           reinterpret_cast<jlong> (this));

        MessageManager::getInstance();

        title = "JUCE View";
        message = "init";
        data = Data(Data::getAndroidTestString());
    }

    ~MainContentComponent()
    {

    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour (0xff001F36));

        g.setFont (Font (24.0f));
        g.setColour (Colours::white);
        g.drawText (title, getLocalBounds(), Justification::centredTop, true);

        g.setFont (Font (16.0f));
        g.drawText (message, getLocalBounds(), Justification::centred, true);
    }

    void resized() override { }

    void addRemoveJuceComponent (jobject containerView)
    {
        if (getPeer() != nullptr)
            removeFromDesktop();
        else
        {
            centreWithSize (getWidth(), getHeight());
            setVisible(true);
            addToDesktop(0, containerView);
        }
    }

private:

    static void JNIEXPORT constructNativeClassJni (JNIEnv* env, jobject javaInstance)
    {
        initialiseJuce_GUI();
        new MainContentComponent (javaInstance);
    }

    static MainContentComponent* getCppInstance (JNIEnv* env, jobject javaInstance)
    {
        // always call JUCE::initialiseJUCEThread in java callbacks
        return reinterpret_cast<MainContentComponent*> (env->GetLongField (javaInstance,
                                                                           NativeNavigationJuceActivityJavaClass.cppCounterpartInstance));
    }

    static void JNIEXPORT destroyNativeClassJni (JNIEnv* env, jobject javaInstance)
    {
        if (auto* myself = getCppInstance (env, javaInstance))
            delete myself;
    }

    static void JNIEXPORT addRemoveJuceComponentJni (JNIEnv* env, jobject javaInstance,
                                                     jobject viewContainer)
    {
        if (auto* myself = getCppInstance (env, javaInstance))
            myself->addRemoveJuceComponent (viewContainer);
    }

    static void JNIEXPORT methodANativeClassJni (JNIEnv* env, jobject javaInstance)
    {
        int i = 1;
    }

    static void JNIEXPORT methodBNativeClassJni (JNIEnv* env, jobject javaInstance)
    {
        int i = 1;
    }

    static jstring JNIEXPORT getJsonStringJni(JNIEnv* env, jobject javaInstance)
    {
        if (auto* myself = getCppInstance (env, javaInstance))
        {
            jsonData = myself->data.toJson();
            return env->NewStringUTF(jsonData.toRawUTF8());
        }
    }

    static void JNIEXPORT setMessageJni(JNIEnv* env, jobject javaInstance, jstring message)
    {
        if (auto* myself = getCppInstance (env, javaInstance))
        {
            myself->message = juceString(env, message);
            myself->repaint();
        }
    }

#define JNI_CLASS_MEMBERS(METHOD, STATICMETHOD, FIELD, STATICFIELD, CALLBACK) \
     FIELD    (cppCounterpartInstance,    "cppCounterpartInstance", "J") \
     CALLBACK (constructNativeClassJni,   "constructNativeClass",   "()V") \
     CALLBACK (destroyNativeClassJni,     "destroyNativeClass",     "()V")    \
     CALLBACK (addRemoveJuceComponentJni, "addRemoveJuceComponent", "(Landroid/view/View;)V") \
     CALLBACK (methodANativeClassJni,     "methodANativeClass",     "()V") \
     CALLBACK (methodBNativeClassJni,     "methodBNativeClass",     "()V") \
     CALLBACK (getJsonStringJni,          "getJsonString",          "()Ljava/lang/String;") \
     CALLBACK (setMessageJni,             "setMessage",             "(Ljava/lang/String;)V")

    DECLARE_JNI_CLASS (NativeNavigationJuceActivityJavaClass, "com/codegarden/nativenavigation/JuceActivity")
#undef JNI_CLASS_MEMBERS

    String title;
    String message;
    Data data;
    jweak javaCounterpartInstance = nullptr;
    Slider juceComponent {Slider::Rotary, Slider::NoTextBox};
};