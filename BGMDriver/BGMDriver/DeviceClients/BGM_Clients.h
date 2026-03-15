// This file is part of Background Music.
//
// Background Music is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 2 of the
// License, or (at your option) any later version.
//
// Background Music is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Background Music. If not, see <http://www.gnu.org/licenses/>.

//
//  BGM_Clients.h
//  BGMDriver
//
//  Copyright © 2016, 2026 Kyle Neideck
//

#ifndef __BGMDriver__BGM_Clients__
#define __BGMDriver__BGM_Clients__

// Local Includes
#include "BGM_Client.h"
#include "BGM_ClientMap.h"

// PublicUtility Includes
#include "CAVolumeCurve.h"
#include "CAMutex.h"
#include "CACFArray.h"

// System Includes
#include <atomic>
#include <CoreAudio/AudioServerPlugIn.h>


// Forward Declarations
class BGM_ClientTasks;


#pragma clang assume_nonnull begin

//==================================================================================================
//	BGM_Clients
//
//  Holds information about the clients (of the host) of the BGMDevice, i.e. the apps registered
//  with the HAL, generally so they can do IO at some point. BGMApp and the music player are special
//  case clients.
//
//  Methods whose names end with "RT" should only be called from real-time threads.
//==================================================================================================

class BGM_Clients
{
    
    friend class BGM_ClientTasks;
    
public:
                                        BGM_Clients(AudioObjectID inOwnerDeviceID, BGM_TaskQueue* inTaskQueue);
                                        ~BGM_Clients() = default;
    // Disallow copying. (It could make sense to implement these in future, but we don't need them currently.)
                                        BGM_Clients(const BGM_Clients&) = delete;
                                        BGM_Clients& operator=(const BGM_Clients&) = delete;
    
    void                                AddClient(BGM_Client inClient);
    void                                RemoveClient(const UInt32 inClientID);

    bool                                IsBGMApp(const UInt32 inClientID) const noexcept { return static_cast<SInt64>(inClientID) == mBGMAppClientID.load(std::memory_order_relaxed); }
    bool                                BGMAppHasClientRegistered() const noexcept { return mBGMAppClientID.load(std::memory_order_relaxed) != -1; }

    // Returns true if a client other than BGMApp has done IO in the last 2 seconds (and the device
    // is running - see StopIO).
    bool                                ClientsOtherThanBGMAppRunningIO() const noexcept;
    // If inClientID isn't BGMApp, records that a non-BGMApp client is doing IO.
    //
    // We only update a timestamp here rather than sending property change notifications so this
    // function can be real-time safe. The notifications are handled separately by
    // SendIORunningPropertyNotification and StopIO.
    //
    // Real-time safe.
    void                                RecordNonBGMAppIO(UInt32 inClientID) noexcept;
    // Sends a notification for kAudioDeviceCustomPropertyDeviceIsRunningSomewhereOtherThanBGMApp if
    // its value has changed since the last time we sent a notification for it. Assumes that value
    // comes from ClientsOtherThanBGMAppRunningIO.
    //
    // Not real-time safe.
    void                                SendIORunningPropertyNotification();
    // Immediately marks non-BGMApp clients as not doing IO and sends a notification for the
    // kAudioDeviceCustomPropertyDeviceIsRunningSomewhereOtherThanBGMApp if that changed its value.
    // Assumes that value comes from ClientsOtherThanBGMAppRunningIO.
    //
    // Call this when the device stops IO.
    //
    // Not real-time safe.
    void                                StopIO();
    
    inline pid_t                        GetMusicPlayerProcessIDProperty() const { return mMusicPlayerProcessIDProperty; }
    inline CFStringRef                  CopyMusicPlayerBundleIDProperty() const { return mMusicPlayerBundleIDProperty.CopyCFString(); }
    
    // Returns true if the PID was changed
    bool                                SetMusicPlayer(const pid_t inPID);
    // Returns true if the bundle ID was changed
    bool                                SetMusicPlayer(const CACFString inBundleID);
    
    bool                                IsMusicPlayerRT(const UInt32 inClientID) const;
    
    Float32                             GetClientRelativeVolumeRT(UInt32 inClientID) const;
    SInt32                              GetClientPanPositionRT(UInt32 inClientID) const;
    
    // Copies the current and past clients into an array in the format expected for
    // kAudioDeviceCustomPropertyAppVolumes. (Except that CACFArray and CACFDictionary are used instead
    // of unwrapped CFArray and CFDictionary refs.)
    CACFArray                           CopyClientRelativeVolumesAsAppVolumes() const { return mClientMap.CopyClientRelativeVolumesAsAppVolumes(mRelativeVolumeCurve); };
    
    // inAppVolumes is an array of dicts with the keys kBGMAppVolumesKey_ProcessID,
    // kBGMAppVolumesKey_BundleID and optionally kBGMAppVolumesKey_RelativeVolume and
    // kBGMAppVolumesKey_PanPosition. This method finds the client for
    // each app by PID or bundle ID, sets the volume and applies mRelativeVolumeCurve to it.
    //
    // Returns true if any clients' relative volumes were changed.
    bool                                SetClientsRelativeVolumes(const CACFArray inAppVolumes);
    
private:
    const AudioObjectID                 mOwnerDeviceID;
    BGM_ClientMap                       mClientMap;

    CAMutex                             mMutex { "Clients" };

    // todo either move mStartCount and mInactivityTimer here from BGM_Device, or delete this comment
    // Counter for the number of clients that are doing IO.
    //
    // We need to reference count this rather than just using a bool because the HAL might (but usually
    // doesn't) call our StartIO/StopIO functions for clients other than the first to start and last to
    // stop.
    // UInt64                              mStartCount GUARDED_BY(mMutex) = 0;

    // Atomic so they can be accessed on both real-time and non-RT threads.

    // BGMApp's client ID, or -1 if BGMApp doesn't have a client registered
    std::atomic<SInt64>                 mBGMAppClientID { -1 };
    // Host timestamp at the most-recent time a client other than BGMApp did IO.
    std::atomic<uint64_t>               mLastNonBGMAppIOTime { 0 };
    // The value kAudioDeviceCustomPropertyDeviceIsRunningSomewhereOtherThanBGMApp had when we last
    // sent a property change notification for it.
    std::atomic<bool>                   mLastNotifiedIsRunning { false };
    
    // The value of the kAudioDeviceCustomPropertyMusicPlayerProcessID property, or 0 if it's unset/null.
    // We store this separately because the music player might not always be a client, but could be added
    // as one at a later time.
    pid_t                               mMusicPlayerProcessIDProperty = 0;
    
    // The value of the kAudioDeviceCustomPropertyMusicPlayerBundleID property, or the empty string if it's
    // unset/null. UTF8 encoding.
    //
    // As with mMusicPlayerProcessID, we keep a copy of the bundle ID the user sets for the music player
    // because there might be no client with that bundle ID. In that case we need to be able to give the
    // property's value if the HAL asks for it, and to recognise the music player if it's added a client.
    CACFString                          mMusicPlayerBundleIDProperty { "" };
    
    // The volume curve we apply to raw client volumes before they're used
    CAVolumeCurve                       mRelativeVolumeCurve;
    
};

#pragma clang assume_nonnull end

#endif /* __BGMDriver__BGM_Clients__ */

