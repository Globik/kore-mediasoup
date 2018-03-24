{
  'target_defaults': {
    'type': 'executable',
    'dependencies':
    [
      'deps/jsoncpp/jsoncpp.gyp:jsoncpp',
      'deps/netstring/netstring.gyp:netstring',
      'deps/libuv/uv.gyp:libuv',
      'deps/openssl/openssl.gyp:openssl',
      'deps/libsrtp/libsrtp.gyp:libsrtp'
    ],
    'sources':
    [
      # C++ source files
      'src/DepLibSRTP.cpp',
      'src/DepLibUV.cpp',
      'src/DepOpenSSL.cpp',
      'src/Logger.cpp',
      'src/Loop.cpp',
      'src/Settings.cpp',
      'src/Channel/Notifier.cpp',
      'src/Channel/Request.cpp',
      'src/Channel/UnixStreamSocket.cpp',
      'src/RTC/DtlsTransport.cpp',
      'src/RTC/IceCandidate.cpp',
      'src/RTC/IceServer.cpp',
      'src/RTC/NackGenerator.cpp',
      'src/RTC/Peer.cpp',
      'src/RTC/Room.cpp',
      'src/RTC/RtpListener.cpp',
      'src/RTC/RtpPacket.cpp',
      'src/RTC/RtpReceiver.cpp',
      'src/RTC/RtpSender.cpp',
      'src/RTC/RtpStream.cpp',
      'src/RTC/RtpStreamRecv.cpp',
      'src/RTC/RtpStreamSend.cpp',
      'src/RTC/RtpDataCounter.cpp',
      'src/RTC/SrtpSession.cpp',
      'src/RTC/StunMessage.cpp',
      'src/RTC/TcpConnection.cpp',
      'src/RTC/TcpServer.cpp',
      'src/RTC/Transport.cpp',
      'src/RTC/TransportTuple.cpp',
      'src/RTC/UdpSocket.cpp',
      'src/RTC/RtpDictionaries/Media.cpp',
      'src/RTC/RtpDictionaries/Parameters.cpp',
      'src/RTC/RtpDictionaries/RtcpFeedback.cpp',
      'src/RTC/RtpDictionaries/RtcpParameters.cpp',
      'src/RTC/RtpDictionaries/RtpCapabilities.cpp',
      'src/RTC/RtpDictionaries/RtpCodecMime.cpp',
      'src/RTC/RtpDictionaries/RtpCodecParameters.cpp',
      'src/RTC/RtpDictionaries/RtpEncodingParameters.cpp',
      'src/RTC/RtpDictionaries/RtpFecParameters.cpp',
      'src/RTC/RtpDictionaries/RtpHeaderExtension.cpp',
      'src/RTC/RtpDictionaries/RtpHeaderExtensionParameters.cpp',
      'src/RTC/RtpDictionaries/RtpHeaderExtensionUri.cpp',
      'src/RTC/RtpDictionaries/RtpParameters.cpp',
      'src/RTC/RtpDictionaries/RtpRtxParameters.cpp',
      'src/RTC/RTCP/Packet.cpp',
      'src/RTC/RTCP/CompoundPacket.cpp',
      'src/RTC/RTCP/SenderReport.cpp',
      'src/RTC/RTCP/ReceiverReport.cpp',
      'src/RTC/RTCP/Sdes.cpp',
      'src/RTC/RTCP/Bye.cpp',
      'src/RTC/RTCP/Feedback.cpp',
      'src/RTC/RTCP/FeedbackPs.cpp',
      'src/RTC/RTCP/FeedbackRtp.cpp',
      'src/RTC/RTCP/FeedbackRtpNack.cpp',
      'src/RTC/RTCP/FeedbackRtpTmmb.cpp',
      'src/RTC/RTCP/FeedbackRtpSrReq.cpp',
      'src/RTC/RTCP/FeedbackRtpTllei.cpp',
      'src/RTC/RTCP/FeedbackRtpEcn.cpp',
      'src/RTC/RTCP/FeedbackPsPli.cpp',
      'src/RTC/RTCP/FeedbackPsSli.cpp',
      'src/RTC/RTCP/FeedbackPsRpsi.cpp',
      'src/RTC/RTCP/FeedbackPsFir.cpp',
      'src/RTC/RTCP/FeedbackPsTst.cpp',
      'src/RTC/RTCP/FeedbackPsVbcm.cpp',
      'src/RTC/RTCP/FeedbackPsLei.cpp',
      'src/RTC/RTCP/FeedbackPsAfb.cpp',
      'src/RTC/RTCP/FeedbackPsRemb.cpp',
      'src/RTC/RemoteBitrateEstimator/AimdRateControl.cpp',
      'src/RTC/RemoteBitrateEstimator/InterArrival.cpp',
      'src/RTC/RemoteBitrateEstimator/OveruseDetector.cpp',
      'src/RTC/RemoteBitrateEstimator/OveruseEstimator.cpp',
      'src/RTC/RemoteBitrateEstimator/RemoteBitrateEstimatorAbsSendTime.cpp',
      'src/RTC/RemoteBitrateEstimator/RemoteBitrateEstimatorSingleStream.cpp',
      'src/Utils/Crypto.cpp',
      'src/Utils/File.cpp',
      'src/Utils/IP.cpp',
      'src/handles/SignalsHandler.cpp',
      'src/handles/TcpConnection.cpp',
      'src/handles/TcpServer.cpp',
      'src/handles/Timer.cpp',
      'src/handles/UdpSocket.cpp',
      'src/handles/UnixStreamSocket.cpp',
      # C++ include files
      'include/DepLibSRTP.hpp',
      'include/DepLibUV.hpp',
      'include/DepOpenSSL.hpp',
      'include/LogLevel.hpp',
      'include/Logger.hpp',
      'include/Loop.hpp',
      'include/MediaSoupError.hpp',
      'include/Settings.hpp',
      'include/Utils.hpp',
      'include/common.hpp',
      'include/Channel/Notifier.hpp',
      'include/Channel/Request.hpp',
      'include/Channel/UnixStreamSocket.hpp',
      'include/RTC/DtlsTransport.hpp',
      'include/RTC/IceCandidate.hpp',
      'include/RTC/IceServer.hpp',
      'include/RTC/NackGenerator.hpp',
      'include/RTC/Parameters.hpp',
      'include/RTC/Peer.hpp',
      'include/RTC/Room.hpp',
      'include/RTC/RtpDictionaries.hpp',
      'include/RTC/RtpListener.hpp',
      'include/RTC/RtpPacket.hpp',
      'include/RTC/RtpReceiver.hpp',
      'include/RTC/RtpSender.hpp',
      'include/RTC/RtpStream.hpp',
      'include/RTC/RtpStreamRecv.hpp',
      'include/RTC/RtpStreamSend.hpp',
      'include/RTC/RtpDataCounter.hpp',
      'include/RTC/SrtpSession.hpp',
      'include/RTC/StunMessage.hpp',
      'include/RTC/TcpConnection.hpp',
      'include/RTC/TcpServer.hpp',
      'include/RTC/Transport.hpp',
      'include/RTC/TransportTuple.hpp',
      'include/RTC/UdpSocket.hpp',
      'include/RTC/RTCP/Packet.hpp',
      'include/RTC/RTCP/CompoundPacket.hpp',
      'include/RTC/RTCP/SenderReport.hpp',
      'include/RTC/RTCP/ReceiverReport.hpp',
      'include/RTC/RTCP/Sdes.hpp',
      'include/RTC/RTCP/Bye.hpp',
      'include/RTC/RTCP/Feedback.hpp',
      'include/RTC/RTCP/FeedbackItem.hpp',
      'include/RTC/RTCP/FeedbackPs.hpp',
      'include/RTC/RTCP/FeedbackRtp.hpp',
      'include/RTC/RTCP/FeedbackRtpNack.hpp',
      'include/RTC/RTCP/FeedbackRtpTmmb.hpp',
      'include/RTC/RTCP/FeedbackRtpSrReq.hpp',
      'include/RTC/RTCP/FeedbackRtpTllei.hpp',
      'include/RTC/RTCP/FeedbackRtpEcn.hpp',
      'include/RTC/RTCP/FeedbackPsPli.hpp',
      'include/RTC/RTCP/FeedbackPsSli.hpp',
      'include/RTC/RTCP/FeedbackPsRpsi.hpp',
      'include/RTC/RTCP/FeedbackPsFir.hpp',
      'include/RTC/RTCP/FeedbackPsTst.hpp',
      'include/RTC/RTCP/FeedbackPsVbcm.hpp',
      'include/RTC/RTCP/FeedbackPsLei.hpp',
      'include/RTC/RTCP/FeedbackPsAfb.hpp',
      'include/RTC/RTCP/FeedbackPsRemb.hpp',
      'include/RTC/RemoteBitrateEstimator/AimdRateControl.hpp',
      'include/RTC/RemoteBitrateEstimator/InterArrival.hpp',
      'include/RTC/RemoteBitrateEstimator/OveruseDetector.hpp',
      'include/RTC/RemoteBitrateEstimator/OveruseEstimator.hpp',
      'include/RTC/RemoteBitrateEstimator/RemoteBitrateEstimator.hpp',
      'include/RTC/RemoteBitrateEstimator/RemoteBitrateEstimatorAbsSendTime.hpp',
      'include/RTC/RemoteBitrateEstimator/RemoteBitrateEstimatorSingleStream.hpp',
      'include/handles/SignalsHandler.hpp',
      'include/handles/TcpConnection.hpp',
      'include/handles/TcpServer.hpp',
      'include/handles/Timer.hpp',
      'include/handles/UdpSocket.hpp',
      'include/handles/UnixStreamSocket.hpp'
    ],
    'include_dirs':
    [
      'include'
    ],
    'conditions':
    [
      # FIPS
      [ 'openssl_fips != ""', {
        'defines': [ 'BUD_FIPS_ENABLED=1' ]
      }],

      # Endianness
      [ 'node_byteorder=="big"', {
          # Define Big Endian
          'defines': [ 'MS_BIG_ENDIAN' ]
        }, {
          # Define Little Endian
          'defines': [ 'MS_LITTLE_ENDIAN' ]
      }],

      # Platform-specifics

      [ 'OS == "mac" and mediasoup_asan == "true"', {
        'xcode_settings':
        {
          'OTHER_CFLAGS': [ '-fsanitize=address' ],
          'OTHER_LDFLAGS': [ '-fsanitize=address' ]
        }
      }],

      [ 'OS == "linux"', {
        'defines':
        [
          '_POSIX_C_SOURCE=200112',
          '_GNU_SOURCE'
        ]
      }],

      [ 'OS == "linux" and mediasoup_asan == "true"', {
        'cflags': [ '-fsanitize=address' ],
        'ldflags': [ '-fsanitize=address' ]
      }],

      [ 'OS in "linux freebsd"', {
        'ldflags':
        [
          '-Wl,--whole-archive <(libopenssl) -Wl,--no-whole-archive'
        ]
      }],

      [ 'OS in "freebsd"', {
        'ldflags': [ '-Wl,--export-dynamic' ]
      }],

      [ 'OS != "win"', {
        'cflags': [ '-std=c++11', '-Wall', '-Wextra', '-Wno-unused-parameter' ]
      }],

      [ 'OS == "mac"', {
        'xcode_settings':
        {
          'WARNING_CFLAGS': [ '-Wall', '-Wextra', '-Wno-unused-parameter' ],
          'OTHER_CPLUSPLUSFLAGS' : [ '-std=c++11' ]
        }
      }]
    ]
	},
  'targets':
  [
    {
      'target_name': 'mediasoup-worker',
      'sources':
      [
        # C++ source files
        'src/main.cpp'
      ]
    },
    {
      'target_name': 'mediasoup-worker-test',
      'defines': [ 'MS_TEST', 'MS_LOG_STD' ],
      'sources':
      [
        # C++ source files
        'test/tests.cpp',
        'test/test-nack.cpp',
        'test/test-rtp.cpp',
        'test/test-rtcp.cpp',
        'test/test-bitrate.cpp',
        'test/test-rtpstreamrecv.cpp',
        # C++ include files
        'test/catch.hpp',
        'test/helpers.hpp'
      ]
    }
  ]
}
