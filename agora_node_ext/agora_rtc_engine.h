/*
* Copyright (c) 2017 Agora.io
* All rights reserved.
* Proprietary and Confidential -- Agora.io
*/

/*
*  Created by Wang Yongli, 2017
*/

#ifndef AGORA_NODE_RTC_ENGINE_H
#define AGORA_NODE_RTC_ENGINE_H

#include "IAgoraMediaEngine.h"
#include "IAgoraRtcEngine.h"
#include <node.h>
#include <node_object_wrap.h>
#include "node_log.h"
#include "node_event_handler.h"
#include "node_napi_api.h"
#include "agora_video_source.h"
#include <functional>
#include <list>
#include <mutex>

/*
* Used to declare native interface to nodejs
*/
#define NAPI_API(m) \
    static void (m)(const FunctionCallbackInfo<Value>& args)

/*
* Used to define native interface which is exposed to nodejs
*/
#define NAPI_API_DEFINE(cls, method) \
    void cls::method(const FunctionCallbackInfo<Value>& args)

namespace agora {
    namespace rtc {
        using media::IExternalVideoRenderFactory;
        using v8::Isolate;

        /*
        * class NodeRtcEngine is the wrapper for IAgoraRtcEngine, and is exposed to nodejs as the native interface.
        */
        class NodeRtcEngine : public node::ObjectWrap
        {
        public:
            /*
            * Constructor
            */
            static void createInstance(const FunctionCallbackInfo<Value>& args);

            /*
            * Helper function, used to declare all supported native interface that are exposed to nodejs.
            */
            static void Init(Local<Object>& module);

            /*
            * Wrapper for RtcEngine functions
            */
            NAPI_API(initialize);
            NAPI_API(getVersion);
            NAPI_API(getErrorDescription);
            NAPI_API(joinChannel);
            NAPI_API(leaveChannel);
            NAPI_API(renewToken);
            NAPI_API(setChannelProfile);
            NAPI_API(setClientRole);
            NAPI_API(startEchoTest);
            NAPI_API(stopEchoTest);
            NAPI_API(enableLastmileTest);
            NAPI_API(disableLastmileTest);
            NAPI_API(enableVideo);
            NAPI_API(disableVideo);
            NAPI_API(startPreview);
            NAPI_API(stopPreview);
            NAPI_API(setVideoProfile);
            NAPI_API(enableAudio);
            NAPI_API(disableAudio);
            NAPI_API(setAudioProfile);
            NAPI_API(getCallId);
            NAPI_API(rate);
            NAPI_API(complain);
            NAPI_API(setEncryptionSecret);
            NAPI_API(createDataStream);
            NAPI_API(sendStreamMessage);       
            NAPI_API(setEncryptionMode);
#if 0
            NAPI_API(setVideoCompositingLayout);
            NAPI_API(clearVideoCompositingLayout);
            NAPI_API(configPublisher);
#endif
            /*
            * Wrapper for RtcEngineParameter API
            */
            NAPI_API(setBool);
            NAPI_API(setInt);
            NAPI_API(setUInt);
            NAPI_API(setNumber);
            NAPI_API(setString);
            NAPI_API(setObject);
            NAPI_API(getBool);
            NAPI_API(getInt);
            NAPI_API(getUInt);
            NAPI_API(getNumber);
            NAPI_API(getString);
            NAPI_API(getObject);
            NAPI_API(getArray);
            NAPI_API(setParameters);
            NAPI_API(setProfile);
            NAPI_API(convertPath);

            NAPI_API(muteLocalAudioStream);
            NAPI_API(muteAllRemoteAudioStreams);
            NAPI_API(muteRemoteAudioStream);
            NAPI_API(muteLocalVideoStream);
            NAPI_API(enableLocalVideo);
            NAPI_API(muteAllRemoteVideoStreams);
            NAPI_API(muteRemoteVideoStream);
            NAPI_API(setRemoteVideoStreamType);
            NAPI_API(setRemoteDefaultVideoStreamType);
            NAPI_API(enableAudioVolumeIndication);
            NAPI_API(startAudioRecording);
            NAPI_API(stopAudioRecording);
            NAPI_API(startAudioMixing);
            NAPI_API(stopAudioMixing);
            NAPI_API(pauseAudioMixing);
            NAPI_API(resumeAudioMixing);
            NAPI_API(adjustAudioMixingVolume);
            NAPI_API(getAudioMixingDuration);
            NAPI_API(getAudioMixingCurrentPosition);
            NAPI_API(setAudioMixingPosition);

            NAPI_API(setLocalVoicePitch);
            NAPI_API(setInEarMonitoringVolume);
            NAPI_API(pauseAudio);
            NAPI_API(resumeAudio);
            NAPI_API(setExternalAudioSource);
#if defined(__APPLE__) || defined(_WIN32)
            NAPI_API(startScreenCapture);
            NAPI_API(stopScreenCapture);
            NAPI_API(updateScreenCaptureRegion);
#endif
            NAPI_API(setLogFile);
            NAPI_API(setLogFilter);

            NAPI_API(setLocalVideoMirrorMode);
            
            NAPI_API(startRecordingService);
            NAPI_API(stopRecordingService);
            NAPI_API(refreshRecordingServiceStatus);
            NAPI_API(enableDualStreamMode);
            NAPI_API(setRecordingAudioFrameParameters);
            NAPI_API(setPlaybackAudioFrameParameters);
            NAPI_API(setMixedAudioFrameParameters);
            NAPI_API(adjustRecordingSignalVolume);
            NAPI_API(adjustPlaybackSignalVolume);
            NAPI_API(setHighQualityAudioParameters);
            NAPI_API(enableWebSdkInteroperability);
            NAPI_API(setVideoQualityParameters);

            NAPI_API(enableLoopbackRecording);
            NAPI_API(onEvent);
            NAPI_API(registerDeliverFrame);

            /*
            * Wrapper for device manager
            */
            NAPI_API(getVideoDevices);
            NAPI_API(setVideoDevice);
            NAPI_API(getCurrentVideoDevice);
            NAPI_API(startVideoDeviceTest);
            NAPI_API(stopVideoDeviceTest);
            NAPI_API(getAudioPlaybackDevices);
            NAPI_API(setAudioPlaybackDevice);
            NAPI_API(getCurrentAudioPlaybackDevice);
            NAPI_API(setAudioPlaybackVolume);
            NAPI_API(getAudioPlaybackVolume);
            NAPI_API(getAudioRecordingDevices);
            NAPI_API(setAudioRecordingDevice);
            NAPI_API(getCurrentAudioRecordingDevice);
            NAPI_API(getAudioRecordingVolume);
            NAPI_API(setAudioRecordingVolume);
            NAPI_API(startAudioPlaybackDeviceTest);
            NAPI_API(stopAudioPlaybackDeviceTest);
            NAPI_API(startAudioRecordingDeviceTest);
            NAPI_API(stopAudioRecordingDeviceTest);
            NAPI_API(getAudioPlaybackDeviceMute);
            NAPI_API(setAudioPlaybackDeviceMute);
            NAPI_API(getAudioRecordingDeviceMute);
            NAPI_API(setAudioRecordingDeviceMute);

            /**
             * Wrapper for video source, which is used to implement multiple video source.
             */
            NAPI_API(videoSourceInitialize);
            NAPI_API(videoSourceJoin);
            NAPI_API(videoSourceLeave);
            NAPI_API(videoSourceRenewToken);
            NAPI_API(videoSourceSetChannelProfile);
            NAPI_API(videoSourceSetVideoProfile);
            NAPI_API(startScreenCapture2);
            NAPI_API(stopScreenCatpure2);
            NAPI_API(videoSourceRelease);
            NAPI_API(videoSourceStartPreview);
            NAPI_API(videoSourceStopPreview);
            NAPI_API(videoSourceEnableWebSdkInteroperability);
            NAPI_API(videoSourceEnableDualStreamMode);
            NAPI_API(videoSourceSetLogFile);
            NAPI_API(videoSourceSetParameter);

            /*
            * Native interface used to setup local and remote video canvas.
            */
            NAPI_API(subscribe);
            NAPI_API(unsubscribe);
            NAPI_API(setupLocalVideo);
            NAPI_API(setVideoRenderDimension);
            NAPI_API(setHighFPS);
            NAPI_API(setFPS);
            NAPI_API(addToHighVideo);
            NAPI_API(removeFromHighVideo);

        public:
            Isolate* getIsolate() { return m_isolate; }
            IRtcEngine* getRtcEngine() { return m_engine; }
            void destroyVideoSource();

        protected:
            NodeRtcEngine(Isolate *isolate);
            ~NodeRtcEngine();
        private:
            DECLARE_CLASS;
            IRtcEngine *m_engine;
            std::unique_ptr<NodeEventHandler> m_eventHandler;
            Isolate *m_isolate;
            std::unique_ptr<IExternalVideoRenderFactory> m_externalVideoRenderFactory;

            /**
             * Currently we only support one video source. This maybe changed if more video source is needed.
             */
            std::unique_ptr<AgoraVideoSource> m_videoSourceSink;

			AVideoDeviceManager* m_videoVdm = nullptr;
			AAudioDeviceManager* m_audioVdm = nullptr;
        };

/*
* Use to extract native this pointer from JS object
*/
#define napi_get_native_this(args, native) \
            native = ObjectWrap::Unwrap<NodeRtcEngine>(args.Holder());

/*
* to extract one parameter from JS call parameters.
*/
#define napi_get_param_1(args, type1, param1) \
        do { \
            status = napi_get_value_##type1##_(args[0], (param1)); \
            if(status != napi_ok) { \
                break; \
            } \
        } while (false);

/*
* to extract two parameters from JS call parameters.
*/
#define napi_get_param_2(argv, type1, param1, type2, param2) \
        do { \
            status = napi_get_value_##type1##_(argv[0], (param1)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type2##_(argv[1], (param2)); \
            if(status != napi_ok) { \
                break; \
            } \
        } while (false);

/*
* to extract three parameters from JS call parameters.
*/
#define napi_get_param_3(argv, type1, param1, type2, param2, type3, param3) \
        do { \
            status = napi_get_value_##type1##_(argv[0], (param1)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type2##_(argv[1], (param2)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type3##_(argv[2], (param3)); \
            if(status != napi_ok) { \
                break; \
            } \
        } while (false);

/*
* to extract four parameters from JS call parameters.
*/
#define napi_get_param_4(argv, type1, param1, type2, param2, type3, param3, type4, param4) \
        do { \
            status = napi_get_value_##type1##_(argv[0], (param1)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type2##_(argv[1], (param2)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type3##_(argv[2], (param3)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type4##_(argv[3], (param4)); \
            if(status != napi_ok) { \
                break; \
            } \
        } while (false);

/*
* to extract seven parameters from JS call parameters.
*/
#define napi_get_param_7(argv, type1, param1, type2, param2, type3, param3, type4, param4, type5, param5, type6, param6, type7, param7) \
        do { \
            status = napi_get_value_##type1##_(argv[0], (param1)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type2##_(argv[1], (param2)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type3##_(argv[2], (param3)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type4##_(argv[3], (param4)); \
            if(status != napi_ok) { \
                break; \
            } \
		    status = napi_get_value_##type5##_(argv[4], (param5)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type6##_(argv[5], (param6)); \
            if(status != napi_ok) { \
                break; \
            } \
            status = napi_get_value_##type7##_(argv[6], (param7)); \
            if(status != napi_ok) { \
                break; \
            } \
        } while (false);
/*
* to return int value for JS call.
*/
#define napi_set_int_result(args, result) (args).GetReturnValue().Set(Integer::New(args.GetIsolate(), (result)))

/**
* to return bool value for JS call
*/
#define napi_set_bool_result(args, result) (args).GetReturnValue().Set(v8::Boolean::New(args.GetIsolate(), (result)))

/*
* to return string value for JS call
*/
#define napi_set_string_result(args, data) \
    Local<Value> tmp = String::NewFromUtf8(args.GetIsolate(), data, NewStringType::kInternalized).ToLocalChecked();\
    args.GetReturnValue().Set(tmp);

/**
* Helper MACRO to check whether the last API call return success.
*/
#define CHECK_NAPI_STATUS(engine, status) \
        if(status != napi_ok) { \
            LOG_ERROR("Error :%s, :%d\n", __FUNCTION__, __LINE__); \
            engine->m_eventHandler->fireApiError(__FUNCTION__); \
            break; \
        }

/**
 * Helper MACRO to check whether the extracted object is emptry;
 */
#define CHECK_NAPI_OBJECT(obj) \
        if(obj.IsEmpty()) { \
            LOG_ERROR("Error :%s, :%d\n", __FUNCTION__, __LINE__); \
            break;\
        }

/**
 * Helper MACRO to check whether the extracted native this is valid.
 */
#define CHECK_NATIVE_THIS(engine) \
        if(!engine || !engine->m_engine) { \
            LOG_ERROR("m_engine is null.\n");\
            break;\
        }

typedef int int32;
typedef NodeString nodestring;
typedef unsigned int uint32;

#ifdef _WIN32
#define CALL_MEM_FUNC_FROM_POINTER(pointer, func) pointer->##func()
#define CALL_MEM_FUNC(cls, func) cls.##func()
#define CALL_MEM_FUNC_WITH_PARAM(cls, func, param) cls.##func(param)

#define CALL_MEM_FUNC_WITH_PARAM2(cls, func, param1, param2) cls.##func(param1, param2)
#define CALL_MEM_FUNC_WITH_PARAM7(cls, func, param1, param2, param3, param4, param5, param6, param7) cls.##func(param1, param2, param3, param4, param5, param6, param7)
#else
#define CALL_MEM_FUNC_FROM_POINTER(pointer, func) pointer->func()
#define CALL_MEM_FUNC(cls, func) cls.func()
#define CALL_MEM_FUNC_WITH_PARAM(cls, func, param) cls.func(param)

#define CALL_MEM_FUNC_WITH_PARAM2(cls, func, param1, param2) cls.func(param1, param2)
#define CALL_MEM_FUNC_WITH_PARAM7(cls, func, param1, param2, param3, param4, param5, param6, param7) cls.func(param1, param2, param3, param4, param5, param6, param7)

#endif
/*
* Helper macro to transfer JS call directly to RtcEngine
*/
#define NAPI_API_DEFINE_WRAPPER_PARAM_0(method) \
    NAPI_API_DEFINE(NodeRtcEngine, method) \
    { \
        LOG_ENTER; \
        do {\
            NodeRtcEngine *pEngine = nullptr;\
            napi_get_native_this(args, pEngine);\
            CHECK_NATIVE_THIS(pEngine);\
            int result = CALL_MEM_FUNC_FROM_POINTER(pEngine->m_engine, method);\
            args.GetReturnValue().Set(Integer::New(args.GetIsolate(), result));\
        } while (false);\
        LOG_LEAVE;\
    }
/*
* Helper macro to transfer call directly to rtc.
*/
#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_0(method) \
    NAPI_API_DEFINE(NodeRtcEngine, method) \
    {\
        LOG_ENTER;\
        do {\
            NodeRtcEngine *pEngine = nullptr;\
            napi_get_native_this(args, pEngine);\
            CHECK_NATIVE_THIS(pEngine);\
            RtcEngineParameters rep(pEngine->m_engine);\
            int result = CALL_MEM_FUNC(rep, method);\
            napi_set_int_result(args, result);\
        } while (false);\
        LOG_LEAVE;\
    }
        
#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_1(method, type) \
    NAPI_API_DEFINE(NodeRtcEngine, method) \
    {\
        LOG_ENTER;\
        do {\
            NodeRtcEngine *pEngine = nullptr;\
            napi_get_native_this(args, pEngine);\
            CHECK_NATIVE_THIS(pEngine);\
            napi_status status = napi_ok;\
            type param;\
            napi_get_param_1(args, type, param);\
            CHECK_NAPI_STATUS(pEngine, status);\
            RtcEngineParameters rep(pEngine->m_engine);\
            int result = CALL_MEM_FUNC_WITH_PARAM(rep, method, param);\
            napi_set_int_result(args, result); \
        } while (false);\
        LOG_LEAVE;\
    }

#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_2(method, type, type2) \
    NAPI_API_DEFINE(NodeRtcEngine, method) \
    {\
        LOG_ENTER;\
        do {\
            NodeRtcEngine *pEngine = nullptr;\
            napi_get_native_this(args, pEngine);\
            CHECK_NATIVE_THIS(pEngine);\
            napi_status status = napi_ok;\
            type param;\
            type2 param2;\
            napi_get_param_2(args, type, param, type2, param2);\
            CHECK_NAPI_STATUS(pEngine, status);\
            RtcEngineParameters rep(pEngine->m_engine);\
            int result = CALL_MEM_FUNC_WITH_PARAM2(rep, method, param, param2);\
            napi_set_int_result(args, result); \
        } while (false);\
        LOG_LEAVE;\
    }

#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_7(method, type, type2, type3, type4, type5, type6, type7) \
 NAPI_API_DEFINE(NodeRtcEngine, method) \
    {\
        LOG_ENTER;\
        do {\
            NodeRtcEngine *pEngine = nullptr;\
            napi_get_native_this(args, pEngine);\
            CHECK_NATIVE_THIS(pEngine);\
            napi_status status = napi_ok;\
            type param;\
            type2 param2;\
            type3 param3;\
            type4 param4;\
            type5 param5;\
            type6 param6;\
            type7 param7;\
            napi_get_param_7(args, type, param, type2, param2, type3, param3, type4, param4, type5, param5, type6, param6, type7, param7);\
            CHECK_NAPI_STATUS(pEngine, status);\
            RtcEngineParameters rep(pEngine->m_engine);\
            int result = CALL_MEM_FUNC_WITH_PARAM7(rep, method, param, param2, param3, param4, param5, param6, param7);\
            napi_set_int_result(args, result); \
        } while (false);\
        LOG_LEAVE;\
    }

    }
}



#endif
