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
//  Mock_CAHALAudioDevice.cpp
//  BGMAppUnitTests
//
//  Copyright © 2020, 2026 Kyle Neideck
//

// Self Include
#include "CAHALAudioDevice.h"

// Local Includes
#include "MockAudioDevice.h"
#include "MockAudioObjects.h"

// BGM Includes
#include "BGM_Types.h"

// PublicUtility Includes
#include "CACFString.h"
#include "CAHALAudioSystemObject.h"
#include "CAPropertyAddress.h"


#pragma clang diagnostic ignored "-Wunused-parameter"

CAHALAudioDevice::CAHALAudioDevice(AudioObjectID inObjectID)
:
    CAHALAudioObject(inObjectID)
{
}

CAHALAudioDevice::CAHALAudioDevice(CFStringRef inUID)
:
        CAHALAudioObject(CAHALAudioSystemObject().GetAudioDeviceForUID(inUID))
{
}

CAHALAudioDevice::~CAHALAudioDevice()
{
}

void	CAHALAudioDevice::GetCurrentVirtualFormats(bool inIsInput, UInt32& ioNumberStreams, AudioStreamBasicDescription* outFormats) const
{
    ioNumberStreams = 1;
    CAPropertyAddress theAddress(kAudioStreamPropertyVirtualFormat);
    UInt32 theSize = sizeof(AudioStreamBasicDescription);
    GetPropertyData(theAddress, 0, NULL, theSize, outFormats);
}

UInt32	CAHALAudioDevice::GetIOBufferSize() const
{
    return MockAudioObjects::GetAudioDevice(GetObjectID())->mIOBufferSize;
}

void	CAHALAudioDevice::SetIOBufferSize(UInt32 inBufferSize)
{
    MockAudioObjects::GetAudioDevice(GetObjectID())->mIOBufferSize = inBufferSize;
}

bool	CAHALAudioDevice::IsAlive() const
{
    return true;
}

AudioDeviceIOProcID	CAHALAudioDevice::CreateIOProcID(AudioDeviceIOProc inIOProc, void* inClientData)
{
    return reinterpret_cast<AudioDeviceIOProcID>(0x99990000);
}

void	CAHALAudioDevice::DestroyIOProcID(AudioDeviceIOProcID inIOProcID)
{
}

Float64	CAHALAudioDevice::GetNominalSampleRate() const
{
    return MockAudioObjects::GetAudioDevice(GetObjectID())->mNominalSampleRate;
}

void	CAHALAudioDevice::SetNominalSampleRate(Float64 inSampleRate)
{
    MockAudioObjects::GetAudioDevice(GetObjectID())->mNominalSampleRate = inSampleRate;
}

CFStringRef    CAHALAudioDevice::CopyDeviceUID() const
{
    std::string uid = MockAudioObjects::GetAudioDevice(GetObjectID())->mUID;
    return CACFString(uid.c_str()).CopyCFString();
}

#pragma mark Unimplemented Methods

bool	CAHALAudioDevice::HasModelUID() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

CFStringRef	CAHALAudioDevice::CopyModelUID() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

CFStringRef	CAHALAudioDevice::CopyConfigurationApplicationBundleID() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

CFURLRef	CAHALAudioDevice::CopyIconLocation() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetTransportType() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::CanBeDefaultDevice(bool inIsInput, bool inIsSystem) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasDevicePlugInStatus() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

OSStatus	CAHALAudioDevice::GetDevicePlugInStatus() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::IsHidden() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

pid_t	CAHALAudioDevice::GetHogModeOwner() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::IsHogModeSettable() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::TakeHogMode()
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::ReleaseHogMode()
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasPreferredStereoChannels(bool inIsInput) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetPreferredStereoChannels(bool inIsInput, UInt32& outLeft, UInt32& outRight) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetPreferredStereoChannels(bool inIsInput, UInt32 inLeft, UInt32 inRight)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasPreferredChannelLayout(bool inIsInput) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetPreferredChannelLayout(bool inIsInput, AudioChannelLayout& outChannelLayout) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetPreferredStereoChannels(bool inIsInput, AudioChannelLayout& inChannelLayout)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetNumberRelatedAudioDevices() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetRelatedAudioDevices(UInt32& ioNumberRelatedDevices, AudioObjectID* outRelatedDevices) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

AudioObjectID	CAHALAudioDevice::GetRelatedAudioDeviceByIndex(UInt32 inIndex) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetNumberStreams(bool inIsInput) const
{
    // The mock devices don't need to model streams yet, but throwing here would make some tests
    // fail. Apologies if this ends up tripping anyone up.
    return 0;
}

void	CAHALAudioDevice::GetStreams(bool inIsInput, UInt32& ioNumberStreams, AudioObjectID* outStreamList) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

AudioObjectID	CAHALAudioDevice::GetStreamByIndex(bool inIsInput, UInt32 inIndex) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetTotalNumberChannels(bool inIsInput) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetCurrentPhysicalFormats(bool inIsInput, UInt32& ioNumberStreams, AudioStreamBasicDescription* outFormats) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::IsRunning() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::IsRunningSomewhere() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetLatency(bool inIsInput) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetSafetyOffset(bool inIsInput) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasClockDomain() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetClockDomain() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float64	CAHALAudioDevice::GetActualSampleRate() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetNumberAvailableNominalSampleRateRanges() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetAvailableNominalSampleRateRanges(UInt32& ioNumberRanges, AudioValueRange* outRanges) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetAvailableNominalSampleRateRangeByIndex(UInt32 inIndex, Float64& outMinimum, Float64& outMaximum) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::IsValidNominalSampleRate(Float64 inSampleRate) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::IsIOBufferSizeSettable() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::UsesVariableIOBufferSizes() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetMaximumVariableIOBufferSize() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasIOBufferSizeRange() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetIOBufferSizeRange(UInt32& outMinimum, UInt32& outMaximum) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::StartIOProc(AudioDeviceIOProcID inIOProcID)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::StartIOProcAtTime(AudioDeviceIOProcID inIOProcID, AudioTimeStamp& ioStartTime, bool inIsInput, bool inIgnoreHardware)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::StopIOProc(AudioDeviceIOProcID inIOProcID)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetIOProcStreamUsage(AudioDeviceIOProcID inIOProcID, bool inIsInput, bool* outStreamUsage) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetIOProcStreamUsage(AudioDeviceIOProcID inIOProcID, bool inIsInput, const bool* inStreamUsage)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetIOCycleUsage() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetIOCycleUsage(Float32 inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetCurrentTime(AudioTimeStamp& outTime)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::TranslateTime(const AudioTimeStamp& inTime, AudioTimeStamp& outTime)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetNearestStartTime(AudioTimeStamp& ioTime, bool inIsInput, bool inIgnoreHardware)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasVolumeControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::VolumeControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetVolumeControlScalarValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetVolumeControlDecibelValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetVolumeControlScalarValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetVolumeControlDecibelValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetVolumeControlScalarForDecibelValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetVolumeControlDecibelForScalarValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasSubVolumeControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::SubVolumeControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetSubVolumeControlScalarValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetSubVolumeControlDecibelValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetSubVolumeControlScalarValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetSubVolumeControlDecibelValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetSubVolumeControlScalarForDecibelValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetSubVolumeControlDecibelForScalarValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasMuteControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::MuteControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::GetMuteControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetMuteControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel, bool inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasSoloControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::SoloControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::GetSoloControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetSoloControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel, bool inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasStereoPanControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::StereoPanControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

Float32	CAHALAudioDevice::GetStereoPanControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetStereoPanControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel, Float32 inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetStereoPanControlChannels(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32& outLeftChannel, UInt32& outRightChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasJackControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::GetJackControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasSubMuteControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::SubMuteControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::GetSubMuteControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetSubMuteControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel, bool inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasiSubOwnerControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::iSubOwnerControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::GetiSubOwnerControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetiSubOwnerControlValue(AudioObjectPropertyScope inScope, UInt32 inChannel, bool inValue)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasDataSourceControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::DataSourceControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetCurrentDataSourceID(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetCurrentDataSourceByID(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32 inID)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetNumberAvailableDataSources(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetAvailableDataSources(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32& ioNumberSources, UInt32* outSources) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetAvailableDataSourceByIndex(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32 inIndex) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

CFStringRef	CAHALAudioDevice::CopyDataSourceNameForID(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32 inID) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasDataDestinationControl(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::DataDestinationControlIsSettable(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetCurrentDataDestinationID(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetCurrentDataDestinationByID(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32 inID)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetNumberAvailableDataDestinations(AudioObjectPropertyScope inScope, UInt32 inChannel) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetAvailableDataDestinations(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32& ioNumberDestinations, UInt32* outDestinations) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetAvailableDataDestinationByIndex(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32 inIndex) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

CFStringRef	CAHALAudioDevice::CopyDataDestinationNameForID(AudioObjectPropertyScope inScope, UInt32 inChannel, UInt32 inID) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::HasClockSourceControl() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

bool	CAHALAudioDevice::ClockSourceControlIsSettable() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetCurrentClockSourceID() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::SetCurrentClockSourceByID(UInt32 inID)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetNumberAvailableClockSources() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioDevice::GetAvailableClockSources(UInt32& ioNumberSources, UInt32* outSources) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetAvailableClockSourceByIndex(UInt32 inIndex) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

CFStringRef	CAHALAudioDevice::CopyClockSourceNameForID(UInt32 inID) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

UInt32	CAHALAudioDevice::GetClockSourceKindForID(UInt32 inID) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

