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
//  Mock_CAHALAudioSystemObject.cpp
//  BGMAppUnitTests
//
//  Copyright © 2017, 2020, 2026 Kyle Neideck
//

// Self include
#include "CAHALAudioSystemObject.h"

// BGM Includes
#include "BGM_Types.h"

// Local Includes
#include "MockAudioObjects.h"


CAHALAudioSystemObject::CAHALAudioSystemObject()
:
    CAHALAudioObject(kAudioObjectSystemObject)
{
}

CAHALAudioSystemObject::~CAHALAudioSystemObject()
{
}

AudioObjectID	CAHALAudioSystemObject::GetAudioDeviceForUID(CFStringRef inUID) const
{
    auto device = MockAudioObjects::GetAudioDevice(inUID);

    if(device)
    {
        return device->GetObjectID();
    }

    return kAudioObjectUnknown;
}

#pragma mark Unimplemented Methods

#pragma clang diagnostic ignored "-Wunused-parameter"

UInt32	CAHALAudioSystemObject::GetNumberAudioDevices() const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioSystemObject::GetAudioDevices(UInt32& ioNumberAudioDevices, AudioObjectID* outAudioDevices) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

AudioObjectID	CAHALAudioSystemObject::GetAudioDeviceAtIndex(UInt32 inIndex) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioSystemObject::LogBasicDeviceInfo()
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

AudioObjectID	CAHALAudioSystemObject::GetDefaultAudioDevice(bool inIsInput, bool inIsSystem) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

void	CAHALAudioSystemObject::SetDefaultAudioDevice(bool inIsInput, bool inIsSystem, AudioObjectID inNewDefaultDevice)
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

AudioObjectID	CAHALAudioSystemObject::GetAudioPlugInForBundleID(CFStringRef inUID) const
{
    Mock_Unimplemented(__PRETTY_FUNCTION__);
}

