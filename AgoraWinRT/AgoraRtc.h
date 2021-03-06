#pragma once
#include "pch.h"
#include "AgoraRtc.g.h"
#include "RawAudioFrameObsever.h"
#include "RawVideoFrameObserver.h"
#include "RawVideoSource.h"

namespace winrt::AgoraWinRT::implementation
{

    struct AgoraRtc : AgoraRtcT<AgoraRtc>,
        public agora::rtc::IRtcEngineEventHandler,
        private agora::rtc::IMetadataObserver,
        private agora::rtc::IPacketObserver
    {
        AgoraRtc() = default;

        AgoraRtc(hstring const& vendorKey);
    public:
        //RtcEngine事件处理
        void RegisterRtcEngineEventHandler(AgoraWinRT::AgoraRtcEventHandler handler);
        //媒体元数据观察器
        void RegisterMediaMetadataObserver(AgoraWinRT::MetadataObserver observer);
    public:
        //频道管理
        int16_t SetChannelProfile(AgoraWinRT::CHANNEL_PROFILE_TYPE const& type);
        int16_t SetClientRole(AgoraWinRT::CLIENT_ROLE_TYPE const& type);
        int16_t JoinChannel(hstring const& token, hstring const& channel, hstring const& info, uint64_t uid);
        int16_t SwitchChannel(hstring const& token, hstring const& channel);
        int16_t LeaveChannel();
        int16_t RenewToken(hstring const& token);
        AgoraWinRT::CONNECTION_STATE_TYPE GetConnectionState();
        void Close();
        //音频管理
        int16_t EnableAudio();
        int16_t DisableAudio();
        int16_t SetAudioProfile(AgoraWinRT::AUDIO_PROFILE_TYPE const& profile, AgoraWinRT::AUDIO_SCENARIO_TYPE const& scenario);
        int16_t AdjustRecordingSignalVolume(int16_t volume);
        int16_t AdjustUserPlaybackSignalVolume(uint64_t uid, int16_t volume);
        int16_t AdjustPlaybackSignalVolume(int16_t volume);
        int16_t EnableLocalAudio(bool enabled);
        int16_t MuteLocalAudioStream(bool muted);
        int16_t MuteRemoteAudioStream(uint64_t uid, bool muted);
        int16_t MuteAllRemoteAudioStreams(bool muted);
        int16_t SetDefaultMuteAllRemoteAudioStreams(bool muted);
        //视频管理
        int16_t EnableVideo();
        int16_t DisableVideo();
        int16_t SetVideoEncoderConfiguration(AgoraWinRT::VideoEncoderConfiguration const& config);
        int16_t MuteLocalVideoStream(bool muted);
        int16_t MuteRemoteVideoStream(uint64_t uid, bool muted);
        int16_t MuteAllRemoteVideoStream(bool muted);
        int16_t SetDefaultMuteAllRemoteVideoStreams(bool muted);
        //视频前处理及后处理
        int16_t SetBeautyEffectOptions(bool enabled, AgoraWinRT::BeautyOptions const& options);
        //音乐文件播放及混音
        int16_t StartAudioMixing(hstring const& file, bool loopback, bool replace, int32_t cycle);
        int16_t StopAudioMixing();
        int16_t PauseAudioMixing();
        int16_t ResumeAudioMixing();
        int16_t AdjustAudioMixingVolume(uint16_t volume);
        int16_t AdjustAudioMixingPlayoutVolume(uint16_t volume);
        int16_t AdjustAudioMixingPublishVolume(uint16_t volume);
        int16_t GetAudioMixingPublishVolume();
        int16_t GetAudioMixingDuration();
        int16_t GetAudioMixingCurrentPosition();
        int16_t SetAudioMixingPosition(uint64_t pos);
        int16_t SetAudioMixingPitch(int16_t pitch);
        //音效文件播放管理
        int16_t GetEffectsVolume();
        int16_t SetEffectsVolume(uint16_t volume);
        int16_t SetVolumeOfEffect(uint64_t soundId, uint16_t volume);
        int16_t PlayEffect(uint64_t soundId, hstring const& file, int16_t loopCount, float pitch, float pan, float gain, bool publish);
        int16_t StopEffect(uint64_t soundId);
        int16_t StopAllEffect();
        int16_t PreloadEffect(uint64_t soundId, hstring const& file);
        int16_t UnloadEffect(uint64_t soundId);
        int16_t PauseEffect(uint64_t soundId);
        int16_t PauseAllEffect();
        int16_t ResumeEffect(uint64_t soundId);
        int16_t ResumeAllEffect();
        //变声与混响
        int16_t SetLocalVoiceChanger(AgoraWinRT::VOICE_CHANGER_PRESET const& changer);
        int16_t SetLocalVoiceReverbPreset(AgoraWinRT::AUDIO_REVERB_PRESET const& preset);
        int16_t SetLocalVoicePitch(float pitch);
        int16_t SetLocalVoiceEqualization(AgoraWinRT::AUDIO_EQUALIZATION_BAND_FREQUENCY const& freq, int16_t gain);
        int16_t SetLocalVoiceReverb(AgoraWinRT::AUDIO_REVERB_TYPE const& type, uint64_t value);
        //听声辩位
        int16_t EnableSoundPositionIndication(bool enabled);
        int16_t SetRemoteVoicePosition(uint64_t uid, float pan, float gain);
        //CDN推流
        int16_t SetLiveTranscoding(AgoraWinRT::LiveTranscoding const& transcoding);
        int16_t AddPublishStreamUrl(hstring const& url, bool enabled);
        int16_t RemovePublishStreamUrl(hstring const& url);
        //跨频道媒体流转发
        int16_t StartChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config);
        int16_t UpdateChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config);
        int16_t StopChannelMediaRelay();
        //音量提示
        int16_t EnableAudioVolumeIndication(int32_t interval, uint8_t smooth, bool report);
        //视频双流模式
        int16_t EnableDualStreamMode(bool enabled);
        int16_t SetRemoteVideoStreamType(uint64_t uid, AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type);
        int16_t SetRemoteDefaultVideoStreamType(AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type);
        //视频流回退
        int16_t SetLocalPublishFallbackOption(AgoraWinRT::STREAM_FALLBACK_OPTIONS const& option);
        int16_t SetRemoteSubscribeFallbackOption(AgoraWinRT::STREAM_FALLBACK_OPTIONS const& option);
        int16_t SetRemoteUserPriority(uint64_t uid, AgoraWinRT::PRIORITY_TYPE const& type);
        //通话前网络测试
        int16_t StartEchoTest(uint8_t interval);
        int16_t StopEchoTest();
        int16_t EnableLastmileTest();
        int16_t DisableLastmileTest();
        int16_t StartLastmileProbeTest(AgoraWinRT::LastmileProbeConfig const& config);
        int16_t StopLastmileProbeTest();
        //设置视频源
        bool SetVideoSource(AgoraWinRT::VideoSource const& source);
        //视频自采集
        int16_t SetExternalVideoSource(bool enable, bool useTexture);
        int16_t PushVideoFrame(AgoraWinRT::ExternalVideoFrame const& frame);
        //音频自采集
        int16_t SetExternalAudioSource(bool enable, uint32_t sampleRate, uint8_t channels);
        int16_t PushAudioFrame(AgoraWinRT::AudioFrame const& frame);
        //音频自渲染
        int16_t SetExternalAudioSink(bool enable, uint32_t sampleRate, uint8_t channels);
        int16_t PullAudioFrame(AgoraWinRT::AudioFrame const& frame);
        //直播水印
        int16_t AddVideoWatermark(hstring const& file, AgoraWinRT::WatermarkOptions const& option);
        int16_t ClearVideoWatermark();
        //加密
        int16_t EnableEncryption(bool enable, AgoraWinRT::EncryptionConfig const& config);
        void RegisterPacketObserver(AgoraWinRT::PacketObserver const& observer);
        //音频录制
        int16_t StartAudioRecording(hstring const& file, uint32_t sampleRate, AgoraWinRT::AUDIO_RECORDING_QUALITY_TYPE const& type);
        int16_t StopAudioRecording();
        //直播输入在线媒体流
        int16_t AddInjectStreamUrl(hstring const& url, AgoraWinRT::InjectStreamConfig const& config);
        int16_t RemoveInjectStreamUrl(hstring const& url);
        //流消息
        int64_t CreateDataStream(bool reliable, bool ordered);
        int16_t SendStreamMessage(int64_t streamId, hstring const& data);
        //其他音频控制
        int16_t EnableLoopbackRecording(bool enabled, hstring const& deviceName);
        //其他视频控制
        int16_t SetCameraCapturerConfiguration(AgoraWinRT::CameraCapturerConfiguration const& config);
        //其他方法
        int16_t SendCustomReportMessage(hstring const& id, hstring const& category, hstring const& eventName, hstring const& label, int64_t value);
        int16_t GetCallId(hstring& id);
        int16_t Rate(hstring const& callId, uint8_t rating, hstring const& desc);
        int16_t Complain(hstring const& callId, hstring const& desc);
        hstring GetVersion(int64_t& build);
        int16_t SetLogFile(hstring const& file);
        int16_t SetLogFilter(uint16_t filter);
        int16_t SetLogFileSize(uint64_t size);
        hstring GetErrorDesc(int64_t code);
        //原始音频数据
        void RegisterAudioFrameObserver(AgoraWinRT::AudioFrameObserver const& observer);
        int16_t SetRecordingAudioFrameParameters(uint32_t sampleRate, uint8_t channels, AgoraWinRT::RAW_AUDIO_FRAME_OP_MODE_TYPE const& mode, uint32_t samplesPerCall);
        int16_t SetPlaybackAudioFrameParameters(uint32_t sampleRate, uint8_t channels, AgoraWinRT::RAW_AUDIO_FRAME_OP_MODE_TYPE const& mode, uint32_t samplesPerCall);
        int16_t SetMixedAudioFrameParameters(uint32_t sampleRate, uint32_t samplesPerCall);
        //原始视频数据
        void RegisterVideoFrameObserver(AgoraWinRT::VideoFrameObserver const& observer);
        //多频道
        AgoraWinRT::Channel CreateChannel(hstring const& channel);
        //设备管理
        AgoraWinRT::AudioDeviceManager GetAudioDeviceManager();
    private:
        agora::rtc::IRtcEngine* m_rtcEngine{ nullptr };
        agora::media::IMediaEngine* m_mediaEngine{ nullptr };
        AgoraWinRT::AgoraRtcEventHandler m_handler{ nullptr };
        AgoraWinRT::MetadataObserver m_metadataObserver{ nullptr };
        AgoraWinRT::PacketObserver m_packetObserver{ nullptr };
        AgoraWinRT::implementation::RawAudioFrameObserver* m_rawAudioFrameObserver{ nullptr };
        AgoraWinRT::implementation::RawVideoFrameObserver* m_rawVideoFrameObserver{ nullptr };
        AgoraWinRT::implementation::RawVideoSource* m_videoSource{ nullptr };
    private:
        //频道管理事件
        void onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE type, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason) override;
        void onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
        void onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed) override;
        void onLeaveChannel(const agora::rtc::RtcStats& value) override;
        void onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole) override;
        void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;
        void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;
        void onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type);
        void onConnectionLost() override;
        void onTokenPrivilegeWillExpire(const char* token) override;
        void onRequestToken() override;
        ////本地媒体事件
        void onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error) override;
        void onLocalVideoStateChanged(agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error) override;
        void onFirstLocalAudioFramePublished(int elapsed) override;
        void onFirstLocalVideoFramePublished(int elapsed) override;
        void onFirstLocalVideoFrame(int width, int height, int elapsed) override;
        void onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed) override;
        void onVideoPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed) override;
        ////远端媒体事件
        void onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed);
        void onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed);
        void onFirstRemoteVideoFrame(agora::rtc::uid_t uid, int width, int height, int elapsed);
        void onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed);
        void onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed);
        ////数据统计事件
        void onRtcStats(const agora::rtc::RtcStats& stats) override;
        void onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality) override;
        void onLocalAudioStats(const agora::rtc::LocalAudioStats& stats) override;
        void onLocalVideoStats(const agora::rtc::LocalVideoStats& stats) override;
        void onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats) override;
        void onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats) override;
        ////音乐文件播放及管理
        void onAudioMixingStateChanged(agora::rtc::AUDIO_MIXING_STATE_TYPE state, agora::rtc::AUDIO_MIXING_ERROR_TYPE error) override;
        void onRemoteAudioMixingBegin() override;
        void onRemoteAudioMixingEnd() override;
        ////音效文件播放及管理
        void onAudioEffectFinished(int soundId) override;
        //CDN推流
        void onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR error) override;
        void onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT code) override;
        void onTranscodingUpdated() override;
        //跨频道媒体流转发
        void onChannelMediaRelayStateChanged(agora::rtc::CHANNEL_MEDIA_RELAY_STATE state, agora::rtc::CHANNEL_MEDIA_RELAY_ERROR error) override;
        void onChannelMediaRelayEvent(agora::rtc::CHANNEL_MEDIA_RELAY_EVENT code) override;
        //音量提示
        void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;
        void onActiveSpeaker(agora::rtc::uid_t uid) override;
        ////视频流回退
        void onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) override;
        void onRemoteSubscribeFallbackToAudioOnly(agora::rtc::uid_t uid, bool isFallbackOrRecover) override;
        //通话前网络测试
        void onLastmileQuality(int quality) override;
        void onLastmileProbeResult(const agora::rtc::LastmileProbeResult& result) override;
        //直播输入在线媒体流
        void onStreamInjectedStatus(const char* url, agora::rtc::uid_t uid, int status) override;
        ////流消息
        void onStreamMessage(agora::rtc::uid_t uid, int streamId, const char* data, size_t length) override;
        void onStreamMessageError(agora::rtc::uid_t uid, int streamId, int code, int missed, int cached) override;
        ////其他事件
        void onWarning(int warn, const char* msg) override;
        void onError(int err, const char* msg) override;
        void onApiCallExecuted(int err, const char* api, const char* result) override;
        //设备管理
        void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;
        void onAudioDeviceVolumeChanged(agora::rtc::MEDIA_DEVICE_TYPE type, int volume, bool muted) override;
    private:
        //IMetadataObserver实现部分
        int getMaxMetadataSize() override;
        bool onReadyToSendMetadata(agora::rtc::IMetadataObserver::Metadata& metadata) override;
        void onMetadataReceived(const agora::rtc::IMetadataObserver::Metadata& metadata) override;
        //IPacketObserver实现部分
        bool onSendAudioPacket(Packet& packet) override;
        bool onSendVideoPacket(Packet& packet) override;
        bool onReceiveAudioPacket(Packet& packet) override;
        bool onReceiveVideoPacket(Packet& packet) override;

    };
}
namespace winrt::AgoraWinRT::factory_implementation
{
    struct AgoraRtc : AgoraRtcT<AgoraRtc, implementation::AgoraRtc>
    {
    };
}
