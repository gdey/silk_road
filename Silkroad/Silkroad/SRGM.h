//
//  SRGM.h
//  Silkroad
//
//  Created by Jason Koo on 9/10/13.
//  Copyright (c) 2013 SilkRoad. All rights reserved.
//
//  BRIEF: This is the Game Master - overall game coordination class


#import <Foundation/Foundation.h>
#import "SRMapVC.h"
#import "SRPlayer.h"

enum SRGamePhase {
    SRGame_Setup,
    SRGame_Game,
    SRGame_End
    };

enum SRPlayerPhase {
    SRPlayer_Placement,
    SRPlayer_Movement,
    SRPlayer_Replenish
    };

@interface SRGM : NSObject

@property (nonatomic)           enum SRGamePhase    currentGamePhase;
@property (nonatomic)           enum SRPlayerPhase  currentPlayerPhase;
@property (nonatomic)           int                 *currentPlayerIndex;
@property (nonatomic, strong)   NSArray             *players; // Array of playerIds, in order of play
@property (nonatomic, strong)   NSDate              *lastResponseCurrentPlayer;

@end
