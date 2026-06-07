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
//  BGMDebugLoggingMenuItem.m
//  BGMApp
//
//  Copyright © 2020, 2026 Kyle Neideck
//

// Self Include
#import "BGMDebugLoggingMenuItem.h"

// Local Includes
#import "BGM_Utils.h"
#import "BGMAudioDeviceManager.h"
#import "BGMBackgroundMusicDevice.h"

// PublicUtility Includes
#import "BGMDebugLogging.h"
#import "CADebugMacros.h"


#pragma clang assume_nonnull begin

@implementation BGMDebugLoggingMenuItem {
    NSMenuItem* _menuItem;
    BOOL _menuShowingExtraOptions;
    BGMAudioDeviceManager* _audioDevices;
}

- (instancetype) initWithMenuItem:(NSMenuItem*)menuItem
                     audioDevices:(BGMAudioDeviceManager*)audioDevices {
    if ((self = [super init])) {
        _menuItem = menuItem;
        _audioDevices = audioDevices;
        _menuItem.state =
                BGMDebugLoggingIsEnabled() ? NSControlStateValueOn : NSControlStateValueOff;

        [self setMenuShowingExtraOptions:NO];

        // Enable/disable debug logging when the menu item is clicked.
        menuItem.target = self;
        menuItem.action = @selector(toggleDebugLogging);
    }

    return self;
}

- (void) setMenuShowingExtraOptions:(BOOL)showingExtra {
    _menuShowingExtraOptions = showingExtra;
    _menuItem.hidden = !BGMDebugLoggingIsEnabled() && !showingExtra;

    DebugMsg("BGMDebugLoggingMenuItem::menuShowingExtraOptions: %s the menu item",
             _menuItem.hidden ? "Hiding" : "Showing");
}

- (void) toggleDebugLogging {
    BGMSetDebugLoggingEnabled(!BGMDebugLoggingIsEnabled());
    _menuItem.state = BGMDebugLoggingIsEnabled() ? NSControlStateValueOn : NSControlStateValueOff;

    // Keep BGMDriver's debug logging in sync with ours.
    BGMLogAndSwallowExceptions("BGMDebugLoggingMenuItem::toggleDebugLogging", [&] {
        [_audioDevices bgmDevice].SetDebugLoggingEnabled(BGMDebugLoggingIsEnabled());
    });

    DebugMsg("BGMDebugLoggingMenuItem::toggleDebugLogging: Debug logging %s",
             BGMDebugLoggingIsEnabled() ? "enabled" : "disabled");
}

@end

#pragma clang assume_nonnull end

